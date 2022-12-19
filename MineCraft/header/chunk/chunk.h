#ifndef CHUNK_H
#define CHUNK_H

#include "../block/voxel_data.h"
#include "../block/blocktype.h"


class World;


std::pair<float, float> GetTextureUV(int index);


class Chunk
{
private:
	BlockType GetBlockType(int x, int y, int z);
	BlockType GetBlockTypeFromBlocks(int x, int y, int z);
	bool CheckVoxel(glm::vec3 pos);
	bool CheckVoxel_C(glm::vec3 pos);
	void AddVoxelDataToChunk_C(std::vector<float>& vertices, glm::vec3 pos, const BlockType block);
public:
	World* world;
	int x = 0;
	int z = 0;
	int terrainHeight[16][16];
	BlockType blocks[16][128][16];
	std::vector<float> vertices;

	Chunk();
	Chunk(int x, int z, World* world);

	void AddVoxelDataToChunk(std::vector<float>& vertices, glm::vec3 pos, const BlockType block);
	void CreateMeshData();
	void ChangeMeshData();
	void PopulateVoxelMap();
	void SetTerrainHeight();
	
};


#endif