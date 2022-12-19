#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

enum BlockType {
    AIR,
    DIRT,
    GRASS,
    STONE,
    COBBLESTONE,
    LOG_OAK,
    PLACKS_OAK,
    SAND,
    BRICK
};


// Back -Z Front +Z Top +Y Bottom -Y Left -X RIght +X
static const int TextureIndex[9][6] = {
    {0, 0, 0, 0, 0, 0},     // AIR = NONE
    {0, 0, 0, 0, 0, 0},     // DIRT
    {2, 2, 1, 0, 2, 2},     // GRASS
    {3, 3, 3, 3, 3, 3},     // STONE
    {4, 4, 4, 4, 4, 4},     // COBBLESTONE
    {6, 6, 5, 5, 6, 6},     // LOG_OAK
    {7, 7, 7, 7, 7, 7},     // PLACKS_OAK
    {8, 8, 8, 8, 8, 8},     // SAND
    {9, 9, 9, 9, 9, 9}      // BRICK
};


#endif
