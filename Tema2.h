#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include <Core/GPU/Mesh.h>


class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

	struct sBall
	{
		float px, py, pz;
		float vx, vz;
		float ax, az;
		float radius;
		float mass;

		int id;
	};

	std::vector<sBall> vecBalls;


private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);
	Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);
	void AddBall(float x, float y, float r = 0.1f);


	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

private:
	bool start = false;
	float sideStep = 0.06;
	float backStep = 0.095;
	float initial = -0.6;
	float ballsHeigth = 1.05;
	bool firstPerson;

protected:
	Laborator::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	float myFov;
	float myUp;
	float myBottom;
	float rotateTac;
	float mouseLeft;
	bool mouseHoldLeft;
	bool rotateBall;
	float ballDirection;
	float radiansToCue;
	std::vector<bool> dissapear;
	std::vector<glm::vec3> holesPositions;

	float DefaultRadius = 0.05;

	float velocityMultiplier;
	int turns;
	bool changePlayer = false;
	int player = 2;

	std::vector<int> redBalls;
	std::vector<int> yellowBalls;

	float firstBallIn = false;
	std::string colorP1;
	std::string colorP2;
	bool firstCollision = false;
};

