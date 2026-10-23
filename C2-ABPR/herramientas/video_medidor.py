"""Animación del CAD real, inspirada en el video de ecualizador-esp32.
BUILD_ONLY=1 blender -b -P herramientas/video_medidor.py
PREVIEW=1 blender -b -P herramientas/video_medidor.py
"""
import bpy, os, json, math
from pathlib import Path
from mathutils import Vector
ROOT=Path(__file__).resolve().parents[1];OUT=ROOT/'docs/video';MESH=OUT/'meshes'
bpy.ops.wm.read_factory_settings(use_empty=True)
s=bpy.context.scene;s.unit_settings.scale_length=.001
s.render.engine='CYCLES';s.cycles.samples=12
prefs=bpy.context.preferences.addons['cycles'].preferences
prefs.compute_device_type='OPTIX';prefs.get_devices()
for d in prefs.devices:d.use=d.type!='CPU'
s.cycles.device='GPU';s.cycles.use_denoising=True;s.cycles.denoiser='OPTIX'
s.render.resolution_x=1920;s.render.resolution_y=1080;s.render.resolution_percentage=100
s.render.fps=24;s.frame_start=1;s.frame_end=576
s.render.image_settings.file_format='PNG';s.render.threads_mode='FIXED';s.render.threads=4
s.view_settings.view_transform='AgX'
def mat(name,c,metal=0):
 m=bpy.data.materials.new(name);m.use_nodes=True;n=m.node_tree.nodes['Principled BSDF'];n.inputs['Base Color'].default_value=(*c,1);n.inputs['Roughness'].default_value=.42;n.inputs['Metallic'].default_value=metal;return m
lid=[]
for row in json.loads((MESH/'piezas.json').read_text()):
 bpy.ops.wm.stl_import(filepath=str(MESH/row['file']));o=bpy.context.object;o.name=row['name']
 o.data.materials.append(mat(o.name,row['color']))
 if row['group']=='tapa':lid.append(o)
# Import actual board and preserve its component colors.
before=set(bpy.data.objects);bpy.ops.import_scene.gltf(filepath=str(MESH/'placa.glb'))
parts=[o for o in set(bpy.data.objects)-before if o.type=='MESH']
bpy.ops.object.select_all(action='DESELECT')
for o in parts:o.select_set(True)
bpy.context.view_layer.objects.active=parts[0];bpy.ops.object.parent_clear(type='CLEAR_KEEP_TRANSFORM');bpy.ops.object.join()
pcb=bpy.context.object;pcb.name='Placa_KiCad';bpy.ops.object.transform_apply(location=True,rotation=True,scale=True)
# Largest horizontal extent is board body; KiCad y points toward its rear after import.
print('PCB dimensions:',tuple(pcb.dimensions))
assert 145<pcb.dimensions.x<160 and 85<pcb.dimensions.y<100,tuple(pcb.dimensions)
coords=[pcb.matrix_world@Vector(v) for v in pcb.bound_box]
pcb.location.x+=25-min(v.x for v in coords);pcb.location.y+=10-min(v.y for v in coords)
# Substrate is z=0..1.6 in KiCad; underside copper may extend below 0.
pcb.location.z+=12.5
# Screen is a diagram, with no invented measurements.
bpy.ops.mesh.primitive_plane_add(size=2,location=(53.25,62.5,74.8));screen=bpy.context.object;screen.name='OLED_demo';screen.scale=(12.8,7.1,1)
m=mat('OLED luminosa',(.005,.015,.02));n=m.node_tree.nodes['Principled BSDF'];tex=m.node_tree.nodes.new('ShaderNodeTexImage');tex.image=bpy.data.images.load(str(OUT/'oled-demo.png'));tex.interpolation='Closest'
m.node_tree.links.new(tex.outputs['Color'],n.inputs['Base Color']);m.node_tree.links.new(tex.outputs['Color'],n.inputs['Emission Color']);n.inputs['Emission Strength'].default_value=.65;screen.data.materials.append(m);lid.append(screen)
for o in lid:
 z=o.location.z;y=o.location.y;x=o.location.x
 for fr,dz,dy in [(1,0,0),(145,0,0),(241,50,40),(433,50,40),(553,0,0),(576,0,0)]:
  o.location.z=z+dz;o.location.y=y+dy;o.location.x=x+(230 if dz else 0);o.keyframe_insert('location',frame=fr)
# Matte studio floor and soft lights, matching the reference's restrained presentation.
bpy.ops.mesh.primitive_plane_add(size=20000,location=(100,75,-.7));floor=bpy.context.object;floor.data.materials.append(mat('Fondo',(.035,.047,.06)))
world=bpy.data.worlds.new('Estudio');s.world=world;world.use_nodes=True;world.node_tree.nodes['Background'].inputs[0].default_value=(.12,.16,.21,1);world.node_tree.nodes['Background'].inputs[1].default_value=.35
for name,pos,power,size in [('Principal',(-170,-200,430),1600000,330),('Relleno',(380,120,300),1000000,260),('Borde',(80,380,350),1800000,220)]:
 bpy.ops.object.light_add(type='AREA',location=pos);o=bpy.context.object;o.name=name;o.data.energy=power;o.data.shape='DISK';o.data.size=size;o.rotation_euler=(Vector((100,75,45))-o.location).to_track_quat('-Z','Y').to_euler()
bpy.ops.object.camera_add();cam=bpy.context.object;s.camera=cam;cam.data.type='ORTHO';cam.data.lens=50
shots=[(1,(390,-380,360),(100,75,40),420),(145,(320,-350,390),(100,75,45),390),(241,(390,-400,550),(205,90,60),650),(337,(260,-220,650),(205,90,55),620),(433,(390,-400,550),(205,90,60),650),(553,(390,-380,360),(100,75,40),420),(576,(390,-380,360),(100,75,40),420)]
for fr,pos,target,scale in shots:
 cam.location=pos;cam.rotation_euler=(Vector(target)-cam.location).to_track_quat('-Z','Y').to_euler();cam.data.ortho_scale=scale
 cam.keyframe_insert('location',frame=fr);cam.keyframe_insert('rotation_euler',frame=fr);cam.data.keyframe_insert('ortho_scale',frame=fr)
s.frame_set(1);bpy.ops.wm.save_as_mainfile(filepath=str(OUT/'medidor-animado.blend'));bpy.ops.file.pack_all();bpy.ops.wm.save_as_mainfile(filepath=str(OUT/'medidor-animado.blend'))
if os.environ.get('PREVIEW'):
 for fr in [1,265,365]:
  s.frame_set(fr);s.render.filepath=str(OUT/f'preview-{fr}.png');bpy.ops.render.render(write_still=True)
elif not os.environ.get('BUILD_ONLY'):
 (OUT/'frames').mkdir(exist_ok=True)
 for fr in range(1,577):
  s.frame_set(fr);s.render.filepath=str(OUT/'frames'/f'frame-{fr:04d}.png');bpy.ops.render.render(write_still=True)
