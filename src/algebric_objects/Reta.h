#ifndef RETAHEADER
#define RETAHEADER

#include <stdexcept>

#include "Vetor.h"
#include "Ponto.h"

class Reta{
public:
    Reta(const Ponto& origem, const Vetor& direcao) : origem(origem), direcao(direcao.normalizado()) {
        if (direcao.norma() == 0) {
            throw std::invalid_argument("A direção da reta não pode ser o vetor nulo.");
        }
    }

    // Getters para a origem e a direção da reta
    Ponto getOrigem() const { return origem; }
    Vetor getDirecao() const { return direcao; }

private:
    Ponto origem;
    Vetor direcao;
};

#endif