#ifndef TRIANGULOHEADER
#define TRIANGULOHEADER

#include <vector>

#include "../algebric_objects/Vetor.h"
#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Reta.h"
#include "../algebric_objects/Matriz.h"
#include "../utils/Cor.h"
#include "Objeto.h"

class Triangulo : public Objeto {
public:
    Triangulo(const Ponto& p1, const Ponto& p2, const Ponto& p3,
         const Cor& cor, const Vetor& normal, const std::vector<Vetor>& normais_vertices);

    bool intersectar(const Reta& reta, double tMin, double tMax, HitRecord& hit) const override;
    
    void aplicarTransformacao(const Matriz& transformacao) override;

    Ponto getP1() const;
    Ponto getP2() const;
    Ponto getP3() const;
    Cor getCor() const;
    Vetor getNormal() const;
    Vetor getV1() const;
    Vetor getV2() const;
    std::vector<Vetor> getNormaisVertices() const;

    bool intersecaoComTriangulo(const Reta& reta, HitRecord& hit) const;

private:
    Ponto p1, p2, p3;
    Vetor v1, v2, normal;
    Cor cor;
    std::vector<Vetor> normais_vertices;
};

#endif