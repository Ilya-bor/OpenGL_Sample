#include "Vector3.h"

class Camera
{
private:
    Vector3 position;
    float azimuthalAngle;
    float zenithAngle;
    float range;
public:
    Camera(Vector3& startPosition = Vector3(0, 0, 0), float startAzimuthalAngle = 180, float startZenithAngle = 25, float range = 400.0);
    float GetAzimuthalAngle();
    float GetZenithAngle();
    float GetRange();
    void SetRange(float range);
    void SetAzimuthalAngle(float azimuthalAngle);
    void SetZenithAngle(float zenithAngle);
    void Setup(float displayWidth, float displayHeight, Vector3 CnSphere);
    Vector3 GetPosition();
    void SetPosition(Vector3 position);
    Vector3 GetOrientation();
};