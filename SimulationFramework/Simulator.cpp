//
// Created by erick on 20/03/17.
//

#include <thread>
#include "Simulator.h"
GLfloat dtA = 0.0;
GLfloat dspawn = 0.0;
GLfloat startColor = 1.0f;
GLfloat factor = -0.01f;

TextRenderer* textRenderer;

Simulator::Simulator(GLuint width, GLuint height)
		: State(SIMULATION_START_SCREEN), Width(width), Height(height)
{
	
}

Simulator::~Simulator()
{
	
}

void Simulator::Init() {
	// Load shaders
	ResourceManager::LoadShader("/home/erick/CLionProjects/GeneticGladiatorSimulator/shaders/sprite.vs",
	                            "/home/erick/CLionProjects/GeneticGladiatorSimulator/shaders/sprite.frag", nullptr,
	                            "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
	                                  static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Set render-specific controls
	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);
	
	// Load textures
	// Bkgrnd
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/Start.jpg", GL_FALSE,
	                             "background");
	
	//Top view players
	//red
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/red/rw1", GL_FALSE, "tv_r1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/red/rw2", GL_FALSE, "tv_r2");
	
	//green
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/green/gw1", GL_FALSE, "tv_g1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/green/gw2", GL_FALSE, "tv_g2");
	
	//Side view animations
	//red
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rDead", GL_FALSE, "rDead");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rKick1", GL_FALSE, "rKick1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rKick2", GL_FALSE, "rKick2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk1", GL_FALSE, "rWalk1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk2", GL_FALSE, "rWalk2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk3", GL_FALSE, "rWalk3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk4", GL_FALSE, "rWalk4");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk5", GL_FALSE, "rWalk5");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk6", GL_FALSE, "rWalk6");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rPunch1", GL_FALSE, "rPunch1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rPunch2", GL_FALSE, "rPunch2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rPunch3", GL_FALSE, "rPunch3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rGotHit1", GL_FALSE, "rGotHit1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rGotHit2", GL_FALSE, "rGotHit2");
	//green
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gDead", GL_FALSE, "gDead");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gKick1", GL_FALSE, "gKick1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gKick2", GL_FALSE, "gKick2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk1", GL_FALSE, "gWalk1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk2", GL_FALSE, "gWalk2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk3", GL_FALSE, "gWalk3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk4", GL_FALSE, "gWalk4");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk5", GL_FALSE, "gWalk5");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk6", GL_FALSE, "gWalk6");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gPunch1", GL_FALSE, "gPunch1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gPunch2", GL_FALSE, "gPunch2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gPunch3", GL_FALSE, "gPunch3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gGotHit1", GL_FALSE, "gGotHit1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gGotHit2", GL_FALSE, "gGotHit2");
	
	
	// Initialization of the game manager
	simulationManager = new SimulationManager(this->Width, this->Height);

	
	textRenderer = new TextRenderer(this->Width, this->Height);
	textRenderer->Load("/home/erick/CLionProjects/GeneticGladiatorSimulator/fonts/OCRAEXT.TTF", 24);
	this->State = SIMULATION_START_SCREEN;
	
}


void Simulator::Update(GLfloat dt)
{
	
	switch (this->State) {
		
		
		
		default:
			break;
			
	}


}


void Simulator::Render()
{
	if(this->State == SIMULATION_START_SCREEN) {
		
		// Draw background
		Texture2D backGround;
		backGround = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(backGround, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		
		
	
		textRenderer->RenderText("Presione ENTER para iniciar", Width / 3 , Height - 200, 1.0f, glm::vec3(startColor));
		if(startColor < 0.0f || startColor > 1.0f){
			factor *= -1;
		}
		startColor += factor;
		
	}
	
	else if(this->State == SIMULATION_WIN){
		textRenderer->RenderText(
				"Nivel superado!!!", 420.0, Height / 2 - 20.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
		);
		textRenderer->RenderText(
				"Presiona ENTER para continuar.", 250.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
		);
	}
	
	/*else if(this->State == SIMULATION_LOST){
		textRenderer->RenderText(
				"Has muerto :(", 420.0, Height / 2 - 20.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
		);
		textRenderer->RenderText(
				"Presiona ENTER para volver a intentarlo.", 200.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
		);
	}*/
	
	
}


void Simulator::ProcessInput(GLfloat dt) {
	
	switch (this->State) {
		
		case (SIMULATION_LABYRINTH):{
			
			// Move player
			if (this->Keys[GLFW_KEY_A]) {
			/*	GameObject *Player = simulationManager->getPlayer();
				GLfloat velocity = 500.0f * dt;
				
				if (Player->Position.x >= 0)
					Player->Position.x -= velocity;*/
			}
			else if (this->Keys[GLFW_KEY_D]) {
/*				GameObject *Player = simulationManager->getPlayer();
				GLfloat velocity = 500.0f * dt;
				
				if (Player->Position.x <= this->Width - Player->Size.x)
					Player->Position.x += velocity;*/
			}
			if (this->Keys[GLFW_KEY_S]) {
//				GameObject *Player = simulationManager->getPlayer();
				GLfloat velocity = 500.0f * dt;
				
				/*if (Player->Position.y <= this->Height - Player->Size.y)
					Player->Position.y += velocity;*/
			}
			else if (this->Keys[GLFW_KEY_W]) {
/*				GameObject *Player = simulationManager->getPlayer();
				GLfloat velocity = 500.0f * dt;
				
				if (Player->Position.y >= 0)
					Player->Position.y -= velocity;*/
			}
			if (this->Keys[GLFW_KEY_SPACE]) {
				//this->simulationManager->PressTheTrigger(dt);
			}
			if (this->Keys[GLFW_KEY_Q]) {
				//this->simulationManager->ActivatePowerUp();
			}
			if (((dt - dtA) >= 0.5) && (this->Keys[GLFW_KEY_ENTER])) {
				this->State = SIMULATION_PAUSED;
				dtA = 0.0;
			}
			else {
				dtA -= dt;
			}
			break;
			
		}
		
		case(SIMULATION_PAUSED): {
			
			if (((dt - dtA) >= 0.5) && (this->Keys[GLFW_KEY_ENTER])) {
				this->State = SIMULATION_LABYRINTH;
				dtA = 0.0;
			}
			else {
				dtA -= dt;
			}
			break;
		}
		
		
		case(SIMULATION_START_SCREEN): {
			if (this->Keys[GLFW_KEY_ENTER]) {
				this->State = SIMULATION_LABYRINTH;
			}
			break;
		}
	
	}
}
