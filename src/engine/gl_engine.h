#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <vector>

#include "utils/compute.h"
#include "base_engine.h"

class RenderEngine : public GLEngine {
    public:
        void init_resources();
        void render(std::vector<Model>& objs);
        void handleImGui();
    
    private:
        ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
        std::string path;

        float startTime;
        AllocatedBuffer planeBuffer;
        unsigned int planeTexture;

        AllocatedBuffer cubemapBuffer;
        unsigned int cubemapTexture;

        AllocatedBuffer quadBuffer;
        
        unsigned int depthFBO;
        unsigned int depthMap;

        unsigned int depthCubemaps[4];
        int shadowHeight = 2048, shadowWidth = 2048;

        float cameraNearPlane = 0.1f;
        float cameraFarPlane = 100.0f;
        int depthMapResolution = 2048;
        unsigned int lightDepthMaps;
        unsigned int dirDepthFBO;

        unsigned int matricesUBO;
        std::vector<float> shadowCascadeLevels = { cameraFarPlane / 50.0f, cameraFarPlane / 25.0f, cameraFarPlane / 10.0f, cameraFarPlane / 2.0f };

        std::vector<GLuint> visualizerVAOs;
        std::vector<GLuint> visualizerVBOs;
        std::vector<GLuint> visualizerEBOs;

        Shader pipeline;
        Shader mapPipeline;
        Shader cascadeMapPipeline;
        Shader depthCubemapPipeline;

        Shader debugCascadePipeline;
        std::vector<glm::mat4> lightMatricesCache;
        Shader debugDepthPipeline;
        int debugLayer = 0;
        bool showQuad = false;
        int numCulled = 0;

        PointLight pointLights[4];
        DirLight directionLight;

        void checkFrustum(std::vector<Model> &objs);
        void renderScene(std::vector<Model> &objs, Shader& shader, bool skipTextures = false);

        void drawCascadeVolumeVisualizers(const std::vector<glm::mat4>& lightMatrices, Shader* shader);

        std::vector<glm::mat4> getLightSpaceMatrices();
        glm::mat4 getLightSpaceMatrix(float nearPlane, float farPlane);
        std::vector<glm::vec4> getFrustumCornerWorldSpace(const glm::mat4& proj, const glm::mat4& view);
};