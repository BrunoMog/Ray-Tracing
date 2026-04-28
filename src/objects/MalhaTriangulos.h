#ifndef MALHATRIANGULOHEADER
#define MALHATRIANGULOHEADER

#include <array>
#include <vector>

#include "../algebric_objects/Vetor.h"
#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Reta.h"
#include "../algebric_objects/Matriz.h"
#include "../utils/Cor.h"
#include "Objeto.h"
#include "Triangulo.h"

class MalhaTriangulos : public Objeto {
public:
    MalhaTriangulos(
        size_t num_triangulos,
        size_t num_vertices,
        const std::vector<Ponto>& vertices,
        const std::vector<std::array<int, 3>>& indices,
        const std::vector<Vetor>& normais,
        const std::vector<Vetor>& normais_vertices,
        const Cor& cor
    );

    void construirTriangulos(const std::vector<Ponto>& vertices, const std::vector<std::array<int, 3>>& indices, const std::vector<Vetor>& normais, const std::vector<Vetor>& normais_vertices);

    bool intersectar(const Reta& raio, double tMin, double tMax, HitRecord& hit) const override;

    void aplicarTransformacao(const Matriz& transformacao) override;

    size_t getNumTriangulos() const;
    size_t getNumVertices() const;
    std::vector<Triangulo> getTriangulos() const;
    std::vector<Vetor> getNormais() const;
    std::vector<Vetor> getNormaisVertices() const;
    Cor getCor() const;

    bool intersecaoComMalha(const Reta& raio, HitRecord& hit) const;

private:
    size_t num_triangulos;
    size_t num_vertices;
    std::vector<Triangulo> triangulos;
    std::vector<Vetor> normais;
    std::vector<Vetor> normais_vertices;
    std::vector<Ponto> vertices;
    std::vector<std::array<int, 3>> indices;
    Cor cor;
};

#endif