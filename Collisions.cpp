#include "Collisions.h"

auto Collisions::DoBallsOverLap(float x1, float y1, float r1, float x2, float y2, float r2)
{
	return fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
};

std::tuple<bool, double> Collisions::DoTheyCollide(glm::vec3 A, glm::vec3 B) {
	/*float radiusSumSquared = 0.1;
	radiusSumSquared *= radiusSumSquared;
	double deltaXSquared = A.x - B.x; // calc. delta X
	deltaXSquared *= deltaXSquared; // square delta X
	double deltaYSquared = A.z - B.z; // calc. delta Y
	deltaYSquared *= deltaYSquared; // square delta Y
	if (deltaXSquared + deltaYSquared <= radiusSumSquared) {
		return true;// A and B are touching
	}*/

	double deltaXSquared = A.x - B.x; // calc. delta X
	deltaXSquared *= deltaXSquared; // square delta X
	double deltaYSquared = A.z - B.z; // calc. delta Y
	deltaYSquared *= deltaYSquared; // square delta Y
	double dist = sqrt(deltaXSquared + deltaYSquared);
	double sumRadii = 0.1;
	dist -= sumRadii;

	if (glm::length(A) < dist) {
		return std::make_tuple(false, 0);
	}

	glm::vec3 N = A;
	N = glm::normalize(N);

	glm::vec3 C = B - A;
	double D = glm::dot(N, C); // Oare? UPDATE: Da, e bine
	if (D <= 0) {
		return std::make_tuple(false, 0);
	}

	double lengthC = glm::length(C);
	double F = (lengthC * lengthC) - (D * D);
	double sumRadiiSquared = sumRadii * sumRadii;
	if (F >= sumRadiiSquared) {
		return std::make_tuple(false, 0);
	}

	double T = sumRadiiSquared - F;
	if (T < 0) {
		return std::make_tuple(false, 0);
	}

	double distance = D - sqrt(T);
	double mag = glm::length(A);
	if (mag < distance) {
		return std::make_tuple(false, 0);
	}

	return std::make_tuple(true, distance);
}

bool Collisions::DoTheyCollideHolles(glm::vec3 A, glm::vec3 B) {
	float radiusSumSquared = 0.15;
	radiusSumSquared *= radiusSumSquared;
	double deltaXSquared = A.x - B.x; // calc. delta X
	deltaXSquared *= deltaXSquared; // square delta X
	double deltaYSquared = A.z - B.z; // calc. delta Y
	deltaYSquared *= deltaYSquared; // square delta Y
	if (deltaXSquared + deltaYSquared <= radiusSumSquared) {
		return true;// A and B are touching
	}

	return false;
}



std::string Collisions::DoBallCollideWall(glm::vec3 A) {
	float south = 1.5 - 0.18;
	float north = -1.5 + 0.18;
	float west = -1 + 0.18;
	float east = 1 - 0.18;

	if (A.x < west) {
		return "WEST";
	}

	if (A.x > east) {
		return "EAST";
	}

	if (A.z < north) {
		return "NORTH";
	}

	if (A.z > south) {
		return "SOUTH";
	}

	return "FALSE";
}

std::tuple<bool, glm::vec3, glm::vec3> Collisions::SetDirectionAfterCollide(glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 n = v1 - v2;
	n = glm::normalize(n);
	float a1 = glm::dot(v1, n);
	float a2 = glm::dot(v2, n);
	float optimizedP = (2.0 * (a1 - a2)) / 0.4f;
	glm::vec3 v1_nou = v1 - optimizedP * 0.2f * n;
	glm::vec3 v2_nou = v2 - optimizedP * 0.2f * n;

	return std::make_tuple(true, v1_nou, v2_nou);
}

float Collisions::CalculateDistance(glm::vec3 A, glm::vec3 B) {
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.z - B.z)*(A.z - B.z));
}

std::vector<int> Collisions::GetOrientationAfterCollision(glm::vec3 A, glm::vec3 B) {
	std::vector<int> result;

	if (A.x >= B.x) {
		result.push_back(1);
	}

	if (A.x < B.x) {
		result.push_back(-1);
	}

	if (A.z >= B.z) {
		result.push_back(1);
	}

	if (A.z < B.z) {
		result.push_back(-1);
	}

	return result;
}


