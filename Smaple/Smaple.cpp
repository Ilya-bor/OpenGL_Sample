#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "SOIL.lib")
#include "StdAfx.h"

#include <iomanip>
#include <GL/SOIL.h>
#include <math.h>
#include <stdio.h>
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "Map.h"
#include <GL/glut.h>
#include<random>



#define PI 3.14159265
#define AZIMUTHAL_INC 0.8
#define ZENITH_INC 0.5
#define MOVING_INC 0.1
#define MOVING_TIME 10
using namespace std;
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

unsigned int TulipsTextureID;
unsigned int YextureID;
unsigned int Yexture1ID;
unsigned int Yexture2ID;
unsigned int Yexture3ID;
unsigned int Yexture4ID;
unsigned int Yexture5ID;

Vector3 cent = Vector3(0,0,0); 
Vector3 cent1 = Vector3(0,0,0); 
Vector3 n1 = Vector3(0,1,0);
Vector3 s1 = Vector3(1,0,0);
Vector3 s2 = Vector3(0,0,0);
Vector3 st = Vector3(10,10,5);
Vector3 DifSp(0.0,0.0,0.0);
Cube L1(cent,n1,s1,st,30,50);
Sphere S1(cent1,s2,200,20);
float Ang = 0;
float Earth = 0;
float CubeR = 0;
int fl = 0;
int N = 200;
Map gameMap(N);
Cube Lk[200];
int** Res;
int fl2 = 0;
int xl[8];
int yl[8];

void display()
{
 cent1 = S1.GetCentr();
 camera.Setup(displayWidth, displayHeight, cent1);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 0.0);

  
    float sp = 1;
    Vector3 CnSpere = S1.GetCentr();
    Vector3 Speed = S1.GetSpeed();
    Speed.X = Speed.X*sp;
    Speed.Y = Speed.Y*sp;
    Speed.Z = Speed.Z*sp;
    for(int j = 0; j<8; j++)
        for(int i = 0; i<8; i++)
        {
            glPushMatrix();
            glTranslatef((3500-i*1000)/pow(2,0.5),0,(3500-j*1000)/pow(2,0.5));
            glRotatef(-90,1,0,0);
            glRotatef(45,0,0,1);
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1);
            glBindTexture(GL_TEXTURE_2D, Yexture2ID);
            GLUquadric* quadric = gluNewQuadric();
            gluQuadricTexture(quadric, GL_TRUE);
            gluDisk(quadric, 0,1000,4,1);
            gluDeleteQuadric(quadric);
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }
        for(int i = 0; i<4; i++)
        {
            float z = 0;
            float x = 0;
            
            if (i == 0)
            {
                x = -4500/pow(2,0.5);
                z = -4210/pow(2,0.5);
                
            }
            if(i == 1)
            {
                x = -4210/pow(2,0.5);
                z = 4500/pow(2,0.5);
                
            }
            if(i == 2)
            {
                x = 4500/pow(2,0.5);
                z = 4210/pow(2,0.5);
                
            }
            if(i == 3)
            {
                x = 4210/pow(2,0.5);
                z = -4500/pow(2,0.5);
                
            }
            glPushMatrix();
            glTranslatef(x, -20, z);
            glRotatef(45,0,0,1);
            glRotatef(90*(i+1),1,1,0);
            
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1);
            glBindTexture(GL_TEXTURE_2D, Yexture4ID);
            GLUquadric* quadric = gluNewQuadric();
            gluQuadricTexture(quadric, GL_TRUE);
            gluCylinder(quadric, 200, 200, 8000,4,4);
            gluDeleteQuadric(quadric);
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();

          
        }

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);
        glRotatef(Earth,-1,0,1);
        Earth +=0.01;
        glBindTexture(GL_TEXTURE_2D, Yexture3ID);
        GLUquadric* quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluSphere(quadric,5000,200,200);
        gluDeleteQuadric(quadric);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        Vector3 centr1(0,0,0);
        float size1 = 0;
        for(int d = 0; d<N;d++ )
        {
            glPushMatrix();
            centr1 = Lk[d].GetCentr();
            if((abs(centr1.X)<2800)&&(abs(centr1.Z)<2800))
            {
                size1 = Lk[d].GetSize();
                glTranslatef(centr1.X, size1, centr1.Z);
                glRotatef(90,1,0,0);
                glRotatef(45,0,0,1);
                glEnable(GL_TEXTURE_2D);
                glColor3f(1, 1, 1);
                glBindTexture(GL_TEXTURE_2D, YextureID);
                GLUquadric* quadric = gluNewQuadric();
                gluQuadricTexture(quadric, GL_TRUE);
                gluCylinder(quadric, size1*pow(2,0.5)/2, size1*pow(2,0.5)/2, size1,4,4);
                gluDeleteQuadric(quadric);
                glDisable(GL_TEXTURE_2D);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(centr1.X,size1,centr1.Z);
                glRotatef(-90,1,0,0);
                glRotatef(45,0,0,1);
                glEnable(GL_TEXTURE_2D);
                glColor3f(1, 1, 1);
                glBindTexture(GL_TEXTURE_2D, Yexture1ID);
                quadric = gluNewQuadric();
                gluQuadricTexture(quadric, GL_TRUE);
                gluDisk(quadric, 0,size1*pow(2,0.5)/2,4,4);
                gluDeleteQuadric(quadric);
                glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            }
           
        }
        for(int y = 0; y<8;y++)
        {
            glPushMatrix();
            glTranslatef(xl[y],1,yl[y]);
            glRotatef(-90,1,0,0);
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1);
            glBindTexture(GL_TEXTURE_2D, Yexture5ID);
            quadric = gluNewQuadric();
            gluQuadricTexture(quadric, GL_TRUE);
            gluDisk(quadric, 0,40,40,50);
            gluDeleteQuadric(quadric);
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }
        
   
     int i  = 1;
     float spSize = S1.GetSize();
     float spWeight = S1.GetWeight();
     Vector3 centr = S1.GetCentr();
     Res = gameMap.GetObj(centr);
     for(int q = 0;q<3; q++)
     {
         for(int e = 0;e<3; e++)
         {
             if(Res[q][e] != -1)
             {
                 int p = Res[q][e];
                 if (Lk[p].CrashPoint(CnSpere,Speed,spSize) == 1)
                 {
                     i = 1;
                 }
                 else
                 {
                     fl2 = 1;
                     Lk[p].MoveCube(Speed,spWeight,0);
                     S1.MoveSphere(DifSp,100,Lk[p].GetWeight(),Lk[p].GetCrashNormal());
                     glPushMatrix();
                     Vector3 centr1 = Lk[p].GetCentr();
                     float size1 = Lk[p].GetSize();
                     glTranslatef(centr1.X, size1, centr1.Z);
                     glRotatef(90,1,0,0);
                     glRotatef(45,0,0,1);
                     //glRotatef(CubeR,0,0,1);
                     glEnable(GL_TEXTURE_2D);
                     glColor3f(1, 1, 1);
                     glBindTexture(GL_TEXTURE_2D, YextureID);
                     GLUquadric* quadric = gluNewQuadric();
                     gluQuadricTexture(quadric, GL_TRUE);
                     gluCylinder(quadric, size1*pow(2,0.5)/2, size1*pow(2,0.5)/2, size1,4,4);
                     gluDeleteQuadric(quadric);
                     glDisable(GL_TEXTURE_2D);
                     glPopMatrix();

                     glPushMatrix();
                     glTranslatef(centr1.X,size1,centr1.Z);
                     glRotatef(-90,1,0,0);
                     glRotatef(45,0,0,1);
                     glEnable(GL_TEXTURE_2D);
                     glColor3f(1, 1, 1);
                     glBindTexture(GL_TEXTURE_2D, Yexture1ID);
                     quadric = gluNewQuadric();
                     gluQuadricTexture(quadric, GL_TRUE);
                     gluDisk(quadric, 0,size1*pow(2,0.5)/2,4,4);
                     gluDeleteQuadric(quadric);
                     glDisable(GL_TEXTURE_2D);
                     glPopMatrix();

                     glColor3f(1.0, 0.0, 0.0);
                     glPushMatrix();
                     Vector3 centr = S1.GetCentr();
                     float size = S1.GetSize();
                     Vector3 Sp1 = S1.GetSpeed();
                     float Norm = pow((double)(Sp1.X*Sp1.X +Sp1.Z*Sp1.Z),0.5);
                     Ang += 360*Norm/(2*PI*size);
                     glTranslatef(centr.X, size, centr.Z);
                     glEnable(GL_TEXTURE_2D);
                     glRotatef(Ang,Sp1.Z, 0 ,-Sp1.X);
                     glColor3f(1, 1, 1);
                     glBindTexture(GL_TEXTURE_2D, TulipsTextureID);
                     quadric = gluNewQuadric();
                     gluQuadricTexture(quadric, GL_TRUE);
                     gluSphere(quadric, size, 50, 50);
                     gluDeleteQuadric(quadric);
                     glDisable(GL_TEXTURE_2D);

                     glPopMatrix();
                     i =0;
                 }
                 if ((i == 1)&&(Lk[p].ControlMove() == 1))
                 {
                     fl2 = 1;
                     Lk[p].MoveCube(Speed,spWeight,1);
                     S1.MoveSphere(DifSp,Lk[p].GetCrashAngle(),Lk[p].GetWeight(),Lk[p].GetCrashNormal());
                     glPushMatrix();
                     Vector3 centr1 = Lk[p].GetCentr();
                     float size1 = Lk[p].GetSize();
                     CubeR = Lk[p].GetCrashRotate();
                     glTranslatef(centr1.X, size1, centr1.Z);
                     glRotatef(90,1,0,0);
                     glRotatef(45,0,0,1);
                    // glRotatef(CubeR,0,0,1);
                     glEnable(GL_TEXTURE_2D);
                     glColor3f(1, 1, 1);
                     glBindTexture(GL_TEXTURE_2D, YextureID);
                     GLUquadric* quadric = gluNewQuadric();
                     gluQuadricTexture(quadric, GL_TRUE);
                     gluCylinder(quadric, size1*pow(2,0.5)/2, size1*pow(2,0.5)/2, size1,4,4);
                     gluDeleteQuadric(quadric);
                     glDisable(GL_TEXTURE_2D);
                     glPopMatrix();

                     glPushMatrix();
                     glTranslatef(centr1.X,size1,centr1.Z);
                     glRotatef(-90,1,0,0);
                     glRotatef(45,0,0,1);
                     glEnable(GL_TEXTURE_2D);
                     glColor3f(1, 1, 1);
                     glBindTexture(GL_TEXTURE_2D, Yexture1ID);
                     quadric = gluNewQuadric();
                     gluQuadricTexture(quadric, GL_TRUE);
                     gluDisk(quadric, 0,size1*pow(2,0.5)/2,4,4);
                     gluDeleteQuadric(quadric);
                     glDisable(GL_TEXTURE_2D);
                     glPopMatrix();

                     glColor3f(1.0, 0.0, 0.0);
                     glPushMatrix();
                     Vector3 centr = S1.GetCentr();
                     float size = S1.GetSize();
                     Vector3 Sp1 = S1.GetSpeed();
                     float Norm = pow((double)(Sp1.X*Sp1.X +Sp1.Z*Sp1.Z),0.5);
                     Ang += 360*Norm/(2*PI*size);
                     glTranslatef(centr.X, size, centr.Z);
                     glEnable(GL_TEXTURE_2D);
                     glRotatef(Ang,Sp1.Z, 0 ,-Sp1.X);
                     glColor3f(1, 1, 1);
                     glBindTexture(GL_TEXTURE_2D, TulipsTextureID);
                     quadric = gluNewQuadric();
                     gluQuadricTexture(quadric, GL_TRUE);
                     gluSphere(quadric, size, 50, 50);
                     gluDeleteQuadric(quadric);
                     glDisable(GL_TEXTURE_2D);

                     glPopMatrix();
                     i = 1;
                 }
                 else
                 {
                     i =0;
                 }
             }
         }
     }
     if(fl2 == 0)
     {
         S1.MoveSphere(DifSp,100,L1.GetWeight(),L1.GetCrashNormal());
         glPushMatrix();
         float size = S1.GetSize();
         Vector3 Sp1 = S1.GetSpeed();
         float Norm = pow((double)(Sp1.X*Sp1.X +Sp1.Z*Sp1.Z),0.5);
         Ang += 360*Norm/(2*PI*size);
         glTranslatef(centr.X, size, centr.Z);
         glEnable(GL_TEXTURE_2D);
         glRotatef(Ang,Sp1.Z, 0 ,-Sp1.X);
         glColor3f(1, 1, 1);
         glBindTexture(GL_TEXTURE_2D, TulipsTextureID);
         quadric = gluNewQuadric();
         gluQuadricTexture(quadric, GL_TRUE);
         gluSphere(quadric, size, 50, 50);
         gluDeleteQuadric(quadric);
         glDisable(GL_TEXTURE_2D);
         glPopMatrix();
     }
     fl2 = 0;
     DifSp = Vector3(0.0,0.0,0.0);
   
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
    camera.SetPosition( Vector3(cent1.X, 30,cent1.Z - 50) );
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(1024.0, 768.0);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Test");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutSetCursor(GLUT_CURSOR_NONE); 
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
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_POINT_SMOOTH);
    GLfloat ambient[] = {  1.0f, 0.3f, 0.3f, 1 };
    GLfloat diffuse[] = {1.0f, 0.0f, 0.0f, 1 };
    GLfloat spec[] = { 1.0f, 0.0f, 0.0f,1 };
    GLfloat pos[] = {0, 1000, -500, 100};
    GLfloat ambient1[] = {  1.0f, 0.3f, 0.3f, 1 };
    GLfloat diffuse1[] = {1.0f, 0.0f, 0.3f, 1 };
    GLfloat spec1[] = { 1.0f, 0.0f, 0.2f,1 };
    GLfloat pos1[] = {1000, 500, 500, 50 };
    float dir1[] = {2000, 0, 2000};
    float dir[] = {-2000, 0, -2000};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);        	
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir1);
    if(fl == 0)
    {
        Vector3 STcentr(0,0,0);
        for(int i = 0;i<N; i++ )
        {
            random_device rd;  
            mt19937 gen(rd());  
            uniform_int_distribution<> dist(1,81); 
            int x = dist(gen);
            int z = dist(gen);
            STcentr.X = (2*x-81)*50/pow(2,0.5);
            STcentr.Z = (2*z-81)*50/pow(2,0.5);
            random_device rd1;  
            mt19937 gen1(rd1());  
            uniform_real_distribution<> dist1(25.0,100.0);
            float s = dist1(gen1);
            if(s < 25)
                s = 25;
            float w = dist1(gen1);
            if(w < 10)
                w = 10;
            Lk[i] = Cube(STcentr,n1,s1,st,w,s);
            gameMap.SetCube(x,z,i);
        }
        int l = 0;
        while(l ==0)
        {
            random_device rd;  
            mt19937 gen(rd());  
            uniform_int_distribution<> dist(1,81); 
            int x = dist(gen);
            int z = dist(gen);
            if(gameMap.GetIJ(x,z) ==-1)
            {
                l =1;
                cent1 = Vector3((2*x-81)*50/pow(2,0.5),20,(2*z-81)*50/pow(2,0.5));
                S1 = Sphere(cent1,s2,100,20);
            }
        }
        for(int y = 0; y<8;y++)
        {
            random_device rd;  
            mt19937 gen(rd());  
            uniform_real_distribution<> dist(0.0,5600.0); 
            float x = dist(gen)-2800;
            float z = dist(gen)-2800;
            xl[y] = x;
            yl[y] = y;
        }
    }
    int width;
	int height;
	unsigned char* TulipsTexture = SOIL_load_image(".\\123.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	
	glGenTextures(1, &TulipsTextureID);
	glBindTexture(GL_TEXTURE_2D, TulipsTextureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TulipsTexture);

	unsigned char* Yexture = SOIL_load_image(".\\de_inferno0001.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	
	glGenTextures(1, &YextureID);
	glBindTexture(GL_TEXTURE_2D, YextureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Yexture);

    unsigned char* Yexture1 = SOIL_load_image(".\\de_inferno0000.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &Yexture1ID);
    glBindTexture(GL_TEXTURE_2D, Yexture1ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Yexture1);
   
    unsigned char* Yexture2 = SOIL_load_image(".\\asphalt_26.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &Yexture2ID);
    glBindTexture(GL_TEXTURE_2D, Yexture2ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Yexture2);

    unsigned char* Yexture3 = SOIL_load_image(".\\Sky4.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &Yexture3ID);
    glBindTexture(GL_TEXTURE_2D, Yexture3ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Yexture3);
    
    unsigned char* Yexture4 = SOIL_load_image(".\\WhiteRoughConc-bump.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &Yexture4ID);
    glBindTexture(GL_TEXTURE_2D, Yexture4ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Yexture4);

    unsigned char* Yexture5 = SOIL_load_image(".\\21.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &Yexture5ID);
    glBindTexture(GL_TEXTURE_2D, Yexture5ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Yexture5);

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
        glutPostRedisplay();
        glutWarpPointer(displayWidth >>1, displayHeight >>1 ); 
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
        DifSp = Vector3(0.01,0.0,0.01);
        if (upPressed)
        {
            DifSp.X = -DifSp.X*sinf(azimuthalAngle)*1.5;
            DifSp.Z = -DifSp.Z*cosf(azimuthalAngle)*1.5;
        }
        if (rightPressed)
        {
            DifSp.X = DifSp.X*cosf(azimuthalAngle)*2;
            DifSp.Z = -DifSp.Z*sinf(azimuthalAngle)*2;
        }
        if (downPressed)
        {
            DifSp.X = DifSp.X*sinf(azimuthalAngle)*2;
            DifSp.Z = DifSp.Z*cosf(azimuthalAngle)*2;
        }
        if (leftPressed)
        {
            DifSp.X = -DifSp.X*cosf(azimuthalAngle)*2;
            DifSp.Z = DifSp.Z*sinf(azimuthalAngle)*2;
        }
        
    }
    glutPostRedisplay();
    glutTimerFunc(MOVING_TIME, Moving, 0); 
}