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
void Camera::Setup(float displayWidth, float displayHeight)
{
    float cosPhi = cosf(azimuthalAngle * PI / 180);
    float sinPhi = sinf(azimuthalAngle * PI / 180);
    float cosTheta = cosf(zenithAngle * PI / 180);
    float sinTheta = sinf(zenithAngle * PI / 180);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, displayWidth / displayHeight, 0, 400);
    gluLookAt(position.X, position.Y, position.Z,position.X-range*cosTheta*sinPhi,position.Y-range*sinTheta,position.Z-range*cosTheta*cosPhi, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    
}
Vector3 Camera::GetPosition()
{
    return position;
}
void Camera::SetPosition(Vector3 position)
{
    this->position = position;
}