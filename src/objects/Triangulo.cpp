#include "Triangulo.h"

#include <limits>

Triangulo::Triangulo(const Ponto& p1, const Ponto& p2, const Ponto& p3,
     const Cor& cor, const Vetor& normal, const std::vector<Vetor>& normais_vertices)
    : p1(p1), p2(p2), p3(p3), cor(cor), normal(normal.normalizado()), normais_vertices(normais_vertices) {
    v1 = p2 - p1;
    v2 = p3 - p1;
}

bool Triangulo::intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const {
    const Vetor crossDirecaoComAresta2 = reta.getDirecao() % v2;
    const double determinante = v1 * crossDirecaoComAresta2; 
    if (std::abs(determinante) < 1e-6) {
        return false; 
    }
    const double fatorInvDeterminante = 1.0 / determinante;
    const Vetor origemRelativaAoP1 = reta.getOrigem() - p1;
    const double coordenadaBariocentricaU = fatorInvDeterminante * (origemRelativaAoP1 * crossDirecaoComAresta2);
    if (coordenadaBariocentricaU < 0.0 || coordenadaBariocentricaU > 1.0) {
        return false;
    }
    const Vetor crossOrigemComAresta1 = origemRelativaAoP1 % v1;
    const double coordenadaBariocentricaV = fatorInvDeterminante * (reta.getDirecao() * crossOrigemComAresta1);
    const double coordenadaBariocentricaW = 1.0 - coordenadaBariocentricaU - coordenadaBariocentricaV;
    if (coordenadaBariocentricaV < 0.0 || coordenadaBariocentricaU + coordenadaBariocentricaV > 1.0) {
        return false;
    }
    const double distanciaIntersecao = fatorInvDeterminante * (v2 * crossOrigemComAresta1);
    if (distanciaIntersecao < tMin || distanciaIntersecao > tMax) {
        return false;
    }
    hit.t = distanciaIntersecao;
    hit.ponto = reta.getOrigem() + (reta.getDirecao() * distanciaIntersecao);
    hit.normal = (normais_vertices[0] * coordenadaBariocentricaW + 
              normais_vertices[1] * coordenadaBariocentricaU + 
              normais_vertices[2] * coordenadaBariocentricaV).normalizado();
    hit.cor = cor;
    return true;
}

void Triangulo::aplicarTransformacao(const Matriz& transformacao) {
    p1 = transformacao * p1;
    p2 = transformacao * p2;
    p3 = transformacao * p3;
    v1 = p2 - p1;
    v2 = p3 - p1;
    normal = transformacao.transformarNormal(normal).normalizado();
    for (size_t i = 0; i < normais_vertices.size(); ++i) {
        normais_vertices[i] = transformacao.transformarNormal(normais_vertices[i]).normalizado();
    }
}

Ponto Triangulo::getP1() const {
    return p1;
}

Ponto Triangulo::getP2() const {
    return p2;
}

Ponto Triangulo::getP3() const {
    return p3;
}

Cor Triangulo::getCor() const {
    return cor;
}

Vetor Triangulo::getNormal() const {
    return normal;
}

Vetor Triangulo::getV1() const {
    return v1;
}

Vetor Triangulo::getV2() const {
    return v2;
}

std::vector<Vetor> Triangulo::getNormaisVertices() const {
    return normais_vertices;
}

bool Triangulo::intersecaoComTriangulo(const Reta& reta, HitRecord& hit) const {
    return intersectar(reta, 0.0, std::numeric_limits<double>::max(), hit);
}