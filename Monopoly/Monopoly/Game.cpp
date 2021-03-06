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
	if (!gra->interfejs->IsOpen())
		return StanKoncowy;
	if (gra->opcjegry.zakup_domku)
	{
		//jakas funkcja

		gra->opcjegry.zakup_domku = false;
	}
	if (gra->opcjegry.zakup_hotelu)
	{
		//jakas funkcja
				//jakas funkcja

		gra->opcjegry.zakup_hotelu = false;
	}
	if (gra->opcjegry.zastaw)
	{
		//jakas funkcja
				//jakas funkcja
		
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
	return RuszaSie;
}
state_t DoStartGrySerwer(Game* gra)
{
	//losujemy gracza ktory zaczyna
	std::default_random_engine silnik;
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> liniowy(0, gra->baza->ilosc_graczy - 1); // <----  musi byc - 1 bo w bazie jest ilosc a tablica jest indeksowana od 0 

	int los = liniowy(silnik);

	sf::Packet nick_rozpoczynajacy;
	std::string nick_rozpoczynajacy_s = gra->baza->nicki[los];				// <----- tu sie program wysypywal bo zwraca� czasem 2  
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
	if (!gra->interfejs->IsOpen())
		return StanKoncowy;
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
			//rzucamy kostk�
			int rzut = gra->interfejs->kostka->Rzuc();

			//aktualizujemy numer pola w uzytkowniku
			int numer_pola = gra->baza->gracze[gra->baza->moj_nick].numer_pola;
			int numer_gracza = gra->baza->gracze[gra->baza->moj_nick].pionek->nr_pionka;
			numer_pola += rzut;
			if (numer_pola > 39)
			{
				gra->baza->gracze[gra->baza->moj_nick].portfel += 200;
				numer_pola -= 40;
			}
			gra->baza->gracze[gra->baza->moj_nick].numer_pola = numer_pola;
			
			//zmieniamy pozycj� pionka
			gra->baza->gracze[gra->baza->moj_nick].pionek->setPosition({ gra->baza->pola[numer_pola]->pozycja[numer_gracza].x , gra->baza->pola[numer_pola]->pozycja[numer_gracza].y });
			
			//wykonujemy funkcj� karty przypisanej do tego pola
			Karta* karta = gra->baza->pola[numer_pola]->karta;
		
			if (karta == nullptr)
			{
				if (numer_pola == 10 || numer_pola == 20 || numer_pola == 30)
				{
					//TODO co wtedy
					Packet_Brak_Zakupu pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel);
					gra->Dane_Do_Wyslania.clear();
					gra->Dane_Do_Wyslania = pakiet.getPakiet();
					return Wysylanie;
				}
				else
				{
					//szansza lub kasa spoleczna
					if (gra->baza->pola[numer_pola]->nazwa == "Kasa Spoleczna")
					{
						//karta to "kasa spo�eczna"
						Funkcje_Kart_Kasa_Szansa funkcje(gra->baza->pola[numer_pola]);
						int los = funkcje.losujKASA();
						funkcje.setKarta(gra->baza->karty_szansa_kasa[los]);

						std::vector<button*> przyciski;
						button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
						przyciski.push_back(&ok);

						gra->interfejs->CreateMessageWindow("", przyciski, karta);
						//TODO napisac funkcj� kart kasa/szansa (grupy funkcji)

						Packet_Brak_Zakupu pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel);
						gra->Dane_Do_Wyslania.clear();
						gra->Dane_Do_Wyslania = pakiet.getPakiet();
						return Wysylanie;

					}
					else
					{
						//to jest karta "Szansa"
						Funkcje_Kart_Kasa_Szansa funkcje(gra->baza->pola[numer_pola]);
						int los = funkcje.losujSZANSA();
						funkcje.setKarta(gra->baza->karty_szansa_kasa[los]);

						std::vector<button*> przyciski;
						button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
						przyciski.push_back(&ok);

						gra->interfejs->CreateMessageWindow("", przyciski, karta);
						//TODO napisac funkcj� kart kasa/szansa (grupy funkcji)

						Packet_Brak_Zakupu pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel);
						gra->Dane_Do_Wyslania.clear();
						gra->Dane_Do_Wyslania = pakiet.getPakiet();
						return Wysylanie;

					}
				}
			}

			if (karta)
			{
				if (dynamic_cast<Ulica*>(karta) || dynamic_cast<Dworzec_Uzyt_Pub*>(karta))
				{
					int czynsz;
					if (karta->wlasciciel)
					{
						if (dynamic_cast<Ulica*>(karta))
						{
							//jest to ulica i jest ju� kupiona
							Funkcje_Kart_Ulica funkcje(gra->baza->pola[numer_pola]);
							czynsz = funkcje.Czynsz();
						}
						else if (karta->nazwa != "Elektrownia" && karta->nazwa != "Wodociagi")
						{
							//jest to dworzec i jest juz kupiony
							Funkcje_Kart_Dworzec funkcje(gra->baza->pola[numer_pola]);
							czynsz = funkcje.Czynsz();
						}
						else
						{
							//jest to elektrownia lub wodociagi i jest ju� kupione
							Funkcje_Kart_UP funkcje(gra->baza->pola[numer_pola]);
							czynsz = funkcje.Czynsz(rzut);
						}
						if (gra->baza->gracze[gra->baza->moj_nick].portfel >= czynsz)
						{
							//gracza stac na op�acenie czynszu
							//wyswietlanie okna z komunikatem
							std::vector<button*> przyciski;
							button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
							przyciski.push_back(&ok);
							gra->interfejs->CreateMessageWindow("Musisz zaplacic graczowi: " + karta->wlasciciel->nick + " " + std::to_string(czynsz), przyciski);

							//akt zaplaty
							if (gra->baza->isServer)
							{
								Funkcje_Kart_Ulica funkcje(gra->baza->pola[numer_pola]);
								funkcje.zaplata_czynszu(czynsz, &gra->baza->gracze[gra->baza->moj_nick]);
							}

							
							//przygotowanie protoko�u
							Packet_Czynsz_Zap pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel, gra->baza->moj_nick, karta->wlasciciel->nick, czynsz);
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

							//dop�ki gracza nie sta� lub nie podda sie zastawia ulice
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
							Funkcje_Kart_Ulica funkcje(gra->baza->pola[numer_pola]);
							funkcje.zaplata_czynszu(czynsz, &gra->baza->gracze[gra->baza->moj_nick]);

							//przygotowanie pakietu
							Packet_Czynsz_Zastaw pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel, gra->baza->moj_nick, czynsz, karta->wlasciciel->nick, gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci);
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
							Packet_Brak_Zakupu pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel);
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
								Packet_Brak_Zakupu pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel);
								gra->Dane_Do_Wyslania.clear();
								gra->Dane_Do_Wyslania = pakiet.getPakiet();
								return Wysylanie;
							}
							else  
							{
								//gracz chce kupic ulice
								if (gra->baza->isServer)
								{
									Funkcje_Kart_Ulica funkcje(gra->baza->pola[numer_pola]);
									funkcje.kup(&gra->baza->gracze[gra->baza->moj_nick]);
								}

								//przygotowanie protokolu
								Packet_Kupiono pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel, gra->baza->moj_nick, karta->nazwa);
								gra->Dane_Do_Wyslania.clear();
								gra->Dane_Do_Wyslania = pakiet.getPakiet();
								return Wysylanie;
							}
						}
					}
				}
				else
				{
					//domiar podatkowy lub podatek dochodowy
					Packet_Brak_Zakupu pakiet(numer_pola, gra->baza->gracze[gra->baza->moj_nick].portfel);
					gra->Dane_Do_Wyslania.clear();
					gra->Dane_Do_Wyslania = pakiet.getPakiet();
					return Wysylanie;
				}
				
			}
		}
	}
	
		if (gra->opcjegry.zakup_domku == 1)
		{
			std::string ulica = gra->interfejs->CreateDomWindow(false, &gra->baza->gracze[gra->baza->moj_nick]);
			if (ulica != "")
			{
				Packet_Pierwszy pakiet(gra->baza->gracze[gra->baza->moj_nick].portfel, gra->baza->NumerPola(ulica), gra->baza->pola[gra->baza->NumerPola(ulica)]->domy, gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci);
			}
		}
		if (gra->opcjegry.zakup_hotelu == 1)
		{
			std::string ulica = gra->interfejs->CreateDomWindow(false, &gra->baza->gracze[gra->baza->moj_nick]);

			gra->interfejs->CreateDomWindow(true, &gra->baza->gracze[gra->baza->moj_nick]);
			if (ulica != "")
			{
				Packet_Pierwszy pakiet(gra->baza->gracze[gra->baza->moj_nick].portfel, gra->baza->NumerPola(ulica), gra->baza->pola[gra->baza->NumerPola(ulica)]->domy, gra->baza->gracze[gra->baza->moj_nick].karty_nieruchomosci);
			}
		}
		if (gra->opcjegry.zastaw == 1)
		{
			Uzytkownik* gracz = &gra->baza->gracze[gra->baza->moj_nick];
			gra->interfejs->CreateZastawWindow(0, gracz);


		}
	

	
	return ExecuteButtons;
}
state_t DoCzeka(Game* gra)
{
	if (!gra->interfejs->IsOpen())
		return StanKoncowy;
	gra->czy_rzucone_kostki = 0;
	std::string typ;
	gra->Dane_Odebrane.clear();
	if (gra->baza->isServer)
	{
		if (gra->internet->RecieveAll(gra->Dane_Odebrane) == -1)
			return Czeka;
		else
		{
			gra->internet->SendAll(gra->Dane_Odebrane);
		}
	}
	else
	{
		if (!gra->internet->Recive(gra->Dane_Odebrane))
		{
			return Czeka;
		}
	}

	gra->Dane_Odebrane >> typ;

	if (typ == WIEZIENIE)
	{
		Packet_Wiezienie pakiet(gra->Dane_Odebrane);
		gra->baza->gracze[gra->baza->nick_aktywnego_gracza].wyrok = pakiet.getLiczbaKolejek();
	}
	else if (typ == CZYNSZ)
	{
		Packet_Czynsz_Zap pakiet(gra->Dane_Odebrane);
		//gra->baza->gracze[pakiet.getNickPlatnika()].portfel = pakiet.getPortfel();
		gra->baza->gracze[pakiet.getNickPlatnika()].numer_pola = pakiet.getNumerPola();
		Funkcje_Kart_Ulica funkcje(gra->baza->pola[pakiet.getNumerPola()]);
		funkcje.zaplata_czynszu(pakiet.getKwota(), &gra->baza->gracze[pakiet.getNickPlatnika()]);
		gra->baza->gracze[pakiet.getNickPlatnika()].portfel = pakiet.getPortfel();

		sf::Vector2f pozycja_pionka = gra->baza->pola[pakiet.getNumerPola()]->pozycja[gra->baza->gracze[pakiet.getNickPlatnika()].pionek->nr_pionka];
		gra->baza->gracze[pakiet.getNickPlatnika()].pionek->setPosition(pozycja_pionka);
	}
	else if (typ == USUN)
	{
		Packet_Usun pakiet(gra->Dane_Odebrane);
		gra->baza->Usun_Gracza(pakiet.getNick());
		std::vector<button*> przyciski;
		button ok({ 100,100 }, { 0,0 }, "\grafiki/button_ok.jpg", "\grafiki/button_ok2.jpg");
		przyciski.push_back(&ok);
		gra->interfejs->CreateMessageWindow("Gracz " + pakiet.getNick() + " przegral,\nnie byl w stanie zaplacic czynszu za: \n" + gra->baza->pola[pakiet.getNumerPola()]->nazwa, przyciski);
	}
	if (typ == CZYNSZZASTAW)
	{
		Packet_Czynsz_Zastaw pakiet(gra->Dane_Odebrane);
		gra->baza->gracze[pakiet.getNickPlatnika()].numer_pola = pakiet.getNumerPola();

		Funkcje_Kart_Ulica funkcje(gra->baza->pola[pakiet.getNumerPola()]);
		//gra->baza->gracze[pakiet.getNickPlatnika()].portfel = pakiet.getPortfel();
		funkcje.zaplata_czynszu(pakiet.getKwota(), &gra->baza->gracze[pakiet.getNickPlatnika()]);
		funkcje.zastaw(&gra->baza->gracze[pakiet.getNickPlatnika()], pakiet.getNazwyUlic(), gra->baza);


		sf::Vector2f pozycja_pionka = gra->baza->pola[pakiet.getNumerPola()]->pozycja[gra->baza->gracze[pakiet.getNickPlatnika()].pionek->nr_pionka];
		gra->baza->gracze[pakiet.getNickPlatnika()].pionek->setPosition(pozycja_pionka);
	}
	if (typ == BRAKZAKUPU)
	{
		Packet_Brak_Zakupu pakiet(gra->Dane_Odebrane);

		gra->baza->gracze[gra->baza->nick_aktywnego_gracza].numer_pola = pakiet.getNumerPola();
		//gra->baza->gracze[gra->baza->nick_aktywnego_gracza].portfel = pakiet.getPortfel();

		sf::Vector2f pozycja_pionka = gra->baza->pola[pakiet.getNumerPola()]->pozycja[gra->baza->gracze[gra->baza->nick_aktywnego_gracza].pionek->nr_pionka];
		gra->baza->gracze[gra->baza->nick_aktywnego_gracza].pionek->setPosition(pozycja_pionka);
	}
	if (typ == KUPIONO)
	{
		Packet_Kupiono pakiet(gra->Dane_Odebrane);

		gra->baza->gracze[pakiet.getNickNabywcy()].numer_pola = pakiet.getNumerPola();
		//gra->baza->gracze[pakiet.getNickNabywcy()].portfel = pakiet.getPortfel();


		Funkcje_Kart_Ulica funkcje(gra->baza->pola[pakiet.getNumerPola()]);
		funkcje.kup(&gra->baza->gracze[pakiet.getNickNabywcy()]);


		sf::Vector2f pozycja_pionka = gra->baza->pola[pakiet.getNumerPola()]->pozycja[gra->baza->gracze[gra->baza->nick_aktywnego_gracza].pionek->nr_pionka];
		gra->baza->gracze[gra->baza->nick_aktywnego_gracza].pionek->setPosition(pozycja_pionka);
	}
	if (typ == PIERWSZY)
	{
		Packet_Pierwszy pakiet(gra->Dane_Odebrane);

		gra->baza->gracze[gra->baza->nick_aktywnego_gracza].portfel = pakiet.getPortfel();
		
		Funkcje_Kart_Ulica funkcje(gra->baza->pola[pakiet.getNumerPolaDomy()]);
		funkcje.zastaw(&gra->baza->gracze[gra->baza->nick_aktywnego_gracza], pakiet.getNazwyUlic(), gra->baza);
		funkcje.dodaj_dom(pakiet.getLiczbaDomow());
		gra->baza->gracze[gra->baza->nick_aktywnego_gracza].portfel = pakiet.getPortfel();


		return Czeka;
	}
	if(typ == NASTEPNY)                //serwer nigdy nie dostanie tego pakietu
	{
		Packet_Nastepny pakiet(gra->Dane_Odebrane);
		gra->baza->nick_aktywnego_gracza = pakiet.GetNastepny();

		if (pakiet.GetNastepny() == gra->baza->moj_nick)
			return RuszaSie;
		else
		{
			return Czeka;
		}
	}
	if (gra->baza->isServer)
	{
		return DelegujDoRuchu;
	}
	else
	{
		return Czeka;
	}
}
state_t DoWysylanie(Game* gra)
{
	if (!gra->interfejs->IsOpen())
		return StanKoncowy;
	sf::Packet kopia;
	kopia = gra->Dane_Do_Wyslania;
	std::string typ;
	kopia >> typ;

	if (typ == PIERWSZY)
	{
		if (gra->baza->isServer)     //server
		{
			gra->internet->SendAll(gra->Dane_Do_Wyslania);
			return RuszaSie;
		}
		else                        //klient
		{
			gra->internet->Send(gra->Dane_Do_Wyslania);
			return RuszaSie;
		}
	}
	else
	{
		if (gra->baza->isServer)
		{
			gra->internet->SendAll(gra->Dane_Do_Wyslania);
			return DelegujDoRuchu;
		}
		else
		{
			gra->internet->Send(gra->Dane_Do_Wyslania);
			return Czeka;
		}
	}
	
	return Czeka;
}
state_t DoDelegujDoRuchu(Game* gra)
{
	if (!gra->interfejs->IsOpen())
		return StanKoncowy;
	std::string nick_nastepnego;

	std::string nick_aktywnego = gra->baza->nick_aktywnego_gracza;
	for (int i = 0; i < gra->baza->nicki.size(); i++)
	{
		if (gra->baza->nicki[i] == nick_aktywnego)
		{
			if (i == gra->baza->nicki.size() - 1)
			{
				gra->baza->nick_aktywnego_gracza = gra->baza->nicki[0];
				nick_nastepnego = gra->baza->nicki[0];
			}
			else
			{
				i++;
				gra->baza->nick_aktywnego_gracza = gra->baza->nicki[i];
				nick_nastepnego = gra->baza->nicki[i];
			}
			
		}
	}


	Packet_Nastepny pakiet(nick_nastepnego);
	gra->Dane_Do_Wyslania.clear();
	gra->Dane_Do_Wyslania = pakiet.getPakiet();
	gra->internet->SendAll(gra->Dane_Do_Wyslania);

	if (nick_nastepnego == gra->baza->moj_nick)
	{
		return RuszaSie;
	}
	else
	{
		return Czeka;
	}
}


state_t DoStanKoncowy(Game* gra)
{
	gra->EndOfGame = 1;
	std::cout << "stan koncowy\n";
	if (gra->interfejs->IsOpen())
	{
	
		return ExecuteButtons;
	}
	return StanKoncowy;

}