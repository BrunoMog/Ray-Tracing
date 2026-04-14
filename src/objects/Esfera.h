#ifndef ESFERAHEADER
#define ESFERAHEADER

#include <cmath>
#include <limits>
#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Vetor.h"
#include "Objeto.h"

class Esfera : public Objeto {
public:
    Esfera(const Ponto& centro, double raio, const Cor& cor) 
        : centro(centro), raio(raio), cor(cor) {}
    
    bool intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const override {
        Vetor oc = reta.getOrigem() - centro;
        double a = reta.getDirecao() * reta.getDirecao();
        double b = 2.0 * (oc * reta.getDirecao());
        double c = (oc * oc) - (raio * raio);
        double discriminante = b*b - 4*a*c;

        if (discriminante < 0) {
            return false;
        }

        double raiz = std::sqrt(discriminante);
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

    // Getters
    Ponto getCentro() const { return centro; }
    double getRaio() const { return raio; }
    Cor getCor() const { return cor; }

    bool intersecaoComEsfera(const Reta& reta, HitRecord& hit) const {
        return intersectar(reta, 0.0, std::numeric_limits<double>::max(), hit);
    }

private:
    Ponto centro;
    double raio;
    Cor cor;
};

#endif