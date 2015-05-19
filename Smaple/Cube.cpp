
#include "StdAfx.h"
#include"Cube.h"
#include <windows.h>
#include <GL/glut.h>
#include <math.h>



#define PI 3.14159265

Cube::Cube(Vector3& startCentr, Vector3& startVnormal, Vector3& startS1normal, float startWeight, int startSize):
centr(startCentr),Vnormal(startVnormal),S1normal(startS1normal),weight(startWeight),size(startSize)
{
    SetupNormales();
    SetPoints();
}
Vector3 Cube::GetCentr()
{
    return centr;
}
Vector3 Cube::GetVnormal()
{
    return Vnormal;
}
Vector3 Cube::GetS1normal()
{
    return S1normal;
}
float Cube::GetWeight()
{
    return weight;
}
int Cube::GetSize()
{
    return size;
}
void Cube::SetCentr(Vector3 centr)
{
    this->centr = centr;
}
void Cube::SetVnormal(Vector3 Vnormal)
{
    this->Vnormal = Vnormal;
}
void Cube::SetS1normal(Vector3 S1normal)
{
    this->S1normal = S1normal;
}
void Cube::SetWeight(float Weight)
{
    this->weight = Weight;
}
void Cube::SetSize(int Size)
{
    this->size = Size;
}
void Cube::SetupNormales()
{
    Normalize(Vnormal);
    Normalize(S1normal);
    S2normal.X = - S1normal.Z;
    S2normal.Y = S1normal.Y;
    S2normal.Z = S1normal.X;
    S3normal.X = - S2normal.Z;
    S3normal.Y = S2normal.Y;
    S3normal.Z = S2normal.X;
    S4normal.X = - S3normal.Z;
    S4normal.Y = S3normal.Y;
    S4normal.Z = S3normal.X;
}
void Cube::Normalize(Vector3& UnNorm)
{
    float Norm = 0.0;
    Norm += (UnNorm.X)*(UnNorm.X)+(UnNorm.Y)*(UnNorm.Y)+(UnNorm.Z)*(UnNorm.Z);
    Norm = pow((double)Norm,0.5);
    UnNorm.X = UnNorm.X/Norm;
    UnNorm.Y = UnNorm.Y/Norm;
    UnNorm.Z = UnNorm.Z/Norm;
}
float Cube::CrashAngle(Vector3 Speed, Vector3 CnSphere, int& CrashSide)
{
    Normalize(Speed);
    float scalar[4];
    float angle;
    scalar[1] = Scalar(Speed,S1normal);
    scalar[2] = Scalar(Speed,S2normal);
    scalar[3] = Scalar(Speed,S3normal);
    scalar[4] = Scalar(Speed,S4normal);
    int i = 1;
    int j = 1;
    float minS = scalar[1];
    if(scalar[2]<minS)
    {
        j = 2;
        i = 2;
        minS = scalar[2];
    }
    else
        if(scalar[2] == minS)
        {
                i = 5;
        }
    if(scalar[3]<minS)
    {
        j = 3;
        i = 3;
        minS = scalar[3];
    }
    else
        if(scalar[3] == minS)
        {
            i = 6;
        }
    if(scalar[4]<minS)
    {
        j = 4;
        i = 4;
        minS = scalar[4];
    }
    else
        if(scalar[4] == minS)
        {
            i = 7;
        }
    if((scalar[4] == minS) &&(scalar[4] == scalar[1])) 
        i = 8;
    if ((minS < - pow(2,-0.5))&&(minS > - 0.95))
    {
        Vector3 Cn1 = CentrLine(CnSphere,TP[j-1]);
        Vector3 Orient1 = SpeedOrientation(Speed,Cn1);
        Vector3 Cn2 = CentrLine(CnSphere,TP[j]);
        Vector3 Orient2 = SpeedOrientation(Speed,Cn2);
        if(Orient1.Y*Orient2.Y > 0)
        {
            if(j == 0 )
            {
                j = 4;
            }
            else
            {
                j--;
            }
            
        }
    }
    switch(j)
    {
    case 1:
        angle = acosf(abs(scalar[1]));
        break;
    case 2:
        angle = acosf(abs(scalar[2]));
        break;
    case 3:
        angle = acosf(abs(scalar[3]));
        break;
    case 4:
        angle = acosf(abs(scalar[4]));
        break;
    }
    CrashSide = j;
    return angle;
}
float Cube::Scalar(Vector3 f, Vector3 s)
{
    float res = 0.0;
    res = f.X*s.X+f.Z*s.Z;
    return res;
}
Vector3 Cube::SpeedOrientation(Vector3 Sp, Vector3 Cn)
{
    Vector3 Res(0,0,0);
    Res.X = Sp.Y*Cn.Z - Sp.Z*Cn.Y;
    Res.Y = Sp.Z*Cn.X - Sp.X*Cn.Z;
    Res.Z = Sp.X*Cn.Y - Sp.Y*Cn.X;
    return Res;
}
Vector3 Cube::CentrLine(Vector3 CnSphere, Vector3 SPoint)
{
    Vector3 Res(0,0,0);
    float tmpZ;
    float tmpX;
    float k = (SPoint.Z - CnSphere.Z)/(SPoint.X - CnSphere.X);
    float b = (CnSphere.Z*SPoint.X - CnSphere.X*SPoint.Z)/(SPoint.X - CnSphere.X);
    if (SPoint.X < CnSphere.X)
    {
        tmpZ = k*(CnSphere.X - 1) + b;
        Res.X = -1;
        Res.Z = tmpZ - CnSphere.Z;
        Res.Y = 0;
        Normalize(Res);
    }
    else
    {
        if(SPoint.X >  CnSphere.X)
        {
            tmpZ = k*(CnSphere.X + 1) + b;
            Res.X = 1;
            Res.Z = tmpZ - CnSphere.Z;
            Res.Y = 0;
            Normalize(Res);
        }
        else
        {
            if ((SPoint.X == CnSphere.X)&&(SPoint.Z < CnSphere.Z))
            {
                tmpX = (CnSphere.Z - 1)/k - b/k;
                Res.X = tmpX - CnSphere.X;
                Res.Y = 0;
                Res.Z = -1;
                Normalize(Res);
            }
            else
            {
                tmpX = (CnSphere.Z + 1)/k - b/k;
                Res.X = tmpX - CnSphere.X;
                Res.Y = 0;
                Res.Z = 1;
                Normalize(Res);
            }
        }
        
    }
    return Res;
}
void Cube::SetPoints()
{
    Normalize(S1normal);
    float cosA = Scalar(S1normal,Vector3(0,0,1));
    if (cosA < 0 )
        cosA = cosA*(-1);
    float angle = acosf(cosA);
    if (angle > PI/2)
        angle -= PI/2;
    angle = PI/4 - angle;
    float delx = pow(2,-0.5)*size*cos(angle);
    float delz = pow(2,-0.5)*size*sin(angle);
    TP[1].X = centr.X - delx;
    TP[1].Y = 0;
    TP[1].Z = centr.Z - delz;
    TP[2].X = centr.X - delz;
    TP[2].Y = 0;
    TP[2].Z = centr.Z + delx;
    TP[3].X = centr.X + delx;
    TP[3].Y = 0;
    TP[3].Z = centr.Z + delz;
    TP[4].X = centr.X + delz;
    TP[4].Y = 0;
    TP[4].Z = centr.Z - delx;
    TP[0].X = centr.X + delz;
    TP[0].Y = 0;
    TP[0].Z = centr.Z - delx;
}