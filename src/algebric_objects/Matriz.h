#ifndef MATRIZHEADER
#define MATRIZHEADER

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <array>

#include "Ponto.h"
#include "Vetor.h"

class Matriz{
public:
    Matriz() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                dados[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    Matriz(const double valores[4][4]) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                dados[i][j] = valores[i][j];
            }
        }
    }

    static Matriz identidade() {
        return Matriz();
    }

    static Matriz translacao(double dx, double dy, double dz) {
        Matriz t = Matriz::identidade();
        t.dados[0][3] = dx;
        t.dados[1][3] = dy;
        t.dados[2][3] = dz;
        return t;
    }

    static Matriz escala(double sx, double sy, double sz) {
        Matriz s = Matriz::identidade();
        s.dados[0][0] = sx;
        s.dados[1][1] = sy;
        s.dados[2][2] = sz;
        return s;
    }

    static Matriz rotacaoX(double anguloRad) {
        Matriz r = Matriz::identidade();
        const double c = std::cos(anguloRad);
        const double s = std::sin(anguloRad);
        r.dados[1][1] = c;
        r.dados[1][2] = -s;
        r.dados[2][1] = s;
        r.dados[2][2] = c;
        return r;
    }

    static Matriz rotacaoY(double anguloRad) {
        Matriz r = Matriz::identidade();
        const double c = std::cos(anguloRad);
        const double s = std::sin(anguloRad);
        r.dados[0][0] = c;
        r.dados[0][2] = s;
        r.dados[2][0] = -s;
        r.dados[2][2] = c;
        return r;
    }

    static Matriz rotacaoZ(double anguloRad) {
        Matriz r = Matriz::identidade();
        const double c = std::cos(anguloRad);
        const double s = std::sin(anguloRad);
        r.dados[0][0] = c;
        r.dados[0][1] = -s;
        r.dados[1][0] = s;
        r.dados[1][1] = c;
        return r;
    }

    static Matriz rotacao(std::array<double, 3> angulosRad) {
        Matriz rx = rotacaoX(angulosRad[0]);
        Matriz ry = rotacaoY(angulosRad[1]);
        Matriz rz = rotacaoZ(angulosRad[2]);
        return rz * ry * rx;
    }

    double at(int linha, int coluna) const {
        validarIndice(linha, coluna);
        return dados[linha][coluna];
    }

    void set(int linha, int coluna, double valor) {
        validarIndice(linha, coluna);
        dados[linha][coluna] = valor;
    }

    Matriz operator*(const Matriz& outra) const {
        Matriz resultado;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                double acumulado = 0.0;
                for (int k = 0; k < 4; ++k) {
                    acumulado += dados[i][k] * outra.dados[k][j];
                }
                resultado.dados[i][j] = acumulado;
            }
        }

        return resultado;
    }

    Vetor transformarVetor(const Vetor& v) const {
        const double x = dados[0][0] * v.getX() + dados[0][1] * v.getY() + dados[0][2] * v.getZ();
        const double y = dados[1][0] * v.getX() + dados[1][1] * v.getY() + dados[1][2] * v.getZ();
        const double z = dados[2][0] * v.getX() + dados[2][1] * v.getY() + dados[2][2] * v.getZ();
        return Vetor(x, y, z);
    }

    Vetor transformarNormal(const Vetor& n) const {
        const double a00 = dados[0][0], a01 = dados[0][1], a02 = dados[0][2];
        const double a10 = dados[1][0], a11 = dados[1][1], a12 = dados[1][2];
        const double a20 = dados[2][0], a21 = dados[2][1], a22 = dados[2][2];

        const double det =
            a00 * (a11 * a22 - a12 * a21) -
            a01 * (a10 * a22 - a12 * a20) +
            a02 * (a10 * a21 - a11 * a20);

        if (std::abs(det) < 1e-12) {
            return transformarVetor(n);
        }

        const double invDet = 1.0 / det;

        const double inv00 =  (a11 * a22 - a12 * a21) * invDet;
        const double inv01 = -(a01 * a22 - a02 * a21) * invDet;
        const double inv02 =  (a01 * a12 - a02 * a11) * invDet;
        const double inv10 = -(a10 * a22 - a12 * a20) * invDet;
        const double inv11 =  (a00 * a22 - a02 * a20) * invDet;
        const double inv12 = -(a00 * a12 - a02 * a10) * invDet;
        const double inv20 =  (a10 * a21 - a11 * a20) * invDet;
        const double inv21 = -(a00 * a21 - a01 * a20) * invDet;
        const double inv22 =  (a00 * a11 - a01 * a10) * invDet;

        const double x = inv00 * n.getX() + inv10 * n.getY() + inv20 * n.getZ();
        const double y = inv01 * n.getX() + inv11 * n.getY() + inv21 * n.getZ();
        const double z = inv02 * n.getX() + inv12 * n.getY() + inv22 * n.getZ();

        return Vetor(x, y, z);
    }

    Ponto transformarPonto(const Ponto& p) const {
        const double x = dados[0][0] * p.getX() + dados[0][1] * p.getY() + dados[0][2] * p.getZ() + dados[0][3];
        const double y = dados[1][0] * p.getX() + dados[1][1] * p.getY() + dados[1][2] * p.getZ() + dados[1][3];
        const double z = dados[2][0] * p.getX() + dados[2][1] * p.getY() + dados[2][2] * p.getZ() + dados[2][3];
        const double w = dados[3][0] * p.getX() + dados[3][1] * p.getY() + dados[3][2] * p.getZ() + dados[3][3];

        if (w == 0.0) {
            return Ponto(x, y, z);
        }

        return Ponto(x / w, y / w, z / w);
    }

    Vetor operator*(const Vetor& v) const {
        return transformarVetor(v);
    }

    Ponto operator*(const Ponto& p) const {
        return transformarPonto(p);
    }


    friend std::ostream& operator<<(std::ostream& os, const Matriz& m) {
        for (int i = 0; i < 4; ++i) {
            os << "[";
            for (int j = 0; j < 4; ++j) {
                os << m.dados[i][j];
                if (j < 3) {
                    os << ", ";
                }
            }
            os << "]";
            if (i < 3) {
                os << "\n";
            }
        }
        return os;
    }

private:
    double dados[4][4];

    static void validarIndice(int linha, int coluna) {
        if (linha < 0 || linha >= 4 || coluna < 0 || coluna >= 4) {
            throw std::out_of_range("Indice de Matriz fora do intervalo [0, 3].");
        }
    }
};

#endif
