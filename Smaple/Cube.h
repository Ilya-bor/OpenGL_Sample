
#include "Vector3.h"

class Cube
{
private:
    Vector3 centr;
    Vector3 Vnormal;
    Vector3 S1normal,S2normal,S3normal,S4normal;
    Vector3 TP[5];
    float weight;
    int size;
    int CrashSide;
public:
    Cube(Vector3& startCentr = Vector3(0,0,0), Vector3& startVnormal = Vector3(0,1,0), 
        Vector3& startS1normal = Vector3(1,0,0), float startWeight = 20, int startSize = 10);
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
    float CrashAngle(Vector3 Speed, Vector3 CnSphere, int& CrashSide);
    void SetupNormales();
    void MoveCube(Vector3& Speed, float BallWeight);
    void Normalize(Vector3& UnNorm);
    Vector3 CentrLine(Vector3 CnSphere,Vector3 Spoint);
    Vector3 SpeedOrientation(Vector3 Sp, Vector3 Cn );
    float Scalar(Vector3 f, Vector3 s);
};