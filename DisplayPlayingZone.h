#pragma once
#include <Core/World.h>
#include <Component/SimpleScene.h>
#include <string>

namespace DisplayPlayingZone
{

	std::vector<glm::mat4> CreateHoles();
	std::vector<std::tuple<std::string, 
		std::string, glm::mat4>> CreateTable();

};

