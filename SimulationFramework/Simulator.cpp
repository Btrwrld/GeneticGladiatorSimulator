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
	// Bkgrnds
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/start.jpg", GL_FALSE, "start");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/grass.jpg", GL_FALSE, "grass");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/scene.png", GL_FALSE, "coliseum");
	
	// Auxiliary objects
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/rock.png", GL_TRUE, "rock");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/gyarados.png", GL_TRUE, "gyarados");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/charizard.png", GL_TRUE, "charizard");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/fireball.png", GL_TRUE, "fireball");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/waterball.png", GL_TRUE, "waterball");
	
	//Top view players
	//red
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/red/rw1.png", GL_TRUE, "tv_r1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/red/rw2.png", GL_TRUE, "tv_r2");
	
	//green
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/green/gw1.png", GL_TRUE, "tv_g1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/topView/green/gw2.png", GL_TRUE, "tv_g2");
	
	//Side view animations
	//red
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rDead.png", GL_TRUE, "rDead");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rKick1.png", GL_TRUE, "rKick1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rKick2.png", GL_TRUE, "rKick2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk1.png", GL_TRUE, "rWalk1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk2.png", GL_TRUE, "rWalk2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk3.png", GL_TRUE, "rWalk3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk4.png", GL_TRUE, "rWalk4");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk5.png", GL_TRUE, "rWalk5");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rWalk6.png", GL_TRUE, "rWalk6");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rPunch1.png", GL_TRUE, "rPunch1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rPunch2.png", GL_TRUE, "rPunch2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rPunch3.png", GL_TRUE, "rPunch3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rGotHit1.png", GL_TRUE, "rGotHit1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/rGotHit2.png", GL_TRUE, "rGotHit2");
	//green
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gDead.png", GL_TRUE, "gDead");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gKick1.png", GL_TRUE, "gKick1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gKick2.png", GL_TRUE, "gKick2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk1.png", GL_TRUE, "gWalk1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk2.png", GL_TRUE, "gWalk2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk3.png", GL_TRUE, "gWalk3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk4.png", GL_TRUE, "gWalk4");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk5.png", GL_TRUE, "gWalk5");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gWalk6.png", GL_TRUE, "gWalk6");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gPunch1.png", GL_TRUE, "gPunch1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gPunch2.png", GL_TRUE, "gPunch2");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gPunch3.png", GL_TRUE, "gPunch3");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gGotHit1.png", GL_TRUE, "gGotHit1");
	ResourceManager::LoadTexture("/home/erick/CLionProjects/GeneticGladiatorSimulator/textures/sideView/gGotHit2.png", GL_TRUE, "gGotHit2");
	
	
	// Initialization of the game manager
	this->simulationManager = new SimulationManager(this->Width, this->Height);

	
	textRenderer = new TextRenderer(this->Width, this->Height);
	textRenderer->Load("/home/erick/CLionProjects/GeneticGladiatorSimulator/fonts/OCRAEXT.TTF", 24);
	this->State = SIMULATION_START_SCREEN;
	
}


void Simulator::Update(GLfloat dt)
{
	
	switch (this->State) {
		
		case SIMULATION_LABYRINTH: {
			
			simulationManager->lControlEnemies(dt);
			simulationManager->updateShots(dt);
			simulationManager->lCheckCollisions();
			simulationManager->escape(dt);
			
			break;
		}
		
		case SIMULATION_PVP: {
			
			simulationManager->PvPCheckCollisions(dt);
			
			break;
		}
		
		default:
			break;
			
	}


}


void Simulator::Render()
{
	if(this->State == SIMULATION_START_SCREEN) {
		
		// Draw background
		Texture2D backGround;
		backGround = ResourceManager::GetTexture("start");
		Renderer->DrawSprite(backGround, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		
		
	
		textRenderer->RenderText("Presione ENTER para iniciar", Width / 3 , Height - 200, 1.0f, glm::vec3(startColor));
		if(startColor < 0.0f || startColor > 1.0f){
			factor *= -1;
		}
		startColor += factor;
		
	}
	
	else if(this->State == SIMULATION_LABYRINTH){
		Texture2D backGround;
		backGround = ResourceManager::GetTexture("grass");
		Renderer->DrawSprite(backGround, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		
		simulationManager->DrawLabyrinth(*Renderer);
		
		if( (abs(simulationManager->getPlayer()->Position.x - 480.0f) < 5) &&
				(abs(simulationManager->getPlayer()->Position.y - 810.f) < 5)){
			simulationManager->clearMaze();
			this->State = SIMULATION_INTERLUDE;
		}
		
	}
	
	
	else if(this->State == SIMULATION_PVP){
		
		Texture2D backGround;
		backGround = ResourceManager::GetTexture("coliseum");
		Renderer->DrawSprite(backGround, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		
		simulationManager->DrawPvP(*Renderer);
		
	}
	
	else if(this->State == SIMULATION_INTERLUDE){
		if(flag){
			
			textRenderer->RenderText(
					"Simulacion del primer gladiador finalizada.", 200.0, Height / 2 - 20.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
			);
			textRenderer->RenderText(
					"Presiona ENTER para continuar con el segundo.", 200.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
			);

			
			
		}
		else{
			textRenderer->RenderText(
					"Simulacion del segundo gladiador finalizada.", 200.0, Height / 2 - 20.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
			);
			textRenderer->RenderText(
					"Presiona ENTER para continuar con PvP.", 200.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
			);
		}
		
	}
	
	
}


void Simulator::ProcessInput(GLfloat dt) {
	
	switch (this->State) {

		
		case (SIMULATION_PVP):{
			GLfloat velocity = 200.0f * dt;
			
			// Move player
			if (this->Keys[GLFW_KEY_A]) {
				GameObject *Player = simulationManager->getPlayer();
				
				
				if (Player->Position.x >= 0){
					Player->Position.x -= velocity;
					simulationManager->walk(true);
					Player->Size.x = 100.0f;
				}
					
			}
			else if (this->Keys[GLFW_KEY_D]) {
				GameObject *Player = simulationManager->getPlayer();
				
				if (Player->Position.x <= this->Width - Player->Size.x) {
					Player->Position.x += velocity;
					simulationManager->walk(true);
					Player->Size.x = 100.0f;
				}
			}
			if (this->Keys[GLFW_KEY_W]) {
				simulationManager->kick(true);
			}
			if (this->Keys[GLFW_KEY_S]) {
				simulationManager->punch(true);
				
			}
			
			
			
			
			
			if (this->Keys[GLFW_KEY_RIGHT]) {
				GameObject *Player = simulationManager->getOponent();
				
				if (Player->Position.x <= this->Width - Player->Size.x) {
					Player->Position.x += velocity;
					simulationManager->walk(false);
					Player->Size.x = 100.0f;
				}
			}
			else if (this->Keys[GLFW_KEY_LEFT]) {
				GameObject *Player = simulationManager->getOponent();
				
				
				if (Player->Position.x >= 0){
					Player->Position.x -= velocity;
					simulationManager->walk(false);
					Player->Size.x = 100.0f;
				}
			}
			if (this->Keys[GLFW_KEY_DOWN]) {
				simulationManager->punch(false);
				
			}
			if (this->Keys[GLFW_KEY_UP]) {
				simulationManager->kick(false);
				
			}
			
			break;
			
		}
		
		case(SIMULATION_INTERLUDE): {
			
			if (this->Keys[GLFW_KEY_ENTER]) {
				
				if(!flag){
					this->State = SIMULATION_PVP;
					simulationManager->setUpPvP();
				}
				else{
					this->State = SIMULATION_LABYRINTH;
					simulationManager->setUpMaze(true);
					flag = !flag;
				}
				
			}
			break;
		}
		
		
		case(SIMULATION_START_SCREEN): {
			if (this->Keys[GLFW_KEY_ENTER]) {
				this->State = SIMULATION_LABYRINTH;
				simulationManager->setUpMaze(false);
			}
			break;
		}
	
	}
}
