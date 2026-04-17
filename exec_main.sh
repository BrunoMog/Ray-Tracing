#!/usr/bin/env bash
set -euo pipefail

# Argumentos opcionais:
# 1) Caminho da cena JSON
# 2) Caminho do arquivo PPM de saida
# 3) Caminho da imagem convertida (png/jpg)
SCENE_PATH="${1:-utils/input/delivery1_floor_spheres.json}"
PPM_OUTPUT="${2:-out.ppm}"
IMAGE_OUTPUT="${3:-}"

mkdir -p "$(dirname "$PPM_OUTPUT")"

g++ -std=c++17 main.cpp -o raytracer
./raytracer "$SCENE_PATH" > "$PPM_OUTPUT"

if [[ -n "$IMAGE_OUTPUT" ]]; then
	mkdir -p "$(dirname "$IMAGE_OUTPUT")"
	python utils/convert_ppm.py "$PPM_OUTPUT" "$IMAGE_OUTPUT"
else
	python utils/convert_ppm.py "$PPM_OUTPUT"
fi

echo "Cena: $SCENE_PATH"
echo "PPM: $PPM_OUTPUT"
if [[ -n "$IMAGE_OUTPUT" ]]; then
	echo "Imagem: $IMAGE_OUTPUT"
else
	echo "Imagem: gerada automaticamente em renders/"
fi
