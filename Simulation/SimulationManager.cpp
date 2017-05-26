//
// Created by erick on 26/03/17.
//

#include "SimulationManager.h"
#include "../Server/HttpRequester.h"

SimulationManager::SimulationManager(GLshort width, GLshort height){
	
	this->Width = width;
	this->Height = height;
}













void SimulationManager::lControlEnemies(GLfloat dt) {
	
	if(this->dt >= 3.0f){
		
		for (int i = 0; i < enemies.sizeOf(); ++i) {
			GameObject* enemy = enemies.get(i);
			
			if( enemy->tag == 1){
				shots.addLast(*new GameObject( glm::vec2( enemy->Position.x +10 , enemy->Position.y +45 ),
				                               glm::vec2(30.0f, 30.0f),
				                               ResourceManager::GetTexture("fireball"),
				                               glm::vec3(1.0f),
				                               glm::vec2(this->Player->Position.x - enemy->Position.x +10 , this->Player->Position.y - enemy->Position.y +45)));
			}
			
			else{
				shots.addLast(*new GameObject( glm::vec2( enemy->Position.x +10 , enemy->Position.y +45 ),
				                               glm::vec2(30.0f, 30.0f),
				                               ResourceManager::GetTexture("waterball"),
				                               glm::vec3(1.0f),
				                               glm::vec2(this->Player->Position.x - enemy->Position.x +10 , this->Player->Position.y - enemy->Position.y +45)));
			}
			
			
		}
		
		this->dt = 0.0f;
		
	}
	else{
		this->dt += dt;
	}
	
	
	


}

void SimulationManager::updateShots(GLfloat dt) {
	
	
	GameObject* iterator = nullptr;
	for (int i = 0; i < this->shots.sizeOf(); ++i) {
		iterator = this->shots.get(i);
		iterator->Position.x += iterator->Velocity.x * dt;
		iterator->Position.y += iterator->Velocity.y * dt;
	}
}

void SimulationManager::generateMaze() {
	
	this->actualMaze = new SimulationMatrix(10 , 10);
	
	if(!this->actualMaze->hasSolution()){
		this->generateMaze();
	}
}

void SimulationManager::setUpMaze(bool playerColor) {
	
	//Player setUp                      w/2 - playerSize.x/2    h - playerSize.y
	//true is green
	string pdata = getIndividuo();
	char data[1024];
	strncpy(data, pdata.c_str(), sizeof(data));
	data[sizeof(data) - 1] = 0;
	
	
	if( playerColor ){
		Player = new GameObject( glm::vec2( 480.0f , 0.0f), //Player position
		                         glm::vec2(100.0f, 90.0f),                            //Player size
		                         ResourceManager::GetTexture("tv_g1"));                //Player texture
		Player->tag = 1;
		
		
		
		int a = 0;
		for(int i = 0; i < 6; i++){
			oAttributes.push(data[a] - '0');
			a += 2;
		}
		
		Player->life = *oAttributes.get() * 10;
		oAttributes.dequeue();
		Player->Velocity.x = *oAttributes.get() * 1000;
		oAttributes.dequeue();
	}
	else{
		Player = new GameObject( glm::vec2( 480.0f , 0.0f), //Player position
		                         glm::vec2(100.0f, 90.0f),                            //Player size
		                         ResourceManager::GetTexture("tv_r1"));                //Player texture
		Player->tag = 2;
		
		
		int a = 0;
		for(int i = 0; i < 6; i++){
			pAttributes.push(data[a] - '0');
			a += 2;
		}
		
		Player->life = *pAttributes.get() * 10;
		pAttributes.dequeue();
		Player->Velocity.x = *pAttributes.get() * 1000;
		pAttributes.dequeue();
	}
	
	
	
	
	this->generateMaze();
	
	int x = 0;
	int y = 0;
	int counter = 1;
	
	MatrixNode* rowptr = this->actualMaze->getFirstElement();
	MatrixNode* columnptr = rowptr;
	bool flag = true;
	
	for (int row = 0; row < this->actualMaze->Rows; row++) {
		
		for (int column = 0; column <  this->actualMaze->Columns; column++) {
			if((columnptr->value == 1) && (counter%6 == 0)){
				GameObject* enemy;
				
				if(flag){
					enemy = new GameObject( glm::vec2( x , y ),
					                       glm::vec2(120.0f, 90.0f),
					                       ResourceManager::GetTexture("charizard"));
					enemy->tag = 1;
					
					
				
					
				}
				else{
					
					
					enemy =new GameObject( glm::vec2( x , y ),
					                       glm::vec2(120.0f, 90.0f),
					                       ResourceManager::GetTexture("gyarados"));
					enemy->tag = 2;
					
					
				}
				
				enemies.addLast( *enemy );
				flag = !flag;
				
			
				
				
			}
			else if((columnptr->value == 1) && !(counter%6 == 0)){
				objects.addLast( *new GameObject( glm::vec2( x , y ),
				                                  glm::vec2(120.0f, 90.0f),
				                                  ResourceManager::GetTexture("rock")));
			}
			
			counter+= 1;
			x += 120.0f;
			columnptr = columnptr->right;
		}
		
		x = 0.0f;
		y += 90.0f;
		rowptr = rowptr->bottom;
		columnptr = rowptr;
	}
}

void SimulationManager::getDirection() {

	
	if( (*this->actualMaze->getPath()->get(0))->top ==  *this->actualMaze->getPath()->get(1)){
		
		this->objPos.y -= 90.0f;
		
	}
	else if( (*this->actualMaze->getPath()->get(0))->bottom ==  *this->actualMaze->getPath()->get(1)){
		
		this->objPos.y += 90.0f;
		
	}
	else if( (*this->actualMaze->getPath()->get(0))->left ==  *this->actualMaze->getPath()->get(1)){
		
		this->objPos.x -= 120.0f;
		
	}
	else if( (*this->actualMaze->getPath()->get(0))->right ==  *this->actualMaze->getPath()->get(1)){
		
		this->objPos.x += 120.0f;
		
	}
	this->actualMaze->getPath()->remove(0);
	
}

void SimulationManager::escape(GLfloat dt) {
	
	if( (this->Player->Position.x -5 < this->objPos.x) && (this->objPos.x < this->Player->Position.x +5) &&
			(this->Player->Position.y -5 < this->objPos.y) && (this->objPos.y < this->Player->Position.y +5) &&
			( this->actualMaze->getPath()->sizeOf() > 1)){
		this->getDirection();
	}
	
	int x = abs( this->objPos.x - this->Player->Position.x );
	int y = abs( this->objPos.y - this->Player->Position.y );
	if( this->objPos.x > this->Player->Position.x ){
		this->Player->Position.x += dt*dt*this->Player->Velocity.x;
		if( x > y){
			this->Player->Rotation = -3.14 / 2;
		}
		
	}
	else if( this->objPos.x < this->Player->Position.x ){
		this->Player->Position.x -= dt*dt*this->Player->Velocity.x;
		if( x > y){
			this->Player->Rotation = 3.14 / 2;
		}
	}
	
	if( this->objPos.y > this->Player->Position.y ){
		this->Player->Position.y += dt*dt*this->Player->Velocity.x;
		if( x < y){
			this->Player->Rotation = 0;
		}
	}
	else if( this->objPos.y < this->Player->Position.y ){
		this->Player->Position.y -= dt*dt*this->Player->Velocity.x;
		if( x < y){
			this->Player->Rotation = 3.14;
		}
	}
	
	
	
}

void SimulationManager::DrawLabyrinth(SpriteRenderer &renderer) {
	
	for (int i = 0; i < enemies.sizeOf(); i++) {
		(enemies.get(i))->Draw(renderer);
	}
	
	for (int i = 0; i < objects.sizeOf(); i++) {
		(objects.get(i))->Draw(renderer);
	}
	
	for (int i = 0; i < shots.sizeOf(); i++) {
		(shots.get(i))->Draw(renderer);
	}
	
	
	this->Player->Draw(renderer);
	iterationCounter += 1;
	
	if( (Player->tag == 1) && (iterationCounter%30 == 15)) {
		this->Player->Sprite = ResourceManager::GetTexture("tv_g2");
	}
	else if( (Player->tag == 1) && (iterationCounter%30 == 0)) {
		this->Player->Sprite = ResourceManager::GetTexture("tv_g1");
	}
	else if ( (Player->tag == 2) && (iterationCounter%30 == 15)) {
		this->Player->Sprite = ResourceManager::GetTexture("tv_r2");
	}
	else if ( (Player->tag == 2) && (iterationCounter%30 == 0)){
		this->Player->Sprite = ResourceManager::GetTexture("tv_r1");
		iterationCounter = 0;
	}
	
	
	
}

void SimulationManager::lCheckCollisions() {
	
	for (int i = 0; i < this->shots.sizeOf(); i++) {
		GameObject* shot = shots.get(i);
	
		if( ((shot->Position.x + shot->Size.x > Player->Position.x +10) && (shot->Position.x < Player->Position.x +90)) &&
				( (shot->Position.y + shot->Size.y > Player->Position.y +15) && (shot->Position.y < Player->Position.y +50)) ){
		
			Player->life -= 5;
			shots.remove(i);
			cout << "player has been hit" << endl;
		}
		if( (shot->Position.x >= 1200) || (shot->Position.x + shot->Size.x <= 0) || (shot->Position.y < 0) || (shot->Position.y - shot->Size.y >= 900) ){
			
			shots.remove(i);
		}
		
	}
	
}

void SimulationManager::clearMaze() {
	
	int a = enemies.sizeOf();
	for (int i = 0; i < a; i++) {
		(enemies.remove(0));
	}
	
	a = objects.sizeOf();
	for (int i = 0; i < a; i++) {
		(objects.remove(0));
	}
	
	a = shots.sizeOf();
	for (int i = 0; i < a; i++) {
		(shots.remove(0));
	}
	actualMaze = nullptr;
	Player = nullptr;
	objPos = glm::vec2(  480.0f , 0.0f );
	
}



///            PvP-related             \\\*
void SimulationManager::setUpPvP() {
	
	this->iterationCounter = 0;
	this->Player = new GameObject( glm::vec2( 300.0f , 700.0f),                               //Player position
	                                   glm::vec2(150.0f, 200.0f),                            //Player size
	                                   ResourceManager::GetTexture("rPunch2"));              //Player texture
	
	//Tag va a ser el coeficiente de daño físico
	Player->tag = *pAttributes.get();
	pAttributes.dequeue();
	Player->life = *pAttributes.get() * 10;
	pAttributes.dequeue();

	
	this->Oponent = new GameObject( glm::vec2( 900.0f , 700.0f),                            //Player position
	                                glm::vec2(150.0f, 200.0f),                             //Player size
	                                ResourceManager::GetTexture("gPunch3"));               //Player texture
	Oponent->tag = *oAttributes.get();
	oAttributes.dequeue();
	Oponent->life = *oAttributes.get() * 10;
	oAttributes.dequeue();
}

///     Colision detection and position calculation      \\\*
void SimulationManager::PvPCheckCollisions(GLfloat dt) { // AABB - AABB collision
	
	if( risKicking && (rKickSecuence > 7) && (rdtAttack > 0.3f) &&
			(Oponent->Position.x <= Player->Position.x + 130) && (Oponent->Position.x + Oponent->Size.x > Player->Position.x +130) ){
		Oponent->life -= Player->tag * 0.75;
		rdtAttack = 0.0f;
		cout << "op has been kicked" << endl;
	}
	else if( risPunching && (rPunchSecuence > 14) && (rdtAttack > 0.3f) &&
	    (Oponent->Position.x <= Player->Position.x + 135) && (Oponent->Position.x + Oponent->Size.x > Player->Position.x +135) ){
		Oponent->life -= Player->tag * 0.4;
		rdtAttack = 0.0f;
		cout << "op has been punched" << endl;
	}
	else{
		rdtAttack += dt;
	}
	
	if( gisKicking && (gKickSecuence > 7) && (gdtAttack > 0.3f) &&
			(Player->Position.x <= Oponent->Position.x + 15) && (Player->Position.x + Player->Size.x > Oponent->Position.x +15) ){
		Player->life -= Oponent->tag * 0.75;
		gdtAttack = 0.0f;
		cout << "pl has been kicked" << endl;
	}
	else if( gisPunching && (gPunchSecuence > 14) && (gdtAttack > 0.3f) &&
			(Player->Position.x <= Oponent->Position.x + 15) && (Player->Position.x + Player->Size.x > Oponent->Position.x +15) ){
		Player->life -= Oponent->tag * 0.4;
		gdtAttack = 0.0f;
		cout << "pl has been punched" << endl;
	}
	else{
		gdtAttack += dt;
	}
	
	
	
	
}

void SimulationManager::DrawPvP(SpriteRenderer &renderer) {

	
	this->Player->Draw(renderer);
	this->iterationCounter += 1;
	if( (iterationCounter % 66 == 33) && (rlastPos == Player->Position.x) && (!isActing(true)) ){
		
		Player->Sprite = ResourceManager::GetTexture("rPunch1");
		Player->Size.x = 150.0f;
		
	
	}
	else if( (iterationCounter % 66 == 0) && (rlastPos == Player->Position.x) && (!isActing(true)) ){
		
		Player->Sprite = ResourceManager::GetTexture("rPunch2");
		iterationCounter = 0;
		Player->Size.x = 150.0f;
	}
	this->rlastPos = Player->Position.x;
	
	
	this->Oponent->Draw(renderer);
	this->oponentIC += 1;
	if( (oponentIC % 66 == 33) && (glastPos == Oponent->Position.x) && (!isActing(false)) ){
		
		Oponent->Sprite = ResourceManager::GetTexture("gPunch1");
		Oponent->Size.x = 150.0f;
		
	}
	else if( (oponentIC % 66 == 0) && (glastPos == Oponent->Position.x) && (!isActing(false)) ){
		
		Oponent->Sprite = ResourceManager::GetTexture("gPunch2");
		oponentIC = 0;
		Oponent->Size.x = 150.0f;
	}
	this->glastPos = Oponent->Position.x;
	
}


///            Adds the animation secuence for a character            \\\*

void SimulationManager::punch(bool player) {
	//User player
	//true is red
	if(player){
		
		switch(rPunchSecuence % 21){
			
			case 0:{
				this->Player->Sprite = ResourceManager::GetTexture("rPunch1");
				
				if( rPunchSecuence == 0){
					this->risPunching = true;
				}
				else if( rPunchSecuence == 21){
					this->risPunching = false;
					rPunchSecuence = -1;
				}
				
				break;
			}
			
			case 7:{
				this->Player->Sprite = ResourceManager::GetTexture("rPunch2");
				break;
			}
			
			case 14:{
				this->Player->Sprite = ResourceManager::GetTexture("rPunch3");
				break;
			}
			
		}
		
		rPunchSecuence += 1;
		
	}
	else{
		//false is green
		switch(gPunchSecuence % 21){
			
			case 0:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gPunch1");
				
				if( gPunchSecuence == 0){
					this->gisPunching = true;
				}
				else if( gPunchSecuence == 21){
					this->gisPunching = false;
					gPunchSecuence = -1;
				}
				break;
			}
			
			case 7:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gPunch2");
				break;
			}
			
			case 14:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gPunch3");
				break;
			}
			
		}
		
		gPunchSecuence += 1;
	}
	
}


void SimulationManager::kick(bool player) {
	
	//User player
	//true is red
	if(player){
		
		switch(rKickSecuence % 14){
			
			case 0:{
				this->Player->Sprite = ResourceManager::GetTexture("rKick1");
				
				if( rKickSecuence == 0){
					this->risKicking = true;
				}
				else if( rKickSecuence == 14){
					this->risKicking = false;
					rKickSecuence = -1;
				}
				
				break;
			}
			
			case 7:{
				this->Player->Sprite = ResourceManager::GetTexture("rKick2");
				break;
			}

			
		}
		
		rKickSecuence += 1;
		
	}
	else{
		//false is green
		switch(gKickSecuence % 14){
			
			case 0:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gKick1");
				
				if( gKickSecuence == 0){
					this->gisKicking = true;
				}
				else if( gKickSecuence == 14){
					this->gisKicking = false;
					gKickSecuence = -1;
				}
				break;
			}
			
			case 7:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gKick2");
				break;
			}
			
		}
		
		gKickSecuence += 1;
	}
	
}



void SimulationManager::walk(bool player) {
	
	//User player
	//true is red
	if(player){
		
		switch(rWalkSecuence % 60){
			
			case 0:{
				this->Player->Sprite = ResourceManager::GetTexture("rWalk1");
				rWalkSecuence = 0;
				break;
			}
			
			case 10:{
				this->Player->Sprite = ResourceManager::GetTexture("rWalk2");
				break;
			}
			
			case 20:{
				this->Player->Sprite = ResourceManager::GetTexture("rWalk3");
				break;
			}
			
			case 30:{
				this->Player->Sprite = ResourceManager::GetTexture("rWalk4");
				break;
			}
			
			case 40:{
				this->Player->Sprite = ResourceManager::GetTexture("rWalk5");
				break;
			}
			
			case 50:{
				this->Player->Sprite = ResourceManager::GetTexture("rWalk6");
				break;
			}
			
		}
		
		rWalkSecuence += 1;
		
	}
	else{
		//false is green
		switch(gWalkSecuence % 60){
			
			case 0:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gWalk1");
				gWalkSecuence = 0;
				break;
			}
			
			case 10:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gWalk2");
				break;
			}
			
			case 20:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gWalk3");
				break;
			}
			
			case 30:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gWalk4");
				break;
			}
			
			case 40:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gWalk5");
				break;
			}
			
			case 50:{
				this->Oponent->Sprite = ResourceManager::GetTexture("gWalk6");
				break;
			}
			
		}
		
		gWalkSecuence += 1;
	}
	
	risKicking = false;
	risPunching = false;
	gisKicking = false;
	gisPunching = false;
	
}




bool SimulationManager::isActing(bool player) {
	
	bool state;
	
	//User player
	//true is red
	if(player){
		state = risKicking || risPunching;
	}
	
	else{
		state = gisKicking || gisPunching;
		
	}
	
	return state;
	
}





void SimulationManager::cleanAttributes() {
	
	int a = this->oAttributes.sizeOf();
	for (int i = 0; i < a; ++i) {
		oAttributes.dequeue();
	}
	
	a = this->pAttributes.sizeOf();
	for (int j = 0; j < a; ++j) {
		pAttributes.dequeue();
	}
	
}



GameObject *SimulationManager::getPlayer() {
	return this->Player;
}

SimulationMatrix *SimulationManager::getActualMaze() const {
	return actualMaze;
}

const glm::vec2 &SimulationManager::getObjPos() const {
	return objPos;
}

GameObject *SimulationManager::getOponent()  {
	return Oponent;
}










