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

	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("ulica Wolska");
	gra->baza->pola[39]->domy = 3;
	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("ulica Konopacka");
	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("Aleje Ujazdowskie");
	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("Aleje Jerozolimskie");
	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("Dworzec Gdanski");
	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("Elektrownia");
	gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci.push_back("ulica Stalowa");
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
		Uzytkownik* gracz = &gra->baza->gracze[gra->baza->moj_nick];
		gra->interfejs->CreateZastawWindow(0, gracz);
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
	std::uniform_int_distribution<int> liniowy(0, gra->baza->ilosc_graczy - 1); // <----  musi byc - 1 bo w bazie jest ilosc a tablica jest indeksowana od 0 

	int los = liniowy(silnik);

	sf::Packet nick_rozpoczynajacy;
	std::string nick_rozpoczynajacy_s = gra->baza->nicki[los];				// <----- tu sie program wysypywal bo zwraca³ czasem 2  
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
	Resolution res;
	sf::Vector2f scale = res.scale();
	if (gra->baza->gracze[gra->baza->moj_nick].wyrok != 0)
	{
		gra->baza->gracze[gra->baza->moj_nick].wyrok--;

		Packet_Wiezienie pakiet(gra->baza->gracze[gra->baza->moj_nick].wyrok);
		gra->Dane_Do_Wyslania.clear();
		gra->Dane_Do_Wyslania = pakiet.getPakiet();
		
		return Wysylanie;
	}
	if (gra->opcjegry.kostki == 1)
	{
		if (gra->czy_rzucone_kostki == 0)
		{
			gra->czy_rzucone_kostki = 1;
			//rzucamy kostk¹
			int rzut = gra->interfejs->kostka->Rzuc();

			//aktualizujemy numer pola w uzytkowniku
			int numer_pola = gra->baza->gracze[gra->baza->moj_nick].numer_pola;
			int numer_gracza = gra->baza->gracze[gra->baza->moj_nick].pionek->nr_pionka;
			numer_pola += rzut;
			if (numer_pola > 39)
			{
				numer_pola -= 40;
			}
			gra->baza->gracze[gra->baza->moj_nick].numer_pola = numer_pola;
			
			//zmieniamy pozycjê pionka
			gra->baza->gracze[gra->baza->moj_nick].pionek->setPosition(res.x({ gra->baza->pola[numer_pola].pozycja[numer_gracza].x }), res.y(gra->baza->pola[numer_pola].pozycja[numer_gracza].y));
			
			//wykonujemy funkcjê karty przypisanej do tego pola
			Karta* karta = gra->baza->pola[numer_pola].karta;
		
			if (karta)
			{
				if (dynamic_cast<Ulica*>(karta) || dynamic_cast<Dworzec_Uzyt_Pub*>(karta))
				{
					Funkcje_Kart_Ulica funkcje(&gra->baza->pola[numer_pola]);
					if (karta->wlasciciel)
					{
						//ulica jest ju¿ kupiona
						int czynsz = funkcje.Czynsz();
						if (gra->baza->gracze[gra->baza->moj_nick].portfel >= czynsz)
						{
							//gracza stac na op³acenie czynszu
							//wyswietlanie okna z komunikatem
							std::vector<button*> przyciski;
							button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
							przyciski.push_back(&ok);
							gra->interfejs->CreateMessageWindow("Musisz zaplacic graczowi: " + karta->wlasciciel->nick + std::to_string(czynsz), przyciski);

							//akt zaplaty
							funkcje.zaplata_czynszu(czynsz, &gra->baza->gracze[gra->baza->moj_nick]);
							
							//przygotowanie protoko³u
							Packet_Czynsz_Zap pakiet(numer_pola, gra->baza->moj_nick, karta->wlasciciel->nick, czynsz);
							gra->Dane_Do_Wyslania.clear();
							gra->Dane_Do_Wyslania = pakiet.getPakiet();
							return Wysylanie;
						}
						else
						{
							//uzytkownika nie stac na zaplate czynszu
							//wyswietlanie okna z komunikatem
							std::vector<button*> przyciski;
							button poddaj_sie({ 100,100 }, { 0,0 }, "\grafiki/button_poddaj.jpg", "\grafiki/button_poddaj2.jpg");
							przyciski.push_back(&poddaj_sie);

							button zastaw({ 100,100 }, { 0,0 }, "\grafiki/button_zastawp.jpg", "\grafiki/button_zastawp2.jpg");
							przyciski.push_back(&zastaw);

							//dopóki gracza nie staæ lub nie podda sie zastawia ulice
							while (gra->baza->gracze[gra->baza->moj_nick].portfel < czynsz)
							{
								int decyzja = gra->interfejs->CreateMessageWindow("Nie stac cie na zaplacenie czynszu!\nPoddaj sie lub zastaw swoje nieruchomosci.", przyciski);
								{
									if (decyzja == 0)
									{
										//uzytkownik sie poddal
										//usuwanie gracza
										gra->baza->Usun_Gracza(gra->baza->moj_nick);

										//przygotowanie protokolu
										Packet_Usun pakiet(numer_pola, gra->baza->moj_nick);
										gra->Dane_Do_Wyslania.clear();
										gra->Dane_Do_Wyslania = pakiet.getPakiet();
										return Wysylanie;
									}
									else
									{
										gra->interfejs->CreateZastawWindow(0, &gra->baza->gracze[gra->baza->moj_nick]);
									}
								}
							}
							//gracz zastawil nieruchomosci i moze zaplacic
							funkcje.zaplata_czynszu(czynsz, &gra->baza->gracze[gra->baza->moj_nick]);

							//przygotowanie pakietu
							Packet_Czynsz_Zastaw pakiet(numer_pola, gra->baza->moj_nick, czynsz, karta->wlasciciel->nick, gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci);
							gra->Dane_Do_Wyslania.clear();
							gra->Dane_Do_Wyslania = pakiet.getPakiet();
							return Wysylanie;
						}
						
					}
					else  //karta nie ma wlasciciela
					{
						if (gra->baza->gracze[gra->baza->moj_nick].portfel < karta->cena)
						{
							//uzytkownika nie stac na zakup
							//wyswietlenie stosownej informacji
							std::vector<button*> przyciski;
							button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
							przyciski.push_back(&ok);

							gra->interfejs->CreateMessageWindow("Nie stac cie na zakup tej nieruchomosci.", przyciski);

							//przygotowanie protokolu
							Packet_Brak_Zakupu pakiet(numer_pola);
							gra->Dane_Do_Wyslania.clear();
							gra->Dane_Do_Wyslania = pakiet.getPakiet();
							
							return Wysylanie;

						}
						else
						{
							//gracza stac na zakup
							//wyswietlenie propozycji zakupu
							std::vector<button*> przyciski;
							button odrzuc({ 100,100 }, { 0,0 }, "\grafiki/button_odrzuc.jpg", "\grafiki/button_odrzuc2.jpg");
							przyciski.push_back(&odrzuc);

							button kup({ 100,100 }, { 0,0 }, "\grafiki/button_kup.jpg", "\grafiki/button_kup2.jpg");
							przyciski.push_back(&kup);

							
							int decyzja = gra->interfejs->CreateMessageWindow("", przyciski, karta);
							if (decyzja == 0)
							{
								//uzytkownik nie chce kupic ulicy
								//przygotowanie protokolu
								Packet_Brak_Zakupu pakiet(numer_pola);
								gra->Dane_Do_Wyslania.clear();
								gra->Dane_Do_Wyslania = pakiet.getPakiet();
							}
							else  
							{
								//gracz chce kupic ulice
								funkcje.kup(&gra->baza->gracze[gra->baza->moj_nick]);

								//przygotowanie protokolu
								Packet_Kupiono pakiet(numer_pola, gra->baza->moj_nick, karta->nazwa);
								gra->Dane_Do_Wyslania.clear();
								gra->Dane_Do_Wyslania = pakiet.getPakiet();
							}
						}
					}
				}
				else if (dynamic_cast<Szansa_Kasa_Spoleczna*>(gra->baza->pola[numer_pola].karta))
				{

				}
			}
			else
			{
				//nie ma karty przypisanej temu polu
			}
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