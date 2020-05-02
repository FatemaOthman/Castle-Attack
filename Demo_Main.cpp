#include "Battle.h"
#include "GUI\GUI.h"
int main()
{
	//
	// THIS IS JUST A DEMO
	// THIS MAIN SHOULD BE CHANGED IN PHASE 1 AND PHASE 2
	//
	
	MenuAction Act;

	Battle* pGameBattle = new Battle;

	GUI * pGUI = new GUI;
	do
	{
		Act = pGUI->GetUserAction();

		switch (Act)
		{
		case IACTIVE:
			pGameBattle->InterActive(pGUI);
			break;
		case STEP:
			pGameBattle->StepByStep(pGUI);
			break;
		case SILENT:
			pGameBattle->Silent(pGUI);
			break;
		case NO:
			break;
		case EXIT:
			delete pGUI;
			delete pGameBattle;
			return 0;
			break;
		}





	} while(Act!=EXIT);



	delete pGUI;
	delete pGameBattle;
	
	return 0;
}

