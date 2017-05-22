//
// Created by erick on 20/03/17.
//

#ifndef AIRWAR_GAME_H
#define AIRWAR_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "../Simulation/SimulationManager.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "TextRenderer.h"


// Represents the current state of the game
enum SimulationState {
	SIMULATION_LABYRINTH,
	SIMULATION_PAUSED,
	SIMULATION_START_SCREEN,
	SIMULATION_WIN,
	SIMULATION_PVP,
};

class Simulator {
private:
	// Simulator-related State data
	SpriteRenderer*  Renderer = nullptr;
	SimulationManager*     simulationManager = nullptr;
	GLshort          lastMove = 0;
	bool server = false;
	
public:
	// Simulator state
	SimulationState  State;
	GLboolean  Keys[1024];
	GLushort   Width, Height;
	
	// Constructor/Destructor
	Simulator(GLuint width, GLuint height);
	~Simulator();
	
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	
};


#endif //AIRWAR_GAME_H