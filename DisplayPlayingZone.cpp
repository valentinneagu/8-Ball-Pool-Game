#include "DisplayPlayingZone.h"
#include <Core/Engine.h>
#include <vector>
#include <iostream>


std::vector<glm::mat4> DisplayPlayingZone::CreateHoles() {

	std::vector<glm::mat4> matrixes;
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1 + 0.1, 1, -1.5 + 0.1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f));
			matrixes.push_back(modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1 - 0.1, 1, -1.5 + 0.1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f));
			matrixes.push_back(modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1 + 0.1, 1, 1.5 - 0.1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f));
			matrixes.push_back(modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1 - 0.1, 1, 1.5 - 0.1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f));
			matrixes.push_back(modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1 + 0.1, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f));
			matrixes.push_back(modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1 - 0.1, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f));
			matrixes.push_back(modelMatrix);
		}
		return matrixes;
}

std::vector<std::tuple<std::string, std::string, glm::mat4>> DisplayPlayingZone::CreateTable() {

	std::vector<std::tuple<std::string, std::string, glm::mat4>> table;

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0, -1.5));
		table.push_back(std::make_tuple("tableBase", "VertexColor", modelMatrix));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 1, -1.5));
		table.push_back(std::make_tuple("longSide", "VertexColor", modelMatrix));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1 - 0.1, 1, -1.5));
		table.push_back(std::make_tuple("longSide", "VertexColor", modelMatrix));
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 1, 1.5 - 0.1));
		table.push_back(std::make_tuple("shortSide", "VertexColor", modelMatrix));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 1, -1.5));
		table.push_back(std::make_tuple("shortSide", "VertexColor", modelMatrix));
	}
	
	return table;
}
