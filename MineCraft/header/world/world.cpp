#include "world.h"
#include "../chunk/chunk.h"
#include "../character/character.h"


World::World() { }

World::World(int seed) 
{
	this->seed = seed;
	perlin.reseed(seed);
	//player = Character(this);
}

void World::GenerateWorld()
{
	activeChunks.clear();
	for (int x = -ViewDistance; x <= ViewDistance; ++x)
	{
		for (int z = -ViewDistance; z <= ViewDistance; ++z)
		{
			CreateNewChunk(x, z);
			activeChunks.push_back(chunks.find({ x, z })->second);
		}
	}
}

void World::CreateNewChunk(int x, int z)
{
 	Chunk* newChunk = new Chunk(x, z, this);
	newChunk->SetTerrainHeight();
	newChunk->PopulateVoxelMap();
	newChunk->CreateMeshData();
	chunks.insert({ {x, z}, newChunk });
}

bool World::IsBlockInWorld(int world_x, int world_y, int world_z)
{
	if (world_x < -(WORLD_MAX - 1) * ChunkWidth || world_x > WORLD_MAX * ChunkWidth)
		return false;
	if (world_y < 0 || world_y >= ChunkHeight)
		return false;
	if (world_z < -(WORLD_MAX - 1) * ChunkWidth || world_z > WORLD_MAX * ChunkWidth)
		return false;

	return true;
}

BlockType World::GetBlockType(int x, int y, int z)
{
	if (!IsBlockInWorld(x, y, z))
		return BlockType::AIR;

	int terrainHeight;
	std::pair<int, int> chunkPos = GetChunkPosFromWorldPos(glm::vec3(x, y, z));

	if (chunks.find({ chunkPos.first, chunkPos.second }) == chunks.end()) {
		terrainHeight = GetTerrainHeight(x, z);
	}
	else {
		Chunk* chunk = chunks.find({ chunkPos.first, chunkPos.second })->second;
		std::pair<int, int> blockPos = GetBlockPosFromWorldPos(glm::vec3(x, y, z));
		terrainHeight = chunk->terrainHeight[blockPos.first][blockPos.second];
	}

	
	if (y < terrainHeight - 5) {
		return BlockType::STONE;
	}
	else if (y <= terrainHeight) {
		return BlockType::GRASS;
	}
	else {
		return BlockType::AIR;
	}
}

std::pair<int, int>  World::GetChunkPosFromWorldPos(glm::vec3 pos)
{
	std::pair<int, int> coord;
	(pos.x >= 0) ? coord.first = static_cast<int>(pos.x) / ChunkWidth : coord.first = static_cast<int>(pos.x + 0.0001f) / ChunkWidth - 1;
	(pos.z >= 0) ? coord.second = static_cast<int>(pos.z) / ChunkWidth : coord.second = static_cast<int>(pos.z + 0.0001f) / ChunkWidth - 1;
	return coord;
}

std::pair<int, int> World::GetBlockPosFromWorldPos(glm::vec3 pos)
{
	std::pair<int, int> coord;
	(pos.x >= 0) ? coord.first = coord.first = static_cast<int>(pos.x) % ChunkWidth : coord.first = static_cast<int>(pos.x + 0.0001f) % ChunkWidth - 1 + ChunkWidth;
	(pos.z >= 0) ? coord.second = coord.second = static_cast<int>(pos.z) % ChunkWidth : coord.second = static_cast<int>(pos.z + 0.0001f) % ChunkWidth - 1 + ChunkWidth;
	return coord;
}

void World::Update()
{
	std::pair<int, int> pos = GetChunkPosFromWorldPos(currentPlayerPos);

	if (pos != GetChunkPosFromWorldPos(prevPlayerPos)) {
		activeChunks.clear();
		int minX = pos.first - ViewDistance;
		int maxX = pos.first + ViewDistance;
		int minZ = pos.second - ViewDistance;
		int maxZ = pos.second + ViewDistance;
		for (int x = minX; x <= maxX; ++x)
		{
			for (int z = minZ; z <= maxZ; ++z)
			{
				// in view distance
				if ((pos.first - x) * (pos.first - x) + (pos.second - z) * (pos.second - z) <= ViewDistance * ViewDistance + 10) {
					// can not find chunk
					if (chunks.find({ x, z }) == chunks.end()) {
						// check world max
						if (x > -WORLD_MAX && x < WORLD_MAX && z > -WORLD_MAX && z < WORLD_MAX) {
							CreateNewChunk(x, z);
							activeChunks.push_back(chunks.find({ x, z })->second);
						}
					}
					// can find chunk
					else {
						activeChunks.push_back(chunks.find({ x, z })->second);
					}
				}
			}
		}
	}
	
	prevPlayerPos = currentPlayerPos;
}

void World::SetPlayerPos(glm::vec3 pos)
{
	currentPlayerPos = pos;
}

int World::GetTerrainHeight(int x, int z)
{
	float noise = perlin.octave2D_01(x * 0.001, z * 0.001, 8);
	return static_cast<int>(ChunkHeight / 4 + noise * 80);
}

glm::vec3 World::GetStartPos()
{
	float startHeight = chunks.find({ 0, 0 })->second->terrainHeight[ChunkWidth / 2][ChunkWidth / 2] + 0.5f;
	return glm::vec3(static_cast<float>(ChunkWidth / 2) + 0.5f, startHeight, static_cast<float>(ChunkWidth / 2) + 0.5f);
}

void World::Init()
{
	skybox.Init();
}

int World::WorldPosIsSolid(glm::vec3 pos)
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);
	int z = static_cast<int>(pos.z);

	if (!IsBlockInWorld(x, y, z))
		return 0; // AIR

	std::pair<int, int> chunkPos = GetChunkPosFromWorldPos(pos);

	// can not find chunk
	if (chunks.find({ chunkPos.first, chunkPos.second }) == chunks.end()) {
		return 0; // AIR
	}
	else {	// can find chunk
		Chunk* chunk = chunks.find({ chunkPos.first, chunkPos.second })->second;
		std::pair<int, int> blockPos = GetBlockPosFromWorldPos(pos);
		BlockType blocktype = chunk->blocks[blockPos.first][y][blockPos.second];
		if (blocktype == BlockType::AIR) {
			return 0; // AIR
		}
		else {
			return 2; // SOLID
		}
	}
}