#include "Esfera.h"

#include <algorithm>
#include <cmath>
#include <limits>

Esfera::Esfera(const Ponto& centro, double raio, const Cor& cor)
    : centro(centro), raio(raio), cor(cor) {}

bool Esfera::intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const {
    const Vetor oc = reta.getOrigem() - centro;
    const double a = reta.getDirecao() * reta.getDirecao();
    const double b = 2.0 * (oc * reta.getDirecao());
    const double c = (oc * oc) - (raio * raio);
    const double discriminante = b * b - 4 * a * c;

    if (discriminante < 0) {
        return false;
    }

    const double raiz = std::sqrt(discriminante);
    double t = (-b - raiz) / (2.0 * a);

    if (t < tMin || t > tMax) {
        t = (-b + raiz) / (2.0 * a);
        if (t < tMin || t > tMax) {
            return false;
        }
    }

    hit.t = t;
    hit.ponto = reta.getOrigem() + (reta.getDirecao() * t);
    hit.normal = (hit.ponto - centro).normalizado();
    hit.cor = cor;
    return true;
}

void Esfera::aplicarTransformacao(const Matriz& transformacao) {
    centro = transformacao * centro;

    const double sx = (transformacao * Vetor(1, 0, 0)).norma();
    const double sy = (transformacao * Vetor(0, 1, 0)).norma();
    const double sz = (transformacao * Vetor(0, 0, 1)).norma();
    const double scale = std::max({sx, sy, sz});

    if (scale > 0.0) {
        raio *= scale;
    }
}

Ponto Esfera::getCentro() const {
    return centro;
}

double Esfera::getRaio() const {
    return raio;
}

Cor Esfera::getCor() const {
    return cor;
}

bool Esfera::intersecaoComEsfera(const Reta& reta, HitRecord& hit) const {
    return intersectar(reta, 0.0, std::numeric_limits<double>::max(), hit);
}
