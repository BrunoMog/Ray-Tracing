#pragma once

#include <map>
#include <string>

#include "../../src/algebric_objects/Vetor.h"

struct MaterialProperties {
    Vetor kd;
    Vetor ks;
    Vetor ka;
    Vetor kr;
    Vetor ke;
    Vetor kt;
    double ns;
    double ni;
    double d;

    MaterialProperties();
};

class colormap {
public:
    colormap();
    explicit colormap(const std::string& input);

    Vetor getColor(const std::string& s) const;
    MaterialProperties getMaterialProperties(const std::string& s) const;

private:
    std::map<std::string, MaterialProperties> mp;
};
