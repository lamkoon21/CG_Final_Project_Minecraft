#ifndef OPENGL_ENGINE_RENDERER_H
#define OPENGL_ENGINE_RENDERER_H


#include <glm/ext.hpp>
#include <queue>
#include "header/world/world.h"
#include "header/camera/camera.h"
#include "header/shader/shader.h"
#include "header/texture/texture.h"
#include "header/chunk/chunk.h"
#include "header/ui/ui.h"


class Renderer {
public:
    Renderer() {}
    Renderer(unsigned int* VBO, Camera* camera, Character* player, const unsigned int& SCR_WIDTH, const unsigned int& SCR_HEIGHT);
    glm::mat4 projection;
    Camera* camera;
    Shader lightingShader;
    Shader skyboxShader;
    Shader uiShader;
    unsigned int* VBO;
    unsigned int VAO;
    Character* player;
    int screenWidth;
    int screenHeight;

    void SetupGL();
    void RenderSkyBox(Skybox* skybox);
    void RenderCharacter(Character* characer);
    void RenderChunk(Chunk* chunk);
    void RenderWorld(World* world);
    void RenderUI(UI* ui, Character* player);
    void SetScreenSize(int screenWidth, int screenHeight);
    void Render();
};


Renderer::Renderer(unsigned int* VBO, Camera* camera, Character* player, const unsigned int& SCR_WIDTH, const unsigned int& SCR_HEIGHT) {
    glGenVertexArrays(1, VBO);
    this->VBO = VBO;
    glGenVertexArrays(1, &VAO);
    this->camera = camera;
    this->player = player;
    this->projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 150.0f);
    lightingShader.setShader("shader/vertex.glsl", "shader/fragment.glsl");
    skyboxShader.setShader("shader/vertex_skybox.glsl", "shader/fragment_skybox.glsl");
    uiShader.setShader("shader/vertex_ui.glsl", "shader/fragment_ui.glsl");
    glGenBuffers(1, VBO);
    screenWidth = SCR_WIDTH;
    screenHeight = SCR_HEIGHT;
}


void Renderer::SetupGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::SetScreenSize(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}


void Renderer::RenderCharacter(Character* character)
{
    if (character == nullptr) return;

    UseTexture("character");
    lightingShader.use();

    lightingShader.setVec3("lightPos", 0.0f, 256.0f, 0.0f);
    lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // view/projection transformations
    lightingShader.setMat4("projection", projection);
    lightingShader.setVec3("viewPos", camera->Position);
    lightingShader.setMat4("view", player->GetViewMatrix());

    character->Render(&lightingShader);
    //character->RenderCollideBox(&lightingShader);

    UseTexture("block_atlas");
    character->RenderBlock(&lightingShader);
}


void Renderer::RenderChunk(Chunk* chunk) {
    if (chunk->vertices.size() == 0) return;

    lightingShader.use();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // bind to buffer
    glBufferData(GL_ARRAY_BUFFER, chunk->vertices.size() * sizeof(float), &chunk->vertices[0], GL_STATIC_DRAW);

    // Textures
    UseTexture("block_atlas");
    
    // light properties
    lightingShader.setVec3("lightPos", 0.0f, 256.0f, 0.0f);
    lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // view/projection transformations
    lightingShader.setMat4("projection", projection);
    lightingShader.setVec3("viewPos", camera->Position);
    lightingShader.setMat4("view", player->GetViewMatrix());

    // world transformation
    lightingShader.setMat4("model", glm::mat4(1.0f));

    int block_cnt = chunk->vertices.size() / 8;
    glDrawArrays(GL_TRIANGLES, 0, block_cnt);
    
}


void Renderer::RenderSkyBox(Skybox* skybox)
{
    glDepthFunc(GL_LEQUAL);
    UseTexture("skybox");
    skyboxShader.use();
    skyboxShader.setMat4("view", glm::mat3(player->GetViewMatrix()));
    skyboxShader.setMat4("projection", projection);

    skybox->Render();
    glDepthFunc(GL_LESS);
}


void Renderer::RenderWorld(World* world)
{
    int chunk_cnt = world->activeChunks.size();
    for (int i = 0; i < chunk_cnt; ++i)
        RenderChunk(world->activeChunks[i]);

    RenderSkyBox(&world->skybox);
}

void Renderer::RenderUI(UI* ui, Character* player)
{
    uiShader.use();
    glEnable(GL_SCISSOR_TEST);
    UseTexture("item_ui");
    ui->Render(screenWidth, screenHeight);
    UseTexture("select_item_ui");
    ui->Render2(screenWidth, screenHeight, player->block_num);
    glDisable(GL_SCISSOR_TEST);
}

void Renderer::Render() {
    
}


#endif
