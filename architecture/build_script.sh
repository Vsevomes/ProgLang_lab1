#!/usr/bin/env bash
set -euo pipefail

ASM=${1:-../tests/trans_example.asm}
LOGIN=${LOGIN:-"507549"}
PASSWORD=${PASSWORD:-"45e6787a-cd45-4fbe-8231-ec28dcf4ba7e"}

MANAGER=(mono Portable.RemoteTasks.Manager.exe)

echo "Assembling..."

# ВАЖНО: забираем и stdout, и stderr, и показываем пользователю
ASSEMBLE_OUTPUT="$(
  "${MANAGER[@]}" \
    -ul "$LOGIN" \
    -up "$PASSWORD" \
    -s AssembleDebug \
    definitionFile "stackdyn64.target.pdsl" \
    archName "stackdyn64" \
    asmListing "$ASM" \
    sourcesDir "/home/vsevolod/ITMO/ProgLang/Prog_lang_lab1/architecture" \
  2>&1 | tee assemble_remote.log
)"

GUID="$(echo "$ASSEMBLE_OUTPUT" | grep -oE '[0-9a-fA-F]{8}-([0-9a-fA-F]{4}-){3}[0-9a-fA-F]{12}' | head -n1)"
if [[ -z "${GUID:-}" ]]; then
  echo "GUID not found. See assemble_remote.log"
  exit 1
fi
echo "GUID: $GUID"

echo "Downloading out.ptptb (retry)..."

# Несколько попыток: либо задача ещё не закончилась, либо файл появляется с задержкой
ok=0
for i in $(seq 1 20); do
  if "${MANAGER[@]}" -ul "$LOGIN" -up "$PASSWORD" -g "$GUID" -r "out.ptptb" -o "out_local.ptptb" 2>&1 | tee -a download_remote.log; then
    ok=1
    break
  fi
  sleep 1
done

if [[ $ok -ne 1 ]]; then
  echo "Failed to download out.ptptb after retries."
  echo "Check assemble_remote.log and download_remote.log"
  exit 1
fi

echo "OK: out_local.ptptb downloaded"
