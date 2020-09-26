#include "LoaderOBJ.h"
#include "Octree.h"
#include <windows.h>
#include <iostream>
#include <math.h>
#include<GL/glut.h>
#include <cmath>
#include <vector>
#include <stdlib.h>
#define KEY_ESC 27
#define GLUT_DISABLE_ATEXIT_HACK
using namespace std;

template<class T>
void PrintOctree(Octree<T>* octo)
{
	if (octo == NULL)
	{
		return;
	}

	if (octo->Points.size() == 0 &&
		octo->zero == NULL && octo->one == NULL && octo->two == NULL && octo->thre == NULL &&
		octo->four == NULL && octo->five == NULL && octo->six == NULL && octo->seven == NULL)
	{
		glPushMatrix();
		glTranslatef((octo->A.x + octo->B.x) / 2, (octo->A.y + octo->B.y) / 2, (octo->A.z + octo->B.z) / 2);	
		glutSolidCube(octo->ancho);		
		glPopMatrix();
	}

	if (octo->Points.size() != 0)
	{
		glPushMatrix();
		glTranslatef((octo->A.x + octo->B.x) / 2, (octo->A.y + octo->B.y) / 2, (octo->A.z + octo->B.z) / 2);	
		glutSolidCube(octo->ancho);		
		glPopMatrix();

		for (unsigned int i = 0; i < octo->Points.size(); i++)
		{
			glBegin(GL_POINTS);
			glColor3d(250, 0, 0); 	
			glVertex3d(octo->Points[i].x, octo->Points[i].y, octo->Points[i].z);	
			glEnd();
			glPointSize(6.0);
		}

	}
	if (octo->Points.size() == 0 && octo->zero != NULL && octo->one != NULL && octo->two != NULL && octo->thre != NULL &&
		octo->four != NULL && octo->five != NULL && octo->six != NULL && octo->seven != NULL)
	{
		glPushMatrix();
		glTranslatef((octo->A.x + octo->B.x) / 2, (octo->A.y + octo->B.y) / 2, (octo->A.z + octo->B.z) / 2);
		glutSolidCube(octo->ancho);		
		glPopMatrix();
		PrintOctree(octo->five);
		PrintOctree(octo->seven);
		PrintOctree(octo->one);
		PrintOctree(octo->thre);
		PrintOctree(octo->four);
		PrintOctree(octo->six);
		PrintOctree(octo->zero);
		PrintOctree(octo->two);
	}
}



int mx = 0;
int my = 0;
double ax = 0.0;
double ay = 0.0;
double speed = 0.1;

void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex3d(-30, 0, 0);
	glVertex3d(30, 0, 0);
	glColor3d(0, 255, 0);
	glVertex3d(0, -30, 0);
	glVertex3d(0, 30, 0);
	glColor3d(0, 0, 255);
	glVertex3d(0, 0, -30);
	glVertex3d(0, 0, 30);
	glEnd();
}
bool r = false;

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx = x;
		my = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		r = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		r = false;
	}
}

void OnMouseMotion(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;
	mx = x;
	my = y;
	ax += dx * speed;
	ay += dy * speed;
}



void idle() { 
	glutPostRedisplay();
}


Octree<double> Octree1(Point3D<double>(-4, -4, 4), Point3D<double>(4, 4, -4), 8);

void glPaint(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	gluPerspective(2, 1, 0.5, 500.0);
	glTranslatef(0, 0, -100.0);
	glRotatef(ax, 0, 1, 0);
	glRotatef(ay, 1, 0, 0);

	displayGizmo();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	PrintOctree(&Octree1);
	
	glutSwapBuffers();
}

void init_GL(void) {
	glClearColor(255, 255, 255, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	default:
		break;
	}
}


int main(int argc,char ** argv) {
	
	vector<vector<double> > Vertex;

	Vertex = LoadObj("Rabbit.obj");

	cout << Vertex.size() << endl;

	
	for (short i = 0; i < Vertex.size(); ++i) {
		Octree1.Insertar(Point3D<double>(Vertex[i][0], Vertex[i][1], Vertex[i][2]));
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); 
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Octree"); 
	init_GL(); 
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
	glutMainLoop();
	
	return 0;
}

