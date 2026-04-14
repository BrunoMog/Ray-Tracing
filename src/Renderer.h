#ifndef RENDERERHEADER
#define RENDERERHEADER

#include <iostream>
#include <limits>
#include "utils/Camera.h"
#include "utils/Cena.h"
#include "algebric_objects/Reta.h"

class Renderer {
public:
	Renderer(const Camera& camera, const Cena& cena, int largura, int altura)
		: camera(camera), cena(cena), largura(largura), altura(altura) {}

	void renderPPM(std::ostream& out) const {
		out << "P3\n";
		out << largura << ' ' << altura << "\n";
		out << 255 << "\n";

		for (int j = 0; j < altura; ++j) {
			for (int i = 0; i < largura; ++i) {
				Vetor direcaoPixel = camera.calcularPosicaoPixel(i, j);
				Reta raio(camera.getLookfrom(), direcaoPixel);

				HitRecord hit;
				Cor corPixel = Cor::preto();

				if (cena.intersectar(raio, 0.001, std::numeric_limits<double>::max(), hit)) {
					corPixel = hit.cor;
				}

				out << corPixel.R255() << ' ' << corPixel.G255() << ' ' << corPixel.B255() << '\n';
			}
		}
	}

private:
	const Camera& camera;
	const Cena& cena;
	int largura;
	int altura;
};

#endif
