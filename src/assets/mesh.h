#pragma once
#include "utils/types.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

struct NodeData {
    glm::mat4 transformation;
    glm::mat4 originalTransform;
    std::string name;
    int parentIndex;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    size_t materialIndex;

    std::unordered_map<std::string, unsigned int> boneName_To_Index;
    std::vector<VertexBoneData> bone_data;
    std::vector<BoneInfo> bone_info;

    glm::mat4 model_matrix;
    BoundingBox aabb;

    AllocatedBuffer buffer;
    unsigned int SSBO;

    void getBoneTransforms(float time, const aiScene* scene, std::vector<NodeData>& nodeData, int animationIndex = 0);
    const aiNodeAnim* findNodeAnim(const aiAnimation* animation, const std::string nodeName);

    void calcInterpolatedScaling(aiVector3D& out, float animationTicks, const aiNodeAnim* nodeAnim);
    void calcInterpolatedRotation(aiQuaternion& out, float animationTicks, const aiNodeAnim* nodeAnim);
    void calcInterpolatedPosition(aiVector3D& out, float animationTicks, const aiNodeAnim* nodeAnim);
};
