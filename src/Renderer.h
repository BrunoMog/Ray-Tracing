#ifndef RENDERERHEADER
#define RENDERERHEADER

#include <iostream>
#include "utils/Camera.h"
#include "utils/Cena.h"

class Renderer {
public:
	Renderer(const Camera& camera, const Cena& cena, const Cena* cenaTransformada = nullptr);
	void renderPPM(std::ostream& out) const;
	void renderPPMTransformacao(std::ostream& outAntes, std::ostream& outDepois) const;

private:
	const Camera& camera;
	const Cena& cena;
	const Cena* cenaTransformada;
	int largura;
	int altura;
	void generatePPM(std::ostream& out, const Cena& cenaAlvo) const;
};

#endif
