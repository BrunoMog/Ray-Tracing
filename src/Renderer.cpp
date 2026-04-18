#include "Renderer.h"

#include <limits>
#include <stdexcept>

Renderer::Renderer(const Camera& camera, const Cena& cena, const Cena* cenaTransformada)
    : camera(camera), cena(cena), cenaTransformada(cenaTransformada), largura(camera.getImageWidth()), altura(camera.getImageHeight()) {}

void Renderer::generatePPM(std::ostream& out, const Cena& cenaAlvo) const {
    out << "P3\n";
    out << largura << ' ' << altura << "\n";
    out << 255 << "\n";

    for (int j = 0; j < altura; ++j) {
        for (int i = 0; i < largura; ++i) {
            Reta raio = camera.gerarRaioPixel(i, j);

            HitRecord hit;
            Cor corPixel = Cor::preto();

            if (cenaAlvo.intersectar(raio, 0.001, std::numeric_limits<double>::max(), hit)) {
                corPixel = hit.cor;
            }

            out << corPixel.R255() << ' ' << corPixel.G255() << ' ' << corPixel.B255() << '\n';
        }
    }
}

void Renderer::renderPPM(std::ostream& out) const {
    generatePPM(out, cena);
}

void Renderer::renderPPMTransformacao(std::ostream& outAntes, std::ostream& outDepois) const {
    generatePPM(outAntes, cena);

    if (cenaTransformada == nullptr) {
        throw std::runtime_error("Renderer sem cena transformada para renderPPMTransformacao.");
    }

    generatePPM(outDepois, *cenaTransformada);
}

