#pragma once
#include <Core/World.h>

namespace PrepareMeshes
{
	std::unordered_map<std::string, Mesh*> setMeshes(
		std::unordered_map<std::string, Mesh*> meshes);
};

