#include "Vector3.h"

class Map
{
private:
	int numbObj;
	int** map;
public:
	Map(int startNumb = 50);
	int GetNumb();
	int GetIJ(int i, int j);
	void SetCube(int i, int j, int num);
	int** GetObj(Vector3 CnSphere);
	void MoveObj(int NumObj);
};