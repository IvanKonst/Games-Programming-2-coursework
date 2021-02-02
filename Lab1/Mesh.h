#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->position = pos;
		this->texCoordinates = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &position; }
	glm::vec2* GetTexCoord() { return &texCoordinates; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 texCoordinates;
	glm::vec3 normal;
};
struct SphereData
{

public:
	SphereData() {};
	SphereData(glm::vec3& position, float radius)
	{
		this->position = position;
	}
	glm::vec3 GetPos() { return position; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 position)
	{
		this->position = position;
	}
	void SetRadius(float radius)
	{
		this->radius = radius;
	}
protected:
private:
	glm::vec3 position;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	void draw();
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);


	void UpdateSphereData(glm::vec3 pos, float radius);
	glm::vec3 GetSpherePos() { return meshSphere.GetPos(); }
	float GetSphereRadius() { return meshSphere.GetRadius(); }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	SphereData meshSphere;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

