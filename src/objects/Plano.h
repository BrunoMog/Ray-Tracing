#ifndef PLANOHEADER
#define PLANOHEADER

#include <cmath>
#include <limits>
#include "../algebric_objects/Vetor.h"
#include "../algebric_objects/Ponto.h"
#include "Objeto.h"

class Plano : public Objeto {
public:
    Plano(const Ponto& ponto, const Vetor& normal, const Cor& cor)
        : ponto(ponto), normal(normal.normalizado()), cor(cor) {}

    bool intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const override {
        double denominador = reta.getDirecao() * normal;
        if (std::abs(denominador) < 1e-6) {
            return false;
        }

        double t = ((ponto - reta.getOrigem()) * normal) / denominador;
        if (t < tMin || t > tMax) {
            return false;
        }

        hit.t = t;
        hit.ponto = reta.getOrigem() + (reta.getDirecao() * t);
        hit.normal = normal;
        hit.cor = cor;
        return true;
    }

    // Getters para o ponto e a normal do plano
    Ponto getPonto() const { return ponto; }
    Vetor getNormal() const { return normal; }
    Cor getCor() const { return cor; }

    bool intersecaoComPlano(const Reta& reta, HitRecord& hit) const {
        return intersectar(reta, 0.0, std::numeric_limits<double>::max(), hit);
    }

private:
    Ponto ponto;
    Vetor normal;
    Cor cor;
};

#endif