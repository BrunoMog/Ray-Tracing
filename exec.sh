#!/usr/bin/env bash
set -euo pipefail

# Uso:
#   ./exec.sh [scene.json] [out.ppm] [out.png]
#   ./exec.sh --transform [scene.json] [before.ppm] [after.ppm] [before.png] [after.png]
TRANSFORM_MODE=false
if [[ "${1:-}" == "-t" || "${1:-}" == "--transform" ]]; then
	TRANSFORM_MODE=true
	shift
fi

SCENE_PATH="${1:-utils/input/delivery1_floor_spheres.json}"
PPM_OUTPUT="${2:-out.ppm}"
IMAGE_OUTPUT="${3:-}"
PYTHON_BIN="${PYTHON_BIN:-python3}"

if [[ "$TRANSFORM_MODE" == true ]]; then
	PPM_OUTPUT_AFTER="${3:-after.ppm}"
	PNG_OUTPUT_BEFORE="${4:-before.png}"
	PNG_OUTPUT_AFTER="${5:-after.png}"
	mkdir -p "$(dirname "$PPM_OUTPUT")" "$(dirname "$PPM_OUTPUT_AFTER")"
	g++ -std=c++17 \
		main.cpp \
		src/Renderer.cpp \
		src/builders/SceneBuilder.cpp \
		src/utils/Camera.cpp \
		src/utils/Cena.cpp \
		src/objects/Esfera.cpp \
		src/objects/Triangulo.cpp \
		src/objects/MalhaTriangulos.cpp \
		src/objects/Plano.cpp \
		utils/MeshReader/Colormap.cpp \
		utils/MeshReader/ObjReader.cpp \
		utils/Scene/jsonParser.cpp \
		utils/Scene/sceneSchema.cpp \
		utils/Scene/sceneParser.cpp \
		-o raytracer
	./raytracer "$SCENE_PATH" "$PPM_OUTPUT" "$PPM_OUTPUT_AFTER"
	mkdir -p "$(dirname "$PNG_OUTPUT_BEFORE")" "$(dirname "$PNG_OUTPUT_AFTER")"
	"$PYTHON_BIN" utils/convert_ppm.py "$PPM_OUTPUT" "$PNG_OUTPUT_BEFORE"
	"$PYTHON_BIN" utils/convert_ppm.py "$PPM_OUTPUT_AFTER" "$PNG_OUTPUT_AFTER"
	echo "Cena: $SCENE_PATH"
	echo "PPM antes: $PPM_OUTPUT"
	echo "PPM depois: $PPM_OUTPUT_AFTER"
	echo "PNG antes: $PNG_OUTPUT_BEFORE"
	echo "PNG depois: $PNG_OUTPUT_AFTER"
	exit 0
fi

mkdir -p "$(dirname "$PPM_OUTPUT")"

g++ -std=c++17 \
	main.cpp \
	src/Renderer.cpp \
	src/builders/SceneBuilder.cpp \
	src/utils/Camera.cpp \
	src/utils/Cena.cpp \
	src/objects/Esfera.cpp \
	src/objects/Triangulo.cpp \
	src/objects/MalhaTriangulos.cpp \
	src/objects/Plano.cpp \
	utils/MeshReader/Colormap.cpp \
	utils/MeshReader/ObjReader.cpp \
	utils/Scene/jsonParser.cpp \
	utils/Scene/sceneSchema.cpp \
	utils/Scene/sceneParser.cpp \
	-o raytracer
./raytracer "$SCENE_PATH" > "$PPM_OUTPUT"

if [[ -n "$IMAGE_OUTPUT" ]]; then
	mkdir -p "$(dirname "$IMAGE_OUTPUT")"
	"$PYTHON_BIN" utils/convert_ppm.py "$PPM_OUTPUT" "$IMAGE_OUTPUT"
else
	"$PYTHON_BIN" utils/convert_ppm.py "$PPM_OUTPUT"
fi

echo "Cena: $SCENE_PATH"
echo "PPM: $PPM_OUTPUT"
if [[ -n "$IMAGE_OUTPUT" ]]; then
	echo "Imagem: $IMAGE_OUTPUT"
else
	echo "Imagem: gerada automaticamente em renders/"
fi
