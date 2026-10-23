#!/usr/bin/env python3
"""Compare existing analog models in ngspice and Xyce (Docker image c2-abpr-xyce:7.10).

Run: python3 herramientas/comparar_simuladores.py
Requires numpy, ngspice and Docker. Writes isolated decks, logs, CSV and a text report
under simulacion/xyce. Does not modify the original models or schematic.
"""
import csv
import json
import os
from pathlib import Path
import re
import subprocess

import numpy as np

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'simulacion' / 'xyce'
IMAGE = 'c2-abpr-xyce:7.10'


def run(cmd, log):
    result = subprocess.run(cmd, cwd=OUT, capture_output=True, text=True, timeout=120)
    log.write_text(result.stdout + result.stderr)
    if result.returncode:
        raise RuntimeError(f'Failed: {cmd}; see {log}')


def main():
    OUT.mkdir(exist_ok=True)
    cases = [(p.stem, p, 27) for p in sorted((ROOT / 'simulacion').glob('*.cir'))]
    for name in ('ch1_sobre_200A', 'ch2_sobre_100A'):
        for temp in (0, 15, 50):
            cases.append((f'{name}_temp{temp}', ROOT / 'simulacion' / f'{name}.cir', temp))
    results = []
    for name, source, temp in cases:
        raw = source.read_text()
        body = raw.split('.control')[0]
        columns = re.search(r'^wrdata\s+\S+\s+(.+)$', raw, re.M).group(1)
        kind = 'AC' if '.ac ' in body else 'DC' if '.dc ' in body else 'TRAN'
        # Explicit max step and tighter tolerances for comparable extrema.
        if kind == 'TRAN':
            body = re.sub(r'(?im)^(\.tran\s+\S+\s+\S+\s+\S+)(\s+uic)?$',
                          lambda m: m[1] + ' 5u' + (m[2] or ''), body)
        ng = OUT / f'{name}.ng.cir'
        ng.write_text(body + f'\n.temp {temp}\n.options reltol=1e-6 abstol=1e-12\n'
                      '.control\nset wr_singlescale\nset wr_vecnames\nset numdgt=12\nrun\n'
                      f'wrdata {name}.ng.dat {columns}\n.endc\n.end\n')
        xy = OUT / f'{name}.xy.cir'
        xycolumns = ('I(Iload) ' if kind == 'DC' else '') + columns
        xy.write_text(body + f'\n.options device temp={temp} tnom=27\n'
                      '.options timeint reltol=1e-6 abstol=1e-12\n'
                      f'.print {kind} format=csv precision=12 file={name}.xy.csv {xycolumns}\n.end\n')
        run(['ngspice', '-b', ng.name], OUT / f'{name}.ng.log')
        run(['docker', 'run', '--rm', '--network', 'none', '--user', f'{os.getuid()}:{os.getgid()}',
             '-v', f'{OUT}:/work', '-w', '/work', IMAGE, xy.name], OUT / f'{name}.xy.log')
        a = np.loadtxt(OUT / f'{name}.ng.dat', skiprows=1)
        with (OUT / f'{name}.xy.csv').open() as f:
            rows = list(csv.reader(f))
        b = np.array([[float(v) for v in row] for row in rows[1:] if row and not row[0].startswith('End')])
        # Xyce CSV begins with TIME, FREQ or swept variable (no index).
        if kind == 'TRAN':
            start = float(re.search(r'(?im)^\.tran\s+\S+\s+\S+\s+(\S+)', body)[1].replace('m', 'e-3'))
            a, b = a[a[:, 0] >= start], b[b[:, 0] >= start]
            ngvalues, xyvalues = [a[:, 1].min(), a[:, 1].max()], [b[:, 1].min(), b[:, 1].max()]
            limits = [-0.3, 3.6] if 'sobre' in name else [0.15, 2.45]
            passed = xyvalues[0] >= limits[0] and xyvalues[1] <= limits[1]
            metric = 'min/max V'
        elif kind == 'DC':
            ngvalues, xyvalues = [np.interp(0.5, a[:, 0], a[:, 1])], [np.interp(0.5, b[:, 0], b[:, 1])]
            passed, metric = xyvalues[0] >= 4.4, 'V at 0.5 A'
            limits = [4.4, None]
        else:
            ngvalues = [np.interp(f, a[:, 0], a[:, 1]) for f in (60, 3000, 4000)]
            xyvalues = [np.interp(f, b[:, 0], b[:, 1]) for f in (60, 3000, 4000)]
            passed, metric, limits = None, 'gain at 60/3000/4000 Hz', None
        error = max(abs(x - y) for x, y in zip(ngvalues, xyvalues))
        results.append(dict(case=name, temperature_C=temp, analysis=kind, metric=metric,
                            ngspice=[float(x) for x in ngvalues], xyce=[float(x) for x in xyvalues],
                            max_metric_difference=float(error), limits=limits, xyce_pass=bool(passed) if passed is not None else None))
        print(f'{name}: Xyce {xyvalues}, difference {error:.6g}', flush=True)
    (OUT / 'resultados.json').write_text(json.dumps(results, indent=2) + '\n')
    lines = ['Independent solver comparison: Xyce 7.10 vs ngspice',
             'Same existing fitted diode/ideal CT models; model agreement is not hardware validation.',
             'Nominal temperature explicitly 27 C. Additional temperatures are sensitivity cases, not qualified component corners.',
             'Criteria reproduce project assumptions: nominal ADC 0.15..2.45 V; overload -0.3..3.6 V; regulator input >=4.4 V.',
             'PTC is a fixed 0.15-ohm resistor: this does NOT simulate its trip behavior.',
             'Ideal 3.3-V source can absorb clamp current: rail rise and power-off behavior are NOT validated.',
             'No CT saturation, ADC sampling/nonlinearity, real ZMPT amplifier, USB path, mains insulation or firmware modeled.',
             '', 'case | Xyce values | ngspice values | maximum difference | criterion']
    for r in results:
        fmt = lambda vs: ', '.join(f'{v:.6f}' for v in vs)
        status = 'informational' if r['xyce_pass'] is None else 'PASS' if r['xyce_pass'] else 'FAIL'
        lines.append(f"{r['case']} | {fmt(r['xyce'])} | {fmt(r['ngspice'])} | {r['max_metric_difference']:.6g} | {status}")
    (OUT / 'resultados.txt').write_text('\n'.join(lines) + '\n')


if __name__ == '__main__':
    main()
