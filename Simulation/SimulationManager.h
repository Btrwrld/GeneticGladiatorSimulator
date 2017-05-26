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
#include "../DataStructures/Stack.h"
#include "../DataStructures/SimulationMatrix.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

//The class that manipulates the enemies
class SimulationManager {
	
public:
	// Constructor
	SimulationManager(GLshort width, GLshort height);
	
	// Colision management
	

	// Render player and enemies
	
	
	
	//Movement and state update related
	
	
	//Labirynth-related actions
	void setUpMaze(bool playerColor);
	void escape(GLfloat dt);
	void updateShots(GLfloat dt);
	void lControlEnemies(GLfloat dt);
	void DrawLabyrinth(SpriteRenderer &renderer);
	void lCheckCollisions();
	void clearMaze();
	
	void cleanAttributes();
	
	//PvP-related actions
	void setUpPvP();
	void DrawPvP(SpriteRenderer &renderer);
	void PvPCheckCollisions(GLfloat dt);
	//Animation-related actions
	void punch(bool player);
	void walk(bool player);
	void kick(bool player);
	bool isActing( bool player);
	
	
	//Enviroment set up
	
	
	//Getters
	GameObject *getPlayer() ;
	GameObject *getOponent() ;
	SimulationMatrix *getActualMaze() const;
	const glm::vec2 &getObjPos() const;

	

private:
	
	
	// PvP management
	GameObject *Player = nullptr;
	GLfloat rlastPos, glastPos;
	GLfloat gdtAttack = 0.0f;
	GLfloat rdtAttack = 0.0f;
	bool gisKicking = false;
	bool risKicking = false;
	bool gisPunching = false;
	bool risPunching = false;
	int iterationCounter = 0;
	int oponentIC = 0;
	int gWalkSecuence = 0;
	int gPunchSecuence = 0;
	int gKickSecuence = 0;
	int rWalkSecuence = 0;
	int rPunchSecuence = 0;
	int rKickSecuence = 0;
	
	

	
	GameObject *Oponent = nullptr;
	GLfloat dt = 0.0f;
	
	// intimidation zone object management
	DoublyLinkedList<GameObject> objects;
	DoublyLinkedList<GameObject> enemies;
	DoublyLinkedList<GameObject> shots;
	glm::vec2 objPos = glm::vec2(  480.0f , 0.0f );
	
	//Enviroment management
	SimulationMatrix* actualMaze = nullptr;
	Queue<int> pAttributes;
	Queue<int> oAttributes;
	
	//Labirynth-related actions
	void generateMaze();
	void getDirection();
	
	
	
	GLushort Width, Height;
};


#endif //AIRWAR_AI_H
