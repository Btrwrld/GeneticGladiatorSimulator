//
// Created by erick on 26/03/17.
//

#ifndef AIRWAR_AI_H
#define AIRWAR_AI_H


#include <vector>
#include <fstream>
#include <sstream>

#include "GameObject.h"
#include "../SimulationFramework/SpriteRenderer.h"
#include "../SimulationFramework/ResourceManager.h"
#include "../DataStructures/DoublyLinkedList.h"
#include "PowerUp.h"
#include "../DataStructures/Stack.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

//The class that manipulates the enemies
class SimulationManager {
	
public:
	// Constructor
	SimulationManager(GLshort width, GLshort height);
	
	// Colision management
	void CheckCollision();
	void CheckPlayerCollision();
	void CheckEnemiesCollisions();
	
	// Render player and enemies
	void Draw(SpriteRenderer &renderer);
	void punch(bool player);
	
	//Movement and state update related
	void updateShots(GLfloat dt);
	void updatePowerUps(GLfloat dt);
	
	//Enemy-related actions
	void ControlEnemies(GLfloat dt, GLushort enemy);
	
	//PLayer-related actions
	void PressTheTrigger(GLfloat dt);
	void ActivatePowerUp();
	
	DoublyLinkedList<PowerUp> fieldPowerUps;
	
	//Getters
	GameObject *getPlayer() ;
	DoublyLinkedList<GameObject> &getPlayerShots() ;
	GLshort getPlayerLifes() const;
	Queue<GLushort> &getEnemySpawn() ;
	GLushort getPoints() const;
	GLushort getPlayerPowerUp();
	
	GLushort level= 1;

private:
	
	
	// Player management
	GameObject *Player = nullptr;
	GameObject *Oponent = nullptr;
	
	
	
	// Animation management
	Queue<GameObject> animations;
	
	//Collision management
	glm::vec4 getTruePosition(GameObject* enemy);
	bool CheckPlayerCollisionAux(GameObject* iterator);
	bool CheckEnemiesCollisionsAux(GameObject* auxIterator, glm::vec4 enemyPosition );
	
	//PowerUp management
	Stack<PowerUp> playerPowerUps;

	

	
	
	GLushort Width, Height;
};


#endif //AIRWAR_AI_H
