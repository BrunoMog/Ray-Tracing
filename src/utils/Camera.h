#ifndef CAMERAHEADER
#define CAMERAHEADER

#include "../algebric_objects/Vetor.h"
#include "../algebric_objects/Ponto.h"
#include "../algebric_objects/Reta.h"

class Camera {
public:
    Camera(const Ponto& lookfrom, const Ponto& lookat, const Vetor& up, double dist, double width, double high);

    void calcularBase();
    void moverCamera(const Ponto& novo_posicao);
    Vetor calcularPosicaoPixel(double x, double y) const;
    Reta gerarRaioPixel(double x, double y) const;
    Ponto getLookfrom() const;

    // Getters para câmera
    Ponto getLookat() const;
    Ponto getLookFrom() const;
    Vetor getW() const;
    Vetor getU() const;
    Vetor getV() const;
    Vetor getUp() const;
    double getScreenDistance() const;
    double getImageWidth() const;
    double getImageHeight() const;

private:
    Ponto lookfrom;
    Ponto lookat;

    Vetor vetor_up;
    Vetor W;
    Vetor U;
    Vetor V;

    Vetor centro_tela;
    Vetor vetor_pixel_horizontal; 
    Vetor vetor_pixel_vertical; 

    double img_height;
    double img_width;
    double screen_distance;
    double aspect_ratio;
    double viewport_width;
    double viewport_height;
};

#endif 