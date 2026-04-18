#include "sceneSchema.hpp"

#include <algorithm>
#include <ostream>

namespace {

int g_indent_spacing = 0;

void indent(std::ostream& os) {
    for (int i = 0; i < g_indent_spacing; ++i) {
        os << "    ";
    }
}

void printAsArray(std::ostream& os, const Vetor& v) {
    os << "[" << v.getX() << ", " << v.getY() << ", " << v.getZ() << "]";
}

void printAsArray(std::ostream& os, const Ponto& p) {
    os << "[" << p.getX() << ", " << p.getY() << ", " << p.getZ() << "]";
}

} // namespace

double ObjectData::getNum(const std::string& key) const {
    return numericData.at(key);
}

int64_t ObjectData::getInt(const std::string& key) const {
    return static_cast<int64_t>(numericData.at(key));
}

Vetor ObjectData::getVetor(const std::string& key) const {
    return vetorPointData.at(key);
}

Ponto ObjectData::getPonto(const std::string& key) const {
    const Vetor p = vetorPointData.at(key);
    return Ponto(p.getX(), p.getY(), p.getZ());
}

std::string ObjectData::getProperty(const std::string& key) const {
    return otherProperties.at(key);
}

std::ostream& operator<<(std::ostream& os, const ColorData& c) {
    return os << "[" << c.r << ", " << c.g << ", " << c.b << "]";
}

std::ostream& operator<<(std::ostream& os, const TransformData& t) {
    indent(os);
    os << "{\n";
    g_indent_spacing++;

    indent(os);
    os << "\"type\": \"" << t.tType << "\",\n";
    indent(os);
    os << "\"data\": ";
    printAsArray(os, t.data);

    os << "\n";
    g_indent_spacing--;
    indent(os);
    return os << "}";
}

std::ostream& operator<<(std::ostream& os, const MaterialData& m) {
    indent(os);
    os << "{\n";
    g_indent_spacing++;
    indent(os);
    os << "\"name\": \"" << m.name << "\",\n";
    indent(os);
    os << "\"color\": " << m.color << ",\n";
    indent(os);
    os << "\"ks\": " << m.ks << ",\n";
    indent(os);
    os << "\"ka\": " << m.ka << ",\n";
    indent(os);
    os << "\"kr\": " << m.kr << ",\n";
    indent(os);
    os << "\"kt\": " << m.kt << ",\n";
    indent(os);
    os << "\"ns\": " << m.ns << ",\n";
    indent(os);
    os << "\"ni\": " << m.ni << ",\n";
    indent(os);
    os << "\"d\": " << m.d << "\n";
    g_indent_spacing--;
    indent(os);
    return os << "}";
}

std::ostream& operator<<(std::ostream& os, const LightData& l) {
    indent(os);
    os << "{\n";
    g_indent_spacing++;

    const auto extraData = l.extraData;

    indent(os);
    os << "\"position\": ";
    printAsArray(os, l.pos);
    os << ",\n";

    indent(os);
    os << "\"color\": " << l.color << ",\n";

    auto nameIt = extraData.find("name");
    indent(os);
    os << "\"name\": \"" << (nameIt == extraData.end() ? "" : nameIt->second) << "\"";

    for (const auto& [k, v] : extraData) {
        if (k == "name") {
            continue;
        }
        os << ",\n";
        indent(os);
        os << "\"" << k << "\": \"" << v << "\"";
    }

    os << "\n";
    g_indent_spacing--;
    indent(os);
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const ObjectData& obj) {
    os << "{\n";
    g_indent_spacing++;

    indent(os);
    os << "\"type\": \"" << obj.objType << "\",\n";
    indent(os);
    os << "\"relativePos\": ";
    printAsArray(os, obj.relativePos);
    os << ",\n";
    indent(os);
    os << "\"material\": \"" << obj.material.name << "\"";

    for (const auto& [k, v] : obj.numericData) {
        os << ",\n";
        indent(os);
        os << "\"" << k << "\": " << v;
    }

    for (const auto& [k, v] : obj.vetorPointData) {
        os << ",\n";
        indent(os);
        os << "\"" << k << "\": ";
        printAsArray(os, v);
    }

    for (const auto& [k, v] : obj.otherProperties) {
        os << ",\n";
        indent(os);
        os << "\"" << k << "\": \"" << v << "\"";
    }

    if (!obj.transforms.empty()) {
        os << ",\n";
        indent(os);
        os << "\"transform\": [\n";
        g_indent_spacing++;

        for (size_t i = 0; i < obj.transforms.size(); ++i) {
            os << obj.transforms[i];
            if (i + 1 < obj.transforms.size()) {
                os << ",";
            }
            os << "\n";
        }

        g_indent_spacing--;
        indent(os);
        os << "]";
    }

    os << "\n";
    g_indent_spacing--;
    indent(os);
    return os << "}";
}

std::ostream& operator<<(std::ostream& os, const CameraData& c) {
    indent(os);
    os << "{\n";
    g_indent_spacing++;

    indent(os);
    os << "\"lookfrom\": ";
    printAsArray(os, c.lookfrom);
    os << ",\n";
    indent(os);
    os << "\"lookat\": ";
    printAsArray(os, c.lookat);
    os << ",\n";
    indent(os);
    os << "\"upVector\": ";
    printAsArray(os, c.upVector);
    os << ",\n";

    indent(os);
    os << "\"image_width\": " << c.image_width << ",\n";
    indent(os);
    os << "\"image_height\": " << c.image_height << ",\n";
    indent(os);
    os << "\"screen_distance\": " << c.screen_distance << "\n";

    g_indent_spacing--;
    indent(os);
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const SceneData& s) {
    indent(os);
    os << "{\n";
    g_indent_spacing++;

    indent(os);
    os << "\"camera\": " << s.camera << ",\n";
    indent(os);
    os << "\"globalLight\": " << s.globalLight.color << ",\n";

    indent(os);
    os << "\"lights\": [\n";
    g_indent_spacing++;

    for (size_t i = 0; i < s.lightList.size(); ++i) {
        os << s.lightList[i];
        if (i + 1 < s.lightList.size()) {
            os << ",";
        }
        os << "\n";
    }

    g_indent_spacing--;
    indent(os);
    os << "],\n";

    std::vector<MaterialData> materials;
    for (const auto& obj : s.objects) {
        materials.push_back(obj.material);
    }

    std::sort(materials.begin(), materials.end(), [](const MaterialData& a, const MaterialData& b) {
        return a.name < b.name;
    });
    materials.erase(std::unique(materials.begin(), materials.end(), [](const MaterialData& a, const MaterialData& b) {
        return a.name == b.name;
    }), materials.end());

    indent(os);
    os << "\"materials\": {\n";
    g_indent_spacing++;
    for (size_t i = 0; i < materials.size(); ++i) {
        indent(os);
        os << "\"" << materials[i].name << "\": " << materials[i];
        if (i + 1 < materials.size()) {
            os << ",";
        }
        os << "\n";
    }
    g_indent_spacing--;
    indent(os);
    os << "},\n";

    indent(os);
    os << "\"objects\": [\n";
    g_indent_spacing++;

    for (size_t i = 0; i < s.objects.size(); ++i) {
        indent(os);
        os << s.objects[i];
        if (i + 1 < s.objects.size()) {
            os << ",";
        }
        os << "\n";
    }

    g_indent_spacing--;
    indent(os);
    os << "]\n";

    g_indent_spacing--;
    indent(os);
    os << "}";
    return os;
}
