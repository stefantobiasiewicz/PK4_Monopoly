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
	std::map<std::string, Uzytkownik>::iterator it = gra->baza->gracze.begin();
	for (it; it != gra->baza->gracze.end(); it++)
	{
		DaneWysylane << it->second.nick;
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
	it = gra->baza->gracze.begin();
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
	return StartGrySerwer;
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
	gra->baza->moj_nick = moj_nick_s;

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
	return StartGryKlient;
}

state_t DoExecuteButtons(Game* gra)
{
	if (gra->opcjegry.zakup_domku)
	{
		//jakas funkcja
		std::vector<button*> przyciski;
		button ok({ 100,100 }, { 0,0 } , "\grafiki/button_ok.jpg","\grafiki/button_ok2.jpg" );
		button kup({ 100,100 }, { 0,0 }, "\grafiki/button_kup.jpg", "\grafiki/button_kup2.jpg");
		button odrzuc({ 100,100 }, { 0,0 }, "\grafiki/button_odrzuc.jpg", "\grafiki/button_odrzuc2.jpg");
		przyciski.push_back(&kup);
		przyciski.push_back(&odrzuc);
		gra->interfejs->CreateMessageWindow("", przyciski, gra->baza->karty_nieruchomosci["ulica Wolska"]);
		gra->opcjegry.zakup_domku = false;
	}
	if (gra->opcjegry.zakup_hotelu)
	{
		//jakas funkcja
				//jakas funkcja
		std::vector<button*> przyciski;
		button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
		button kup({ 100,100 }, { 0,0 }, "\grafiki/button_kup.jpg", "\grafiki/button_kup2.jpg");
		przyciski.push_back(&kup);
		przyciski.push_back(&ok);
		gra->interfejs->CreateMessageWindow("", przyciski, gra->baza->karty_szansa_kasa[2]);
		gra->opcjegry.zakup_domku = false;
		gra->opcjegry.zakup_hotelu = false;
	}
	if (gra->opcjegry.zastaw)
	{
		//jakas funkcja
				//jakas funkcja
		std::vector<button*> przyciski;
		button odrzuc({ 100,100 }, { 0,0 }, "\grafiki/button_odrzuc.jpg", "\grafiki/button_odrzuc2.jpg");
		przyciski.push_back(&odrzuc);
		gra->interfejs->CreateMessageWindow("alfa tango", przyciski);
		gra->opcjegry.zakup_domku = false;
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
	gra->baza->nick_aktywnego_gracza = nick_rozpoczynajacy_s;
	nick_rozpoczynajacy << gra->baza->nicki[los];

	gra->internet->SendAll(nick_rozpoczynajacy);
	
	if (nick_rozpoczynajacy_s == gra->baza->moj_nick)
	{
		//gra->interfejs->aktywny_gracz.setString("Teraz Ty sie ruszasz.");
		return RuszaSie;
	}
	else
	{
		//gra->interfejs->aktywny_gracz.setString("Teraz rusza sie gracz: " + nick_rozpoczynajacy_s);
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
	gra->baza->nick_aktywnego_gracza = nick_rozpoczynajacy_s;

	if (nick_rozpoczynajacy_s == gra->baza->moj_nick)
	{
		//gra->interfejs->aktywny_gracz.setString("Teraz Ty sie ruszasz.");
		return RuszaSie;
	}
	else
	{
		//gra->interfejs->aktywny_gracz.setString("Teraz rusza sie gracz: " + nick_rozpoczynajacy_s);
		return Czeka;
	}
}
state_t DoRuszaSie(Game* gra)
{
	if (gra->baza->gracze[gra->baza->moj_nick].wyrok != 0)
	{
		gra->baza->gracze[gra->baza->moj_nick].wyrok--;
		gra->Dane_Do_Wyslania << WIEZIENIE;
		gra->Dane_Do_Wyslania << gra->baza->gracze[gra->baza->moj_nick].wyrok;
		
		return Wysylanie;
	}
	if (gra->opcjegry.kostki == 1)
	{
		if (gra->czy_rzucone_kostki == 0)
		{
			gra->czy_rzucone_kostki = 1;
			/////
		}
	}
	if (gra->czy_rzucone_kostki == 0)
	{
		if (gra->opcjegry.zakup_domku == 1)
		{

		}
		if (gra->opcjegry.zakup_hotelu == 1)
		{

		}
		if (gra->opcjegry.zastaw == 1)
		{

		}
	}

	
	return Stan2;
}
state_t DoCzeka(Game* gra)
{
	return Stan2;
}
state_t DoWysylanie(Game* gra)
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