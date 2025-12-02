#!/usr/bin/env bash

# Использование:
#   ./visualize_dot.sh [директория] [формат]
#
# Примеры:
#   ./visualize_dot.sh              # все *.dot в текущей директории -> PNG
#   ./visualize_dot.sh out svg      # все *.dot в ./out -> SVG

set -e

DIR="."
FORMAT="png"

if [ -n "$1" ]; then
  DIR="$1"
fi

if [ -n "$2" ]; then
  FORMAT="$2"
fi

if ! command -v dot >/dev/null 2>&1; then
  echo "Ошибка: утилита 'dot' (Graphviz) не найдена. Установи graphviz." >&2
  exit 1
fi

if [ ! -d "$DIR" ]; then
  echo "Ошибка: директория '$DIR' не существует." >&2
  exit 1
fi

shopt -s nullglob

cd "$DIR"

DOT_FILES=(*.dot)
if [ ${#DOT_FILES[@]} -eq 0 ]; then
  echo "В директории '$DIR' нет .dot файлов."
  exit 0
fi

for f in "${DOT_FILES[@]}"; do
  base="${f%.dot}"
  out="${base}.${FORMAT}"
  echo "Генерирую $out из $f ..."
  dot -T"$FORMAT" "$f" -o "$out"
done

echo "Готово."
