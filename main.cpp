#include <iostream>
#include <fstream>
#include <string>
#include "src/builders/SceneBuilder.h"
#include "src/Renderer.h"
#include "utils/Scene/sceneParser.hpp"

int main(int argc, char* argv[]) {
    std::string scenePath = "utils/input/delivery1_floor_spheres.json";
    if (argc > 1) {
        scenePath = argv[1];
    }

    SceneData sceneData = SceneJsonLoader::loadFile(scenePath);

    Camera camera = SceneBuilder::buildCamera(sceneData.camera);

    if (argc >= 4) {
        const std::string beforePath = argv[2];
        const std::string afterPath = argv[3];

        std::ofstream beforeOut(beforePath);
        std::ofstream afterOut(afterPath);

        if (!beforeOut || !afterOut) {
            std::cerr << "Erro ao abrir arquivos de saida para render antes/depois.\n";
            return 1;
        }

        Cena cenaAntes = SceneBuilder::buildScene(sceneData, false);
        Cena cenaDepois = SceneBuilder::buildScene(sceneData, true);

        Renderer renderer(camera, cenaAntes, &cenaDepois);
        renderer.renderPPMTransformacao(beforeOut, afterOut);
    }
    else{
        Cena cena = SceneBuilder::buildScene(sceneData, true);
        Renderer renderer(camera, cena);
        renderer.renderPPM(std::cout);
    }

    return 0;
}