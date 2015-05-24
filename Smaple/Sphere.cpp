#include "StdAfx.h"
#include "Sphere.h"
#include <windows.h>
#include <GL/glut.h>
#include <GL/SOIL.h>
#include <math.h>


#define PI 3.14159265

Sphere::Sphere(Vector3& startCentr, Vector3& stratSpeed, float stratWeight, float stratSize):
centr(startCentr), spSpeed(stratSpeed), weight(stratWeight), size(stratSize)
{
	

}
Vector3 Sphere::GetCentr()
{
    return centr;
}
Vector3 Sphere::GetSpeed()
{
    return spSpeed;
}
float Sphere::GetWeight()
{
    return weight;
}
float Sphere::GetSize()
{
    return size;
}
/*void Sphere::ShowSphere()
{
    glColor3f(1.0, 0.0, 0.0);
   glPushMatrix();
   glTranslatef(centr.X, size, centr.Z);
    glutSolidSphere(size,50,50);
     glPopMatrix();
}*/
void Sphere::MoveSphere(Vector3 DifSpeed, float Crangle, float CubeWeight, Vector3 CrashNorm)
{
    if(Crangle == 100)
    {
        if ((DifSpeed.X == 0)&&(DifSpeed.Z == 0))
        {
            spSpeed.X = 0.999*spSpeed.X;
            spSpeed.Z = 0.999*spSpeed.Z;
        }
        spSpeed.X += DifSpeed.X;
        spSpeed.Z += DifSpeed.Z;
        centr.X += spSpeed.X;
        centr.Z += spSpeed.Z;
       // ShowSphere();
    }
    else
    {
        float Mass = weight/CubeWeight;
        float SPimpuls = weight*GetNorm(spSpeed);
        float Cbimpuls = (GetNorm(spSpeed)*weight*(1-abs(sinf(Crangle))))/2;
        SPimpuls -= 1.1*Cbimpuls;
        float newSpeed = (SPimpuls/weight)/GetNorm(spSpeed);
        Vector3 SpOrient = SpeedOrientation(spSpeed,CrashNorm);
        float CosAngl ;
        float SinAngl;
        float k;
        if (SpOrient.Y == 1000)
        {
            k = 1;
            CosAngl = cosf(PI);
            SinAngl = sinf(0);
        }
        else
        {
            CosAngl = cosf(Crangle*2);
            SinAngl = sinf(Crangle*2);
            k = SpOrient.Y/abs(SpOrient.Y);
        }
        Vector3 oldSpeed = spSpeed;
        oldSpeed.X = -oldSpeed.X;
        oldSpeed.Z = -oldSpeed.Z;
        spSpeed.X = (oldSpeed.X*CosAngl + k*oldSpeed.Z*SinAngl)*newSpeed;
        spSpeed.Z = (-k*oldSpeed.X*SinAngl + oldSpeed.Z*CosAngl)*newSpeed;
        centr.X += spSpeed.X;
        centr.Z += spSpeed.Z;
       // ShowSphere();
    }
    
}
float Sphere::GetNorm(Vector3 obj)
{
    float Norm = 0.0;
    Norm = (obj.X)*(obj.X)+(obj.Y)*(obj.Y)+(obj.Z)*(obj.Z);
    Norm = pow((double)Norm,0.5);
    return Norm;
}
Vector3 Sphere::SpeedOrientation(Vector3 Sp, Vector3 Cn)
{
    Vector3 Res(0,0,0);
    Sp.X = -Sp.X;
    Sp.Z = -Sp.Z;
    Res.X = Sp.Y*Cn.Z - Sp.Z*Cn.Y;
    Res.Y = Sp.Z*Cn.X - Sp.X*Cn.Z;
    Res.Z = Sp.X*Cn.Y - Sp.Y*Cn.X;
    if ((Res.Y < 0.0001)&&(Res.Y > - 0.0001))
        Res.Y = 1000;
    return Res;
}