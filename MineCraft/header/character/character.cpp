#include "character.h"
#include "../transform/tranform.h"
#include "../world/world.h"
#include "../chunk/chunk.h"


void Character::PosUpdate()
{
    float ds = glm::sin(glm::radians(BodyYaw));
    float dc = glm::cos(glm::radians(BodyYaw));

    HeadPos = glm::vec3(Position.x, Position.y + 1.5f, Position.z);
    BodyPos = glm::vec3(Position.x, Position.y + 0.75f, Position.z);
    LeftArmPos = glm::vec3(Position.x - 0.37501f * ds, Position.y + 1.5f, Position.z - 0.37501f * dc);
    RightArmPos = glm::vec3(Position.x + 0.37501f * ds, Position.y + 1.5f, Position.z + 0.37501f * dc);
    LeftLegPos = glm::vec3(Position.x - 0.12501f * ds, Position.y + 0.75f, Position.z - 0.12501f * dc);
    RightLegPos = glm::vec3(Position.x + 0.12501f * ds, Position.y + 0.75f, Position.z + 0.12501f * dc);
    camera.Position = glm::vec3(Position.x + 0.25001f * glm::cos(glm::radians(HeadYaw)), Position.y + 1.75f, Position.z - 0.25001f * glm::sin(glm::radians(HeadYaw)));
}

Character::Character() 
{ 
    Position = glm::vec3(0.0f);
    PosUpdate();
}

Character::Character(World* world)
{
    this->world = world;
    Position = world->GetStartPos();
    PosUpdate();
}

Character::Character(World* world, glm::vec3 position)
{
    this->world = world;
    Position = position;
    PosUpdate();
}

void Character::Init()
{
    characterReader[0].initBuffer(VAO_head);
    characterReader[1].initBuffer(VAO_body);
    characterReader[2].initBuffer(VAO_left_arm);
    characterReader[3].initBuffer(VAO_right_arm);
    characterReader[4].initBuffer(VAO_left_leg);
    characterReader[5].initBuffer(VAO_right_leg);

    glGenVertexArrays(1, &VAO_block);
    glGenBuffers(1, &VBO);
}

void Character::RenderCollideBox(Shader* shader)
{
    SRT(glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f), shader);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(Position.x - box_interval, Position.y + 0.01f, Position.z - box_interval);
    glVertex3f(Position.x - box_interval, Position.y + 0.01f, Position.z + box_interval);
    glVertex3f(Position.x + box_interval, Position.y + 0.01f, Position.z + box_interval);
    glVertex3f(Position.x + box_interval, Position.y + 0.01f, Position.z - box_interval);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(Position.x, Position.y + 0.01f, Position.z);
    glVertex3f(Position.x + 0.5f, Position.y + 0.01f, Position.z);
    glEnd();

    int x = static_cast<int>(Position.x);
    int y = static_cast<int>(Position.y);
    int z = static_cast<int>(Position.z);
    glLineWidth(6.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y + 0.01f, z);
    glVertex3f(x + 1, y + 0.01f, z);
    glVertex3f(x + 1, y + 0.01f, z + 1);
    glVertex3f(x, y + 0.01f, z + 1);
    glEnd();
}

void Character::Render(Shader* shader)
{
    SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(HeadYaw), glm::radians(HeadPitch)), HeadPos, shader);
    glBindVertexArray(VAO_head);
    glDrawArrays(GL_TRIANGLES, 0, HeadObj);

    SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(BodyYaw), 0.0f), BodyPos, shader);
    glBindVertexArray(VAO_body);
    glDrawArrays(GL_TRIANGLES, 0, BodyObj);

    SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(BodyYaw), glm::radians(shake_deg)), LeftArmPos, shader);
    glBindVertexArray(VAO_left_arm);
    glDrawArrays(GL_TRIANGLES, 0, LeftArmObj);

    if (blocks[block_num] == BlockType::AIR) {
        SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(BodyYaw), -glm::radians(shake_deg)), RightArmPos, shader);
        glBindVertexArray(VAO_right_arm);
        glDrawArrays(GL_TRIANGLES, 0, RightArmObj);
    }
    else {
        float rad = glm::radians(60.0f - shake_deg / 2 + HeadPitch);
        if (rad < 0.0f) rad = 0.0f;
        SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(BodyYaw), rad), RightArmPos, shader);
        glBindVertexArray(VAO_right_arm);
        glDrawArrays(GL_TRIANGLES, 0, RightArmObj);
    }
    
    SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(BodyYaw), -glm::radians(shake_deg)), LeftLegPos, shader);
    glBindVertexArray(VAO_left_leg);
    glDrawArrays(GL_TRIANGLES, 0, LeftLegObj);

    SRT(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(BodyYaw), glm::radians(shake_deg)), RightLegPos, shader);
    glBindVertexArray(VAO_right_leg);
    glDrawArrays(GL_TRIANGLES, 0, RightLegObj);

    if (!god_mode)
        RenderUI(shader);
}

void Character::SetBlockVertices()
{
    block_vertices.clear();

    for (int f = 0; f < 6; f++) // Back -Z, Front +Z, Top Face +Y, Bottom -Y, Left -X, RIght +X
    {
        for (int i = 0; i < 6; i++) {
            block_vertices.push_back(voxelVertex[voxelTris[f][i]].x);
            block_vertices.push_back(voxelVertex[voxelTris[f][i]].y);
            block_vertices.push_back(voxelVertex[voxelTris[f][i]].z);

            block_vertices.push_back(faceChecks[f].x);
            block_vertices.push_back(faceChecks[f].y);
            block_vertices.push_back(faceChecks[f].z);

            block_vertices.push_back(GetTextureUV(TextureIndex[blocks[block_num]][f]).first + voxelUvs[i][0]);
            block_vertices.push_back(GetTextureUV(TextureIndex[blocks[block_num]][f]).second + voxelUvs[i][1]);
        }
    }
}

void Character::RenderBlock(Shader* shader)
{
    if (block_vertices.size() == 0 || blocks[block_num] == BlockType::AIR)
        return;

    glBindVertexArray(VAO_block);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBufferData(GL_ARRAY_BUFFER, block_vertices.size() * sizeof(float), block_vertices.data(), GL_STATIC_DRAW);

    glm::vec3 pos1(0.0f, -0.75f, 0.5f);
    glm::vec3 pos2(0.0f, 0.75f, 0.5f);
    //SRT(glm::vec3(0.4f), glm::vec3(glm::radians(45.0f), 0.0f, 0.0f), RightArmPos - glm::vec3(0.0f, 0.0f, 0.0f), shader);
    float rad = glm::radians(60.0f - shake_deg / 2 + HeadPitch);
    if (rad < -10.0f) rad = -10.0f;
    STRT(glm::vec3(0.4f), pos1, glm::vec3(0.0f, glm::radians(BodyYaw / 2 + 15.0f), rad), Position - pos1 + pos2, shader);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //glDeleteVertexArrays(1, &VBO);
    //glDeleteVertexArrays(1, &VAO_block);
}

void Character::RenderUI(Shader* shader)
{
    SRT(glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f), shader);

    if (selectblock) {
        float itv = 0.001f;
        int x, y, z; 
        (selectBlockPos.x >= 0) ? x = static_cast<int>(selectBlockPos.x) : x = static_cast<int>(selectBlockPos.x + 0.0001f) - 1;
        y = static_cast<int>(selectBlockPos.y);
        (selectBlockPos.z >= 0) ? z = static_cast<int>(selectBlockPos.z) : z = static_cast<int>(selectBlockPos.z + 0.0001f) - 1;

        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(x - itv, y - itv, z - itv);
        glVertex3f(x + 1.0f + itv, y - itv, z - itv);
        glVertex3f(x + 1.0f + itv, y - itv, z + 1.0f + itv);
        glVertex3f(x - itv, y - itv, z + 1.0f + itv);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(x - itv, y + 1.0f + itv, z - itv);
        glVertex3f(x + 1.0f + itv, y + 1.0f + itv, z - itv);
        glVertex3f(x + 1.0f + itv, y + 1.0f + itv, z + 1.0f + itv);
        glVertex3f(x - itv, y + 1.0f + itv, z + 1.0f + itv);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(x - itv, y - itv, z - itv);
        glVertex3f(x - itv, y + 1.0f + itv, z - itv);
        glVertex3f(x + 1.0f + itv, y - itv, z - itv);
        glVertex3f(x + 1.0f + itv, y + 1.0f + itv, z - itv);
        glVertex3f(x + 1.0f + itv, y - itv, z + 1.0f + itv);
        glVertex3f(x + 1.0f + itv, y + 1.0f + itv, z + 1.0f + itv);
        glVertex3f(x - itv, y - itv, z + 1.0f + itv);
        glVertex3f(x - itv, y + 1.0f + itv, z + 1.0f + itv);
        glEnd();
    }
    
}

void Character::Input()
{
    if (!god_mode) {
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) // shift
            move_state = 2;
        else if (GetAsyncKeyState(VK_CONTROL) & 0x8000) // ctr
            move_state = 1;
        else
            move_state = 0;

        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && jump) { // space
            speedY = 0.2f;
            jump = false;
        }
    }
    else {
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) // ctr
            Position.y -= 0.3f;

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) // space
            Position.y += 0.3f;
    }

    dir_front = 0;
    dir_left = 0;
    if (GetAsyncKeyState(0x57) & 0x8000) // up
        dir_front += 1;
    if (GetAsyncKeyState(0x53) & 0x8000) // down
        dir_front -= 1;
    if (GetAsyncKeyState(0x41) & 0x8000) // left
        dir_left += 1;
    if (GetAsyncKeyState(0x44) & 0x8000) // right
        dir_left -= 1;
    
    /*
    if (GetAsyncKeyState(VK_CONTROL) & 0x8000) // space
        Position.y -= 0.1f;
    */
}

void Character::KeyboardInput(unsigned char key)
{
    if (key >= '1' && key <= '9') {
        if (block_num != key - '1' && key - '1' != 0) {
            block_num = key - '1';
            SetBlockVertices();
        }
        else
            block_num = key - '1';
    }
}

void Character::SpecialKeyboardInput(unsigned char key)
{
    if (key == GLUT_KEY_F5) {
        camera_mode = (camera_mode + 1) % 3;
    }

    if (key == GLUT_KEY_F1) {
        god_mode = !god_mode;
    }
}

void Character::MouseInput(bool left_state, bool right_state)
{
    mouse_left_state = left_state;
    mouse_right_state = right_state;

    if (!mouse_left_state)
        add_block_time = 0.0f;
    if (!mouse_right_state)
        del_block_time = 0.0f;
}

void Character::MouseWheelInput(int dir)
{
    if (dir > 0)
    {
        if (block_num > 0) {
            block_num -= 1;
            SetBlockVertices();
        }
        else
            block_num = 8;
    }
    else
    {
        if (block_num < 8) {
            block_num += 1;
            SetBlockVertices();
        }
        else
            block_num = 0;
    }
}

void Character::Update()
{
    // set angle
    HeadPitch = camera.Pitch;
    HeadYaw = -camera.Yaw;


    if (glm::abs(HeadYaw - BodyYaw) > 5.0f) {
        if (HeadYaw > BodyYaw)
            BodyYaw = HeadYaw - 5.0f;
        else
            BodyYaw = HeadYaw + 5.0f;
    }

    // set body_deg
    if (dir_front != 0 || dir_left != 0) {
        BodyYaw = HeadYaw;
    }

    // set shake_deg
    if (dir_front == 0 && dir_left == 0) {
        shake_deg /= 1.1f;
        if (glm::abs(shake_deg) < 0.1f)
            shake_deg = 0.0f;
    }
    else {
        if (shake_state) {
            shake_deg += ADD_SHAKE_DEG[move_state];
            if (shake_deg > MAX_SHAKE_DEG[move_state]) {
                shake_deg = MAX_SHAKE_DEG[move_state];
                shake_state = false;
            }
        }
        else {
            shake_deg -= ADD_SHAKE_DEG[move_state];
            if (shake_deg < -MAX_SHAKE_DEG[move_state]) {
                shake_deg = -MAX_SHAKE_DEG[move_state];
                shake_state = true;
            }
        }
    }

    // set Pos
    float speed = 0.0f;
    if (dir_front != 0 && dir_left != 0)
        speed = CHARACTER_SPEED[move_state] / 1.4f;
    else if ((dir_front == 0) ^ (dir_left == 0))
        speed = CHARACTER_SPEED[move_state];

    if (god_mode)
        speed *= 5.0f;

    speedX = (static_cast<float>(dir_front) * glm::cos(glm::radians(HeadYaw)) + static_cast<float>(dir_left) * -glm::sin(glm::radians(HeadYaw))) * speed;
    speedZ = (static_cast<float>(dir_front) * -glm::sin(glm::radians(HeadYaw)) + static_cast<float>(dir_left) * -glm::cos(glm::radians(HeadYaw))) * speed;
    Position.x += speedX;
    Position.z += speedZ;

    add_block_time -= 1.0f;
    del_block_time -= 1.0f;

    if (!god_mode)
        PhysicsUpdate();
    else
        speedY = 0.0f;
    BlockUpdate();
    PosUpdate();
}

void Character::PhysicsUpdate()
{
    speedY -= GRAVITY_ACC * 0.001f;
    if (speedY > MAX_SPEED)
        speedY = MAX_SPEED;

    Position.y += speedY;
    float itv = 0.001f;

    int px = static_cast<int>(Position.x);
    int py = static_cast<int>(Position.y);
    int pz = static_cast<int>(Position.z);

    glm::vec3 collide_box[8] = {
        {box_interval, 0.0f, box_interval},
        {-box_interval, 0.0f, box_interval},
        {-box_interval, 0.0f, -box_interval},
        {box_interval, 0.0f, -box_interval},
        {box_interval, 1.1f, box_interval},
        {-box_interval, 1.1f, box_interval},
        {-box_interval, 1.1f, -box_interval},
        {box_interval, 1.1f, -box_interval}
    };

    /*
    glm::vec3 collide_XZ[4] = { // +X, -X, +Z, -Z
        {box_interval, 0.2f, 0.0f},
        {-box_interval, 0.2f, 0.0f},
        {0.0f, 0.2f, box_interval},
        {0.0f, 0.2f, -box_interval}
    };
    */

    // height
    for (int i = 0; i < 4; ++i)
    {
        if (world->WorldPosIsSolid(Position + collide_box[i]) == 2) {
            if (speedY <= 0.0f) {
                Position.y = py + 1.0f;
                speedY = 0.0f;
                jump = true;
                break;
            }
        }
    }

    if (glm::abs(speedX) > glm::abs(speedZ)) {
        for (int i = 0; i < 4; i++)
        {
            glm::vec3 point = Position + collide_box[i];
            int x2 = static_cast<int>(point.x);
            int z2 = static_cast<int>(point.z);

            float dx = point.x - px;
            float dz = point.z - pz;

            if (x2 < px && speedX < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + box_interval + itv;
                }
            }
            if (x2 > px && speedX > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + 1.0f - box_interval - itv;
                }
            }
            if (z2 < pz && speedZ < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + box_interval + itv;
                }
            }
            if (z2 > pz && speedZ > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + 1.0f - box_interval - itv;
                }
            }
        }
    }
    else {
        for (int i = 0; i < 4; i++)
        {
            glm::vec3 point = Position + collide_box[i];
            int x2 = static_cast<int>(point.x);
            int z2 = static_cast<int>(point.z);

            float dx = point.x - px;
            float dz = point.z - pz;

            if (z2 < pz && speedZ < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + box_interval + itv;
                }
            }
            if (z2 > pz && speedZ > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + 1.0f - box_interval - itv;
                }
            }
            if (x2 < px && speedX < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + box_interval + itv;
                }
            }
            if (x2 > px && speedX > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + 1.0f - box_interval - itv;
                }
            }
        }
    }

    if (glm::abs(speedX) > glm::abs(speedZ)) {
        for (int i = 4; i < 8; i++)
        {
            glm::vec3 point = Position + collide_box[i];
            int x2 = static_cast<int>(point.x);
            int z2 = static_cast<int>(point.z);

            float dx = point.x - px;
            float dz = point.z - pz;

            if (x2 < px && speedX < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + box_interval + itv;
                }
            }
            if (x2 > px && speedX > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + 1.0f - box_interval - itv;
                }
            }
            if (z2 < pz && speedZ < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + box_interval + itv;
                }
            }
            if (z2 > pz && speedZ > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + 1.0f - box_interval - itv;
                }
            }
        }
    }
    else {
        for (int i = 4; i < 8; i++)
        {
            glm::vec3 point = Position + collide_box[i];
            int x2 = static_cast<int>(point.x);
            int z2 = static_cast<int>(point.z);

            float dx = point.x - px;
            float dz = point.z - pz;

            if (z2 < pz && speedZ < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + box_interval + itv;
                }
            }
            if (z2 > pz && speedZ > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.z = pz + 1.0f - box_interval - itv;
                }
            }
            if (x2 < px && speedX < 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + box_interval + itv;
                }
            }
            if (x2 > px && speedX > 0) {
                if (world->WorldPosIsSolid(point) == 2) {
                    Position.x = px + 1.0f - box_interval - itv;
                }
            }
        }
    }
}

void Character::BlockUpdate()
{
    selectblock = false;
    glm::vec3 headPos = camera.Position;
    glm::vec3 headDir = glm::normalize(camera.Front);
    glm::vec3 delta_headDir = headDir * 0.1f;

    for (int i = 1; i <= 50; i++)
    {
        if (world->WorldPosIsSolid(headPos + (delta_headDir * static_cast<float>(i))) == 2) {
            selectblock = true;
            selectBlockPos = headPos + (delta_headDir * static_cast<float>(i));
            glm::vec3 bp = headPos + (delta_headDir * static_cast<float>(i - 1));
            
            int sx, sy, sz;
            (selectBlockPos.x >= 0) ? sx = static_cast<int>(selectBlockPos.x) : sx = static_cast<int>(selectBlockPos.x + 0.0001f) - 1;
            (selectBlockPos.y >= 0) ? sy = static_cast<int>(selectBlockPos.y) : sy = static_cast<int>(selectBlockPos.y + 0.0001f) - 1;
            (selectBlockPos.z >= 0) ? sz = static_cast<int>(selectBlockPos.z) : sz = static_cast<int>(selectBlockPos.z + 0.0001f) - 1;

            int bx, by, bz;
            (bp.x >= 0) ? bx = static_cast<int>(bp.x) : bx = static_cast<int>(bp.x + 0.0001f) - 1;
            (bp.y >= 0) ? by = static_cast<int>(bp.y) : by = static_cast<int>(bp.y + 0.0001f) - 1;
            (bp.z >= 0) ? bz = static_cast<int>(bp.z) : bz = static_cast<int>(bp.z + 0.0001f) - 1;

            if (sx > bx) {
                nextBlockPos = selectBlockPos + glm::vec3(-1.0f, 0.0f, 0.0f);
            }
            else if (sx < bx) {
                nextBlockPos = selectBlockPos + glm::vec3(1.0f, 0.0f, 0.0f);
            }
            else if (sy > by) {
                nextBlockPos = selectBlockPos + glm::vec3(0.0f, -1.0f, 0.0f);
            }
            else if (sy < by) {
                nextBlockPos = selectBlockPos + glm::vec3(0.0f, 1.0f, 0.0f);
            }
            else if (sz > bz) {
                nextBlockPos = selectBlockPos + glm::vec3(0.0f, 0.0f, -1.0f);
            }
            else if (sz < bz) {
                nextBlockPos = selectBlockPos + glm::vec3(0.0f, 0.0f, 1.0f);
            }

            break;
        }
    }

    if (mouse_left_state && selectblock && del_block_time <= 0.0f) {
        std::pair<int, int> chunkPos = world->GetChunkPosFromWorldPos(selectBlockPos);
        // find chunk
        if (world->chunks.find({ chunkPos.first, chunkPos.second }) != world->chunks.end()) {
            Chunk* chunk = world->chunks.find({ chunkPos.first, chunkPos.second })->second;
            std::pair<int, int> blockPos = world->GetBlockPosFromWorldPos(selectBlockPos);
            int by = static_cast<int>(selectBlockPos.y);
            chunk->blocks[blockPos.first][by][blockPos.second] = BlockType::AIR;
            chunk->ChangeMeshData();
            del_block_time = 10.0f;

            if (blockPos.first == 0 && world->chunks.find({ chunkPos.first - 1, chunkPos.second }) != world->chunks.end()) {
                //world->chunks.find({ chunkPos.first - 1, chunkPos.second })->second->blocks[15][by][blockPos.second] = BlockType::AIR;
                world->chunks.find({ chunkPos.first - 1, chunkPos.second })->second->ChangeMeshData();
            }
            if (blockPos.first == 15 && world->chunks.find({ chunkPos.first + 1, chunkPos.second }) != world->chunks.end()) {
                world->chunks.find({ chunkPos.first + 1, chunkPos.second })->second->ChangeMeshData();
            }
            if (blockPos.second == 0 && world->chunks.find({ chunkPos.first, chunkPos.second - 1 }) != world->chunks.end()) {
                world->chunks.find({ chunkPos.first, chunkPos.second - 1 })->second->ChangeMeshData();
            }
            if (blockPos.second == 15 && world->chunks.find({ chunkPos.first, chunkPos.second + 1 }) != world->chunks.end()) {
                world->chunks.find({ chunkPos.first, chunkPos.second + 1 })->second->ChangeMeshData();
            }
        }
    }

    if (mouse_right_state && selectblock && add_block_time <= 0.0f) {
        if (blocks[block_num] != BlockType::AIR) {
            std::pair<int, int> chunkPos = world->GetChunkPosFromWorldPos(nextBlockPos);
            // find chunk
            if (world->chunks.find({ chunkPos.first, chunkPos.second }) != world->chunks.end()) {
                Chunk* chunk = world->chunks.find({ chunkPos.first, chunkPos.second })->second;
                std::pair<int, int> blockPos = world->GetBlockPosFromWorldPos(nextBlockPos);
                chunk->blocks[blockPos.first][static_cast<int>(nextBlockPos.y)][blockPos.second] = blocks[block_num];
                chunk->ChangeMeshData();
                add_block_time = 10.0f;
            }
        }
    }
}

glm::mat4 Character::GetViewMatrix()
{
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    if (camera_mode == 0) {
        cameraPos = camera.Position;
        cameraFront = camera.Front;
    }
    if (camera_mode == 1) {
        cameraPos = camera.Position - 5.0f * glm::normalize(camera.Front);
        cameraFront = camera.Front;
    }
    if (camera_mode == 2) {
        cameraPos = camera.Position + 5.0f * glm::normalize(camera.Front);
        cameraFront = -camera.Front;
    }

    return glm::lookAt(cameraPos, cameraPos + cameraFront, camera.Up);
}