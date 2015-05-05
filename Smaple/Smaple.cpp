#include "StdAfx.h"
#include <GL/glut.h>
#include <math.h>

void display()
{
 
 
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt( 30.0,15.0,0.0, 10.0,15.0,-10.0, 0.0,1.0,0.0);
  glColor3f(1.0, 0.0, 0.0);
  
  glBegin (GL_QUADS);

  glVertex3f (10.0, 10.0, -10.0);
  glVertex3f (20.0, 10.0, -10.0);
  glVertex3f (20.0, 20.0, -10.0); 
  glVertex3f (10.0, 20.0, -10.0);


  glEnd(); 
 
  glutSwapBuffers();
  
}
void reshape(int w, int h)
{
  glViewport(0,0,(GLsizei)w,(GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 50.0);
  //gluPerspective(60.0, 1.0, -5, -11);
  glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(300.0, 300.0);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Test");
  glClearColor(0.0, 0.0, 0.0, 1.0);
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  //gluPerspective(90, 4/3, 1, 500);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}