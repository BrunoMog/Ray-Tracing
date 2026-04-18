#pragma once

#include <cstdint>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include "../../src/algebric_objects/Ponto.h"
#include "../../src/algebric_objects/Vetor.h"

struct CameraData {
    Ponto lookfrom;
    Ponto lookat;
    Vetor upVector = Vetor(0, 1, 0);

    int image_width = 0;
    int image_height = 0;
    double screen_distance = 1.0;
};

struct ColorData {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    ColorData() = default;
    ColorData(double r, double g, double b) : r(r), g(g), b(b) {}
};

struct LightData {
    Ponto pos;
    ColorData color;
    std::map<std::string, std::string> extraData;
};

struct TransformData {
    std::string tType;
    Vetor data;
};

struct MaterialData {
    std::string name;
    ColorData color;
    ColorData ks;
    ColorData ka;
    ColorData kr;
    ColorData kt;
    double ns = 0.0;
    double ni = 1.0;
    double d = 1.0;
};

struct ObjectData {
    std::string objType;

    Ponto relativePos = Ponto(0, 0, 0);
    MaterialData material;

    std::map<std::string, double> numericData;
    std::map<std::string, Vetor> vetorPointData;
    std::map<std::string, std::string> otherProperties;

    std::vector<TransformData> transforms;

    double getNum(const std::string& key) const;
    int64_t getInt(const std::string& key) const;
    Vetor getVetor(const std::string& key) const;
    Ponto getPonto(const std::string& key) const;
    std::string getProperty(const std::string& key) const;
};

struct SceneData {
    CameraData camera;

    LightData globalLight;
    std::vector<LightData> lightList;

    std::vector<ObjectData> objects;
};

std::ostream& operator<<(std::ostream& os, const ColorData& c);
std::ostream& operator<<(std::ostream& os, const TransformData& t);
std::ostream& operator<<(std::ostream& os, const MaterialData& m);
std::ostream& operator<<(std::ostream& os, const LightData& l);
std::ostream& operator<<(std::ostream& os, const ObjectData& obj);
std::ostream& operator<<(std::ostream& os, const CameraData& c);
std::ostream& operator<<(std::ostream& os, const SceneData& s);
