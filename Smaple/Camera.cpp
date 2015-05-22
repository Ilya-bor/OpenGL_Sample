#include "StdAfx.h"
#include "Camera.h"
#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

Camera::Camera(Vector3& startPosition, float startAzimuthalAngle, float startZenithAngle, float startRange) 
    : position(startPosition), azimuthalAngle(startAzimuthalAngle), zenithAngle(startZenithAngle),range(startRange)
{
}
float Camera::GetAzimuthalAngle()
{
    return azimuthalAngle;
}
float Camera::GetZenithAngle()
{
    return zenithAngle;
}
float Camera::GetRange()
{
    return range;
}
void Camera::SetAzimuthalAngle(float azimuthalAngle)
{
    this->azimuthalAngle = azimuthalAngle;
}
void Camera::SetZenithAngle(float zenithAngle)
{
    this->zenithAngle = zenithAngle;
}
void Camera::SetRange(float renge)
{
   this->range = range;
}
void Camera::Setup(float displayWidth, float displayHeight, Vector3 CnSphere)
{
    float cosPhi = cosf(azimuthalAngle * PI / 180);
    float sinPhi = sinf(azimuthalAngle * PI / 180);
    float cosTheta = cosf(zenithAngle * PI / 180);
    float sinTheta = sinf(zenithAngle * PI / 180);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, displayWidth / displayHeight, 1.0, 2000);
    gluLookAt(CnSphere.X + range*cosTheta*sinPhi,CnSphere.Y + range*sinTheta,CnSphere.Z + range*cosTheta*cosPhi,CnSphere.X, CnSphere.Y,CnSphere.Z, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
   // position.X-range*cosTheta*sinPhi,position.Y-range*sinTheta,position.Z-range*cosTheta*cosPhi
}
Vector3 Camera::GetPosition()
{
    return position;
}
void Camera::SetPosition(Vector3 position)
{
    this->position = position;
}
Vector3 Camera::GetOrientation()
{
    float cosPhi = cosf(azimuthalAngle * PI / 180);
    float sinPhi = sinf(azimuthalAngle * PI / 180);
    float cosTheta = cosf(zenithAngle * PI / 180);
    float sinTheta = sinf(zenithAngle * PI / 180);
    Vector3 Res(0,0,0);
    Res.X = -range*cosTheta*sinPhi;
    Res.Z = -range*cosTheta*cosPhi;
    float Norm  = 0.0;
    Norm = (Res.X)*(Res.X)+(Res.Y)*(Res.Y)+(Res.Z)*(Res.Z);
    Norm = pow((double)Norm,0.5);
    Res.X = Res.X/Norm;
    Res.Y = Res.Y/Norm;
    Res.Z = Res.Z/Norm;
    return Res;
}