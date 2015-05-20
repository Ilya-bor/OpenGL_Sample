#ifndef Vector3_INCLUDED
#define Vector3_INCLUDED
struct Vector3
{
    float X;
    float Y;
    float Z;
    Vector3(): X(0), Y(0), Z(0){}
    Vector3(float X, float Y, float Z) : X(X), Y(Y), Z(Z){}
    Vector3(Vector3& other) : X(other.X), Y(other.Y), Z(other.Z){}
};
#endif