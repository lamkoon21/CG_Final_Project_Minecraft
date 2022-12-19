#include "chunk.h"
#include "../world/world.h"
#include <iostream>


Chunk::Chunk() {}

Chunk::Chunk(int x, int z, World* world)
{
	this->x = x;
	this->z = z;
	this->world = world;
}

bool Chunk::CheckVoxel(glm::vec3 pos)
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);
	int z = static_cast<int>(pos.z);

	/*
	if (x < 0 || x > ChunkWidth - 1 ||
		y < 0 || y > ChunkHeight - 1 ||
		z < 0 || z > ChunkWidth - 1)
		return false;
	*/

	if (GetBlockType(x, y, z) == BlockType::AIR)
		return false;

	return true;
}


void Chunk::AddVoxelDataToChunk(std::vector<float>& vertices, glm::vec3 pos, const BlockType block)
{
	if (block == BlockType::AIR) return;

	for (int f = 0; f < 6; f++) // Back -Z, Front +Z, Top Face +Y, Bottom -Y, Left -X, RIght +X
	{
		if (CheckVoxel(pos) && !CheckVoxel(pos + faceChecks[f])) {
			for (int i = 0; i < 6; i++) {
				vertices.push_back(voxelVertex[voxelTris[f][i]].x + pos.x + this->x * ChunkWidth);
				vertices.push_back(voxelVertex[voxelTris[f][i]].y + pos.y);
				vertices.push_back(voxelVertex[voxelTris[f][i]].z + pos.z + this->z * ChunkWidth);

				vertices.push_back(faceChecks[f].x);
				vertices.push_back(faceChecks[f].y);
				vertices.push_back(faceChecks[f].z);

				vertices.push_back(GetTextureUV(TextureIndex[block][f]).first + voxelUvs[i][0]);
				vertices.push_back(GetTextureUV(TextureIndex[block][f]).second + voxelUvs[i][1]);
			}
		}
	}
}

bool Chunk::CheckVoxel_C(glm::vec3 pos)
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);
	int z = static_cast<int>(pos.z);

	if (GetBlockTypeFromBlocks(x, y, z) == BlockType::AIR)
		return false;

	return true;
}


void Chunk::AddVoxelDataToChunk_C(std::vector<float>& vertices, glm::vec3 pos, const BlockType block)
{
	if (block == BlockType::AIR) return;

	for (int f = 0; f < 6; f++) // Back -Z, Front +Z, Top Face +Y, Bottom -Y, Left -X, RIght +X
	{
		if (CheckVoxel_C(pos) && !CheckVoxel_C(pos + faceChecks[f])) {
			for (int i = 0; i < 6; i++) {
				vertices.push_back(voxelVertex[voxelTris[f][i]].x + pos.x + this->x * ChunkWidth);
				vertices.push_back(voxelVertex[voxelTris[f][i]].y + pos.y);
				vertices.push_back(voxelVertex[voxelTris[f][i]].z + pos.z + this->z * ChunkWidth);

				vertices.push_back(faceChecks[f].x);
				vertices.push_back(faceChecks[f].y);
				vertices.push_back(faceChecks[f].z);

				vertices.push_back(GetTextureUV(TextureIndex[block][f]).first + voxelUvs[i][0]);
				vertices.push_back(GetTextureUV(TextureIndex[block][f]).second + voxelUvs[i][1]);
			}
		}
	}
}

void Chunk::CreateMeshData()
{
	vertices.clear();
	for (int x = 0; x < ChunkWidth; ++x)
	{
		for (int y = 0; y < ChunkHeight; ++y)
		{
			for (int z = 0; z < ChunkWidth; ++z)
			{
				AddVoxelDataToChunk(vertices, glm::vec3(x, y, z), blocks[x][y][z]);
			}
		}
	}
}

void Chunk::ChangeMeshData()
{
	vertices.clear();
	for (int x = 0; x < ChunkWidth; ++x)
	{
		for (int y = 0; y < ChunkHeight; ++y)
		{
			for (int z = 0; z < ChunkWidth; ++z)
			{
				AddVoxelDataToChunk_C(vertices, glm::vec3(x, y, z), blocks[x][y][z]);
			}
		}
	}
}

void Chunk::PopulateVoxelMap()
{
	for (int x = 0; x < ChunkWidth; ++x)
	{
		for (int y = 0; y < ChunkHeight; ++y)
		{
			for (int z = 0; z < ChunkWidth; ++z)
			{
				blocks[x][y][z] = GetBlockType(x, y, z);
			}
		}
	}
}

std::pair<float, float> GetTextureUV(int index)
{
	float x = 0.25f * (index % 4);
	float y = 0.75f - 0.25f * (index / 4);
	return { x, y };
}

void Chunk::SetTerrainHeight()
{
	int chunkX = this->x * ChunkWidth;
	int chunkZ = this->z * ChunkWidth;

	for (int x = 0; x < ChunkWidth; ++x)
	{
		for (int z = 0; z < ChunkWidth; ++z)
		{
			terrainHeight[x][z] = world->GetTerrainHeight(x + chunkX, z + chunkZ);
		}
	}
}

BlockType Chunk::GetBlockType(int x, int y, int z)
{
	// Immutable Pass
	if (y < 0 || y >= ChunkHeight)
		return BlockType::AIR;

	// Terrain Pass
	int terrainHeight;
	if (x < 0 || x >= ChunkWidth || z < 0 || z >= ChunkWidth) {
		return world->GetBlockType(this->x * ChunkWidth + x, y, this->z * ChunkWidth + z);
	}
	else {
		terrainHeight = this->terrainHeight[x][z];
	}

	if (y == terrainHeight) {
		return BlockType::GRASS;
	}
	else if (y < terrainHeight) {
		return BlockType::STONE;
	}
	else {
		return BlockType::AIR;
	}
}

BlockType Chunk::GetBlockTypeFromBlocks(int x, int y, int z)
{
	// Immutable Pass
	if (y < 0 || y >= ChunkHeight)
		return BlockType::AIR;

	if (x < 0 || x >= ChunkWidth || z < 0 || z >= ChunkWidth) {
		if (x < 0 && world->chunks.find({ this->x - 1, this->z }) != world->chunks.end()) {
			return world->chunks.find({ this->x - 1, this->z })->second->blocks[15][y][z];
		}
		if (x >= ChunkWidth && world->chunks.find({ this->x + 1, this->z }) != world->chunks.end()) {
			return world->chunks.find({ this->x + 1, this->z })->second->blocks[0][y][z];
		}
		if (z < 0 && world->chunks.find({ this->x, this->z - 1 }) != world->chunks.end()) {
			return world->chunks.find({ this->x, this->z - 1 })->second->blocks[x][y][15];
		}
		if (z >= ChunkWidth && world->chunks.find({ this->x, this->z + 1 }) != world->chunks.end()) {
			return world->chunks.find({ this->x, this->z + 1 })->second->blocks[x][y][0];
		}
		//return world->GetBlockType(this->x * ChunkWidth + x, y, this->z * ChunkWidth + z);
	}
	else {
		return blocks[x][y][z];
	}

	return BlockType::AIR;
}