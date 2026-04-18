#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../../src/algebric_objects/Ponto.h"
#include "../../src/algebric_objects/Vetor.h"
#include "Colormap.hpp"

struct FaceData {
    int verticeIndice[3];
    int normalIndice[3];
    MaterialProperties material;
};

class objReader {
public:
    explicit objReader(std::string filename);

    std::vector<std::vector<Ponto>> getFacePoints() const;
    Vetor getKd() const;
    Vetor getKa() const;
    Vetor getKe() const;
    double getNs() const;
    double getNi() const;
    Vetor getKs() const;
    double getD() const;
    std::vector<Ponto> getVertices() const;
    std::vector<Vetor> getNormals() const;
    std::vector<FaceData> getFaces() const;
    void print_faces() const;
    std::string getFilename() const;

private:
    std::ifstream file;
    std::vector<Ponto> vertices;
    std::vector<Vetor> normals;
    std::vector<FaceData> faces;
    std::vector<std::vector<Ponto>> facePoints;
    MaterialProperties curMaterial;
    colormap cmap;
    std::string filename;
};
