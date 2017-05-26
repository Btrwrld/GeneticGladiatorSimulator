//
// Created by erick on 18/05/17.
//

#ifndef GENETICGLADIATORSIMULATOR_LABYRINTHMATRIX_H
#define GENETICGLADIATORSIMULATOR_LABYRINTHMATRIX_H

#include <cstdlib>
#include <fstream>
#include "DoublyLinkedList.h"

using namespace std;


struct MatrixNode {

public:
	MatrixNode(	unsigned short value) { this->value = value; }
	
	
	int costToGoal;
	unsigned short value;
	MatrixNode* top = nullptr;
	MatrixNode* bottom = nullptr;
	MatrixNode* left = nullptr;
	MatrixNode* right = nullptr;
	
	
	
	
	
};

class SimulationMatrix {

public:
	unsigned short Rows;
	unsigned short Columns;
	
	
	SimulationMatrix(unsigned short rows, unsigned short columns);
	
	MatrixNode *getGoalNode() const;
	MatrixNode *getStartNode() const;
	MatrixNode *getFirstElement() const;
	DoublyLinkedList<MatrixNode *> *getPath();
	bool hasSolution() const;

private:
	struct MatrixNode *goalNode = nullptr;
	struct MatrixNode *startNode = nullptr;
	struct MatrixNode *firstElement = nullptr;
	
	
	DoublyLinkedList<MatrixNode *> *path;
	
	bool solution;
	
	MatrixNode* generateRow( unsigned short row , unsigned short length);
	void mixRows( MatrixNode* top , MatrixNode* bottom , unsigned short length );
	void pathFinderAux(DoublyLinkedList<MatrixNode*>* blocked);
	void pathFindingAStar();
	void printMarix();
	
};






#endif //GENETICGLADIATORSIMULATOR_LABYRINTHMATRIX_H
