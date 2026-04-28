#ifndef ESFERAHEADER
#define ESFERAHEADER

#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Vetor.h"
#include "../algebric_objects/Reta.h"
#include "../algebric_objects/Matriz.h"
#include "../utils/Cor.h"
#include "Objeto.h"

class Esfera : public Objeto {
public:
    Esfera(const Ponto& centro, double raio, const Cor& cor);

    bool intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const override;

    void aplicarTransformacao(const Matriz& transformacao) override;

    Ponto getCentro() const;
    double getRaio() const;
    Cor getCor() const;

    bool intersecaoComEsfera(const Reta& reta, HitRecord& hit) const;

private:
    Ponto centro;
    double raio;
    Cor cor;
};

#endif