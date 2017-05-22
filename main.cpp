#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SimulationFramework/Simulator.h"
#include "DataStructures/LabyrinthMatrix.h"


DoublyLinkedList<MatrixNode> path;

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 1200;
// The height of the screen
const GLuint SCREEN_HEIGHT = 900;


Simulator GeneticGladiator(SCREEN_WIDTH, SCREEN_HEIGHT);


void pathFinderAux(DoublyLinkedList<MatrixNode*>* path, DoublyLinkedList<MatrixNode*>* blocked){
	

	if((path->sizeOf() > 0) && ((*path->get(path->sizeOf() - 1))->costToGoal != 0)){
		MatrixNode* current =  *path->get(path->sizeOf() - 1);
		DoublyLinkedList<MatrixNode*> successors;
		
		if((current->top != nullptr) && (current->top->value == 0) &&
				(!blocked->isContained(current->top)) && (!path->isContained(current->top))){
			
			successors.addLast(current->top);
		}
		
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
		
		pathFinderAux(path, blocked);
		
	}
	
}


DoublyLinkedList<MatrixNode*>* pathFindingAStar(SimulationMatrix* matrix){
	DoublyLinkedList<MatrixNode*> path;
	path.addLast(matrix->getStartNode());
	DoublyLinkedList<MatrixNode*> blocked;
	pathFinderAux(&path, &blocked);
	
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
	}
	
	
	return &path;
	
}


int main(void) {
	
	SimulationMatrix* test  = new SimulationMatrix( 10 , 10 );
	test->printMarix();
	DoublyLinkedList<MatrixNode*>* path = pathFindingAStar(test);
	
	return 0;
}
/*
int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AirWar++", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
	
	glfwSetKeyCallback(window, key_callback);
	
	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GeneticGladiator.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	
	// Start Simulator within Menu State
	//GeneticGladiator.State = GAME_PAUSED;
	
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		
		//deltaTime = 0.001f;
		// Manage user input
		GeneticGladiator.ProcessInput(deltaTime);
		
		// Update Simulator state
		GeneticGladiator.Update(deltaTime);
		
		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		GeneticGladiator.Render();
		
		glfwSwapBuffers(window);
	}
	
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
	
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			GeneticGladiator.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			GeneticGladiator.Keys[key] = GL_FALSE;
	}
}*/

