#ifndef VETORHEADER
#define VETORHEADER
#include <iostream>
#include <cmath>

class Vetor{
public:
    Vetor(double x=0, double y=0, double z=0): x(x), y(y), z(z) {}

    //Vetor + Vetor
    Vetor  operator+ (const Vetor&v) const{ 
        return Vetor(x+v.x, y+v.y, z+v.z); 
    }
    //Vetor - Vetor
    Vetor  operator- (const Vetor&v) const{ 
        return Vetor(x-v.x, y-v.y, z-v.z); 
    }
    //Dot product
    double operator* (const Vetor&v) const{ 
        return x*v.x + y*v.y + z*v.z; 
    }
    //Cross product
    Vetor operator% (const Vetor&v) const{ 
        return Vetor(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); 
    }  
    //Vector * double
    Vetor operator* (double escalar) const{ 
        return Vetor(x*escalar, y*escalar, z*escalar); 
    }
    //Norma
    double norma() const{ 
        return std::sqrt(x*x + y*y + z*z); 
    }
    //Normalização
    Vetor normalizado() const{ 
        double n = norma();
        if (n == 0) return Vetor(0, 0, 0); // Evitar divisão por zero 
        return Vetor(x/n, y/n, z/n); 
    }
    //Projeção de um vetor em outro
    Vetor projetadoEm(const Vetor& v) const {
        double escalar = (*this * v) / (v * v); // (A . B) / (B . B)
        return v * escalar; // B * escalar
    }

    // cout << Vetor
    friend std::ostream& operator<<(std::ostream& os, const Vetor &v){ 
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")T"; 
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

private:
    double x, y, z;
};

#endif