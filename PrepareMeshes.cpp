#include "PrepareMeshes.h"
#include <Core/Engine.h>
#include "ObjectRectangle3D.h"

std::unordered_map<std::string, Mesh*> PrepareMeshes::setMeshes(
	std::unordered_map<std::string, Mesh*> meshes) {

		{
			Mesh* mesh = new Mesh("sphere");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* tableBase = ObjectRectangle3D::CreateRectangle3D("tableBase",
				1, 2, 3, glm::vec3(0, 0, 1));
			meshes[tableBase->GetMeshID()] = tableBase;
		}

		{
			Mesh* longSide = ObjectRectangle3D::CreateRectangle3D("longSide",
				0.085, 0.1, 3, glm::vec3(0, 0, 0.5));
			meshes[longSide->GetMeshID()] = longSide;
		}

		{
			Mesh* shortSide = ObjectRectangle3D::CreateRectangle3D("shortSide",
				0.085, 2, 0.1, glm::vec3(0, 0, 0.5));
			meshes[shortSide->GetMeshID()] = shortSide;
		}

		{
			Mesh* batz = ObjectRectangle3D::CreateRectangle3D("batz",
				0.02, 0.02, 1, glm::vec3(0.5, 0.5, 0.5));
			meshes[batz->GetMeshID()] = batz;
		}

	return meshes;
}
