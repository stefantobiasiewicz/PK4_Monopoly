#include "Game.h"

Game::Game()
{
	EndOfGame = 0;
	cur_state = StanInicjalizacj;
	// inicjalizacja nastepuje w stanie inicjalizacji 
	baza = nullptr;
	internet = nullptr;
	interfejs = nullptr;
	InternetStart = 0;
	InterfejsStart = 0;
}

void Game::Run()
{
	while (!EndOfGame)
	{
		//***********************************************************************
		// miejsce kodu maszyny stanow
		RunState(this);
		//***********************************************************************
		// internet
		if (InternetStart)
		{

		}
		//***********************************************************************
		// interfejs 
		if (InterfejsStart)
		{
			interfejs->MainFunction();
		}
	}
}






Game::~Game()
{
	delete baza;
	delete interfejs;
	delete internet;
}


//***********************************************************************
// Maszyna stanow


void Game::RunState(Game* gra)
{
	// dzialanie stanow naszyny 
	cur_state = state_table[cur_state](gra);
}

state_t DoStanInicjalizacj(Game* gra)
{
	std::cout << "stan inicjalizacji\n";
	gra->baza = new BazaDanych;
	// internet musi byc aktywowany po start window;
	//gra->internet = new Internet(0,0);
	gra->interfejs = new Interfejs(gra->baza);
	gra->interfejs->StartWindow();
	return Stan1;
}
state_t DoStan1(Game* gra)
{
	std::cout << "stan 1\n";
	gra->InterfejsStart = 1;
	gra->interfejs->CreateMainWindow();
	gra->interfejs->CreatePlansza("\grafiki/planszaG.jpg");
	gra->interfejs->CreateButtons();
	return Stan2;
}
state_t DoStan2(Game* gra)
{
	std::cout << "stan 2\n";
	if (gra->interfejs->IsOpen())
	{
		//gra->interfejs->CreateMessageWindow("");
		return Stan2;
	}
	return StanKoncowy;
}
state_t DoStanKoncowy(Game* gra)
{
	gra->EndOfGame = 1;
	std::cout << "stan koncowy\n";
	return Stan1;
}