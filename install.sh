#!/bin/bash
set -e

if [ "$EUID" -ne 0 ]; then
  exec sudo "$0" "$@"
fi

echo "📦 Instalando dependencias..."

apt update
apt install -y \
  build-essential \
  libcurl4 \
  libcurl4-openssl-dev \
  libxml2 \
  libxml2-dev
