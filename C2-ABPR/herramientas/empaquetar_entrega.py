"""Empaqueta fuentes y material de exposición, sin credenciales ni datos de ejecución."""
from pathlib import Path
import hashlib,json,zipfile
ROOT=Path(__file__).resolve().parents[1]
EXCLUDED_DIRS={'.git','.pio','.venv','node_modules','.output','.tanstack','.nitro','datos','__pycache__','frames','meshes'}
EXCLUDED_NAMES={'secretos.h','.env','.env.local','entrega-c2.zip','manifest-entrega.json','prueba','trama'}
EXCLUDED_SUFFIXES={'.pyc','.blend1','.kicad_prl','.bak','.dat','.db','.sqlite','.sqlite3'}
files=[ROOT/'README.md',ROOT/'.gitignore']
for folder in ['docs','img','hardware','freecad','firmware','plataforma','pronostico','herramientas','interfaz','simulacion']:
 for p in (ROOT/folder).rglob('*'):
  if not p.is_file() or set(p.relative_to(ROOT).parts)&EXCLUDED_DIRS:continue
  if p.name in EXCLUDED_NAMES or p.name.startswith('.env') or p.suffix in EXCLUDED_SUFFIXES:continue
  # Xyce waveforms are reproducible; summaries, decks and logs suffice for delivery.
  if p.name.endswith('.xy.csv'):continue
  files.append(p)
manifest=[]
for p in sorted(files):
 manifest.append({'path':str(p.relative_to(ROOT)),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
m=ROOT/'docs/manifest-entrega.json';m.write_text(json.dumps(manifest,indent=2)+'\n');files.append(m)
zip_path=ROOT/'docs/entrega-c2.zip'
with zipfile.ZipFile(zip_path,'w',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
 for p in sorted(files):z.write(p,'C2-ABPR/'+str(p.relative_to(ROOT)))
with zipfile.ZipFile(zip_path) as z:
 assert z.testzip() is None
 assert not any(n.endswith('/secretos.h') or '/node_modules/' in n or '/datos/' in n for n in z.namelist())
print(f'{zip_path}: {len(files)} archivos; {zip_path.stat().st_size/1e6:.1f} MB')
