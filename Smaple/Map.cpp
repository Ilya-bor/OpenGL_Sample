#include "StdAfx.h"
#include"Map.h"
#include <math.h>

Map::Map(int startNumb):numbObj(startNumb)
{
	map = new int*[82];
	for(int i = 0; i<82; i++)
	{
		map[i] = new int [82];
		for(int j = 0; j<82; j++)
		{
			map[i][j] = -1;
		}
	}
}
int Map::GetNumb()
{
	return numbObj;
}
int Map::GetIJ(int i, int j)
{
	return map[i][j];
}
void Map::SetCube(int i, int j, int num)
{
    if(this-> map[i][j] == -1)
    {
        this-> map[i][j] = num;
    }
    else
    {
        if ((i != 80)&&(this-> map[i+1][j] == -1))
        {
            this-> SetCube(i+1,j,num); 
        }
        else
        {
            this-> SetCube(i,j+1,num);
        }
    }
	
}
int** Map::GetObj(Vector3 CnSphere)
{
	int** Res;
	Res = new int*[3];
	for(int u = 0; u<3; u++)
	{
		Res[u] = new int[3];
		for(int y = 0; y<3; y++)
		{
			Res[u][y] = -1;
		}
	}
	CnSphere.X += 4000/pow(2,0.5);
	CnSphere.Z += 4000/pow(2,0.5);
	int i = (CnSphere.X*pow(2,0.5)/100) + 1;
	int j = (CnSphere.Z*pow(2,0.5)/100) + 1;
	int h = 0;
	int l = 0;
	for(int u = i-1; u<i+2; u++)
	{
		for(int y = j-1; y<j+2;y++)
		{
			Res[h][l] = map[u][y];
			l++;
		}
		h++;
		l = 0;
	}
	return  Res;
}