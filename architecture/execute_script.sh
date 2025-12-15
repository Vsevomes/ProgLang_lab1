#!/usr/bin/env bash
set -euo pipefail

EXE=${1:-out_local.ptptb}
LOGIN=${LOGIN:-"507549"}
PASSWORD=${PASSWORD:-"45e6787a-cd45-4fbe-8231-ec28dcf4ba7e"}
ARC_FILE=${1:-stackdyn64.target.pdsl}
ARC=${1:-stackdyn64}

MANAGER=(mono Portable.RemoteTasks.Manager.exe)

echo "Executing..."

"${MANAGER[@]}" -ul "$LOGIN" -up "$PASSWORD" -w -s \
 ExecuteBinaryWithInput definitionFile "$ARC_FILE" \
 archName "$ARC" binaryFileToRun "$EXE" \
 ipRegStorageName ip finishMnemonicName hlt \
 codeRamBankName code stdinRegStName rin \
 stdoutRegStName rout inputFile in.txt > output

echo "Result written in output"
