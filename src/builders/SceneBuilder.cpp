#include "SceneBuilder.h"

#include <array>
#include <cctype>
#include <memory>
#include <string>
#include <vector>

#include "../objects/Esfera.h"
#include "../objects/MalhaTriangulos.h"
#include "../objects/Plano.h"
#include "../../utils/MeshReader/ObjReader.hpp"

namespace SceneBuilder {

Cor toCor(const ColorData& colorData) {
    return Cor(colorData.r, colorData.g, colorData.b);
}

namespace {

std::string toLowerCopy(std::string value) {
    for (char& c : value) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return value;
}

Matriz composeExtraTransform(const ObjectData& objectData) {
    Matriz composed = Matriz::identidade();

    for (const auto& transformData : objectData.transforms) {
        const std::string type = toLowerCopy(transformData.tType);
        Matriz current = Matriz::identidade();

        if (type == "translation" || type == "translate") {
            current = Matriz::translacao(transformData.data.getX(), transformData.data.getY(), transformData.data.getZ());
        } else if (type == "scaling" || type == "scale") {
            current = Matriz::escala(transformData.data.getX(), transformData.data.getY(), transformData.data.getZ());
        } else if (type == "rotation" || type == "rotate") {
            current = Matriz::rotacao({
                transformData.data.getX(),
                transformData.data.getY(),
                transformData.data.getZ()
            });
        } else {
            continue;
        }

        // Apply transforms in the same sequence they appear in JSON.
        composed = current * composed;
    }

    return composed;
}

} // namespace

std::unique_ptr<Objeto> buildObject(const ObjectData& objectData, bool aplicarTransformacoes) {
    const Cor materialColor = toCor(objectData.material.color);
    std::unique_ptr<Objeto> objeto;

    if (objectData.objType == "sphere") {
        const Ponto center = objectData.relativePos;
        const double radius = objectData.numericData.at("radius");
        objeto = std::make_unique<Esfera>(center, radius, materialColor);
    }

    if (objectData.objType == "plane") {
        const Ponto point = objectData.relativePos;
        const Vetor normal = objectData.vetorPointData.at("normal");
        objeto = std::make_unique<Plano>(point, normal, materialColor);
    }

    if (objectData.objType == "mesh") {
        const auto pathIt = objectData.otherProperties.find("path");
        if (pathIt == objectData.otherProperties.end()) {
            return nullptr;
        }

        objReader meshReader(pathIt->second);

        std::vector<Ponto> vertices = meshReader.getVertices();
        const std::vector<FaceData> faces = meshReader.getFaces();
        const std::vector<Vetor> meshNormals = meshReader.getNormals();

        if (vertices.empty() || faces.empty()) {
            return nullptr;
        }

        const Vetor translation = objectData.relativePos - Ponto(0, 0, 0);
        if (translation.norma() > 0.0) {
            for (auto& vertex : vertices) {
                vertex = vertex + translation;
            }
        }

        std::vector<std::array<int, 3>> indices;
        std::vector<Vetor> triangleNormals;
        std::vector<Vetor> vertexNormals(vertices.size(), Vetor(0, 0, 0));
        std::vector<size_t> vertexNormalCount(vertices.size(), 0);

        indices.reserve(faces.size());
        triangleNormals.reserve(faces.size());

        for (const auto& face : faces) {
            const std::array<int, 3> idx = {
                face.verticeIndice[0],
                face.verticeIndice[1],
                face.verticeIndice[2]
            };

            indices.push_back(idx);

            Vetor faceNormal;
            const bool hasObjNormals =
                !meshNormals.empty() &&
                face.normalIndice[0] >= 0 &&
                face.normalIndice[1] >= 0 &&
                face.normalIndice[2] >= 0 &&
                static_cast<size_t>(face.normalIndice[0]) < meshNormals.size() &&
                static_cast<size_t>(face.normalIndice[1]) < meshNormals.size() &&
                static_cast<size_t>(face.normalIndice[2]) < meshNormals.size();

            if (hasObjNormals) {
                faceNormal = (
                    meshNormals[face.normalIndice[0]] +
                    meshNormals[face.normalIndice[1]] +
                    meshNormals[face.normalIndice[2]]
                ) * (1.0 / 3.0);
            } else {
                const Vetor edge1 = vertices[idx[1]] - vertices[idx[0]];
                const Vetor edge2 = vertices[idx[2]] - vertices[idx[0]];
                faceNormal = edge1 % edge2;
            }

            if (faceNormal.norma() == 0.0) {
                faceNormal = Vetor(0, 1, 0);
            } else {
                faceNormal = faceNormal.normalizado();
            }

            triangleNormals.push_back(faceNormal);

            for (const int vertexIndex : idx) {
                if (vertexIndex >= 0 && static_cast<size_t>(vertexIndex) < vertexNormals.size()) {
                    vertexNormals[vertexIndex] = vertexNormals[vertexIndex] + faceNormal;
                    vertexNormalCount[vertexIndex]++;
                }
            }
        }

        for (size_t i = 0; i < vertexNormals.size(); ++i) {
            if (vertexNormalCount[i] == 0) {
                vertexNormals[i] = Vetor(0, 1, 0);
                continue;
            }

            vertexNormals[i] = (vertexNormals[i] * (1.0 / static_cast<double>(vertexNormalCount[i]))).normalizado();
        }

        objeto = std::make_unique<MalhaTriangulos>(
            indices.size(),
            vertices.size(),
            vertices,
            indices,
            triangleNormals,
            vertexNormals,
            materialColor
        );
    }

    if (!objeto) {
        return nullptr;
    }

    if (aplicarTransformacoes) {
        const Matriz transformacaoObjeto = composeExtraTransform(objectData);
        objeto->aplicarTransformacao(transformacaoObjeto);
    }

    return objeto;
}

Cena buildScene(const SceneData& sceneData, bool aplicarTransformacoes) {
    Cena cena(toCor(sceneData.globalLight.color));

    for (const auto& objectData : sceneData.objects) {
        std::unique_ptr<Objeto> objeto = buildObject(objectData, aplicarTransformacoes);
        if (objeto) {
            cena.adicionarObjeto(std::move(objeto));
        }
    }

    return cena;
}

Camera buildCamera(const CameraData& cameraData) {
    return Camera(
        cameraData.lookfrom,
        cameraData.lookat,
        cameraData.upVector,
        cameraData.screen_distance,
        cameraData.image_width,
        cameraData.image_height
    );
}

} // namespace SceneBuilder