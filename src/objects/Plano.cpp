#include "Plano.h"

#include <cmath>
#include <limits>

Plano::Plano(const Ponto& ponto, const Vetor& normal, const Cor& cor)
    : ponto(ponto), normal(normal.normalizado()), cor(cor) {}

bool Plano::intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const {
    const double denominador = reta.getDirecao() * normal;
    if (std::abs(denominador) < 1e-6) {
        return false;
    }

    const double t = ((ponto - reta.getOrigem()) * normal) / denominador;
    if (t < tMin || t > tMax) {
        return false;
    }

    hit.t = t;
    hit.ponto = reta.getOrigem() + (reta.getDirecao() * t);
    hit.normal = normal;
    hit.cor = cor;
    return true;
}

void Plano::aplicarTransformacao(const Matriz& transformacao) {
    ponto = transformacao * ponto;
    normal = transformacao.transformarNormal(normal).normalizado();
}

Ponto Plano::getPonto() const {
    return ponto;
}

Vetor Plano::getNormal() const {
    return normal;
}

Cor Plano::getCor() const {
    return cor;
}

bool Plano::intersecaoComPlano(const Reta& reta, HitRecord& hit) const {
    return intersectar(reta, 0.0, std::numeric_limits<double>::max(), hit);
}
