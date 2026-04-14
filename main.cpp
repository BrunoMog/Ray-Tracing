#include <iostream>
#include <string>
#include "src/builders/SceneBuilder.h"
#include "src/Renderer.h"
#include "utils/Scene/sceneParser.cpp"
#include "src/builders/SceneBuilder.cpp"

int main() {
    const std::string scenePath = "utils/input/delivery1_floor_spheres.json";
    SceneData sceneData = SceneJsonLoader::loadFile(scenePath);

    Camera camera = SceneBuilder::buildCamera(sceneData.camera);
    Cena cena = SceneBuilder::buildScene(sceneData);

    const int largura = sceneData.camera.image_width;
    const int altura = sceneData.camera.image_height;

    Renderer renderer(camera, cena, largura, altura);
    renderer.renderPPM(std::cout);

    return 0;
}