#ifndef CHARACTER_H
#define CHARACTER_H


#include "../shader/shader.h"
#include "../camera/camera.h"
#include "../objreader/objRead.h"
#include "../block/blocktype.h"


class World;


class Character
{
private:
    GLuint VAO_block, VAO_head, VAO_body, VAO_left_arm, VAO_right_arm, VAO_left_leg, VAO_right_leg;
    objRead characterReader[6];
    GLint HeadObj = characterReader[0].loadObj_normalize_center("resource/obj/character/character_head.obj");
    GLint BodyObj = characterReader[1].loadObj_normalize_center("resource/obj/character/character_body.obj");
    GLint LeftArmObj = characterReader[2].loadObj_normalize_center("resource/obj/character/character_left_arm.obj");
    GLint RightArmObj = characterReader[3].loadObj_normalize_center("resource/obj/character/character_right_arm.obj");
    GLint LeftLegObj = characterReader[4].loadObj_normalize_center("resource/obj/character/character_left_leg.obj");
    GLint RightLegObj = characterReader[5].loadObj_normalize_center("resource/obj/character/character_right_leg.obj");
    unsigned int VBO;

    const float CHARACTER_SPEED[3] = { 0.08f, 0.16f, 0.04f };
    const float MAX_SHAKE_DEG[3] = { 20.0f, 40.0f, 15.0f };
    const float ADD_SHAKE_DEG[3] = { 2.0f, 4.0f, 1.5f };
    

    glm::vec3 HeadPos;
    glm::vec3 BodyPos;
    glm::vec3 LeftArmPos;
    glm::vec3 RightArmPos;
    glm::vec3 LeftLegPos;
    glm::vec3 RightLegPos;

    float BodyYaw = 0.0f;
    float HeadPitch = 0.0f;
    float HeadYaw = 0.0f;
    int dir_front = 0;
    int dir_left = 0;

    float shake_deg = 0.0f;
    bool shake_state = true;

    int move_state = 0; // walk, run, crouch
    bool jump = false;

    float speedX = 0.0f;
    float speedY = 0.0f;
    float speedZ = 0.0f;
    const float MAX_SPEED = 10.0;
    const float GRAVITY_ACC = 9.8f;

    float box_interval = 0.3f;
    World* world;
    void PosUpdate();
    void PhysicsUpdate();
    void BlockUpdate();
    void SetBlockVertices();
    bool selectblock = false;
    glm::vec3 nextBlockPos = glm::vec3(0.0f);
    glm::vec3 selectBlockPos = glm::vec3(0.0f);
    bool mouse_left_state = false;
    bool mouse_right_state = false;
    float add_block_time = 0.0f;
    float del_block_time = 0.0f;
    BlockType blocks[9] = {
        BlockType::AIR,
        BlockType::GRASS,
        BlockType::DIRT,
        BlockType::STONE,
        BlockType::COBBLESTONE,
        BlockType::LOG_OAK,
        BlockType::PLACKS_OAK,
        BlockType::BRICK,
        BlockType::SAND,
    };
    int camera_mode = 0;
public:
    int block_num = 0;
    bool god_mode = false;
    Camera camera;
    glm::vec3 Position;
    std::vector<float> block_vertices;

    Character();
    Character(World* world);
    Character(World* world, glm::vec3 position);

    void Init();
    void RenderCollideBox(Shader* shader);
    void RenderUI(Shader* shader);
    void Render(Shader* shader);
    void MouseInput(bool left_state, bool right_state);
    void KeyboardInput(unsigned char key);
    void SpecialKeyboardInput(unsigned char key);
    void MouseWheelInput(int dir);
    void RenderBlock(Shader* shader);
    void Input();
    void Update();
    glm::mat4 GetViewMatrix();
};


#endif