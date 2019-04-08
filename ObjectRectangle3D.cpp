#include "ObjectRectangle3D.h"
#include <Core/Engine.h>


Mesh* ObjectRectangle3D::CreateRectangle3D(std::string name,
	float heigth, float width,
	float length, glm::vec3 color)
{
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = 
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, 0, length), color),
		VertexFormat(corner + glm::vec3(0, 0, length), color),
		VertexFormat(corner + glm::vec3(0, heigth, 0), color),
		VertexFormat(corner + glm::vec3(width, heigth, 0), color),
		VertexFormat(corner + glm::vec3(width, heigth, length), color),
		VertexFormat(corner + glm::vec3(0, heigth, length), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	indices.push_back(0);
	indices.push_back(2);

	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(2);

	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(1);

	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(7);
	
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(0);

	indices.push_back(7);
	indices.push_back(4);
	indices.push_back(6);

	indices.push_back(6);
	indices.push_back(4);
	indices.push_back(5);

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
