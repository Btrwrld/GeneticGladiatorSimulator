//
// Created by erick on 18/05/17.
//

#include <random>
#include "SimulationMatrix.h"
#include "DoublyLinkedList.h"


SimulationMatrix::SimulationMatrix(unsigned short rows, unsigned short columns) {
	
	this->Rows = rows;
	this->Columns = columns;
	this->path = new DoublyLinkedList<MatrixNode *>();
	
	struct MatrixNode* topRow = generateRow( 0 , Columns);
	this->firstElement = topRow;
	
	for(int row = 1; row < Rows; row++ ){
		
		struct MatrixNode* bottomRow = generateRow( row , Columns);
		
		mixRows( topRow , bottomRow , Columns );
		
		topRow = bottomRow;
		
	}
	this->startNode = this->firstElement;
	for(int i = 0; i < 4; i++){
		this->startNode = this->startNode->right;
	}
	
	this->goalNode = this->startNode;
	for(int i = 0; i < 9; i++){
		this->goalNode = this->goalNode->bottom;
	}
	
	this->pathFindingAStar();
	
}


MatrixNode *SimulationMatrix::generateRow(unsigned short row, unsigned short length) {
	
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0,9);
	
	DoublyLinkedList<int> pos;
	pos.addLast(dist6(rng));
	pos.addLast(dist6(rng));
	pos.addLast(dist6(rng));
	pos.addLast(dist6(rng));
	
	
	struct MatrixNode* matrixNode = new MatrixNode(0);
	struct MatrixNode* firstNode = matrixNode;
	
	for( int i = 0; i < length; i++){
		
	

		matrixNode->costToGoal =  abs(row - (this->Rows - 1)) + abs((i + 1) - (this->Columns/2));
		
		if(pos.isContained(i)){
			
			matrixNode->right = new MatrixNode(1);
			
		}
		else{
			
			matrixNode->right = new MatrixNode(0);
			
		}
		
		
		matrixNode->right->left = matrixNode;
		matrixNode = matrixNode->right;
		
		if( (i == 3) &&( (row == 0) || ( row == this->Rows -1))){
			matrixNode->value = 0;
		}
		
	}
	
	matrixNode->costToGoal =  abs(row - (this->Rows - 1)) + abs(length - (this->Columns/2));

	
	return firstNode;
}

void SimulationMatrix::mixRows(MatrixNode *top, MatrixNode *bottom, unsigned short length) {
	
	for (int i = 0; i < length; i++){
		
		top->bottom = bottom;
		bottom->top = top;
		
		top = top->right;
		bottom = bottom->right;
	}
	
}

void SimulationMatrix::printMarix() {
	
	ofstream archivo;
	archivo.open("/home/erick/CLionProjects/GeneticGladiatorSimulator/Lab.txt");
	
	struct MatrixNode *rowptr = firstElement;
	struct MatrixNode *columnptr = rowptr;
	
	for (int row = 0; row < Rows; row++) {
		
		for (int column = 0; column < Columns; column++) {
			archivo << columnptr->value;
			columnptr = columnptr->right;
		}
		
		archivo << endl;
		rowptr = rowptr->bottom;
		columnptr = rowptr;
	}
}


void SimulationMatrix::pathFindingAStar(){
	path->addLast(this->getStartNode());
	DoublyLinkedList<MatrixNode*> blocked = *new DoublyLinkedList<MatrixNode*>();
	pathFinderAux(&blocked);
	/*
	if(path.sizeOf() == 0){
		cout << "No tiene solución" << endl;
	}
	else{
		for (int i = 1; i < path.sizeOf(); ++i) {
			
			if(*path.get(i) == (*path.get(i - 1))->top){
				cout << "Arriba" << endl;
			}
			else if(*path.get(i) == (*path.get(i - 1))->bottom){
				cout << "Abajo" << endl;
			}
			else if(*path.get(i) == (*path.get(i - 1))->left){
				cout << "Izq" << endl;
			}
			else if(*path.get(i) == (*path.get(i - 1))->right){
				cout << "Der" << endl;
			}
		}
	}*/
	
	printMarix();
	
	if(path->sizeOf() ==0){
		
		this->solution = false;
		
	}
	else{
		this->solution = true;
	}
}

void SimulationMatrix::pathFinderAux(DoublyLinkedList<MatrixNode*>* blocked){
	
	
	if((path->sizeOf() > 0) && ((*path->get(path->sizeOf() - 1))->costToGoal != 0)){
		MatrixNode* current =  *path->get(path->sizeOf() - 1);
		DoublyLinkedList<MatrixNode*> successors;
		
		if((current->bottom != nullptr) && (current->bottom->value == 0) &&
		   (!blocked->isContained(current->bottom)) && (!path->isContained(current->bottom))){
			
			successors.addLast(current->bottom);
		}
		
		if((current->right != nullptr) && (current->right->value == 0) &&
		   (!blocked->isContained(current->right)) && (!path->isContained(current->right))){
			
			successors.addLast(current->right);
		}
		
		
		if((current->left != nullptr) && (current->left->value == 0) &&
		   (!blocked->isContained(current->left)) && (!path->isContained(current->left))){
			
			successors.addLast(current->left);
		}
		
		if((current->top != nullptr) && (current->top->value == 0) &&
		   (!blocked->isContained(current->top)) && (!path->isContained(current->top))){
			
			successors.addLast(current->top);
		}
		
		
		if(successors.sizeOf() == 0){
			blocked->addLast(current);
			path->remove(path->sizeOf() - 1);
		}
		else{
			MatrixNode* successor = *successors.get(0);
			for(int i = 1; i < successors.sizeOf(); i++){
				
				if ( ((*successors.get(i))->costToGoal + current->costToGoal) < (successor->costToGoal + current->costToGoal)) {
					successor = *successors.get(i);
				}
				
			}
			
			path->addLast(successor);
		}
		
		pathFinderAux(blocked);
		
	}
	
}





MatrixNode *SimulationMatrix::getGoalNode() const {
	return goalNode;
}

MatrixNode *SimulationMatrix::getStartNode() const {
	return startNode;
}

MatrixNode *SimulationMatrix::getFirstElement() const {
	return firstElement;
}

DoublyLinkedList<MatrixNode *> *SimulationMatrix::getPath()  {
	return path;
}

bool SimulationMatrix::hasSolution() const {
	return solution;
}
