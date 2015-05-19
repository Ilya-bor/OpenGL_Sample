#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "glu32.lib")
#include "StdAfx.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Camera.h"
#include "Cube.h"


#define PI 3.14159265
#define AZIMUTHAL_INC 0.3
#define ZENITH_INC 0.3
#define MOVING_INC 0.1
#define MOVING_TIME 10

void display();
void reshape(int width, int height);
void MouseMove(int x, int y);
void SpecialKeyPressed(int key, int x, int y);
void SpecialKeyReleased(int key, int x, int y);
void Moving(int timerValue);


Camera camera;
int displayWidth;
int displayHeight;
bool upPressed;
bool rightPressed;
bool downPressed;
bool leftPressed;
void display()
{
 
 camera.Setup(displayWidth, displayHeight);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(-30, -10, -10);
    glRotatef(180, 0, 1, 0);
    glutSolidCube(20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 0, 10);
    glutSolidSphere(10,100,100);
    glPopMatrix();
 
    glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(-200,0,0);
    glVertex3f(100,0,0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0,200,0);
    glVertex3f(0,-100,0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0,0,50);
    glVertex3f(0,0,-200);
    glEnd();
 /* glPushMatrix();
  glColor3f(0.0, 1.0, 1.0);
  glTranslatef(-10, -10, 20);
  glRotatef(180, 0, 1, 0);
  glScalef(1.5, 0.5, 0.5);
  glutSolidCube(20);
  glPopMatrix();*/
  glutSwapBuffers();
  
}
void reshape(int w, int h)
{
  glViewport(0,0,(GLsizei)w,(GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  displayWidth = w;
  displayHeight = h;
  glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char* argv[])
{
    upPressed = false;
    rightPressed = false;
    downPressed = false;
    leftPressed = false;
    camera.SetPosition( Vector3(50, 15, 40) );
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(500.0, 500.0);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Test");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glutSetCursor(GLUT_CURSOR_NONE); 
    glutIgnoreKeyRepeat(1); 
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    glutPassiveMotionFunc(MouseMove); 
    glutSpecialFunc(SpecialKeyPressed); 
    glutSpecialUpFunc(SpecialKeyReleased); 
    Moving(0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GLfloat ambient[] = {  0.2f, 0.2f, 0.2f, 1 };
    GLfloat diffuse[] = {0.5f, 0.2f, 0.2f, 1 };
    GLfloat spec[] = { 0.8f, 0.8f, 0.8f,0.4 };
    GLfloat pos[] = {300, 300, 300, 0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);        	
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    /*  GLfloat pos1[] = {-60, 40, -20, 2 };
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);


    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, pos);*/
    // glEnable(GL_LIGHT2);
    // glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

    // glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    // glLightfv(GL_LIGHT2, GL_POSITION, pos1);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(90, 4/3, 1, 500);

    glutMainLoop();
}
void MouseMove(int x, int y)
{
    int xShift = (displayWidth >> 1) - x;
    int yShift = (displayHeight >> 1) - y;
    if (xShift != 0)
    {
        float azimuthalAngle = camera.GetAzimuthalAngle();
        if (xShift < 0)
        {
            camera.SetAzimuthalAngle(azimuthalAngle - AZIMUTHAL_INC >= 0 ? azimuthalAngle - AZIMUTHAL_INC : 360 + azimuthalAngle - AZIMUTHAL_INC);
        }
        else
        {
            camera.SetAzimuthalAngle(azimuthalAngle + AZIMUTHAL_INC < 360 ? azimuthalAngle + AZIMUTHAL_INC : 360 - azimuthalAngle - AZIMUTHAL_INC);
        }
    }
    if (yShift != 0)
    {
        float zenithAngle = camera.GetZenithAngle();
        if (yShift < 0)
        {
            if (zenithAngle - ZENITH_INC >= -90)
            {
                camera.SetZenithAngle(zenithAngle - ZENITH_INC);
            }
        }
        else
        {
            if (zenithAngle + ZENITH_INC <= 90)
            {
                camera.SetZenithAngle(zenithAngle + ZENITH_INC);
            }
        }
    }
    if (xShift != 0 || yShift != 0)
    {
        glutPostRedisplay(); //repaint
        glutWarpPointer(displayWidth >>1, displayHeight >>1 ); //return cursor to center
    }	
}
void SpecialKeyPressed(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: upPressed = true; break;
    case GLUT_KEY_RIGHT: rightPressed = true; break;
    case GLUT_KEY_DOWN: downPressed = true; break;
    case GLUT_KEY_LEFT: leftPressed = true; break;
    default: break;
    }
}
void SpecialKeyReleased(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: upPressed = false; break;
    case GLUT_KEY_RIGHT: rightPressed = false; break;
    case GLUT_KEY_DOWN: downPressed = false; break;
    case GLUT_KEY_LEFT: leftPressed = false; break;
    default: break;
    }
}
void Moving(int timerValue)
{
    if (upPressed || rightPressed || downPressed || leftPressed)
    {
        float azimuthalAngle = camera.GetAzimuthalAngle() * PI / 180;
        float zenithAngle = camera.GetZenithAngle() * PI / 180;
        Vector3 cameraPosition = camera.GetPosition();
        if (upPressed)
        {
            cameraPosition.Z -= (MOVING_INC*cosf(zenithAngle)) * cosf(azimuthalAngle);
            cameraPosition.X -= (MOVING_INC*cosf(zenithAngle)) * sinf(azimuthalAngle);
            cameraPosition.Y -= MOVING_INC*sinf(zenithAngle);
        }
        if (rightPressed)
        {
            cameraPosition.X += MOVING_INC * sinf((PI-2*azimuthalAngle)/2);
            cameraPosition.Z -= MOVING_INC * cosf((PI-2*azimuthalAngle)/2);
        }
        if (downPressed)
        {
            cameraPosition.Z += (MOVING_INC*cosf(zenithAngle)) * cosf(azimuthalAngle);
            cameraPosition.X += (MOVING_INC*cosf(zenithAngle)) * sinf(azimuthalAngle);
            cameraPosition.Y += MOVING_INC*sinf(zenithAngle);
        }
        if (leftPressed)
        {
            cameraPosition.X -= MOVING_INC * sinf((PI-2*azimuthalAngle)/2);
            cameraPosition.Z += MOVING_INC * cosf((PI-2*azimuthalAngle)/2);
        }
        camera.SetPosition(cameraPosition);
        glutPostRedisplay(); //repaint
    }
    glutTimerFunc(MOVING_TIME, Moving, 0); //функция по таймеру
}