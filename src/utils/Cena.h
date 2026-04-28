#ifndef CENAHEADER
#define CENAHEADER

#include <memory>
#include <vector>
#include "Cor.h"
#include "../objects/Objeto.h"

class Cena {
public:
    explicit Cena(const Cor& cor_ambiente);

    void adicionarObjeto(std::unique_ptr<Objeto> objeto);
    void adicionarTransformacao(const Matriz& transformacao);
    bool intersectar(const Reta& raio, double tMin, double tMax, HitRecord& hitMaisProximo) const;
    void aplicarTransformacao();
    Cor getCorAmbiente() const;
    bool isTransformacaoAplicada() const;

private:
    Cor cor_ambiente;
    std::vector<std::unique_ptr<Objeto>> objetos;
    Matriz transformacao;
    bool transformacaoAplicada = false;
};

#endif