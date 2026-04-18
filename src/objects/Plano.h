#ifndef PLANOHEADER
#define PLANOHEADER

#include "../algebric_objects/Vetor.h"
#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Reta.h"
#include "../algebric_objects/Matriz.h"
#include "../utils/Cor.h"
#include "Objeto.h"

class Plano : public Objeto {
public:
    Plano(const Ponto& ponto, const Vetor& normal, const Cor& cor);

    bool intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const override;

    void aplicarTransformacao(const Matriz& transformacao) override;
    
    Ponto getPonto() const;
    Vetor getNormal() const;
    Cor getCor() const;

    bool intersecaoComPlano(const Reta& reta, HitRecord& hit) const;

private:
    Ponto ponto;
    Vetor normal;
    Cor cor;
};

#endif