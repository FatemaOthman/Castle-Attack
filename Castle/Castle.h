#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "Tower.h"
class List;

class Castle
{
	Tower Towers[NoOfRegions];

	//
	// TODO: Add More Data Members As Needed
	//
	
public:

	Castle();
	void SetTowers(double h, int m, double p);
	void SetTowersHealth(double h);
	void SetTowersMax(int  h);
	void SetTowersPower(double h);
	void Fight(List&Active,int Count, int ts);
	Tower* GetArrayOfTowers();
	void SetArrayOfTowers(Tower, int i);
		// UpdateTowers
	// TODO: Add More Member Functions As Needed
	//
};
