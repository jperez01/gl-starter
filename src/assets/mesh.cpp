#include "mesh.h"

#include <glm/gtx/quaternion.hpp>

void Mesh::calcInterpolatedScaling(aiVector3D& out, float animationTicks, const aiNodeAnim* nodeAnim) {
    if (nodeAnim->mNumScalingKeys == 1) {
        out = nodeAnim->mScalingKeys[0].mValue;
        return;
    }

    unsigned int scalingIndex = 0;
    for (unsigned int i = 0; i < nodeAnim->mNumScalingKeys - 1; i++) {
        float t = nodeAnim->mScalingKeys[i+1].mTime;
        if (animationTicks < t)  {
            scalingIndex = i;
            break;
        }
    }
    unsigned int nextScalingIndex = scalingIndex + 1;

    float t1 = nodeAnim->mScalingKeys[scalingIndex].mTime,
        t2 = nodeAnim->mScalingKeys[nextScalingIndex].mTime;

    float deltaTime = t2 - t1;
    float factor = (animationTicks - t1) / deltaTime;

    const aiVector3D& start = nodeAnim->mScalingKeys[scalingIndex].mValue,
        end = nodeAnim->mScalingKeys[nextScalingIndex].mValue;
    aiVector3D delta = end - start;
    out = start + factor * delta;
}

void Mesh::calcInterpolatedRotation(aiQuaternion& out, float animationTicks, const aiNodeAnim* nodeAnim) {
    if (nodeAnim->mNumRotationKeys == 1) {
        out = nodeAnim->mRotationKeys[0].mValue;
        return;
    }

    unsigned int rotationIndex = 0;
    for (unsigned int i = 0; i < nodeAnim->mNumRotationKeys - 1; i++) {
        float t = nodeAnim->mRotationKeys[i+1].mTime;
        if (animationTicks < t)  {
            rotationIndex = i;
            break;
        }
    }
    unsigned int nextRotationIndex = rotationIndex + 1;
    assert(nextRotationIndex < nodeAnim->mNumRotationKeys);

    float t1 = nodeAnim->mRotationKeys[rotationIndex].mTime,
        t2 = nodeAnim->mRotationKeys[nextRotationIndex].mTime;

    float deltaTime = t2 - t1;
    float factor = (animationTicks - t1) / deltaTime;

    const aiQuaternion& start = nodeAnim->mRotationKeys[rotationIndex].mValue,
        end = nodeAnim->mRotationKeys[nextRotationIndex].mValue;

    aiQuaternion::Interpolate(out, start, end, factor);
    out.Normalize();
}

void Mesh::calcInterpolatedPosition(aiVector3D& out, float animationTicks, const aiNodeAnim* nodeAnim) {
    if (nodeAnim->mNumPositionKeys == 1) {
        out = nodeAnim->mPositionKeys[0].mValue;
        return;
    }

    unsigned int positionIndex = 0;
    for (unsigned int i = 0; i < nodeAnim->mNumPositionKeys - 1; i++) {
        float t = nodeAnim->mPositionKeys[i+1].mTime;
        if (animationTicks < t)  {
            positionIndex = i;
            break;
        }
    }
    unsigned int nextPositionIndex = positionIndex + 1;

    float t1 = nodeAnim->mPositionKeys[positionIndex].mTime,
        t2 = nodeAnim->mPositionKeys[nextPositionIndex].mTime;

    float deltaTime = t2 - t1;
    float factor = (animationTicks - t1) / deltaTime;

    const aiVector3D& start = nodeAnim->mPositionKeys[positionIndex].mValue,
        end = nodeAnim->mPositionKeys[nextPositionIndex].mValue;
    aiVector3D delta = end - start;
    out = start + factor * delta;
}

void Mesh::getBoneTransforms(float time, const aiScene* scene,
    std::vector<NodeData>& nodeData, int animationIndex) {
    const aiAnimation* animation = scene->mAnimations[animationIndex];

    float ticksPerSecond = animation->mTicksPerSecond != 0
        ? animation->mTicksPerSecond : 25.0f;
    float timeInTicks = time * ticksPerSecond;
    float animationTimeTicks = fmod(timeInTicks, animation->mDuration);

    glm::mat4 identity(1.0f);

    for (int i = 0; i < nodeData.size(); i++) {
        NodeData& node = nodeData[i];
        const aiNodeAnim* nodeAnim = findNodeAnim(animation, node.name);
        glm::mat4 totalTransform = node.originalTransform;

        if (nodeAnim) {
            aiVector3D scaling;
            calcInterpolatedScaling(scaling, animationTimeTicks, nodeAnim);
            glm::mat4 scalingMatrix = glm::scale(identity, glm::vec3(scaling.x, scaling.y, scaling.z));

            aiQuaternion rotationQ;
            calcInterpolatedRotation(rotationQ, animationTimeTicks, nodeAnim);
            glm::quat rotateQ(rotationQ.w, rotationQ.x, rotationQ.y, rotationQ.z);
            glm::mat4 rotationMatrix = glm::toMat4(rotateQ);

            aiVector3D translation;
            calcInterpolatedPosition(translation, animationTimeTicks, nodeAnim);
            glm::mat4 translationMatrix = glm::translate(identity, glm::vec3(translation.x, translation.y, translation.z));

            totalTransform = translationMatrix * rotationMatrix * scalingMatrix;
        }

        glm::mat4 parentTrasform = node.parentIndex == -1 ? identity : nodeData[node.parentIndex].transformation;
        node.transformation = parentTrasform * totalTransform;

        if (boneName_To_Index.find(node.name) != boneName_To_Index.end()) {
            unsigned int boneIndex = boneName_To_Index[node.name];
            bone_info[boneIndex].finalTransform = node.transformation * bone_info[boneIndex].offsetTransform;
        }
    }
}

const aiNodeAnim* Mesh::findNodeAnim(const aiAnimation* animation, const std::string nodeName) {
    for (unsigned int i = 0; i < animation->mNumChannels; i++) {
        const aiNodeAnim* nodeAnim = animation->mChannels[i];

        if (std::string(nodeAnim->mNodeName.data) == nodeName) return nodeAnim;
    }
    return nullptr;
}