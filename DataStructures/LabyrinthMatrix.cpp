//
// Created by erick on 18/05/17.
//

#include <random>
#include "LabyrinthMatrix.h"
#include "DoublyLinkedList.h"


SimulationMatrix::SimulationMatrix(unsigned short rows, unsigned short columns) {
	
	this->Rows = rows;
	this->Columns = columns;
	
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

MatrixNode *SimulationMatrix::getGoalNode() const {
	return goalNode;
}

MatrixNode *SimulationMatrix::getStartNode() const {
	return startNode;
}
