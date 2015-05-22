
#include "Vector3.h"

class Cube
{
private:
    Vector3 centr;
    Vector3 Vnormal;
    Vector3 SN[5];
    Vector3 S1normal;
    Vector3 TP[5];
    Vector3 CbSpeed;
    float weight;
    int size;
    int CrashSide; 
    float Crangle;
    Vector3 CrashNormal;
public:
    Cube(Vector3& startCentr = Vector3(0,0,0), Vector3& startVnormal = Vector3(0,1,0), 
        Vector3& startSnormal = Vector3(1,0,0),Vector3& startSpeed = Vector3(10,10,5), float startWeight = 20, int startSize = 10);
    Vector3 GetCentr();
    Vector3 GetVnormal();
    Vector3 GetS1normal();
    float GetWeight();
    int GetSize();
    void SetCentr(Vector3 Centr);
    void SetVnormal(Vector3 VNormal);
    void SetS1normal(Vector3 S1Normal);
    void SetWeight(float Weight);
    void SetSize(int Size);
    void SetPoints();
    void CrashAngle(Vector3 Speed, Vector3 CnSphere, int& CrashSide, float&Crangle, float SpSize);
    void SetupNormales();
    void MoveCube(Vector3& Speed, float BallWeight, int flag);
    void Normalize(Vector3& UnNorm);
    Vector3 CentrLine(Vector3 CnSphere,Vector3 Spoint);
    Vector3 SpeedOrientation(Vector3 Sp, Vector3 Cn );
    float Scalar(Vector3 f, Vector3 s);
    void ShowCube();
    int CrashPoint(Vector3 CnSphere, Vector3 Sp, float SpSize);
    float GetNorm(Vector3 obj);
    int ControlMove();
    float GetCrashAngle();
    Vector3 GetCrashNormal();
};
