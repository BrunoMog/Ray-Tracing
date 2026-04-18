#include "ObjReader.hpp"

#include <filesystem>
#include <iostream>
#include <sstream>

namespace {

std::string resolveObjPath(const std::string& requestedPath) {
    namespace fs = std::filesystem;

    const fs::path direct(requestedPath);
    if (fs::exists(direct)) {
        return direct.string();
    }

    const fs::path filename = direct.filename();
    const fs::path inputDir = fs::path("utils/input");

    const fs::path candidates[] = {
        inputDir / direct,
        inputDir / filename,
        fs::path("utils") / direct,
        fs::path("utils") / filename
    };

    for (const auto& candidate : candidates) {
        if (fs::exists(candidate)) {
            return candidate.string();
        }
    }

    return requestedPath;
}

} // namespace

objReader::objReader(std::string filename) : filename(std::move(filename)) {
    this->filename = resolveObjPath(this->filename);
    file.open(this->filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << this->filename << std::endl;
        return;
    }

    std::string line;
    std::string colorname;
    std::string filename_mtl;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "mtllib") {
            iss >> filename_mtl;
            std::string filename_mtl_path = this->filename;
            filename_mtl_path.replace(filename_mtl_path.length() - 3, 3, "mtl");
            cmap = colormap(filename_mtl_path);
        } else if (prefix == "usemtl") {
            iss >> colorname;
            curMaterial = cmap.getMaterialProperties(colorname);
        } else if (prefix == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        } else if (prefix == "vn") {
            double x, y, z;
            iss >> x >> y >> z;
            normals.emplace_back(x, y, z);
        } else if (prefix == "f") {
            FaceData face;
            face.material = curMaterial;

            for (int i = 0; i < 3; ++i) {
                std::string token;
                iss >> token;
                const size_t first = token.find('/');
                const size_t second = token.find('/', first + 1);
                face.verticeIndice[i] = std::stoi(token.substr(0, first)) - 1;
                face.normalIndice[i] = std::stoi(token.substr(second + 1)) - 1;
            }

            faces.push_back(face);
        }
    }

    for (const auto& face : faces) {
        std::vector<Ponto> points = {
            vertices[face.verticeIndice[0]],
            vertices[face.verticeIndice[1]],
            vertices[face.verticeIndice[2]]};
        facePoints.push_back(points);
    }

    file.close();
}

std::vector<std::vector<Ponto>> objReader::getFacePoints() const {
    return facePoints;
}

Vetor objReader::getKd() const {
    return curMaterial.kd;
}

Vetor objReader::getKa() const {
    return curMaterial.ka;
}

Vetor objReader::getKe() const {
    return curMaterial.ke;
}

double objReader::getNs() const {
    return curMaterial.ns;
}

double objReader::getNi() const {
    return curMaterial.ni;
}

Vetor objReader::getKs() const {
    return curMaterial.ks;
}

double objReader::getD() const {
    return curMaterial.d;
}

std::vector<Ponto> objReader::getVertices() const {
    return vertices;
}

std::vector<Vetor> objReader::getNormals() const {
    return normals;
}

std::vector<FaceData> objReader::getFaces() const {
    return faces;
}

void objReader::print_faces() const {
    int i = 0;
    for (const auto& face : facePoints) {
        i++;
        std::clog << "Face " << i << ": ";
        for (const auto& point : face) {
            std::cout << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")";
        }
        std::clog << std::endl;
    }
}

std::string objReader::getFilename() const {
    return filename;
}
