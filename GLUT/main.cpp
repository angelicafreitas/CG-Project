#include<fstream>
#include<sstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif




float translate[3] = {0,0,0};
float rotate[4] = {0,0,0,0};

void removeChar(std::string& str, char character)
{
	size_t pos;
	while ((pos = str.find(character)) != std::string::npos)
		str.erase(pos, 1);
}

void fileToGL(std::string file) {

	std::ifstream fd(file);
	float x, y, z;
	int i;

	for (std::string line; getline(fd, line);) {

		removeChar(line, ',');

		//if(line[0] != )

		std::istringstream data(line);

		for (i = 0; i < 3; i++) {
			data >> x >> y >> z;
			glVertex3f(x, y, z);

		}

	}

}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();


	// put the geometric transformations here
	glTranslatef(translate[0],translate[1],translate[2]);
	glRotatef(rotate[0],rotate[1],rotate[2],rotate[3]);

	// put drawing instructions here
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);

	
	/*glPushMatrix();
	glTranslated(0.0, -1.2, -6);
	glutWireSphere(1, 20, 3);
	glPopMatrix();
	*/
	
	glBegin(GL_TRIANGLES);;

	
	fileToGL("lol.txt");


	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events




void function(unsigned char key, int x, int y) { 
	if (key == 'A' || key == 'a') {
		translate[0] += -.5;
		glutPostRedisplay();
	}
	else if (key == 'S' || key == 's') {
		translate[1] += -.5;
		glutPostRedisplay();
	}
	else if (key == 'd' || key == 'D') {
		translate[0] += .5;
		glutPostRedisplay();
	}
	else if (key == 'w' || key == 'W') {
		translate[1] += .5;
		glutPostRedisplay();
	}
	else if (key == 'R' || key == 'r') {
		rotate[0] += 5;
		rotate[2] = 1.0;
		glutPostRedisplay();
	}

	else if (key == 't' || key == 'T') {
		rotate[0] += 5;
		rotate[1] = 1.0;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(function);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
