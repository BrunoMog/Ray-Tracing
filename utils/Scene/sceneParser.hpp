#pragma once

#include <string>
#include "sceneSchema.hpp"

class SceneJsonLoader {
public:
    static SceneData loadFile(const std::string& filename);
    static SceneData loadString(const std::string& text);
};