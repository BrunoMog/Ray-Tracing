#ifndef CORHEADER
#define CORHEADER

#include <algorithm>
#include <cmath>
#include <ostream>

#include "../algebric_objects/Vetor.h"

class Cor {
public:
    Cor() : r(0.0), g(0.0), b(0.0) {}
    Cor(double r, double g, double b) : r(clamp01(r)), g(clamp01(g)), b(clamp01(b)) {}

    static Cor preto() { return Cor(0.0, 0.0, 0.0); }

    double R() const { return r; }
    double G() const { return g; }
    double B() const { return b; }

    Cor operator+(const Cor& c) const {
        return Cor(r + c.r, g + c.g, b + c.b);
    }
    Cor operator*(double s) const {
        return Cor(r * s, g * s, b * s);
    }
    double operator*(Vetor s) const {
        return r * s.getX() + g * s.getY() + b * s.getZ();
    }
    double operator*(Cor s) const {
        return r * s.R() + g * s.G() + b * s.B();
    }
    
    int R255() const { return to255(r); }
    int G255() const { return to255(g); }
    int B255() const { return to255(b); }

private:
    double r, g, b;

    static double clamp01(double x) {
        return std::max(0.0, std::min(1.0, x));
    }

    static int to255(double x) {
        return static_cast<int>(std::round(clamp01(x) * 255.0));
    }
};

#endif