//
// Created by erick on 26/03/17.
//

#include "SimulationManager.h"

SimulationManager::SimulationManager(GLshort width, GLshort height){
	
	this->Width = width;
	this->Height = height;
	//Player setUp                      w/2 - playerSize.x/2    h - playerSize.y
	Player = new GameObject( glm::vec2( width / 2 - 100.0f / 2, height - 100.0f), //Player position
	                         glm::vec2(100.0f, 100.f),                            //Player size
	                         ResourceManager::GetTexture("ship"));                //Player texture
	Player->life = 500;
	Player->tag = 1;
	Player->Color = glm::vec3(0.0f , 1.0f , 0.0);
}

///     Colision detection and position calculation      \\\*
void SimulationManager::CheckPlayerCollision() { // AABB - AABB collision
	GameObject *iterator = nullptr;
	/*
	//Colision detection for player and enemy shots
	if(!this->Player->hasShield){
		for (int i = 0; i < this->enemyShots.sizeOf(); i++) {
			
			iterator = this->enemyShots.get(i);
			
			// Calls tha auxilary function tho check the axis collision
			if (this->CheckPlayerCollisionAux(iterator)) {
				
				Player->life -= iterator->tag * (9 + this->level);
				
				Texture2D auxText;
				if (Player->life <= 0) {
					auxText = ResourceManager::GetTexture("death");
					playerLifes -= 1;
					
					//Dormir el tread un tiempo
					
				} else {
					auxText = ResourceManager::GetTexture("hit");
					
				}
				iterator->tag = 0;
				this->animations.push(*new GameObject(iterator->Position,
				                                      glm::vec2(50.0f, 50.f),
				                                      auxText));
			}
			
		}
	}
	
	PowerUp *PUiterator = nullptr;
	//Colision detection for player powerUps
	for (int i = 0; i < this->fieldPowerUps.sizeOf(); i++) {
		
		//Iterator gets the value of the enemy shot
		PUiterator = this->fieldPowerUps.get(i);
		
		// Collision only if on both axes
		if ( this->CheckPlayerCollisionAux( PUiterator ) ) {
			
			this->playerPowerUps.push_back( *PUiterator );
			this->fieldPowerUps.remove(i);
		}
		
	}*/
}

bool SimulationManager::CheckPlayerCollisionAux(GameObject* iterator){
	
	// Collision x-axis?
	bool collisionX = Player->Position.x + Player->Size.x >= iterator->Position.x &&
	                  iterator->Position.x + iterator->Size.x >= Player->Position.x;
	// Collision y-axis?
	bool collisionY = Player->Position.y + Player->Size.y >= iterator->Position.y &&
	                  iterator->Position.y + iterator->Size.y >= Player->Position.y;
	
	return collisionX && collisionY;
}


void SimulationManager::CheckEnemiesCollisions() { // AABB - AABB collision
	/*GameObject *iterator = nullptr;
	GameObject *auxIterator = nullptr;
	
	//Colision detection for enemies and player bullets
	for (int i = 0; i < this->Enemies.sizeOf(); i++) {
		//Iterator takes the value of the limits of the enemy
		iterator = this->Enemies.get(i);
		if(iterator->tag !=7) {
			glm::vec4 enemyPosition = getTruePosition(iterator);
			
			for (int j = 0; j < this->playerShots.sizeOf(); j++) {
				
				//AuxIterator takes the value of a shot
				auxIterator = this->playerShots.get(j);
				
				// Calls tha auxilary function tho check the axis collision
				if (CheckEnemiesCollisionsAux(auxIterator, enemyPosition)) {
					
					iterator->life -= auxIterator->tag * (29 + this->level);
					Texture2D auxText;
					if (iterator->life <= 0) {
						this->points += iterator->tag;
						if (this->points% 100 == 0){
							this->playerLifes +=1;
						}
						
						short powerUpProb = rand() % 12;
						PowerUp *power = nullptr;
						switch (powerUpProb) {
							
							case 12: {
								// 12 represents a laser
								power = new PowerUp(3, glm::vec3(1.0f), 30.f,
								                    glm::vec2(iterator->Position.x, iterator->Position.y),
								                    ResourceManager::GetTexture("laserPU"));
								break;
							}
							case 11: {
								// 11 represents missiles
								power = new PowerUp(2, glm::vec3(1.0f), 30.f,
								                    glm::vec2(iterator->Position.x, iterator->Position.y),
								                    ResourceManager::GetTexture("missilePU"));
								break;
							}
							case 10: {
								// 10 represents the shield
								power = new PowerUp(1, glm::vec3(1.0f), 30.f,
								                    glm::vec2(iterator->Position.x, iterator->Position.y),
								                    ResourceManager::GetTexture("shield"));
								break;
							}
							default:
								break;
						}
						
						if (power != nullptr) {
							this->fieldPowerUps.addLast(*power);
						}
						
						auxText = ResourceManager::GetTexture("death");
					} else {
						auxText = ResourceManager::GetTexture("hit");
					}
					auxIterator->tag = 0;
					this->animations.push(*new GameObject(auxIterator->Position,
					                                      glm::vec2(50.0f, 50.f),
					                                      auxText));
				}
			}
		}
		
	}
	
	
	//Colision detection for player crashing with enemies
	if(!this->Player->hasShield) {
		for (int i = 0; i < this->Enemies.sizeOf(); i++) {
			if (this->Enemies.get(i)->tag != 7) {
				glm::vec4 enemyPosition = getTruePosition(this->Enemies.get(i));
				
				if (CheckEnemiesCollisionsAux(this->Player, enemyPosition)) {
					
					Texture2D auxText;
					auxText = ResourceManager::GetTexture("death");
					
					Player->life = 0;
					playerLifes -= 1;
					
					this->Enemies.get(i)->life = 0;
					
					//Dormir el tread un tiempo
					
					this->animations.push(*new GameObject(glm::vec2(enemyPosition.x, enemyPosition.z),
					                                      glm::vec2(enemyPosition.x - enemyPosition.y,
					                                                enemyPosition.z - enemyPosition.w),
					                                      auxText));
					
					this->animations.push(*new GameObject(Player->Position,
					                                      Player->Size,
					                                      auxText));
				}
			}
		}
	}*/
}

bool SimulationManager::CheckEnemiesCollisionsAux(GameObject* auxIterator, glm::vec4 enemyPosition ){
	
	// Collision x-axis?
	bool collisionX = auxIterator->Position.x + auxIterator->Size.x >= enemyPosition.x &&
	                  enemyPosition.y >= auxIterator->Position.x;
	// Collision y-axis?
	bool collisionY = auxIterator->Position.y + auxIterator->Size.y >= enemyPosition.z &&
	                  enemyPosition.w >= auxIterator->Position.y;
	return collisionX && collisionY;
}


glm::vec4 SimulationManager::getTruePosition(GameObject* enemy) {
	glm::vec4 position;
	
	
}





void SimulationManager::Draw(SpriteRenderer &renderer)
{
	
	
	
	this->Player->Draw(renderer);
	

}

///            Adds the punch secuence for a character            \\\*
void SimulationManager::punch(bool player) {
	//User player
	if(player){
		
		GameObject temp1 = *this->Player;
		temp1.Sprite = ResourceManager::GetTexture("gPunch1");
		this->animations.push(temp1);
		
		GameObject temp2 = *this->Player;
		temp2.Sprite = ResourceManager::GetTexture("gPunch2");
		this->animations.push(temp2);
		
		GameObject temp3 = *this->Player;
		temp3.Sprite = ResourceManager::GetTexture("gPunch3");
		this->animations.push(temp3);
		
	}
	else{
		
		GameObject temp1 = *this->Oponent;
		temp1.Sprite = ResourceManager::GetTexture("rPunch1");
		this->animations.push(temp1);
		
		GameObject temp2 = *this->Oponent;
		temp2.Sprite = ResourceManager::GetTexture("rPunch2");
		this->animations.push(temp2);
		
		GameObject temp3 = *this->Oponent;
		temp3.Sprite = ResourceManager::GetTexture("rPunch3");
		this->animations.push(temp3);
	}
	
}





///            Enemy-related             \\\*
void SimulationManager::ControlEnemies(GLfloat dt, GLushort enemyPos)
{

}









