#include <iostream>
#include <string>
#include "src/builders/SceneBuilder.h"
#include "src/Renderer.h"
#include "utils/Scene/sceneParser.cpp"
#include "src/builders/SceneBuilder.cpp"

int main(int argc, char* argv[]) {
    std::string scenePath = "utils/input/delivery1_floor_spheres.json";
    if (argc > 1) {
        scenePath = argv[1];
    }

    SceneData sceneData = SceneJsonLoader::loadFile(scenePath);

    Camera camera = SceneBuilder::buildCamera(sceneData.camera);
    Cena cena = SceneBuilder::buildScene(sceneData);

    Renderer renderer(camera, cena);
    renderer.renderPPM(std::cout);

    return 0;
}