#include "Vector3.h"

class Sphere
{
private:
    Vector3 centr;
    Vector3 spSpeed;
    float weight;
    float size;
public:
    Sphere(Vector3& startCentr = Vector3(0,0,0),Vector3& startSpeed = Vector3(0,0,0), float stratWeight = 20, float startSize = 20);
    Vector3 GetCentr();
    Vector3 GetSpeed();
    float GetWeight();
    float GetSize();
    //void ShowSphere();
    void MoveSphere(Vector3 DifSpeed, float Crangle, float CubeWeight, Vector3 CrashNorm);
    float GetNorm(Vector3 obj);
    Vector3 SpeedOrientation(Vector3 Sp, Vector3 Cn);
};