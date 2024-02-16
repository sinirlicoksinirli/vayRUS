#include"vertexArray.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>


vertexArrayObject::vertexArrayObject()
{
	VaoId = 0;
	VboId = 0;
	VibId = 0;

}

vertexArrayObject::~vertexArrayObject()
{
	if (VaoId) {
		glDeleteVertexArrays(1,&VaoId);
	}
	if (VboId) {
		glDeleteBuffers(1, &VboId);
	}
	if (VibId) {
		glDeleteBuffers(1, &VibId);
	}
}

void vertexArrayObject::createObject(Vertex& vertices, unsigned int verticesCount, indexData& indices, unsigned int indicesCount)
{
	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);
	glGenBuffers(1, &VibId);

	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VibId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticesCount, &vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)* indicesCount, &indices, GL_STATIC_DRAW);
	indexCount = indicesCount;
	//vertex bilgisi
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
	glEnableVertexAttribArray(0);
	//texture bilgisi
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//normal bilgisi
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 9, (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//texture level bilgisi
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(float) * 9, (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	t_Attirbs.push_back(0);
	t_Attirbs.push_back(1);
	t_Attirbs.push_back(2);
}

void vertexArrayObject::activateBuffer()
{
	glBindVertexArray(VaoId);
	for (auto next : t_Attirbs) {
		glEnableVertexAttribArray(next);
	}
}

void vertexArrayObject::deactivateBuffer()
{
	for (auto next : t_Attirbs) {
		glDisableVertexAttribArray(next);
	}
	glBindVertexArray(0);
}

unsigned int vertexArrayObject::getIndexCount()
{
	return indexCount;
}
