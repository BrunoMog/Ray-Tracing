#include "MalhaTriangulos.h"

#include <limits>
#include <cmath>

MalhaTriangulos::MalhaTriangulos(
    size_t num_triangulos,
    size_t num_vertices,
    const std::vector<Ponto>& vertices,
    const std::vector<std::array<int, 3>>& indices,
    const std::vector<Vetor>& normais,
    const std::vector<Vetor>& normais_vertices,
    const Cor& cor
) : num_triangulos(num_triangulos),
    num_vertices(num_vertices),
    normais(normais),
    normais_vertices(normais_vertices),
    vertices(vertices),
    indices(indices),
    cor(cor) {
    construirTriangulos(vertices, indices, normais, normais_vertices);
}

void MalhaTriangulos::construirTriangulos(const std::vector<Ponto>& vertices,
     const std::vector<std::array<int, 3>>& indices, const std::vector<Vetor>& normais,
      const std::vector<Vetor>& normais_vertices) {
    for (size_t i = 0; i < num_triangulos; ++i) {
        const auto& idx = indices[i];
        std::vector<Vetor> normais_vertices_triangulo = { normais_vertices[idx[0]], normais_vertices[idx[1]], normais_vertices[idx[2]] };
        triangulos.emplace_back(vertices[idx[0]], vertices[idx[1]], vertices[idx[2]], cor, normais[i], normais_vertices_triangulo);
    }
}

bool MalhaTriangulos::intersectar(const Reta& raio, double tMin, double tMax, HitRecord& hit) const {
    HitRecord hitTemp;
    double tAtual = tMax;
    bool encontrou = false;
    
    for (const auto& triangulo : triangulos) {
        if (triangulo.intersectar(raio, tMin, tAtual, hitTemp)) {
            if (!std::isfinite(hitTemp.t)) {
                continue;
            }
            encontrou = true;
            tAtual = hitTemp.t;
            hit = hitTemp;
        }
    }
    return encontrou;
}

void MalhaTriangulos::aplicarTransformacao(const Matriz& transformacao) {
    for (auto& triangulo : triangulos) {
        triangulo.aplicarTransformacao(transformacao);
    }
}

size_t MalhaTriangulos::getNumTriangulos() const {
    return num_triangulos;
}

size_t MalhaTriangulos::getNumVertices() const {
    return num_vertices;
}

std::vector<Triangulo> MalhaTriangulos::getTriangulos() const {
    return triangulos;
}

std::vector<Vetor> MalhaTriangulos::getNormais() const {
    return normais;
}

std::vector<Vetor> MalhaTriangulos::getNormaisVertices() const {
    return normais_vertices;
}

Cor MalhaTriangulos::getCor() const {
    return cor;
}

bool MalhaTriangulos::intersecaoComMalha(const Reta& raio, HitRecord& hit) const {
    return intersectar(raio, 0.0, std::numeric_limits<double>::max(), hit);
}
