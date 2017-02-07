#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Game.hpp>

#include <GL/glut.h>

using namespace std;

// Current game pointer
Game* currGame;

// Function Declarations
void paintCell(int i, int j, color col);
void RenderString(float x, float y, void *font, const char* string);
void startWindow();
void EndScreen();
void displayCurrentState();
void displaySimulation();
std::pair<int,int> getClickedCell(int x,int y);
void onClick(int side, int state, int x, int y);
void runSimulation(unsigned char key, int x, int y);
void handleKeypress(unsigned char key, int x, int y);

// Draw boxes of the grid with a given color (retrieved from the current state)
void paintCell(int i, int j, color col)
{
	if(col == GREEN)glColor3f(0, 1, 0);
	else if(col == BLUE)glColor3f(0, 0, 1);
	else if(col == RED)glColor3f(1,0,0);
	else glColor3f(1, 1, 1);

	glBegin(GL_POLYGON);
		glVertex2i((GLint)j*CELL_SIZE, (GLint)(i)*CELL_SIZE);
		glVertex2i((GLint)j*CELL_SIZE, (GLint)(i+1)*CELL_SIZE);
		glVertex2i((GLint)(j+1)*CELL_SIZE, (GLint)(i+1)*CELL_SIZE);
		glVertex2i((GLint)(j+1)*CELL_SIZE, (GLint)(i)*CELL_SIZE);
	glEnd();
}

// Write text on openGL window
void RenderString(float x, float y, void *font, const char* string)
{  
  glRasterPos2f(x, y);

  int len = (int)strlen(string);
  for (int i = 0; i < len; i++)
  	glutBitmapCharacter(font, string[i]);
}

// Display the starting screen
void startWindow(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 	glColor3f(1, 0, 0); 
  	RenderString(330.0f, 350.0f, GLUT_BITMAP_TIMES_ROMAN_24, "ChecknGo");
  	RenderString(350.0f, 300.0f, GLUT_BITMAP_9_BY_15, "Press 1 to play vsPlayer");
  	RenderString(350.0f, 250.0f, GLUT_BITMAP_9_BY_15, "Press 2 to play vsAI (Random)");
  	RenderString(350.0f, 200.0f, GLUT_BITMAP_9_BY_15, "Press 3 to play vsAI (Minmax)");
  	RenderString(350.0f, 150.0f, GLUT_BITMAP_9_BY_15, "Press 4 to play vsAI (MCTS)");
  	RenderString(350.0f, 100.0f, GLUT_BITMAP_9_BY_15, "Press 5 to watch MCTS(Blue)");
  	RenderString(350.0f, 70.0f, GLUT_BITMAP_9_BY_15,  "vs MINMAX(Green)");

	glFlush();
  	glutSwapBuffers();
}

//Display the End window
void EndScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FOREACH(0, GRID_SIZE-1,i)
		FOREACH(0, GRID_SIZE-1,j){
			color pos = currGame->getColoratPosition(std::make_pair(i,j));
			paintCell(i,j,pos);
		}

	// Draw grid lines
	glColor3f(0,0,0);
	glBegin(GL_LINES);
    for (GLint i = 0; i < GRID_SIZE; i ++) {
      glVertex2f(i*CELL_SIZE, 0); glVertex2f(i*CELL_SIZE,GRID_SIZE*CELL_SIZE);
      glVertex2f(0, i*CELL_SIZE); glVertex2f(GRID_SIZE*CELL_SIZE, i*CELL_SIZE);
    }
  	glEnd();

 	glColor3f(1, 0, 0); 
  	RenderString(330.0f, 400.0f, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER !");

  	if(currGame->getWinner() == BLUE)
  		RenderString(330.0f, 300.0f, GLUT_BITMAP_TIMES_ROMAN_24, "BLUE WINS !");
  	else if(currGame->getWinner() == GREEN)
  		RenderString(330.0f, 300.0f, GLUT_BITMAP_TIMES_ROMAN_24, "GREEN WINS !");
  	else
  		RenderString(330.0f, 300.0f, GLUT_BITMAP_TIMES_ROMAN_24, "IT'S A DRAW !");

	glFlush();
  	glutSwapBuffers();
}

// Display this window for SINGLEPLAYER/MULTIPLAYER Game. It is updated with every move.
void displayCurrentState()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FOREACH(0, GRID_SIZE-1,i)
		FOREACH(0, GRID_SIZE-1,j){
			color pos = currGame->getColoratPosition(std::make_pair(i,j));
			paintCell(i,j,pos);
		}

	// Draw grid lines
	glColor3f(0,0,0);
	glBegin(GL_LINES);
    for (GLint i = 0; i < GRID_SIZE; i ++) {
      glVertex2f(i*CELL_SIZE, 0); glVertex2f(i*CELL_SIZE,GRID_SIZE*CELL_SIZE);
      glVertex2f(0, i*CELL_SIZE); glVertex2f(GRID_SIZE*CELL_SIZE, i*CELL_SIZE);
    }
  	glEnd();

  	glColor3f(1, 0, 0); 
  	RenderString(580.0f, 500.0f, GLUT_BITMAP_TIMES_ROMAN_24, "ChecknGo Rules:-");
  	RenderString(580.0f, 450.0f, GLUT_BITMAP_9_BY_15, "1. Select your piece");
  	RenderString(580.0f, 400.0f, GLUT_BITMAP_9_BY_15, "2. Possible moves are");
  	RenderString(580.0f, 380.0f, GLUT_BITMAP_9_BY_15, "   shown in Red");

  	RenderString(580.0f, 330.0f, GLUT_BITMAP_9_BY_15, "3. convert opponents by");
  	RenderString(580.0f, 310.0f, GLUT_BITMAP_9_BY_15, "   jumping near them");

  	RenderString(580.0f, 260.0f, GLUT_BITMAP_9_BY_15, "4. Maximize pieces of");
  	RenderString(580.0f, 240.0f, GLUT_BITMAP_9_BY_15, "	  your color");
  	RenderString(580.0f, 190.0f, GLUT_BITMAP_9_BY_15, "5. Esc to Exit ! ");


  	RenderString(580.0f, 150.0f, GLUT_BITMAP_9_BY_15, "NEXT TURN :");
  	if(currGame->getTurn() == BLUE){
  		glColor3f(0, 0, 1); 
  		RenderString(580.0f, 100.0f, GLUT_BITMAP_TIMES_ROMAN_24, "BLUE");
  	}
  	else{
  		glColor3f(0, 1, 0); 
  		RenderString(580.0f, 100.0f, GLUT_BITMAP_TIMES_ROMAN_24, "GREEN");
  	}

	glFlush();
  	glutSwapBuffers();
}

// Display this window to view game simulation for AIvsAI
void displaySimulation()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FOREACH(0, GRID_SIZE-1,i)
		FOREACH(0, GRID_SIZE-1,j){
			color pos = currGame->getColoratPosition(std::make_pair(i,j));
			paintCell(i,j,pos);
		}

	// Draw grid lines
	glColor3f(0,0,0);
	glBegin(GL_LINES);
    for (GLint i = 0; i < GRID_SIZE; i ++) {
      glVertex2f(i*CELL_SIZE, 0); glVertex2f(i*CELL_SIZE,GRID_SIZE*CELL_SIZE);
      glVertex2f(0, i*CELL_SIZE); glVertex2f(GRID_SIZE*CELL_SIZE, i*CELL_SIZE);
    }
  	glEnd();

  	glColor3f(1, 0, 0); 
  	RenderString(580.0f, 500.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press c to move");
  	RenderString(580.0f, 480.0f, GLUT_BITMAP_TIMES_ROMAN_24, "to next step");

  	RenderString(580.0f, 190.0f, GLUT_BITMAP_9_BY_15, "Esc to Exit ! ");


  	RenderString(580.0f, 150.0f, GLUT_BITMAP_9_BY_15, "NEXT TURN :");
  	if(currGame->getTurn() == BLUE){
  		glColor3f(0, 0, 1); 
  		RenderString(580.0f, 100.0f, GLUT_BITMAP_TIMES_ROMAN_24, "BLUE");
  	}
  	else{
  		glColor3f(0, 1, 0); 
  		RenderString(580.0f, 100.0f, GLUT_BITMAP_TIMES_ROMAN_24, "GREEN");
  	}

	glFlush();
  	glutSwapBuffers();
}

// Get board position for the clicked cell
std::pair<int,int> getClickedCell(int x,int y)
{
	return std::make_pair((GRID_SIZE - 1) - (y-40)/CELL_SIZE, x/CELL_SIZE);
}

// Mouse callback : validate the click and initiate the move
void onClick(int side, int state, int x, int y)
{
	if(side == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		std::pair<int, int> cell = getClickedCell(x,y);

		if(cell.first < 0 || cell.first > GRID_SIZE-1 || cell.second < 0 || cell.second > GRID_SIZE-1)
		{
			std::cout<<"Click inside the grid !"<<std::endl;
			return;
		}

		Status s = currGame->move(cell);
		glutPostRedisplay();

		if(s != SUCCESS)
		{
			if(s == END){
			std::cout<<"GAME OVER !"<<std::endl;
			glutDisplayFunc(EndScreen);
			
			}
			std::cout<<"BAD MOVE, status : "<<s<<std::endl;
		}

	}
}

// Keyboard control to view simulation
void runSimulation(unsigned char key, int x, int y){
	if(key == 'c'){
		Status s = currGame->move(std::make_pair(0,0));
		glutPostRedisplay();

		if(s != SUCCESS){
			if(s == END){
			std::cout<<"GAME OVER !"<<std::endl;
			glutDisplayFunc(EndScreen);
			glutKeyboardFunc(handleKeypress);
			}
			std::cout<<"BAD MOVE, status : "<<s<<std::endl;
			}
	}
	else if(key == 27){
			exit(-1);
	}
}

// Keyboard control for the start screen
void handleKeypress(unsigned char key, int x, int y){
if(key == 49){
	glutDisplayFunc(displayCurrentState);
	currGame = new Game((GameMode)MULTIPLAYER,(AIMode)NONE);
	glutMouseFunc(onClick);
	glutPostRedisplay();

}
else if(key == 50){
	glutDisplayFunc(displayCurrentState);
	currGame = new Game((GameMode)SINGLEPLAYER, (AIMode)RANDOM);
	glutMouseFunc(onClick);
	glutPostRedisplay();

}
else if(key == 51){
	glutDisplayFunc(displayCurrentState);
	currGame = new Game((GameMode)SINGLEPLAYER, (AIMode)MINMAX);
	glutMouseFunc(onClick);
	glutPostRedisplay();

}
else if(key == 52){
	glutDisplayFunc(displayCurrentState);
	currGame = new Game((GameMode)SINGLEPLAYER, (AIMode)MCTS);
	glutMouseFunc(onClick);
	glutPostRedisplay();

}
else if(key == 53){
	glutDisplayFunc(displaySimulation);
	currGame = new Game((GameMode)WATCH, (AIMode)NONE);
	glutKeyboardFunc(runSimulation);
	glutPostRedisplay();

}
else if(key == 27){
	exit(-1);
}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ChecknGo");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 800, 0,600);

	glutDisplayFunc(startWindow);
	glutKeyboardFunc(handleKeypress);

	glutMainLoop();
	return 0;
}