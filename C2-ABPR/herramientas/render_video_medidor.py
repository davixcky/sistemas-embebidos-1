"""Renderiza la escena guardada. Permite reanudar solo la misma versión de la escena."""
import bpy
from pathlib import Path
s=bpy.context.scene
prefs=bpy.context.preferences.addons['cycles'].preferences;prefs.compute_device_type='OPTIX';prefs.get_devices()
for d in prefs.devices:d.use=d.type!='CPU'
s.cycles.device='GPU';s.cycles.denoiser='OPTIX'
out=Path(bpy.data.filepath).parent/'frames';out.mkdir(exist_ok=True)
for frame in range(s.frame_start,s.frame_end+1):
 path=out/f'frame-{frame:04d}.png'
 if path.exists():continue
 s.frame_set(frame);s.render.filepath=str(path);bpy.ops.render.render(write_still=True)
