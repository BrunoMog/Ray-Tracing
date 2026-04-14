#ifndef CAMERAHEADER
#define CAMERAHEADER

#include "algebric_objects/Vetor.h"
#include "algebric_objects/Ponto.h"

class Camera {
public:
    Camera(const Ponto& lookfrom, const Ponto& lookat, const Vetor& up, double dist, double width, double high) 
        : 
    lookfrom(lookfrom), lookat(lookat), vetor_up(up), screen_distance(dist), img_width(width), img_height(high) {
        calcularBase();
    }

    void calcularBase() {
        //Calcula os vetores base da câmera: W, U e V.
        W = (lookfrom - lookat).normalizado();
        U = (W % vetor_up).normalizado();
        V = (U % W).normalizado();
        centro_tela =  (W * screen_distance)*-1.0;
        vetor_pixel_horizontal = (U * (1.0 / img_width));
        vetor_pixel_vertical = (V * (1.0 / img_height));
    }

    void moverCamera(const Ponto& novo_posicao) {
        // Move a câmera para uma nova posição, mantendo a direção de visão.
        lookfrom = novo_posicao;
        calcularBase();
    }

    Vetor calcularPosicaoPixel(double x, double y) {
        //Calcula o vetor que aponta para o centro do pixel (x, y) na tela a partir da posição da câmera.
        if (x < 0 || x >= img_width || y < 0 || y >= img_height) {
            std::cerr << "Coordenadas de pixel fora dos limites da imagem." << std::endl;
            return Vetor(0, 0, 0);
        }
        double sentidoHorizontal, sentidoVertical, fatorHorizontal, fatorVertical;
        Vetor resultado;
        if (x < (img_width/2.0)) sentidoHorizontal = -1.0; 
        else sentidoHorizontal = 1.0;
        if (y < (img_height/2.0)) sentidoVertical = 1.0; 
        else sentidoVertical = -1.0;
        fatorHorizontal = std::abs((x - (img_width/2.0)) * vetor_pixel_horizontal.norma());
        fatorVertical = std::abs((y - (img_height/2.0)) * vetor_pixel_vertical.norma());
        resultado = centro_tela + (U * fatorHorizontal * sentidoHorizontal) + (V * fatorVertical * sentidoVertical);
        return resultado + vetor_pixel_horizontal*0.5 - vetor_pixel_vertical*0.5;

    }

    Ponto getLookfrom() const {
        return lookfrom;
    }

private:
    Ponto lookfrom;
    Ponto lookat;
    Vetor centro_tela;
    Vetor vetor_up;
    Vetor W;
    Vetor U;
    Vetor V;
    Vetor vetor_pixel_horizontal; 
    Vetor vetor_pixel_vertical; 
    double img_height;
    double img_width;
    double screen_distance;
};

#endif 