#include "Battle.h"
#include"Enemies\Enemy.h"
#include"Enemies\NonShieldedEnemy.h"
#include"Enemies\PaverEnemy.h"
#include"Enemies\ShieldedEnemy.h"
#include"Enemies\MagicianEnemy.h"
#include"Enemies\TheSpy.h"
#include<iostream>
#include<fstream>
#include<Windows.h>
//#include"ADT\List.h"
//#include"ADT\Queue.h"
#pragma comment(lib,"Winmm.lib")
using namespace std;
#include<string.h>
Battle::Battle()
{
	SpyCount = 0;
	EnemyCount = 0;
	EnemyACount = 0;
	EnemyBCount = 0;
	EnemyCCount = 0;
	EnemyDCount = 0;
	KilledCount = 0;
	Win = false;
	Lose = false;
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::ReadInput(GUI *pGUI)
{
	ifstream fIn;
	Point p;
	p.x = 0; p.y = 0;
	pGUI->ClearStatusBar();
	pGUI->PrintMessage("Hey there Warrior! Please Enter the name of your file,May the odds be in your favor", 1);
	pGUI->GetPointClicked(p);
	pGUI->ClearStatusBar();
	FileName = pGUI->GetString();

	pGUI->ClearStatusBar();
	string s = FileName + ".txt";
	fIn.open(s);
	while (!fIn.is_open())
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("WE Couldn't find it :( Please Enter the name of your file Again ", 1);
		pGUI->GetPointClicked(p);
		pGUI->ClearStatusBar();
		string s = pGUI->GetString();
		pGUI->ClearStatusBar();
		s = s + ".txt";
		fIn.open(s);
	}
	if (fIn.is_open())
	{
		double Health;
		int Max;
		double Power;
		fIn >> Health >> Max >> Power;
		BCastle.SetTowers(Health, Max, Power);
		fIn >> C1 >> C2 >> C3;
		int id;
		fIn >> id;
		while (id != -1)
		{
			int Type, T, H, POW, RLD;
			char r;
			REGION R;
			fIn >> Type >> T >> H >> POW >> RLD >> r;
			if (r == 'A')
				R = A_REG;
			else if (r == 'B')
				R = B_REG;
			else if (r == 'C')
				R = C_REG;
			else if (r == 'D')
				R = D_REG;

			if (Type == 0)
			{
				PaverEnemy* E = new PaverEnemy(DARKBLUE, R);
				E->SetData(id, H, POW, RLD, T);
				InActiveEnemies.enqueue(E);

			}
			if (Type == 1)
			{
				NonShieldedEnemy* E = new NonShieldedEnemy(DARKOLIVEGREEN, R);
				E->SetData(id, H, POW, RLD, T);
				InActiveEnemies.enqueue(E);

			}
			if (Type == 2)
			{
				ShieldedEnemy* E = new ShieldedEnemy(ORANGERED, R);
				E->SetData(id, H, POW, RLD, T);
				InActiveEnemies.enqueue(E);
			}
			if (Type == 3)
			{
				MagicianEnemy* E = new MagicianEnemy(Patriarch, R);
				E->SetData(id, H, POW, RLD, T);
				InActiveEnemies.enqueue(E);

			}
			if (Type == 4)
			{
				SpyCount++;
				TheSpy* E = new TheSpy(BLACK, R);
				E->SetData(id, H, POW, RLD, T);
				InActiveEnemies.enqueue(E);

			}
			fIn >> id;
		}
	}

}
void Battle::MoveToBattle(int TS)
{
	while (InActiveEnemies.isempty()==false&& (InActiveEnemies.peekFront())->GetArrivalTime() == TS)
	{
		switch (InActiveEnemies.peekFront()->GetRegion())
		{
		case 0:
			ActiveA.Insert(InActiveEnemies.peekFront());
			AddEnemy(InActiveEnemies.peekFront());
			
			EnemyACount++;
			break;
		case 1:
			ActiveB.Insert(InActiveEnemies.peekFront());
			AddEnemy(InActiveEnemies.peekFront());
			EnemyBCount++;
			break;
		case 2:
			ActiveC.Insert(InActiveEnemies.peekFront());
			AddEnemy(InActiveEnemies.peekFront());
			EnemyCCount++;
			break;
		case 3:
			ActiveD.Insert(InActiveEnemies.peekFront());
			AddEnemy(InActiveEnemies.peekFront());
			EnemyDCount++;
			break;
		}
		//EnemyCount++;
		InActiveEnemies.dequeue();
	}
}

void Battle::ToGraves()
{
	Node *E = ActiveA.GetHead();
	while (E != NULL)
	{
		if (E != NULL&&E->GetData()->GetHealth() == 0)
		{
			/*Enemy*x;
			if (E->GetData()->ENon_Shielded())
			x = new NonShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else if (E->GetData()->EPaver())
			x = new PaverEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else
			x = new ShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			x->SetData(E->GetData()->GetID(), E->GetData()->GetHealth(), E->GetData()->GetFirePower(), E->GetData()->GetReloadTime(), E->GetData()->GetArrivalTime());*/
			KilledEnemy.enqueue(E->GetData());
			Enemy*P = E->GetData();
			E = E->GetNext();
			if (ActiveA.Remove(P));
			{
				if (P->GetK() == 0)
				{
					Tower T = BCastle.GetArrayOfTowers()[0];
					T.SetSpy(false);
					BCastle.SetArrayOfTowers(T, 0);
					SpyCount--;
				}
				EnemyACount--;
				EnemyCount--;
				KilledCount++;
			}

		}
		else
			E = E->GetNext();
	}
	E = ActiveB.GetHead();
	while (E != NULL)
	{
		if (E != NULL&&E->GetData()->GetHealth() == 0)
		{
			/*Enemy*x;
			if (E->GetData()->ENon_Shielded())
			x = new NonShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else if (E->GetData()->EPaver())
			x = new PaverEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else
			x = new ShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			x->SetData(E->GetData()->GetID(), E->GetData()->GetHealth(), E->GetData()->GetFirePower(), E->GetData()->GetReloadTime(), E->GetData()->GetArrivalTime());*/

			KilledEnemy.enqueue(E->GetData());
			Enemy*P = E->GetData();
			E = E->GetNext();
			if (P->GetK() == 0)
			{

				Tower T = BCastle.GetArrayOfTowers()[1];
				T.SetSpy(false);
				BCastle.SetArrayOfTowers(T, 1);
				SpyCount--;
			}
			if (ActiveB.Remove(P))
			{
				EnemyBCount--;
				EnemyCount--;
				KilledCount++;
			}

		}
		else
			E = E->GetNext();
	}
	E = ActiveC.GetHead();
	while (E != NULL)
	{
		if (E != NULL&&E->GetData()->GetHealth() == 0)
		{
			/*Enemy*x;
			if (E->GetData()->ENon_Shielded())
			x = new NonShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else if (E->GetData()->EPaver())
			x = new PaverEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else
			x = new ShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			x->SetData(E->GetData()->GetID(), E->GetData()->GetHealth(), E->GetData()->GetFirePower(), E->GetData()->GetReloadTime(), E->GetData()->GetArrivalTime());*/


			KilledEnemy.enqueue(E->GetData());
			Enemy*P = E->GetData();
			E = E->GetNext();
			if (P->GetK() == 0)
			{

				Tower T = BCastle.GetArrayOfTowers()[2];
				T.SetSpy(false);
				BCastle.SetArrayOfTowers(T, 2);
				SpyCount--;
			}
			if (ActiveC.Remove(P))
			{

				EnemyCCount--;
				EnemyCount--;
				KilledCount++;
			}
		}
		else
			E = E->GetNext();
	}
	E = ActiveD.GetHead();
	while (E != NULL)
	{
		if (E != NULL&&E->GetData()->GetHealth() == 0)
		{
			/*Enemy*x;
			if (E->GetData()->ENon_Shielded())
			x = new NonShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else if (E->GetData()->EPaver())
			x = new PaverEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			else
			x = new ShieldedEnemy(E->GetData()->GetColor(), E->GetData()->GetRegion());
			x->SetData(E->GetData()->GetID(), E->GetData()->GetHealth(), E->GetData()->GetFirePower(), E->GetData()->GetReloadTime(), E->GetData()->GetArrivalTime());*/

			KilledEnemy.enqueue(E->GetData());
			Enemy*P = E->GetData();
			E = E->GetNext();
			if (P->GetK() == 0)
			{
				Tower T = BCastle.GetArrayOfTowers()[3];
				T.SetSpy(false);
				BCastle.SetArrayOfTowers(T, 3);
				SpyCount--;
			}
			if (ActiveD.Remove(P))
			{

				EnemyDCount--;
				EnemyCount--; 
				KilledCount++;
			}

		}
		else
			E = E->GetNext();
	}
}void Battle::Fight(int ts)
{
	if (EnemyCount == 0)
		return;
	BCastle.Fight(ActiveA,EnemyACount,ts);
	BCastle.Fight(ActiveB, EnemyBCount,ts);
	BCastle.Fight(ActiveC, EnemyCCount,ts);
	BCastle.Fight(ActiveD, EnemyDCount,ts);
}

void Battle::Simulator(GUI*pGUI)
{
	ReadInput(pGUI);
	for (int i = 0;i < 10;i++)
	{
		
		UpdateEnemies();
		MoveToBattle(i);
		ToGraves();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		DrawEnemies(pGUI);
		PrintInfo(pGUI);
		Fight(i);
		Point p;
		p.x = 0;p.y = 0;
		pGUI->GetPointClicked(p);
	}

}
void Battle::PrintInfo(GUI*pGUI)
{
	
	
	pGUI->ClearStatusBar();
	string r;
	Tower T;
	for (int i = 0; i < 4; i++)
	{
	  T  = BCastle.GetArrayOfTowers()[i];
		if (i == 0)
		{
			r = 'A';
		}
		if (i == 1)
		{
			r = 'B';
		}
		if (i == 2)
		{
			r = 'C';
		}
		if (i == 3)
		{
			r = 'D';
		}
		pGUI->PrintMessage("Tower" + r + " Health = " + to_string(T.GetHealth()) + " Power = " + to_string(T.GetPower()) + " Max number of Enemies  = " + to_string(T.GetMax()), i);
	}

	pGUI->PrintMessage("Total Number of Active Enemy = " + to_string(EnemyCount), 4);
	pGUI->PrintMessage("Total Number of killed Enemy = " + to_string(KilledCount), 5);
	int j = 6;
	int count = 0;
	for (int i = 0;i < EnemyACount;i++)
	{
		j += i;
		Enemy* ptr;
		ActiveA.getEntry(i + 1, ptr);
		if(ptr->GetK()==0)
		pGUI->PrintMessage("ID: = " + to_string(ptr->GetID()) + " " + "Color: = " + ptr->ColorToString(ptr->GetColor()) + "   Region: = " + ptr->RegionToString(ptr->GetRegion()) + " Distance: = " + to_string(ptr->GetDistance()) + " Fire Power: = " + to_string(ptr->GetFirePower()), j);
		
		count++;
	}
	if (count == 1)
		j++;
	count = 0;
	for (int i = 0;i < EnemyBCount;i++)
	{

		j += i;
		Enemy* ptr;
		ActiveB.getEntry(i + 1, ptr);
		if (ptr->GetK() == 0)
		pGUI->PrintMessage("ID: = " + to_string(ptr->GetID()) + " " + "Color: = " + ptr->ColorToString(ptr->GetColor()) + "   Region: = " + ptr->RegionToString(ptr->GetRegion()) + " Distance: = " + to_string(ptr->GetDistance()) + " Fire Power: = " + to_string(ptr->GetFirePower()), j);
		count++;
	}
	if (count == 1)
		j++;
	count = 0;
	for (int i = 0;i < EnemyCCount;i++)
	{
		j += i;
		Enemy* ptr;
		ActiveC.getEntry(i + 1, ptr);
		if (ptr->GetK() == 0)
		pGUI->PrintMessage("ID: = " + to_string(ptr->GetID()) + " " + "Color: = " + ptr->ColorToString(ptr->GetColor()) + "   Region: = " + ptr->RegionToString(ptr->GetRegion()) + " Distance: = " + to_string(ptr->GetDistance()) + " Fire Power: = " + to_string(ptr->GetFirePower()), j);
		count++;
	}
	if (count == 1)
		j++;
	count = 0;
	for (int i = 0;i < EnemyDCount;i++)
	{
		j += i;
		Enemy* ptr;
		ActiveD.getEntry(i + 1, ptr);
		if (ptr->GetK() == 0)
		pGUI->PrintMessage("ID: = " + to_string(ptr->GetID()) + " " + "Color: = " + ptr->ColorToString(ptr->GetColor()) + "   Region: = " + ptr->RegionToString(ptr->GetRegion()) + " Distance: = " + to_string(ptr->GetDistance()) + " Fire Power: = " + to_string(ptr->GetFirePower()), j);
		count++;
	}

	
}
void Battle::UpdateEnemies()
{
	Enemy*E1;
	if (EnemyCount == 0)
		return;
	int j = EnemyCount - 1;
	for (int i = 0;i < EnemyCount;i++)
	{
		if (BEnemiesForDraw[i]->GetHealth() == 0)
		{
			while (BEnemiesForDraw[j]->GetHealth() == 0 && j > i)
				j--;
			if (j == i)
				break;
			else
			{
				BEnemiesForDraw[i] = BEnemiesForDraw[j];
				j--;

			}
		}
	}/*
	for (int i = 0; i < EnemyCount; i++)
	{
		if (BEnemiesForDraw[i]->GetHealth() == 0)
		{
				BEnemiesForDraw[EnemyCount-1] = BEnemiesForDraw[i];
		}
	}
*/
	
}



void Battle::Winfn(GUI* pGUI)
{

	if (EnemyCount == SpyCount && InActiveEnemies.isempty())
	{

		Win = true;

	}

	int CountForTower = 0;
	for (int i = 0; i<4; i++)
	{
		if (BCastle.GetArrayOfTowers()[i].GetHealth() == 0)
			CountForTower++;

	}
	if (CountForTower == 4)
	{

		Lose = true;


	}
	if (Win && !Lose)
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("You win!", 4);
		PlaySound("win.wav", NULL, SND_FILENAME | SND_SYNC);
	}
	else if (!Win&&Lose)
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("You lose!", 4);
	PlaySound("troy.wav", NULL, SND_FILENAME | SND_SYNC);
	}
	else if (Win&&Lose)
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("You win!", 4);
		 PlaySound("win.wav", NULL, SND_FILENAME | SND_SYNC);
	}



}

bool Battle::UpdateTowers()
{
	/*int Dead = 0;
	Tower*T = BCastle.GetArrayOfTowers();
	for (int i = 0; i < 4; i++)
	{
	if (T[i].GetHealth() == 0)
	Dead++;

	}
	if (Dead == 4)
	return false;

	List<Enemy*> enemyarr[4] = { ActiveA, ActiveB, ActiveC, ActiveD };

	for (int i = 0; i < 4; i++)
	{
	if (BCastle.GetArrayOfTowers()[i].GetHealth() == 0)
	{
	int j = (i + 1) < 3 ? i + 1 : 0;
	while (T[j].GetHealth() == 0 && j <= 3)
	{
	j++;
	if (j == 3 && T[j].GetHealth() == 0 && T[0].GetHealth() != 0)
	j = 0;
	}

	for (int k = 0; k<4; k++)
	{
	if (k == j)
	{
	int l = 0;
	Enemy* temp;
	while (!enemyarr[i].IsEmpty())
	{
	enemyarr[i].getEntry(l, temp);
	enemyarr[k].Insert(temp);
	l++;
	enemyarr[i].Remove(temp);
	}
	break;
	}
	}
	}

	}*/

	int Dead = 0
		
		;
	Tower*T = BCastle.GetArrayOfTowers();
	for (int i = 0; i < 4; i++)
	{
		if (T[i].GetHealth() == 0)
			Dead++;

	}
	if (Dead == 4)
		return false;
	List* enemyarr[4] = { &ActiveA, &ActiveB, &ActiveC, &ActiveD };
	if(Dead>0)
	{
		

		for (int i = 0; i < 4; i++)
		{
			if (BCastle.GetArrayOfTowers()[i].GetHealth() == 0)
			{
				int j = (i + 1) < 3 ? i + 1 : 0;
				while (T[j].GetHealth() == 0 && j <= 3)
				{
					j++;
					if (j == 3 && T[j].GetHealth() == 0 && T[0].GetHealth() != 0)
						j = 0;
				}
				Node *N1 = enemyarr[j]->GetHead();
				Node *N2 = enemyarr[i]->GetHead();
				REGION R;
				switch (j)
				{
				case 0:
					R = A_REG;
					break;
				case 1:
					R = B_REG;
					break;
				case 2:
					R = C_REG;
					break;
				case 3:
					R = D_REG;
					break;
				}
				while (N2 != NULL)
				{
					if (N2->GetData()->GetDistance() < T[j].GetPavedArea())
						N2->GetData()->SetDistance(T[j].GetPavedArea());
					N2->GetData()->SetRegion(R);
					N2 = N2->GetNext();
				}
				Enemy*B;
		
				int LL;
				if (i == 0)
				{
					LL = EnemyACount;EnemyACount = 0;
				}
				else if (i == 1)
				{
					LL = EnemyBCount;EnemyBCount = 0;
				}
				else if (i == 2)
				{
					LL = EnemyCCount;EnemyCCount = 0;
				}
				else
				{
					LL = EnemyDCount;EnemyDCount = 0;
				}
				switch (j)
				{
				case 0:
					EnemyACount += LL;
					break;
				case 1:
					EnemyBCount += LL;
					break;
				case 2:
					EnemyCCount += LL;
					break;
				case 3:
					EnemyDCount += LL;
					break;
				}

				//enemyarr[j].SortedMerge(N1, N2);
				enemyarr[j]->Append(*enemyarr[i]);
				//ActiveB.Append(ActiveA);
				for (int n = 0; n < InActiveEnemies.GetCount(); n++)
				{
					B = InActiveEnemies.peekFront();
					if (B->GetRegion() == i)
						B->SetRegion(R);
					InActiveEnemies.dequeue();
					InActiveEnemies.enqueue(B);

				}

			}

		}
	}
}
void Battle::OutputFile()
{
	double AvrKillDelay = 0;
	double AvrFirstShot = 0;
	ofstream fOut;
	fOut.open(FileName + "OutputFill.txt");
	fOut << " KTS    S    FD    KD    LT  " << endl;
	for (int i = 0; i < KilledCount; i++)
	{
		Enemy* E = KilledEnemy.peekFront();
		AvrKillDelay += E->GetKillDelay();
		AvrFirstShot += E->GetFirstShootingTime();
		int LT = E->GetKTS() - E->GetArrivalTime();
		fOut << E->GetKTS() << "    " << E->GetID() << "    " << E->GetFirstShootingTime() << "    " << E->GetKillDelay() << "    " << LT << endl;
		KilledEnemy.dequeue();
		delete E;

	}
	fOut << " T1_Total_Damage    T2_Total_Damage    T3_Total_Damage    T4_Total_Damage " << endl;
	Tower* T = BCastle.GetArrayOfTowers();
	for (int i = 0; i < 4; i++)
	{
		fOut << T[i].GetTotalDamage() << "                 ";
	}
	fOut << endl;
	fOut << " T1_Unpaved_Dist    T2_Unpaved_Dist    T3_Unpaved_Dist   T4_Unpaved_Dist " << endl;
	for (int i = 0; i < 4; i++)
	{
		int d = T[i].GetPavedArea();
		fOut << d << "                 ";
	}
	fOut << endl << "The Game is  ";
	if (Win)
	{
		fOut << " WIN " << endl;
		fOut << "Total Enemys =  " << KilledCount << endl;
	}
	else
	{
		fOut << " LOSS " << endl;
		fOut << "Numbe Of Killed Enemys =  " << KilledCount << endl;
		fOut << "Numbe Of Active Enemys =  " << EnemyCount << endl;
	}
	fOut << "Average First Shot Delay = " << (AvrFirstShot / KilledCount) << endl;
	fOut << "Average Kill Delay = " << (AvrKillDelay / KilledCount) << endl;

}

void Battle::InterActive(GUI*pGUI)
{
	ReadInput(pGUI);
	int y = 0;

	while (Win == false && y >= 0 && Lose == false)
	{
		Point P;
		pGUI->GetPointClicked(P);

		MoveToBattle(y);
		UpdateAndSort(y);

		EnemyAttack(y,true);
		EnemyMove();
		Fight(y);
		UpdateEnemies();
		ToGraves();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		pGUI->DrawUnPaved(BCastle.GetArrayOfTowers()[0].GetPavedArea(), BCastle.GetArrayOfTowers()[1].GetPavedArea(), BCastle.GetArrayOfTowers()[2].GetPavedArea(), BCastle.GetArrayOfTowers()[3].GetPavedArea());

		DrawEnemies(pGUI);
		PrintInfo(pGUI);
		Winfn(pGUI);
		UpdateTowers();
		//fee output and tower attack
		 
		
		
           
	   
	    y++;
	}
	OutputFile();

}

void Battle::StepByStep(GUI*pGUI)
{
	
	ReadInput(pGUI);
	int y=0;
	
	while(Win==false&&y>=0&&Lose==false)
	{

		MoveToBattle(y);
		UpdateAndSort(y);
		EnemyAttack(y,true);
		EnemyMove();
		Fight(y);
		UpdateEnemies();
		ToGraves();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		pGUI->DrawUnPaved(BCastle.GetArrayOfTowers()[0].GetPavedArea(), BCastle.GetArrayOfTowers()[1].GetPavedArea(), BCastle.GetArrayOfTowers()[2].GetPavedArea(), BCastle.GetArrayOfTowers()[3].GetPavedArea());

		DrawEnemies(pGUI);
	    PrintInfo(pGUI);
		UpdateTowers();
		Winfn(pGUI);
		Sleep(1000);
    y++;
	}
	OutputFile();
}

void Battle::Silent(GUI* pGUI)
{
	ReadInput(pGUI);
	int y=0;
	

	while (Win == false && y >= 0 && Lose == false)
	{

		MoveToBattle(y);
		UpdateAndSort(y);
		EnemyAttack(y, false);
		EnemyMove();
		Fight(y);
		UpdateEnemies();
		ToGraves();
		//pGUI->ClearBattleArea();
		//pGUI->DrawCastle();
		//DrawEnemies(pGUI);
		//PrintInfo(pGUI);
		UpdateTowers();
		Winfn(pGUI);
		y++;
	}
	OutputFile();
}
void Battle::EnemyAttack(int TS,bool x)
{

	Tower T;
	Node *ptr = ActiveA.GetHead();
	for (int i = 0; i<EnemyACount; i++)
	{
		T = BCastle.GetArrayOfTowers()[0];
		ptr->GetData()->Attack(ActiveA, T, TS,x);
		ptr = ptr->GetNext();
		BCastle.SetArrayOfTowers(T, 0);

	}

	ptr = ActiveB.GetHead();
	for (int i = 0; i<EnemyBCount; i++)
	{

		T = BCastle.GetArrayOfTowers()[1];
		ptr->GetData()->Attack(ActiveB, T, TS,x);
		ptr = ptr->GetNext();
		BCastle.SetArrayOfTowers(T, 1);
	}
	ptr = ActiveC.GetHead();
	for (int i = 0; i<EnemyCCount; i++)
	{
		T = BCastle.GetArrayOfTowers()[2];
		ptr->GetData()->Attack(ActiveC, T, TS,x);
		ptr = ptr->GetNext();
		BCastle.SetArrayOfTowers(T, 2);
	}

	ptr = ActiveD.GetHead();
	for (int i = 0; i<EnemyDCount; i++)
	{
		T = BCastle.GetArrayOfTowers()[3];
		ptr->GetData()->Attack(ActiveD, T, TS,x);
		ptr = ptr->GetNext();
		BCastle.SetArrayOfTowers(T, 3);
	}

}
void Battle::EnemyMove()
{

	Tower T;
	Node*ptr = ActiveA.GetHead();
	for (int i = 0; i<EnemyACount; i++)
	{
		T = BCastle.GetArrayOfTowers()[0];
		ptr->GetData()->Move(T);
		ptr = ptr->GetNext();
		
	}

	ptr = ActiveB.GetHead();
	for (int i = 0; i<EnemyBCount; i++)
	{

		T = BCastle.GetArrayOfTowers()[1];
		ptr->GetData()->Move(T);
		ptr = ptr->GetNext();
	}
	ptr = ActiveC.GetHead();
	for (int i = 0; i<EnemyCCount; i++)
	{
		T = BCastle.GetArrayOfTowers()[2];
		ptr->GetData()->Move(T);
		ptr = ptr->GetNext();
	}

	ptr = ActiveD.GetHead();
	for (int i = 0; i<EnemyDCount; i++)
	{
		T = BCastle.GetArrayOfTowers()[3];
		ptr->GetData()->Move(T);
		ptr = ptr->GetNext();
	}

}
void Battle::UpdateAndSort(int Ts)
{
	Node *N = ActiveA.GetHead();
	while (N != NULL)
	{
		if (N->GetData()->GetK() == 2)
			N->GetData()->CalcPriority(C1, C2, C3, Ts);
		N = N->GetNext();

	}
	ActiveA.Sort();
	N = ActiveB.GetHead();
	while (N != NULL)
	{
		if (N->GetData()->GetK() == 2)
			N->GetData()->CalcPriority(C1, C2, C3, Ts);
		N = N->GetNext();

	}
	ActiveB.Sort();
	N = ActiveC.GetHead();
	while (N != NULL)
	{
		if (N->GetData()->GetK() == 2)
			N->GetData()->CalcPriority(C1, C2, C3, Ts);
		N = N->GetNext();
	}
	ActiveC.Sort();
	N = ActiveD.GetHead();
	while (N != NULL)
	{
		if (N->GetData()->GetK() == 2)
			N->GetData()->CalcPriority(C1, C2, C3, Ts);
		N = N->GetNext();

	}
	ActiveD.Sort();
}