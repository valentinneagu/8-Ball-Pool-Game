#include "Balls.h"
#include <Core/Engine.h>
#include <vector>
#include <iostream>

std::vector<std::tuple<std::string,
	std::string, glm::mat4>> Balls::Show(
		std::vector<Tema2::sBall> vecBalls, float rotateTac) {

	std::vector<std::tuple<std::string, std::string, glm::mat4>> result;
	std::vector<std::string> colors;
	colors.push_back("ColorWhite");
	colors.push_back("ColorRED");
	colors.push_back("ColorRED");
	colors.push_back("ColorYellow");
	colors.push_back("ColorYellow");
	colors.push_back("ColorBlack");
	colors.push_back("ColorRED");
	colors.push_back("ColorYellow");
	colors.push_back("ColorRED");
	colors.push_back("ColorRED");
	colors.push_back("ColorYellow");
	colors.push_back("ColorRED");
	colors.push_back("ColorRED");
	colors.push_back("ColorYellow");
	colors.push_back("ColorYellow");
	colors.push_back("ColorRED");

	for (int i = 0; i < 16; i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		/*if (i == 0) {
			modelMatrix = glm::rotate(modelMatrix, RADIANS(rotateTac), glm::vec3(0, 1, 0));
		}*/
		modelMatrix = glm::translate(modelMatrix, glm::vec3(vecBalls[i].px, vecBalls[i].py, vecBalls[i].pz));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		result.push_back(std::make_tuple("sphere", colors[i], modelMatrix));
	}

	return result;
}



