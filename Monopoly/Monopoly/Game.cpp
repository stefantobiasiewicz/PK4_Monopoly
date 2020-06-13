#include "Game.h"

Game::Game()
{
	EndOfGame = 0;
	cur_state = StanInicjalizacji;
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

state_t DoStanInicjalizacji(Game* gra)
{
	std::cout << "stan inicjalizacji\n";
	gra->baza = new BazaDanych;
	// internet musi byc aktywowany po start window;
	//gra->internet = new Internet(0,0);
	gra->interfejs = new Interfejs(gra->baza);
	gra->interfejs->SetOpcjeGry(&gra->opcjegry);

	gra->interfejs->StartWindow();


	// wybor KONKRETNEJ inicjalizacji programu 
	if (gra->baza->isServer)
	{
		return InicjalizacjaSerwer;
	}
	else
	{
		return InicjalizacjaKlient;
	}

	return StanKoncowy;
}
state_t DoInicjalizacjaSerwera(Game* gra)
{
	// pierwsza kominikacja przez internet: oczekiwanie na graczy
	gra->internet = new Internet(false, INTERNET_PORT);
	gra->interfejs->CreateWaitingWindow(gra->internet);
	// odebralismy informacje o klientach 
	// wysylamy kazdemu klientowi daaaaane ( ilosc graczy,{nicki, pionki}, plansza )
	sf::Packet DaneWysylane;
	DaneWysylane << gra->internet->getClientCount()+1;
	gra->baza->ilosc_graczy = gra->internet->getClientCount()+1;
	int pionek = 0;
	for (auto i : gra->baza->gracze)
	{
		DaneWysylane << i.second.nick;
		DaneWysylane << pionek++;
	}
	DaneWysylane << gra->baza->kolor;
	// wysylamy do wszyskich 
	for (int i = 0; i < gra->internet->getClientCount() ;i++)
	{
		gra->internet->Send(DaneWysylane, i);
	}



	// wybor koloru planszy 
	switch (gra->baza->kolor)
	{
	case Rozowa:
		gra->interfejs->CreatePlansza("\grafiki/planszaR.jpg");
		break;
	case Zielona:
		gra->interfejs->CreatePlansza("\grafiki/planszaG.jpg");
		break;
	case Niebieska:
		gra->interfejs->CreatePlansza("\grafiki/planszaB.jpg");
		break;
	case Brak:
		std::cerr << "brak informacji o kolorze planszy :(\n";
		break;
	}

	gra->InterfejsStart = 1;
	gra->interfejs->CreateMainWindow();
	gra->interfejs->CreateButtons();
	return Stan1;
}
state_t DoInicjalizacjaKlienta(Game* gra)
{
	// pierwsza komunikacja przez internet, podlaczenie do serwera wyslanie nickow, i odebranie danych (plansza...)
	gra->internet = new Internet(true, gra->baza->IP , INTERNET_PORT);
	while (gra->internet->setConnection() != sf::Socket::Status::Done)
	{
		cout << "proboje laczyc ponownie\n";
	}
	// Polaczenie 
	sf::Packet nick;
	nick << gra->baza->gracze.begin()->second.nick; // wpisanie do pakietu nicku gracza 1 czyli klienta
	gra->internet->Send(nick);	// wyslanie tego pakietu

	sf::Packet DaneOdebrane;
	while (!gra->internet->Recive(DaneOdebrane))
	{
		// while dziala dopoki nie odbierze danych od serwera ( planszy )
	}
	int kolor;
	int IloscGraczy;
	std::string NickName;
	int pionek;
	DaneOdebrane >> IloscGraczy;
	gra->baza->ilosc_graczy = IloscGraczy;
	for (int i = 0; i < IloscGraczy; i++)
	{
		DaneOdebrane >> NickName;
		DaneOdebrane >> pionek;
		Uzytkownik user(NickName);
		user.pionek = gra->baza->pionki[pionek];
		gra->baza->gracze[NickName] = user;
	}
	DaneOdebrane >> kolor;
	gra->baza->kolor = (Kolor_Planszy)kolor;

	// wybor koloru planszy 
	switch (gra->baza->kolor)
	{
	case Rozowa:
		gra->interfejs->CreatePlansza("\grafiki/planszaR.jpg");
		break;
	case Zielona:
		gra->interfejs->CreatePlansza("\grafiki/planszaG.jpg");
		break;
	case Niebieska:
		gra->interfejs->CreatePlansza("\grafiki/planszaB.jpg");
		break;
	case Brak:
		std::cerr << "brak informacji o kolorze planszy :(\n";
		break;
	}

	gra->InterfejsStart = 1;
	gra->interfejs->CreateMainWindow();
	gra->interfejs->CreateButtons();
	return Stan1;
}

state_t DoStan1(Game* gra)
{
	std::cout << "stan 1\n";
	return Stan2;
}
state_t DoStan2(Game* gra)
{
	//std::cout << "stan 2\n";
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