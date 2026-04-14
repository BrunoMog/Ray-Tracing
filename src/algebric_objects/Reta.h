#ifndef RETAHEADER
#define RETAHEADER
#include "Vetor.h"
#include "Ponto.h"

class Reta{
public:
    Reta(const Ponto& origem, const Vetor& direcao) : origem(origem), direcao(direcao.normalizado()) {}

    // Getters para a origem e a direção da reta
    Ponto getOrigem() const { return origem; }
    Vetor getDirecao() const { return direcao; }

private:
    Ponto origem;
    Vetor direcao;
};

#endif