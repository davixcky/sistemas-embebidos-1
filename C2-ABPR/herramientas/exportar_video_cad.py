"""Exporta las piezas del CAD existente, sin modificarlo. Ejecutar con freecadcmd."""
import json
from pathlib import Path
import FreeCAD as App
import MeshPart
ROOT=Path(__file__).resolve().parents[1]
out=ROOT/'docs/video/meshes';out.mkdir(parents=True,exist_ok=True)
doc=App.openDocument(str(ROOT/'freecad/medidor.FCStd'))
rows=[]
for o in doc.Objects:
    if not hasattr(o,'ColorRGB') or o.Name=='Placa_KiCad':continue
    mesh=MeshPart.meshFromShape(Shape=o.Shape,LinearDeflection=0.12,AngularDeflection=0.3)
    mesh.write(str(out/f'{o.Name}.stl'))
    rows.append(dict(name=o.Name,file=f'{o.Name}.stl',color=[float(x) for x in o.ColorRGB.split(',')],group=o.Grupo))
(out/'piezas.json').write_text(json.dumps(rows,indent=2))
print('Exportadas',len(rows),'piezas del medidor')
