#pragma once

#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include"ADT\List.h"
#include"ADT\Queue.h"
// it is the controller of the project
class Battle
{
private:

	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
	double C1;						// No matter what list type you are using to hold enemies, 
	double C2;						// you must pass the enemies to the GUI function as an array of enemy pointers. 
	double C3;						// At every time step, you should update those pointers 
	Queue InActiveEnemies,KilledEnemy;									// to point to the current active enemies 
	List ActiveA;
	List ActiveB;
	List ActiveC;
	List ActiveD;
	
	int EnemyACount;
	int EnemyBCount;
	int EnemyCCount;
	int EnemyDCount;
	int KilledCount;
	bool Win;
	bool Lose;
	string FileName;
	int SpyCount;
	// then pass the pointers list to the GUI function

	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	void UpdateEnemies();
	void ToGraves();
	Castle * GetCastle();
	void ReadInput(GUI *pGUI);//to read from the iput file 
	void MoveToBattle(int TS);
	void Fight(int ts);
	void Simulator(GUI*pGUI);
	void PrintInfo(GUI*pGUI);
	void UpdateAndSort(int Ts);

	//StartGame->Loadfile
	// ask user to choose the mode, default mode ->?

	bool UpdateTowers(); //-> move the active list from dead towers 
	//Output File(Enemy*)
	void Winfn(GUI* pGUI);
	void OutputFile();
	void InterActive(GUI*pGUI);
	void StepByStep(GUI* pGUI);
	void Silent(GUI*pGUI);
	void EnemyAttack(int T, bool x);
	void EnemyMove();

	//Update PavedArea(pGUI); 
	//Silent
	//InterActive
	//StepByStep
	//
	



	//
	// TODO: Add More Member Functions As Needed
};

