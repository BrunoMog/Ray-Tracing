#include "Cena.h"

#include <cmath>

Cena::Cena(const Cor& cor_ambiente) : cor_ambiente(cor_ambiente) {}

void Cena::adicionarObjeto(std::unique_ptr<Objeto> objeto) {
    objetos.push_back(std::move(objeto));
}

void Cena::adicionarTransformacao(const Matriz& transformacao) {
    this->transformacao = transformacao;
    transformacaoAplicada = true;
}

void Cena::aplicarTransformacao() {
    for (auto& objeto : objetos) {
        objeto->aplicarTransformacao(transformacao);
    }
}

bool Cena::intersectar(const Reta& raio, double tMin, double tMax, HitRecord& hitMaisProximo) const {
    bool encontrou = false;
    HitRecord hitTemp;
    double tAtual = tMax;

    for (const auto& objeto : objetos) {
        if (objeto->intersectar(raio, tMin, tAtual, hitTemp)) {
            if (!std::isfinite(hitTemp.t)) {
                continue;
            }
            encontrou = true;
            tAtual = hitTemp.t;
            hitMaisProximo = hitTemp;
        }
    }

    return encontrou;
}

Cor Cena::getCorAmbiente() const {
    return cor_ambiente;
}

bool Cena::isTransformacaoAplicada() const {
    return transformacaoAplicada;
}