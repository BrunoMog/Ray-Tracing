#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "src/Camera.h"
#include "src/Cena.h"
#include "src/algebric_objects/Reta.h"
#include "src/objects/Esfera.h"
#include "src/objects/Plano.h"
#include "utils/Scene/sceneParser.cpp"

namespace {

Cor toCor(const ColorData& colorData) {
    return Cor(colorData.r, colorData.g, colorData.b);
}

Ponto toPonto(const Ponto& ponto) {
    return ponto;
}

Vetor toVetor(const Vetor& vetor) {
    return vetor;
}

std::unique_ptr<Objeto> buildObject(const ObjectData& objectData) {
    const Cor materialColor = toCor(objectData.material.color);

    if (objectData.objType == "sphere") {
        const Ponto center = objectData.relativePos;
        const double radius = objectData.numericData.at("radius");
        return std::make_unique<Esfera>(center, radius, materialColor);
    }

    if (objectData.objType == "plane") {
        const Ponto point = objectData.relativePos;
        const Vetor normal = objectData.vetorPointData.at("normal");
        return std::make_unique<Plano>(point, normal, materialColor);
    }

    return nullptr;
}

Cena buildScene(const SceneData& sceneData) {
    Cena cena(toCor(sceneData.globalLight.color));

    for (const auto& objectData : sceneData.objects) {
        std::unique_ptr<Objeto> objeto = buildObject(objectData);
        if (objeto) {
            cena.adicionarObjeto(std::move(objeto));
        }
    }

    return cena;
}

Camera buildCamera(const CameraData& cameraData) {
    return Camera(
        cameraData.lookfrom,
        cameraData.lookat,
        cameraData.upVector,
        cameraData.screen_distance,
        cameraData.image_width,
        cameraData.image_height
    );
}

} // namespace

int main() {
    const std::string scenePath = "utils/input/sampleScene.json";
    SceneData sceneData = SceneJsonLoader::loadFile(scenePath);

    Camera camera = buildCamera(sceneData.camera);
    Cena cena = buildScene(sceneData);

    const int largura = sceneData.camera.image_width;
    const int altura = sceneData.camera.image_height;

    std::cout << "P3\n";
    std::cout << largura << ' ' << altura << "\n";
    std::cout << 255 << "\n";

    for (int j = 0; j < altura; ++j) {
        for (int i = 0; i < largura; ++i) {
            Vetor direcaoPixel = camera.calcularPosicaoPixel(i, j);
            Reta raio(camera.getLookfrom(), direcaoPixel);

            HitRecord hit;
            Cor corPixel = Cor::preto();

            if (cena.intersectar(raio, 0.001, std::numeric_limits<double>::max(), hit)) {
                corPixel = hit.cor;
            }

            std::cout << corPixel.R255() << ' ' << corPixel.G255() << ' ' << corPixel.B255() << '\n';
        }
    }

    return 0;
}