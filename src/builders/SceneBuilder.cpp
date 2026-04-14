#include "SceneBuilder.h"

#include <memory>
#include "../objects/Esfera.h"
#include "../objects/Plano.h"

namespace SceneBuilder {

Cor toCor(const ColorData& colorData) {
    return Cor(colorData.r, colorData.g, colorData.b);
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

} // namespace SceneBuilder