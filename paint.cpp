#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
//Math library included for the creation of shapes
#include <math.h>

/* SE 3GC3: Computer Graphics - Assignment 1 Part B	
 * Gabriel Lopez de Leon, lopezdg, 1310514
 * 08 October 2015
 */	 
 
 /*Code for the Different Types of Shapes
Shape Codes:
0 - Point
1 - Line
2 - Rectangles
3 - Circles
*/
int shapeType = 0;
 
int flag = 0;

//Different Colours for Shapes
float Red = 1.0f;
float Green = 1.0f;
float Blue = 1.0f;

//Points Selected for the Shapes (1 for Points, 2 for line/rectangle/circle)
int pointsSelected = 0;
int requiredPoints = 1;

//The X and Y Coordinates for the first point selected
float point1x = 0;
float point1y = 0;

//The X and Y Coordinates for the second point selected
float point2x = 0;
float point2y = 0;

//The following is used to draw a single point
void drawPixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

//The following is code to create lines in the paint program
void drawLine(float x1, float y1, float x2, float y2){
	//delta X and Y used to calculate the distance between two points which will be used to create a line
	float deltaY = y2 - y1;
	float deltaX = x2 - x1;

	float incAmount = (sqrt(pow(deltaX,2) + pow(deltaY,2)))/0.001;
	float increments = 0;
	
	//These represents the current coordinates for drawing
	float currentX = x1; 
	float currentY = y1; 

	for(int i = increments; i < incAmount; i++){
		drawPixel(currentX, currentY);
		currentX = currentX + deltaX/incAmount;
		currentY = currentY + deltaY/incAmount;
	}
}

void displayClear(){
	glColor3f(0.0f,0.0f,0.0f);

	//Since we cannot use certain gl functions like glClear, a clear method is simulated by adding a black box to the screen
	//note that the background was originaly black so it is as if all objects displayed are removed.
	for(float i = -1; i < 1; i+=0.001){
		drawLine(-1, i, 1, i);
	}
	glColor3f(Red,Green,Blue);
}

 //display function used to set up what the user sees when the program is run
void display(void)
{
	switch(shapeType){
		case 0: //Case for Point (code: 0)
			drawPixel(point1x, point1y);
			pointsSelected = 0;
			break;

		case 1: //Case for Line (code: 1)
			if(pointsSelected == requiredPoints){

				drawLine(point1x, point1y, point2x, point2y);
				printf("Line Drawn\n");
				pointsSelected = 0;
			}
			break;

		case 2: //Case for Rectangle (code: 2)
			if(pointsSelected == requiredPoints){
				//Use similar incrementing in drawLine
				float deltaY = point2y - point1y; //delta y
				float deltaX = point2x - point1x; //delta x

				float incAmount = (sqrt(pow(deltaX,2) + pow(deltaY,2)))/0.001;
				float increments = 0;
				
				float currentY = point1y; //current y coordinate for drawing
				float currentX = point1x; //current x coordinate for drawing
				
				for(int i = increments; i < incAmount; i++){
					drawLine(point1x, currentY, point2x, currentY);
					currentY = currentY + deltaY/incAmount;
				}

				printf("Rectangle Drawn\n");
				pointsSelected = 0;
			}
			break;

		case 3: //Case for Circle (code: 3)
			if(pointsSelected == requiredPoints){
				float deltaY = point2y - point1y; //delta y used to calculate distance of two points in the vertical(y) direction
				float deltaX = point2x - point1x; //delta x used to calculate distance of two points in the horizontal(x) direction
				
				float radius = (sqrt(pow(deltaX,2) + pow(deltaY,2))); //This gives the hypotenuse using the pythagorean theorem. Once again the math library is used for sqrt and pow
				float resolution = 1/(radius*50); //Used to scale the number of lines drawn with radius

				//The following code is used to rotate around the centre
				int circumference = 360;
				for(float i = 0; i < circumference; i+= resolution){
					drawLine(point1x, point1y, point1x + radius*cos(i), point1y + radius*sin(i)); //This uses the math library to access cos and sin functions
				}

				pointsSelected = 0;
				printf("Circle Drawn of Radius %f\n", radius);
			}
			break;
	}

	if(flag){
		glPointSize(10);
		glBegin(GL_POINTS);
			glVertex2f(-0.6f, -0.6f);
		glEnd();
	}

	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){

		case 'q': //use of lower case letters for the cases so as to not require the user to press multiple keys
			exit(0);
			break;

		case 'c':
			displayClear();
			printf("Display Cleared\n");
			break;

		case 'r':
			int randomNumber = rand() % 5; //The following code radomizes a number which is then used as the case number to choose a colour.
			switch(randomNumber){
				case 0: //Red
				Red = 1.0f;
				Green = 0.0f;
				Blue = 0.0f;
				printf("Random Colour Chosen: Red\n");
				break;

				case 1: //Green
					Red = 0.0f;
					Green = 1.0f;
					Blue = 0.0f;
					printf("Random Colour Chosen: Green\n");
					break;

				case 2: //Blue
					Red = 0.0f;
					Green = 0.0f;
					Blue = 1.0f;
					printf("Random Colour Chosen: Blue\n");
					break;

				case 3: //Purple
					Red = 1.0f;
					Green = 0.0f;
					Blue = 1.0f;
					printf("Random Colour Chosen: purple\n");
					break;

				case 4: //Yellow
					Red = 1.0f;
					Green = 1.0f;
					Blue = 0.0f;
					printf("Random Colour Chosen: yellow\n");
					break;

				default:
					break;
				}
	}
}

float *convertToGrid(float mouseX, float mouseY){

	float gridPos [2] = {0,0};
	int offSet = 150;
	mouseY = -mouseY;

	if(mouseX > offSet){
		mouseX = mouseX - offSet;
	}

	else if(mouseX < offSet){
		mouseX = -1 * (offSet - mouseX);
	}

	if(mouseY > offSet){
		mouseY = mouseY - offSet;
	}

	else if(mouseY < offSet){
		mouseY = -1 * (offSet - mouseY);
	}

	gridPos[0] = (mouseX) / offSet;
	gridPos[1] = (mouseY+300) / offSet;

	return gridPos;
}

void mouse(int btn, int state, int x, int y){
	switch(btn){
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_DOWN){
				glColor3f(Red, Green, Blue);
		
				if(pointsSelected == 0){
					point1x = convertToGrid(x,y)[0];
					point1y = convertToGrid(x,y)[1];
					printf("Point 1: %f, %f\n", point1x, point1y);
				}
				else{
					point2x = convertToGrid(x,y)[0];
					point2y = convertToGrid(x,y)[1];
					printf("Point 2: %f, %f\n", point2x, point2y);
				}

				pointsSelected++;
	
				flag = 0;
			}
			break;
	}
}

void motion(int x,int y){
	point1x = convertToGrid(x,y)[0];
	point1y = convertToGrid(x,y)[1];
	display();
}

void passive(int x,int y){
	
}

void showTimer(int value){
	glutTimerFunc(32, showTimer, 0);
	display();
}

void menu(int value){
	printf("Menu Interaction\n");
	switch(value){
		case 0: //Red
			Red = 1.0f;
			Green = 0.0f;
			Blue = 0.0f;
			break;

		case 1: //Green
			Red = 0.0f;
			Green = 1.0f;
			Blue = 0.0f;
			break;

		case 2: //Blue
			Red = 0.0f;
			Green = 0.0f;
			Blue = 1.0f;
			break;

		case 3: //Purple
			Red = 1.0f;
			Green = 0.0f;
			Blue = 1.0f;
			break;

		case 4: //Yellow
			Red = 1.0f;
			Green = 1.0f;
			Blue = 0.0f;
			break;

		case 5: //Point
			shapeType = 0;
			requiredPoints = 1;
			break;

		case 6: //Line
			shapeType = 1;
			requiredPoints = 2;
			break;

		case 7: //Rectangle
			shapeType = 2;
			requiredPoints = 2;
			break;
		
		case 8: //Circle
			shapeType = 3;
			requiredPoints = 2;
			break;
		case 9: //Closes the Program
			exit(0);
			break;
		case 10: //Clears the Screen
			displayClear();
			break;
	}
}

//functions which need to be run initialy when the program starts
void glutCallbacks(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
}

static int subMenu_id ;// used to creat a submenu for the colours
static int subMenu2_id ;// used to creat a submenu for the shapes
static int id ; // used to create the main menu which appears when the right mouse button is clicked

void initMenu(){
	subMenu_id = glutCreateMenu(menu);	
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);
	glutAddMenuEntry("Purple", 3);
	glutAddMenuEntry("Yellow", 4);
	subMenu2_id = glutCreateMenu(menu);
	glutAddMenuEntry("Points", 5);
	glutAddMenuEntry("Lines", 6);
	glutAddMenuEntry("Rectangles", 7);
	glutAddMenuEntry("Circles", 8);
	id = glutCreateMenu(menu);
	glutAddSubMenu("Colour", subMenu_id);
	glutAddSubMenu("Shape", subMenu2_id);
	glutAddMenuEntry("Clear", 10);
	glutAddMenuEntry("Quit", 9);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//The following is used as the main constructor of the code
int main(int argc, char** argv)
{

	glutInit(&argc, argv);	//This is used to start up GLUT
	glutCreateWindow("Paint: lopezdg - 1310514 ");	//creates the window and sets the title
	glutCallbacks();
	initMenu();
	showTimer(0);
	printf("\n\n\n\n---------------------------------\nPaint by Gabriel Lopez de Leon\n---------------------------------\nList of Controls:\n\nRandom Colour = 'r'\nClear Display = 'c'\nExit = 'q'\nAccess Menu = 'Right Mouse Button'\nDraw Point = 'Left Mouse Button'\n");
	glutMainLoop();	//starts the event loop which occurs when the program is running
	return(0);
}