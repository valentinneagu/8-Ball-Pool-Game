#pragma once
#include <Core/World.h>
#include <string>
#include <math.h>

namespace Collisions
{
	std::tuple<bool, double> DoTheyCollide(glm::vec3 A, glm::vec3 B);
	std::string DoBallCollideWall(glm::vec3 A);
	std::tuple<bool, glm::vec3, glm::vec3> SetDirectionAfterCollide(glm::vec3 v1, glm::vec3 v2);
	bool DoTheyCollideHolles(glm::vec3 A, glm::vec3 B);
	float CalculateDistance(glm::vec3 A, glm::vec3 B);
	std::vector<int> GetOrientationAfterCollision(glm::vec3 A, glm::vec3 B);
	
	auto DoBallsOverLap(float x1, float y1, float r1, float x2, float y2, float r2);
};

