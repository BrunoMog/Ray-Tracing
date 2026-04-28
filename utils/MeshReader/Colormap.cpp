#include "Colormap.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

MaterialProperties::MaterialProperties()
    : kd(0, 0, 0), ks(0, 0, 0), ka(0, 0, 0), kr(0, 0, 0), ke(0, 0, 0), kt(0, 0, 0), ns(0), ni(0), d(0) {}

colormap::colormap() = default;

colormap::colormap(const std::string& input) {
    std::ifstream mtlFile(input);

    if (!mtlFile.is_open()) {
        std::cerr << "erro abrindo arquivo cores.mtl\n";
        return;
    }

    std::string line;
    std::string currentMaterial;

    while (std::getline(mtlFile, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "newmtl") {
            iss >> currentMaterial;
            if (!currentMaterial.empty()) {
                mp[currentMaterial] = MaterialProperties();
            }
        } else if (keyword == "Kd") {
            double kdR, kdG, kdB;
            iss >> kdR >> kdG >> kdB;
            if (!currentMaterial.empty()) {
                mp[currentMaterial].kd = Vetor(kdR, kdG, kdB);
            }
        } else if (keyword == "Ks") {
            double ksR, ksG, ksB;
            iss >> ksR >> ksG >> ksB;
            if (!currentMaterial.empty()) {
                mp[currentMaterial].ks = Vetor(ksR, ksG, ksB);
            }
        } else if (keyword == "Ke") {
            double keR, keG, keB;
            iss >> keR >> keG >> keB;
            if (!currentMaterial.empty()) {
                mp[currentMaterial].ke = Vetor(keR, keG, keB);
            }
        } else if (keyword == "Kr") {
            double krR, krG, krB;
            iss >> krR >> krG >> krB;
            if (!currentMaterial.empty()) {
                mp[currentMaterial].kr = Vetor(krR, krG, krB);
            }
        } else if (keyword == "Ka") {
            double kaR, kaG, kaB;
            iss >> kaR >> kaG >> kaB;
            if (!currentMaterial.empty()) {
                mp[currentMaterial].ka = Vetor(kaR, kaG, kaB);
            }
        } else if (keyword == "Ns") {
            iss >> mp[currentMaterial].ns;
        } else if (keyword == "Ni") {
            iss >> mp[currentMaterial].ni;
        } else if (keyword == "d") {
            iss >> mp[currentMaterial].d;
        }
    }
}

Vetor colormap::getColor(const std::string& s) const {
    const auto it = mp.find(s);
    if (it != mp.end()) {
        return it->second.kd;
    }

    std::cerr << "Error: cor " << s << " indefinida no arquivo .mtl\n";
    return Vetor(0, 0, 0);
}

MaterialProperties colormap::getMaterialProperties(const std::string& s) const {
    const auto it = mp.find(s);
    if (it != mp.end()) {
        return it->second;
    }

    std::cerr << "Error: Cor " << s << " indefinida no arquivo .mtl\n";
    return MaterialProperties();
}
