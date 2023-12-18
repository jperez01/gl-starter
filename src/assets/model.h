#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "utils/material.h"
#include "assets/mesh.h"

enum FileType {
    GLTF = 0, OBJ
};

bool textureFromMemory(void* data, unsigned int bufferSize, Texture& texture);
bool textureFromFile(const char *path, const std::string &directory, Texture& texture, bool gamma = false);
glm::mat4 convertMatrix(const aiMatrix4x4& aiMat);

class Model {
    public:
        std::unordered_map<std::string, Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::vector<NodeData> nodes;

        std::vector<Material> materials_loaded;

        std::string directory;
        bool gammaCorrection;
        glm::mat4 model_matrix;
        BoundingBox aabb;
        bool shouldDraw = true;
        int numAnimations = 0;

        const aiScene* scene;

        Model();
        explicit Model(std::string path, FileType type = OBJ);
    private:
        void loadInfo(std::string path, FileType type);

        void processNode(aiNode *node, const aiScene *scene, int parentIndex = -1);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        void readNodeHierarchy(const aiNode* node, Mesh& mesh);

        std::vector<std::string> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};