#include "Camera.h"

#include <iostream>

Camera::Camera(const Ponto& lookfrom, const Ponto& lookat, const Vetor& up, double dist, double width, double high)
    : lookfrom(lookfrom),
      lookat(lookat),
      vetor_up(up),
      img_height(high),
      img_width(width),
      screen_distance(dist),
      aspect_ratio(0.0),
      viewport_width(0.0),
      viewport_height(0.0) {
    calcularBase();
}

void Camera::calcularBase() {
    W = (lookfrom - lookat).normalizado();
    U = (W % vetor_up).normalizado();
    V = (U % W).normalizado();
    centro_tela = (W * screen_distance) * -1.0;

    aspect_ratio = img_width / img_height;
    viewport_height = 1.0;
    viewport_width = viewport_height * aspect_ratio;
    vetor_pixel_horizontal = U * (viewport_width / img_width);
    vetor_pixel_vertical = V * (viewport_height / img_height);
}

void Camera::moverCamera(const Ponto& novo_posicao) {
    lookfrom = novo_posicao;
    calcularBase();
    screen_distance = (lookfrom - lookat).norma();
}

Vetor Camera::calcularPosicaoPixel(double x, double y) const {
    if (x < 0 || x >= img_width || y < 0 || y >= img_height) {
        std::cerr << "Coordenadas de pixel fora dos limites da imagem." << std::endl;
        return Vetor(0, 0, 0);
    }

    const double deslocamentoX = (x - img_width / 2.0);
    const double deslocamentoY = ((img_height / 2.0) - y);

    Vetor resultado = centro_tela +
                      (U * deslocamentoX * (viewport_width / img_width)) +
                      (V * deslocamentoY * (viewport_height / img_height));

    return resultado + vetor_pixel_horizontal * 0.5 + vetor_pixel_vertical * 0.5;
}

Reta Camera::gerarRaioPixel(double x, double y) const {
    Vetor direcaoPixel = calcularPosicaoPixel(x, y);
    return Reta(lookfrom, direcaoPixel);
}

Ponto Camera::getLookfrom() const {
    return lookfrom;
}

Ponto Camera::getLookat() const {
    return lookat;
}

Ponto Camera::getLookFrom() const {
    return lookfrom;
}

Vetor Camera::getW() const {
    return W;
}

Vetor Camera::getU() const {
    return U;
}

Vetor Camera::getV() const {
    return V;
}

Vetor Camera::getUp() const {
    return vetor_up;
}

double Camera::getScreenDistance() const {
    return screen_distance;
}

double Camera::getImageWidth() const {
    return img_width;
}

double Camera::getImageHeight() const {
    return img_height;
}
