#ifndef OBJETOHEADER
#define OBJETOHEADER

#include "../algebric_objects/Reta.h"
#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Vetor.h"
#include "../utils/Cor.h"

struct HitRecord {
    double t;
    Ponto ponto;
    Vetor normal;
    Cor cor;
};

class Objeto {
public:
    virtual ~Objeto() = default;
    virtual bool intersectar(const Reta& raio, double tMin, double tMax, HitRecord& hit) const = 0;
};

#endif