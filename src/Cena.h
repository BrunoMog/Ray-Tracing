#ifndef CENAHEADER
#define CENAHEADER

#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include "utils/Cor.h"
#include "algebric_objects/Vetor.h"
#include "algebric_objects/Ponto.h"
#include "objects/Objeto.h"

class Cena {
public:
    Cena(const Cor& cor_ambiente) : cor_ambiente(cor_ambiente) {}

    void adicionarObjeto(std::unique_ptr<Objeto> objeto) {
        objetos.push_back(std::move(objeto));
    }

    bool intersectar(const Reta& raio, double tMin, double tMax, HitRecord& hitMaisProximo) const {
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

    Cor getCorAmbiente() const {
        return cor_ambiente;
    }

private:
    Cor cor_ambiente;
    std::vector<std::unique_ptr<Objeto>> objetos;
};

#endif