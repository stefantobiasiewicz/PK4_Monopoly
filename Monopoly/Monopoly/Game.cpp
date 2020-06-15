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
	if (gra->baza->gracze.size() == 0)
	{
		return StanKoncowy;
	}
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
	//wypelniamy pionki graczom w bazie danych
	int count = 0;
	std::map<std::string, Uzytkownik>::iterator it = gra->baza->gracze.begin();
	for (it;it != gra->baza->gracze.end(); it++)
	{
		it->second.pionek = gra->baza->pionki[count];
		gra->baza->nicki.push_back(it->second.nick);
		count++;

	}

	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("ulica Wolska");
	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("ulica Konopacka");
	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("Aleje Ujazdowskie");
	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("Aleje Jerozolimskie");
	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("Dworzec Gdanski");
	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("Elektrownia");
	gra->baza->gracze.begin()->second.karty_nieruchomosci.push_back("ulica Stalowa");
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
	return Stan1;
}
state_t DoInicjalizacjaKlienta(Game* gra)
{
	// pierwsza komunikacja przez internet, podlaczenie do serwera wyslanie nickow, i odebranie danych (plansza...)
	int count = 0;
	gra->internet = new Internet(true, gra->baza->IP , INTERNET_PORT);
	while (gra->internet->setConnection() != sf::Socket::Status::Done)
	{
		count++;
		if (count >= 40)	// po 40 sekundacjh zostanie wylaczony program
			return StanKoncowy;
		cout << "proboje laczyc ponownie\n";
	}
	// Polaczenie 
	sf::Packet nick;
	nick << gra->baza->gracze.begin()->second.nick; // wpisanie do pakietu nicku gracza 1 czyli klienta
	gra->internet->Send(nick);	// wyslanie tego pakietu


	sf::Packet moj_nick;
	while (!gra->internet->Recive(moj_nick))
	{
		// while dziala dopoki nie odbierze danych od serwera ( obliczonego nicku )
	}
	std::string moj_nick_s;
	moj_nick >> moj_nick_s;

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
		gra->baza->nicki.push_back(NickName);
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
	return Stan1;
}

state_t DoExecuteButtons(Game* gra)
{
	if (gra->opcjegry.zakup_domku)
	{
		//jakas funkcja
		gra->opcjegry.zakup_domku = false;
	}
	if (gra->opcjegry.zakup_hotelu)
	{
		//jakas funkcja
		gra->opcjegry.zakup_hotelu = false;
	}
	if (gra->opcjegry.zastaw)
	{
		//jakas funkcja
		gra->opcjegry.zastaw = false;
	}
	if (gra->opcjegry.kostki)
	{
		//jakas funkcja
		gra->opcjegry.kostki = false;
	}
	if (gra->opcjegry.kup)
	{
		//jakas funkcja
		gra->opcjegry.kup = false;
	}
	if (gra->opcjegry.odrzuc)
	{
		//jakas funkcja
		gra->opcjegry.odrzuc = false;
	}
	if (gra->opcjegry.ok)
	{
		//jakas funkcja
		gra->opcjegry.ok = false;
	}
	if (gra->opcjegry.szansa)
	{
		//jakas funkcja
		gra->opcjegry.szansa = false;
	}
	if (gra->opcjegry.zachowaj)
	{
		//jakas funkcja
		gra->opcjegry.zachowaj = false;
	}
	if (gra->opcjegry.karty1)
	{
		gra->interfejs->CreateCardsWindow(gra->baza->nicki[0]);
		gra->opcjegry.karty1 = false;
	}
	if (gra->opcjegry.karty2)
	{
		gra->interfejs->CreateCardsWindow(gra->baza->nicki[1]);
		gra->opcjegry.karty2 = false;
	}
	return Stan2;
}
state_t DoStartGrySerwer(Game* gra)
{
	//losujemy gracza ktory zaczyna
	std::default_random_engine silnik;
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> liniowy(0, gra->baza->ilosc_graczy);

	int los = liniowy(silnik);

	sf::Packet nick_rozpoczynajacy;
	std::string nick_rozpoczynajacy_s = gra->baza->nicki[los];
	nick_rozpoczynajacy << gra->baza->nicki[los];

	gra->internet->SendAll(nick_rozpoczynajacy);
	
	if (nick_rozpoczynajacy_s == gra->baza->moj_nick)
	{
		return RuszaSie;
	}
	else
	{
		return Czeka;
	}
}
state_t DoStartGryKlient(Game* gra)
{
	sf::Packet nick_rozpoczynajacy;
	bool czy_odebrano = gra->internet->Recive(nick_rozpoczynajacy);
	if (!czy_odebrano)
	{
		return StartGryKlient;
	}

	std::string nick_rozpoczynajacy_s;
	nick_rozpoczynajacy >> nick_rozpoczynajacy_s;

	if (nick_rozpoczynajacy_s == gra->baza->moj_nick)
	{
		return RuszaSie;
	}
	else
	{
		return Czeka;
	}
}

state_t DoRuszaSie(Game* gra)
{
	return Stan2;
}

state_t DoCzeka(Game* gra)
{
	return Stan2;
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
		return ExecuteButtons;
	}
	return StanKoncowy;
}
state_t DoStanKoncowy(Game* gra)
{
	gra->EndOfGame = 1;
	std::cout << "stan koncowy\n";
	return Stan1;
}