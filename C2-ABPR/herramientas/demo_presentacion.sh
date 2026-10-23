#!/usr/bin/env bash
# Demostración local con base temporal y datos explícitamente simulados.
set -euo pipefail
cd "$(dirname "$0")/../plataforma"
demo_dir=$(mktemp -d /tmp/medidor-demo.XXXXXX)
demo_port=${DEMO_PORT:-3100}
demo_server_pid=''
demo_sim_pid=''
cleanup() {
  if [[ -n "$demo_sim_pid" ]]; then kill "$demo_sim_pid" 2>/dev/null || true; fi
  if [[ -n "$demo_server_pid" ]]; then kill "$demo_server_pid" 2>/dev/null || true; fi
}
trap cleanup EXIT INT TERM
pnpm build > "$demo_dir/build.log" 2>&1
DATOS_DIR="$demo_dir" PORT="$demo_port" HOST=127.0.0.1 node .output/server/index.mjs > "$demo_dir/server.log" 2>&1 &
demo_server_pid=$!
for ((i=0;i<30;i++)); do
  if curl -fsS "http://127.0.0.1:$demo_port/" -o /dev/null; then break; fi
  if ! kill -0 "$demo_server_pid" 2>/dev/null; then cat "$demo_dir/server.log"; exit 1; fi
  sleep 1
done
curl -fsS "http://127.0.0.1:$demo_port/" -o /dev/null
node scripts/simular.ts --url "http://127.0.0.1:$demo_port" --nodo demo-c2 --dias 2 --paso 60 > "$demo_dir/simulador.log" 2>&1 &
demo_sim_pid=$!
echo "Demo local: http://127.0.0.1:$demo_port — DATOS SIMULADOS"
echo "Registros de ejecución: $demo_dir. Ctrl+C para detener."
wait "$demo_sim_pid"
