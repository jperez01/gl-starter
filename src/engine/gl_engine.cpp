#include "gl_engine.h"

#include <iostream>
#include <iterator>
#include <SDL.h>
#include <thread>
#include <future>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

void RenderEngine::init_resources() {
    starterPipeline = Shader("default/default.vs", "default/default.fs");

    planeBuffer = glutil::createPlane();
    planeTexture = glutil::loadTexture("../../resources/textures/wood.png");

    cubemapBuffer = glutil::createUnitCube();

    std::string cubemapPath = "../../resources/textures/skybox/";
    cubemapTexture = glutil::loadCubemap(cubemapPath);

    screenQuad.init();
}

void RenderEngine::subscribePrograms(UpdateListener& listener) {
    listener.subscribe(starterPipeline);
}


void RenderEngine::render(std::vector<Model>& objs) {
    float currentFrame = static_cast<float>(SDL_GetTicks());
    animationTime = (currentFrame - startTime) / 1000.0f;

    glm::mat4 proj = camera->getProjectionMatrix();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    checkFrustum(objs);

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glm::mat4 identity(1.0f);
    starterPipeline.use();
    starterPipeline.setMat4("model", model);
    starterPipeline.setMat4("view", view);
    starterPipeline.setMat4("projection", proj);
    screenQuad.draw();
}

void RenderEngine::renderScene(std::vector<Model>& objs, Shader& shader, bool skipTextures) {
    drawModels(objs, shader, skipTextures & SKIP_TEXTURES);

    glm::mat4 planeModel = glm::mat4(1.0f);
    planeModel = glm::translate(planeModel, glm::vec3(0.0, -2.0, 0.0));

    if (!skipTextures) {
        glBindTextureUnit(0, planeTexture);
        shader.setInt("diffuseTexture", 0);
    }
    shader.setMat4("model", planeModel);
    glBindVertexArray(planeBuffer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderEngine::handleImGui() {
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::CollapsingHeader("Start Here")) {
    }
}
