#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <vector>

#include "utils/compute.h"
#include "base_engine.h"

class RenderEngine : public GLEngine {
    public:
        void init_resources() override;
    void subscribePrograms(UpdateListener& listener) override;
        void render(std::vector<Model>& objs) override;
        void handleImGui() override;
    
    private:
        ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;

        float startTime;
        AllocatedBuffer planeBuffer;
        unsigned int planeTexture;

        AllocatedBuffer cubemapBuffer;
        unsigned int cubemapTexture;

        Shader starterPipeline;

        void RenderEngine::renderScene(std::vector<Model>& objs, Shader& shader, bool skipTextures);
};