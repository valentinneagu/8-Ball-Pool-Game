#include "Tema2.h"
#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "ObjectRectangle3D.h"
#include <time.h>
#include "PrepareMeshes.h"
#include "DisplayPlayingZone.h"
#include "Balls.h"
#include "Collisions.h"

using namespace std;

std::vector<glm::mat4> matrixes;
std::vector<std::tuple<std::string, std::string, glm::mat4>> table;
std::vector<std::tuple<std::string, std::string, glm::mat4>> result;

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::Init()
{
	//printf("TURN: Player1\n");
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	matrixes = DisplayPlayingZone::CreateHoles();
	table = DisplayPlayingZone::CreateTable();
	meshes = PrepareMeshes::setMeshes(meshes);

	//Initial positions
	Tema2::AddBall(0, 0.8, DefaultRadius);
	Tema2::AddBall(0, initial, DefaultRadius);
	Tema2::AddBall(sideStep, initial - backStep, DefaultRadius);
	Tema2::AddBall(-sideStep, initial - backStep, DefaultRadius);
	Tema2::AddBall(2 * sideStep, initial - 2 * backStep, DefaultRadius);
	Tema2::AddBall(0, initial - 2 * backStep, DefaultRadius);
	Tema2::AddBall(-2 * sideStep, initial - 2 * backStep, DefaultRadius);
	Tema2::AddBall(3 * sideStep, initial - 3 * backStep, DefaultRadius);
	Tema2::AddBall(sideStep, initial - 3 * backStep, DefaultRadius);
	Tema2::AddBall(-sideStep, initial - 3 * backStep, DefaultRadius);
	Tema2::AddBall(-3 * sideStep, initial - 3 * backStep, DefaultRadius);
	Tema2::AddBall(4 * sideStep, initial - 4 * backStep, DefaultRadius);
	Tema2::AddBall(2 * sideStep, initial - 4 * backStep, DefaultRadius);
	Tema2::AddBall(0 * sideStep, initial - 4 * backStep, DefaultRadius);
	Tema2::AddBall(-2 * sideStep, initial - 4 * backStep, DefaultRadius);
	Tema2::AddBall(-4 * sideStep, initial - 4 * backStep, DefaultRadius);


	//Set color vectors
	redBalls.push_back(1);
	redBalls.push_back(2);
	redBalls.push_back(6);
	redBalls.push_back(8);
	redBalls.push_back(9);
	redBalls.push_back(11);
	redBalls.push_back(12);
	redBalls.push_back(15);

	yellowBalls.push_back(3);
	yellowBalls.push_back(4);
	yellowBalls.push_back(7);
	yellowBalls.push_back(10);
	yellowBalls.push_back(13);
	yellowBalls.push_back(14);


	//Orientation of each ball
	for (int i = 0; i < 16; i++) {
		dissapear.push_back(false);
	}

	holesPositions.push_back(glm::vec3(-1 + 0.1, 1, -1.5 + 0.1));
	holesPositions.push_back(glm::vec3(1 - 0.1, 1, -1.5 + 0.1));
	holesPositions.push_back(glm::vec3(-1 + 0.1, 1, 1.5 - 0.1));
	holesPositions.push_back(glm::vec3(1 - 0.1, 1, 1.5 - 0.1));
	holesPositions.push_back(glm::vec3(-1 + 0.1, 1, 0));
	holesPositions.push_back(glm::vec3(1 - 0.1, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	myFov = RADIANS(60);
	myUp = 10;
	myBottom = -10;
	firstPerson = true;
	rotateTac = 0;
	mouseLeft = 0;
	mouseHoldLeft = false;
	rotateBall = false;
	ballDirection = 0;
	radiansToCue = 90;
	velocityMultiplier = 0;
	turns = 0;

	{
		Mesh* mesh = new Mesh("tac");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tac.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("cub");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(0, 0.02,  0), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(0.02,  0.02,  0), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(0.02,  0,  0), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(0, 0, 1.3), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(0, 0.02, 1.3), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(0.02,  0.02, 1.3), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(0.02,  0, 1.3), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 2, 6,		1, 5, 6,
			6, 7, 4,		6, 5, 4,
			0, 4, 1,		1, 4, 5,
			3, 7, 4,		0, 3, 4,
		};

		CreateMesh("tacv2", vertices, indices);
	}

	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

Mesh* Tema2::CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	//Camera settings
	if (firstPerson == true) {
		camera->Set(glm::vec3(0.7, 3, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	}

	result = Balls::Show(vecBalls, rotateTac);

	//HOLLS
	for (int i = 0; i < 6; i++) {
			glm::mat4 modelMatrix = matrixes[i];
			RenderMesh(meshes["sphere"], shaders["ColorBlack"], modelMatrix);
	}
	//Masa
	for (int i = 0; i < 5; i++) {
		RenderMesh(meshes[std::get<0>(table[i])], 
			shaders[std::get<1>(table[i])], std::get<2>(table[i]));
	}
	//Bile Joc
	for (int i = 0; i < 16; i++) {
		if (dissapear[i] == false) {
			RenderMesh(meshes[std::get<0>(result[i])],
				shaders[std::get<1>(result[i])], std::get<2>(result[i]));
		}
	}

	{
		//tac
		if (firstPerson == false) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(vecBalls[0].px, vecBalls[0].py, vecBalls[0].pz) - glm::vec3(0.01, 0.01, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(rotateTac), glm::vec3(0, 1, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(-10), glm::vec3(1, 0, 0));
				RenderSimpleMesh(meshes["tacv2"], shaders["ShaderTema2"], modelMatrix);
			}
		}
	}

	//===================================================================================================================================================================================
	//===================================================================================================================================================================================
	//===================================================================================================================================================================================
	//===================================================================================================================================================================================
	//===================================================================================================================================================================================


	if (firstBallIn == false) {
		for (int i = 0; i < 16; i++) {
			if (dissapear[i] == true) {
				for (auto it : redBalls) {
					if (i == it) {
						if (player == 1) {
							colorP1 = "RED";
							colorP2 = "YELLOW";
						}
						else {
							colorP2 = "RED";
							colorP1 = "YELLOW";
						}
					}
				}

				for (auto it : yellowBalls) {
					if (i == it) {
						if (player == 1) {
							colorP1 = "YELLOW";
							colorP2 = "RED";
						}
						else {
							colorP2 = "YELLOW";
							colorP1 = "RED";
						}
					}
				}
				firstBallIn = true;
				printf("Color Player1: %s\nColor Player2: %s\n", colorP1.c_str(), colorP2.c_str());
			}
		}
	}


	if (dissapear[0] == true) {
		printf("FAULT Player%d\n", player);
		vecBalls[0].px = 0;
		vecBalls[0].pz = 0.8;
		vecBalls[0].vx = 0;
		vecBalls[0].vz = 0;
		vecBalls[0].ax = 0;
		vecBalls[0].az = 0;
		dissapear[0] = false;
	}



	if (changePlayer) {
		if (player == 1) {
			player = 2;
		}
		else {
			player = 1;
		}

		printf("TURN: Player%d\n", player);
		changePlayer = false;
	}

	if (rotateBall) {
		if (velocityMultiplier > 5) {
			velocityMultiplier = 5;
		}
		vecBalls[0].vx = 2 * velocityMultiplier * -sin(ballDirection);
		vecBalls[0].vz = 2 * velocityMultiplier * -cos(ballDirection);
		rotateBall = false;
		rotateTac = 0;
		ballDirection = 0;
		velocityMultiplier = 0;
		radiansToCue = 90;

		turns++;
		/*if (turns % 2 == 1) {
			printf("TURN: Player2\n");
		}
		else {
			printf("TURN: Player1\n");
		}*/
	}


	



	vector<pair<sBall*, sBall*>> vecCollidingPairs;

	auto DoCirclesOverlap = [](float x1, float z1, float r1, float x2, float z2, float r2)
	{
		return fabs((x1 - x2) * (x1 - x2) + (z1 - z2) * (z1 - z2)) <= (r1 + r2) * (r1 + r2);
	};

	// Update Ball Positions
	for (auto &ball : vecBalls)
	{
		// Add Drag to emulate rolling friction
		ball.ax = -ball.vx * 0.8f;
		ball.az = -ball.vz * 0.8f;

		// Update ball physics
		ball.vx += ball.ax * deltaTimeSeconds;
		ball.vz += ball.az * deltaTimeSeconds;
		ball.px += ball.vx * deltaTimeSeconds;
		ball.pz += ball.vz * deltaTimeSeconds;

		// Clamp velocity near zero
		if (fabs(ball.vx*ball.vx + ball.vz*ball.vz) < 0.01f)
		{
			ball.vx = 0;
			ball.vz = 0;
		}
	}

	// Static collisions, i.e. overlap
	for (auto &ball : vecBalls)
	{
		for (auto &target : vecBalls)
		{
			if (ball.id != target.id && dissapear[ball.id] == false && dissapear[target.id] == false)
			{
				if (DoCirclesOverlap(ball.px, ball.pz, ball.radius, target.px, target.pz, target.radius))
				{
					// Collision has occured
					vecCollidingPairs.push_back({ &ball, &target });

					// Distance between ball centers
					float fDistance = sqrtf((ball.px - target.px)*(ball.px - target.px) + (ball.pz - target.pz)*(ball.pz - target.pz));

					// Calculate displacement required
					float fOverlap = 0.5f * (fDistance - ball.radius - target.radius);

					// Displace Current Ball away from collision
					ball.px -= fOverlap * (ball.px - target.px) / fDistance;
					ball.pz -= fOverlap * (ball.pz - target.pz) / fDistance;

					// Displace Target Ball away from collision
					target.px += fOverlap * (ball.px - target.px) / fDistance;
					target.pz += fOverlap * (ball.pz - target.pz) / fDistance;
					if (firstBallIn) {
						if (firstCollision) {
							firstCollision = false;
							if (player == 1) {
								if (colorP1 == "RED") {
									for (auto it : yellowBalls) {
										if (target.id == it) {
											printf("FAULT Player%d\n", player);
										}
									}
								}

								if (colorP1 == "YELLOW") {
									for (auto it : redBalls) {
										if (target.id == it) {
											printf("FAULT Player%d\n", player);
										}
									}
								}
							}

							if (player == 2) {
								if (colorP2 == "RED") {
									for (auto it : yellowBalls) {
										if (target.id == it) {
											printf("FAULT Player%d\n", player);
										}
									}
								}

								if (colorP2 == "YELLOW") {
									for (auto it : redBalls) {
										if (target.id == it) {
											printf("FAULT Player%d\n", player);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Now work out dynamic collisions
	for (auto c : vecCollidingPairs)
	{
		sBall *b1 = c.first;
		sBall *b2 = c.second;

		// Distance between balls
		float fDistance = sqrtf((b1->px - b2->px)*(b1->px - b2->px) + (b1->pz - b2->pz)*(b1->pz - b2->pz));

		// Normal
		float nx = (b2->px - b1->px) / fDistance;
		float nz = (b2->pz - b1->pz) / fDistance;

		// Tangent
		float tx = -nz;
		float tz = nx;

		// Dot Product Tangent
		float dpTan1 = b1->vx * tx + b1->vz * tz;
		float dpTan2 = b2->vx * tx + b2->vz * tz;

		// Dot Product Normal
		float dpNorm1 = b1->vx * nx + b1->vz * nz;
		float dpNorm2 = b2->vx * nx + b2->vz * nz;

		// Conservation of momentum in 1D
		float m1 = (dpNorm1 * (b1->mass - b2->mass) + 2.0f * b2->mass * dpNorm2) / (b1->mass + b2->mass);
		float m2 = (dpNorm2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpNorm1) / (b1->mass + b2->mass);

		// Update ball velocities
		b1->vx = tx * dpTan1 + nx * m1;
		b1->vz = tz * dpTan1 + nz * m1;
		b2->vx = tx * dpTan2 + nx * m2;
		b2->vz = tz * dpTan2 + nz * m2;

	}


	//===================================================================================================================================================================================
	//===================================================================================================================================================================================
	//===================================================================================================================================================================================
	//===================================================================================================================================================================================


	//Walls Collisions
	for (int i = 0; i < 16; i++) {
		std::string whereTheBallHit = Collisions::DoBallCollideWall(glm::vec3(vecBalls[i].px, vecBalls[i].py, vecBalls[i].pz));

		if (whereTheBallHit == "WEST" ||
			whereTheBallHit == "EAST") {
			vecBalls[i].vx = vecBalls[i].vx * -1;
		}

		if (whereTheBallHit == "SOUTH" ||
			whereTheBallHit == "NORTH") {
			vecBalls[i].vz = vecBalls[i].vz * -1;
		}
	}

	//Ball enters a hole
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 6; j++) {
			bool checkCollision = Collisions::DoTheyCollideHolles(glm::vec3(vecBalls[i].px, vecBalls[i].py, vecBalls[i].pz), holesPositions[j]);
			if (checkCollision == true) {
				dissapear[i] = true;
			}

		}
	}

	if (mouseHoldLeft) {
		radiansToCue -= deltaTimeSeconds * 50;
		if (radiansToCue < 0) {
			radiansToCue = 0;
		}
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->program, "Model");
	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->program, "View");
	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->program, "Projection");

	glm::mat4 projMatr = projectionMatrix;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projMatr));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

	
	location = glGetUniformLocation(shader->program, "time");

	//float time = Engine::GetElapsedTime();
	//glUniform1f(location, Engine::GetElapsedTime());
	glUniform1f(location, RADIANS(radiansToCue));

	location = glGetUniformLocation(shader->program, "mouseLeft");

	//float time = Engine::GetElapsedTime();
	glUniform1f(location, mouseLeft);
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

//NEW COLLISION ALGORITHM++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Tema2::AddBall(float x, float z, float r) {
	sBall b;
	b.px = x; b.pz = z; b.py = ballsHeigth;
	b.vx = 0; b.vz = 0;
	b.ax = 0; b.az = 0;
	b.radius = r;
	b.mass = r * 10.0f;

	b.id = vecBalls.size();
	vecBalls.emplace_back(b);
}

//END NEW COLLISION ALGORITHM+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// add key press event
	if (window->KeyHold(GLFW_KEY_W) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		vecBalls[0].px -= deltaTime;
		if (vecBalls[0].px < -1 + 0.15) {
			vecBalls[0].px = -1 + 0.15;
		}
	}

	if (window->KeyHold(GLFW_KEY_S) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		vecBalls[0].px += deltaTime;
		if (vecBalls[0].px > 1 - 0.15) {
			vecBalls[0].px = 1 - 0.15;
		}
	}

	if (window->KeyHold(GLFW_KEY_A) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		vecBalls[0].pz += deltaTime;
		if (vecBalls[0].pz > 1.35) {
			vecBalls[0].pz = 1.35;
		}
	}

	if (window->KeyHold(GLFW_KEY_D) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		vecBalls[0].pz -= deltaTime;
		if (vecBalls[0].pz < 0.5) {
			vecBalls[0].pz = 0.5;
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 0.1f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(cameraSpeed);
			// TODO : translate the camera forward
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-cameraSpeed);
			// TODO : translate the camera to the left
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(-cameraSpeed);
			// TODO : translate the camera backwards
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(cameraSpeed);
			// TODO : translate the camera to the right
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpword(-cameraSpeed);
			// TODO : translate the camera down
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpword(cameraSpeed);
			// TODO : translate the camera up
		}
	}

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && mouseHoldLeft == true) {
		firstPerson = true;
		rotateBall = true;
		mouseHoldLeft = false;
		firstCollision = true;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		firstPerson = false;
		camera->Set(glm::vec3(vecBalls[0].px, vecBalls[0].py, vecBalls[0].pz) + glm::vec3(0, 0.5, 1), 
			glm::vec3(vecBalls[0].px, vecBalls[0].py, vecBalls[0].pz), glm::vec3(0, 1, 0));
		changePlayer = true;
	}
	if (key == GLFW_KEY_Y)
	{
		firstPerson = true;
		camera->Set(glm::vec3(0.7, 3, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float sensivityOX = 0.001f;
	float sensivityOY = 0.001f;
	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (firstPerson) {
			camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);

		}
		if (!firstPerson) {
			camera->TranslateForward(1.118034);
			//camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
			camera->TranslateForward(-1.118034);
			rotateTac += -deltaX * 0.0573;
			ballDirection += -deltaX * sensivityOY;
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		mouseLeft = 1;
		mouseHoldLeft = true;
		velocityMultiplier += 0.1;
	}
	else {
		mouseLeft = 0;
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

