#pragma once
#include <Core/World.h>
#include <string>
#include "Tema2.h"

namespace Balls
{
	std::vector<std::tuple<std::string,
		std::string, glm::mat4>> Show(
			std::vector<Tema2::sBall> vecBalls, float rotateTac);
};

