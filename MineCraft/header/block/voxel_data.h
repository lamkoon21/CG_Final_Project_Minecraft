#ifndef VOXELDATA_H
#define VOXELDATA_H


#include "glm/glm.hpp"
#include <vector>


static const int ChunkWidth = 16;
static const int ChunkHeight = 128;


static const glm::vec3 voxelVertex[8] = {
	// Front
	{0.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},

	// Back
	{0.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f}
};


static const int voxelTris[6][6] = {
	{0, 3, 1, 1, 3, 2 }, // Back Face   (-Z)
	{5, 6, 4, 4, 6, 7 }, // Front Face  (+Z)
	{3, 7, 2, 2, 7, 6 }, // Top Face    (+Y)
	{1, 5, 0, 0, 5, 4 }, // Bottom Face (-Y)
	{4, 7, 0, 0, 7, 3 }, // Left Face   (-X)
	{1, 2, 5, 5, 2, 6 }, // RIght Face  (+X)
};


static const float voxelUvs[6][2] = {
	{0.0f, 0.0f}, // 1
	{0.0f, 0.25f}, // 3
	{0.25f, 0.0f}, // 2
	{0.25f, 0.0f}, // 2
	{0.0f, 0.25f}, // 3
	{0.25f, 0.25f} // 4
};


static const glm::vec3 faceChecks[6] = {
	{0.0, 0.0, -1.0},
	{0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0},
	{0.0, -1.0, 0.0},
	{-1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
};


#endif