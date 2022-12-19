#include "objRead.h"

int objRead::loadObj_normalize_center(const char* filename)
{
	std::ifstream fin(filename, std::ios::in);

	if (!fin) {
		printf("Impossible to open the file !\n");
		assert(false);
		return false;
	}
	while (!fin.eof()) {
		std::string lineHeader;
		// read the first word of the line
		fin >> lineHeader;
		if (lineHeader == "v") {
			glm::vec3 vertex;
			fin >> vertex.x >> vertex.y >> vertex.z;

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (lineHeader == "vt") {
			glm::vec2 uv;
			fin >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (lineHeader == "vn") {
			glm::vec3 normal;
			fin >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (lineHeader == "f") {
			for (int i = 0; i < 3; i++)
			{
				std::string str;
				fin >> str;
				int v = -1, t = -1, n = -1, cnt = 0;
				int str_len = str.length();
				for (int i = 0, di = 0; i <= str_len; i++)
				{
					if (str[i] == '/' || i == str_len) {
						if (cnt == 0) {
							if (i - di <= 0) {
								di = i + 1;
								++cnt;
								continue;
							}
							v = stoi(str.substr(0, i - di));
						}
						else if (cnt == 1) {
							if (i - di <= 0) {
								di = i + 1;
								++cnt;
								continue;
							}
							t = stoi(str.substr(di, i - di));
						}
						else {
							if (i - di <= 0) {
								di = i + 1;
								++cnt;
								continue;
							}
							n = stoi(str.substr(di, i - di));
						}
						di = i + 1;
						++cnt;
					}
				}

				if (v != -1)
					//std::cout << "v: " << v << " ";
					vertexIndices.push_back(v);
				if (t != -1)
					uvIndices.push_back(t);
				if (n != -1)
					normalIndices.push_back(n);
			}
		}
	}

	//std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
	//std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	//std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

	//std::cout << "scaleX: " << scaleX << " scaleY: " << scaleY << " scaleZ: " << scaleZ << std::endl;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		
		unsigned int vertexIndex = vertexIndices[i];
		/*
		temp = temp_vertices[vertexIndex - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		outvertex.push_back(temp);
		*/
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		outnormal.push_back(vertex);
	}

	return outvertex.size();
}

void objRead::initBuffer(GLuint& VAO)
{
	GLuint VBO[3];

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	if (outnormal.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}
	
	if (outuv.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
		glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(2);
	}
}