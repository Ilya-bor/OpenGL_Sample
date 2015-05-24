
#include "StdAfx.h"
#include"Cube.h"
#include <windows.h>
#include <GL/glut.h>
#include <math.h>



#define PI 3.14159265

Cube::Cube(Vector3& startCentr, Vector3& startVnormal, Vector3& startSnormal,Vector3& startSpeed, float startWeight, int startSize):
centr(startCentr),Vnormal(startVnormal),S1normal(startSnormal),CbSpeed(startSpeed), weight(startWeight),size(startSize)
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
    return SN[1];
}
float Cube::GetWeight()
{
    return weight;
}
int Cube::GetSize()
{
    return size;
}
float Cube::GetCrashAngle()
{
    return Crangle;
}
float Cube::GetCrashRotate()
{
    return CrashRotate;
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
    this->SN[1] = SN[1];
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
    SN[1].X = S1normal.X;
    SN[1].Y = S1normal.Y;
    SN[1].Z = S1normal.Z;
    Normalize(Vnormal);
    Normalize(SN[1]);
    SN[2].X = SN[1].Z;
    SN[2].Y = SN[1].Y;
    SN[2].Z = -SN[1].X;
    SN[3].X = SN[2].Z;
    SN[3].Y = SN[2].Y;
    SN[3].Z = -SN[2].X;
    SN[4].X = SN[3].Z;
    SN[4].Y = SN[3].Y;
    SN[4].Z = -SN[3].X;
    SN[0].X = SN[3].Z;
    SN[0].Y = SN[3].Y;
    SN[0].Z = -SN[3].X;
}
void Cube::Normalize(Vector3& UnNorm)
{
    float Norm = GetNorm(UnNorm);
    UnNorm.X = UnNorm.X/Norm;
    UnNorm.Y = UnNorm.Y/Norm;
    UnNorm.Z = UnNorm.Z/Norm;
}
void Cube::CrashAngle(Vector3 Speed, Vector3 CnSphere, int& CrashSide, float& Crangle, float SpSize)
{
    Normalize(Speed);
    float scalar[5];
    scalar[1] = Scalar(Speed,SN[1]);
    scalar[2] = Scalar(Speed,SN[2]);
    scalar[3] = Scalar(Speed,SN[3]);
    scalar[4] = Scalar(Speed,SN[4]);
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
    if ((minS <= - pow(2,-0.5)+0.05))
    {
        Vector3 tmp1,tmp2,tmp3;
        Vector3 SizeS(SpSize,0,SpSize);
        tmp1.X = (SizeS.X*SN[j-1].X +SizeS.X*SN[j].X) +TP[j-1].X;
        tmp1.Z = (SizeS.Z*SN[j-1].Z +SizeS.Z*SN[j].Z) +TP[j-1].Z;
        tmp2.X = (SizeS.X*SN[j].X +SizeS.X*SN[(j+1)%4].X) + TP[j].X;
        tmp2.Z = (SizeS.Z*SN[j].Z +SizeS.Z*SN[(j+1)%4].Z) + TP[j].Z;
        tmp3.X = (SizeS.X*SN[(j+1)%4].X +SizeS.X*SN[(j+2)%4].X) + TP[(j+1)%4].X;
        tmp3.Z = (SizeS.Z*SN[(j+1)%4].Z +SizeS.Z*SN[(j+2)%4].Z) + TP[(j+1)%4].Z;
        Vector3 Cn1 = CentrLine(CnSphere,tmp1);
        Vector3 Orient1 = SpeedOrientation(Speed,Cn1);
        Vector3 Cn2 = CentrLine(CnSphere,tmp2);
        Vector3 Orient2 = SpeedOrientation(Speed,Cn2);
        Vector3 Cn3 = CentrLine(CnSphere,tmp3);
        Vector3 Orient3 = SpeedOrientation(Speed,Cn3);
        if(Orient1.Y*Orient2.Y < 0)
        {
            CrashSide = j;
        }
        else
        {
            if(Orient2.Y*Orient3.Y < 0)
            { 
                if( j == 3 )
                    CrashSide = 4;
                else
                    CrashSide = (j+1)%4;
            }
            else
            {
                CrashSide = 5;
            }
        }
        
    }
    switch(CrashSide)
    {
    case 1:
        Crangle = acosf(abs(scalar[1]));
        if (Crangle < 0.01)
            Crangle = 0;
        CrashNormal = SN[1];
        break;
    case 2:
        Crangle = acosf(abs(scalar[2]));
        if (Crangle < 0.01)
            Crangle = 0;
        CrashNormal = SN[2];
        break;
    case 3:
        Crangle = acosf(abs(scalar[3]));
        if (Crangle < 0.01)
            Crangle = 0;
        CrashNormal = SN[3];
        break;
    case 4:
        Crangle = acosf(abs(scalar[4]));
        if (Crangle < 0.01)
            Crangle = 0;
        CrashNormal = SN[4];
        break;
    case 5:
        break;
    }
      
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
    if ((Res.Y < 0.0001)&&(Res.Y > - 0.0001))
        Res.Y = 1000;
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
    Normalize(SN[1]);
    float cosA = Scalar(SN[1],Vector3(0,0,1));
    if (cosA < 0 )
        cosA = cosA*(-1);
    float angle = acosf(cosA);
    if (angle > PI/2)
        angle -= PI/2;
    if(angle > 0.01)
    {
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
    else
    {
        TP[1].X = centr.X + size/2;
        TP[1].Y = 0;
        TP[1].Z = centr.Z - size/2;
        TP[2].X = centr.X - size/2;
        TP[2].Y = 0;
        TP[2].Z = centr.Z - size/2;
        TP[3].X = centr.X - size/2;
        TP[3].Y = 0;
        TP[3].Z = centr.Z + size/2;
        TP[4].X = centr.X + size/2;
        TP[4].Y = 0;
        TP[4].Z = centr.Z + size/2;
        TP[0].X = centr.X + size/2;
        TP[0].Y = 0;
        TP[0].Z = centr.Z + size/2;
    }
    
}
/*void Cube::ShowCube()
{
   glPushMatrix();
    glTranslatef(centr.X, size/2, centr.Z);
    glutSolidCube(size);
     glPopMatrix();
}*/
int Cube::CrashPoint(Vector3 CnSphere, Vector3 Sp, float SpSize)
{
    CrashAngle(Sp,CnSphere,CrashSide,Crangle, SpSize);
    if(CrashSide == 5)
    {
        return 0;
    }
    Vector3 res(0,0,0);
    Vector3 tmp(0,0,0);
    res.X = CnSphere.X + Sp.X;
    res.Z = CnSphere.Z + Sp.Z;
    if((TP[CrashSide-1].X - TP[CrashSide].X) != 0)
    {
        float k1 = (TP[CrashSide-1].Z - TP[CrashSide].Z)/(TP[CrashSide-1].X - TP[CrashSide].X);
        float b1 = (TP[CrashSide].Z*TP[CrashSide-1].X - TP[CrashSide].X*TP[CrashSide-1].Z)/(TP[CrashSide-1].X - TP[CrashSide].X);
        if((res.X - CnSphere.X) != 0)
        {
            float k2 = (res.Z - CnSphere.Z)/(res.X - CnSphere.X);
            float b2 = (CnSphere.Z*res.X - CnSphere.X*res.Z)/(res.X - CnSphere.X);
            tmp.X = (b2 - b1)/(k1 - k2);
            tmp.Z = (k1*b2 - k2*b1)/(k1 - k2);
        }
        else
        {
            tmp.X = CnSphere.X;
            tmp.Z = k1*tmp.X +b1;
        }
    }
    else
    {
        tmp.X = TP[CrashSide].X;
        if((res.X - CnSphere.X) != 0)
        {
            float k2 = (res.Z - CnSphere.Z)/(res.X - CnSphere.X);
            float b2 = (CnSphere.Z*res.X - CnSphere.X*res.Z)/(res.X - CnSphere.X);
            tmp.Z = k2*tmp.X + b2;
        }
        else
        {
            tmp.Y = TP[CrashSide].Y;
        }
    }
    res.X = tmp.X - CnSphere.X;
    res.Y = 0;
    res.Z = tmp.Z - CnSphere.Z;
    float Norm = GetNorm(res);
    Vector3 Rt1, Rt2;
    if((Norm*sinf((PI - Crangle)/2)) > (SpSize + 0.01))
    {
        res.X -= Sp.X;
        res.Z -= Sp.Z;
        Norm = GetNorm(res);
    }
    else
    {
        Rt1.X = TP[CrashSide-1].X-CnSphere.X;
        Rt1.Y = 0;
        Rt1.Z = TP[CrashSide-1].Z-CnSphere.Z;
        Rt2.X = TP[CrashSide].X-CnSphere.X;
        Rt2.Y = 0;
        Rt2.Z = TP[CrashSide].Z-CnSphere.Z;
        CrashRotate = GetNorm(Rt1) - GetNorm(Rt2);
        return 1;
    }
        
    return 0;
    
}
float Cube::GetNorm(Vector3 obj)
{
    float Norm = 0.0;
    Norm = (obj.X)*(obj.X)+(obj.Y)*(obj.Y)+(obj.Z)*(obj.Z);
    Norm = pow((double)Norm,0.5);
    return Norm;
}
void Cube::MoveCube(Vector3& Speed, float BallWeight, int flag)
{
    if((GetNorm(CbSpeed) == 15)&&(flag == 1))
    {
        float Mass = BallWeight/weight;
        float SPimpuls = BallWeight*GetNorm(Speed);
        float CbSp = (GetNorm(Speed)*Mass*(1-abs(sinf(Crangle))))/2;
        Normalize(Speed);
        Vector3 newSp = Speed;
        newSp.X = -newSp.X;
        newSp.Z = -newSp.Z;
        Vector3 orient = SpeedOrientation(newSp, CrashNormal);
        float CosAngl ;
        float SinAngl;
        float k;
        if (orient.Y == 1000)
        {
            k = 1;
            CosAngl = cosf(PI);
            SinAngl = sinf(0);
        }
        else
        {
            CosAngl = cosf(Crangle/2);
            SinAngl = sinf(Crangle/2);
            k = orient.Y/abs(orient.Y);
        }
        Vector3 oldSpeed = Speed;
        Speed.X = (oldSpeed.X*CosAngl + k*oldSpeed.Z*SinAngl);
        Speed.Z = (-k*oldSpeed.X*SinAngl + oldSpeed.Z*CosAngl);
        CbSpeed.X = Speed.X*CbSp;
        CbSpeed.Y = 0;
        CbSpeed.Z = Speed.Z*CbSp;
        centr.X += CbSpeed.X;
        centr.Z += CbSpeed.Z;
        float CosCR = cosf(CrashRotate);
        float SinCR = sinf(CrashRotate);
        Vector3 oldS1 = S1normal;
        S1normal.X = (oldS1.X*CosCR - oldS1.Z*SinCR);
        S1normal.Z = (oldS1.X*SinCR + oldS1.Z*CosCR);
        SetupNormales();
        //ShowCube();
        SetPoints();
    }
    else
    {
        if((GetNorm(CbSpeed) >= 0.1)&&(GetNorm(CbSpeed) != 15))
        {
            centr.X += CbSpeed.X;
            CbSpeed.Y = 0;
            centr.Z += CbSpeed.Z;
            CbSpeed.X = CbSpeed.X*0.9;
            CbSpeed.Z = CbSpeed.Z*0.9;
           // ShowCube();
            SetPoints();
        }
        else
        {
            CbSpeed = Vector3(10,10,5);
        }
    }
    
}
int Cube::ControlMove()
{
    if(GetNorm(CbSpeed) == 15)
    {
        return 1;
    }
    if(GetNorm(CbSpeed) >= 0.1)
    {
        return 1;
    }
    else
    {
        CbSpeed = Vector3(10,10,5);
        return 0;
    }
}
Vector3 Cube::GetCrashNormal()
{
    return CrashNormal;
}