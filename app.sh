#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

need_root() {
  if [ "$EUID" -ne 0 ]; then
    exec sudo "$0" "$@"
  fi
}

check_cmd() {
  command -v "$1" >/dev/null 2>&1
}

check_lib() {
  ldconfig -p | grep -q "$1"
}

echo "🔍 Comprobando dependencias..."

MISSING=0

check_cmd gcc || MISSING=1
check_cmd make || MISSING=1
check_lib libcurl.so.4 || MISSING=1
check_lib libxml2.so.2 || MISSING=1

if [ "$MISSING" -eq 1 ]; then
  echo "📦 Faltan dependencias"
  need_root "$@"
  ./install.sh
fi

if [ ! -x "./app" ]; then
  echo "🔨 Compilando aplicación..."
  make
fi

echo "🚀 Ejecutando aplicación"
exec ./app "$@"
