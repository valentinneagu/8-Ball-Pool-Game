#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
namespace ObjectRectangle3D
{
	Mesh* CreateRectangle3D(std::string name,
		float heigth, float width, 
		float length, glm::vec3 color);
};

