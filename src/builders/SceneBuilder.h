#ifndef SCENEBUILDERHEADER
#define SCENEBUILDERHEADER

#include <memory>
#include "../utils/Camera.h"
#include "../utils/Cena.h"
#include "../objects/Objeto.h"
#include "../../utils/Scene/sceneSchema.hpp"

namespace SceneBuilder {

Cor toCor(const ColorData& colorData);
std::unique_ptr<Objeto> buildObject(const ObjectData& objectData);
Cena buildScene(const SceneData& sceneData);
Camera buildCamera(const CameraData& cameraData);

} // namespace SceneBuilder

#endif