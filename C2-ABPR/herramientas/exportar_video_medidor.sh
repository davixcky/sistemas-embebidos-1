#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
ffmpeg -y -loglevel warning -framerate 24 -i docs/video/frames/frame-%04d.png \
  -vf 'ass=docs/video/rotulos.ass' -c:v libx264 -preset slow -crf 18 -pix_fmt yuv420p \
  -movflags +faststart docs/video/medidor-animado.mp4
ffmpeg -y -loglevel error -ss 14 -i docs/video/medidor-animado.mp4 -frames:v 1 -update 1 docs/video/portada.jpg
