#include "BazaDanych.h"

BazaDanych::BazaDanych()
{
	Tworz_Ulice();
	Tworz_Szansa_Kasa_Spoleczna();
	Tworz_Dworce();
	Tworz_Obiekt_UP();
	Tworz_Pola();
	Sortuj_Pola();
	Tworz_Pionki();
}

BazaDanych::~BazaDanych()
{
	Usun_Nieruchomosci();
	Usun_Szansa_Kasa_Spoleczna();
}

void BazaDanych::Tworz_Ulice()
{
	string linia;
	int liczba;
	
	this->plik_ulice_dworce_uzyt.open("\dane/ulice_dworce_uzytek_pub.txt");
	if (this->plik_ulice_dworce_uzyt)
	{
		while (!plik_ulice_dworce_uzyt.eof())
		{
			
			plik_ulice_dworce_uzyt >> linia;                         //informacja o tym czy to ullica, dworzec czy obiekt UP
			if (linia == "ulica")
			{
				Ulica* u = new Ulica;
				getline(plik_ulice_dworce_uzyt, linia);            //nazwa nieruchomosci - getline, bo moze byæ wiêcej n¿ jedno s³owo
				getline(plik_ulice_dworce_uzyt, u->nazwa);
				plik_ulice_dworce_uzyt >> linia;                     //cena nieruchomoœci
				u->cena = atoi(linia.c_str());

				for (int i = 0; i < 6; i++)
				{
					plik_ulice_dworce_uzyt >> linia;                //czynsze dla kazdej liczby postawionych domów
					u->czynsze.push_back(atoi(linia.c_str()));
				}

				plik_ulice_dworce_uzyt >> linia;                    //cena domu (cena hotelu = cena domu + cena 4 domów)
				u->cena_dom = atoi(linia.c_str());

				plik_ulice_dworce_uzyt >> linia;                     //nazwa pliku z tekstur¹
				if (!u->tekstura.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}

				plik_ulice_dworce_uzyt >> linia;                      //nazwa pliku z tekstur¹ - miniatur¹
				if (!u->tekstura_min.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}
				this->karty_nieruchomosci[u->nazwa] = u;                             //dodanie nowego elementu do mapy kart
				
			}
			else
			{
				
			}
		}
		plik_ulice_dworce_uzyt.close();
	}
	else
	{
		std::cerr << "Nie udalo sie otworzyc pliku z danymi.";
	}
	
	
}
void BazaDanych::Usun_Nieruchomosci()
{
	std::map<string, Karta*>::iterator it = this->karty_nieruchomosci.begin();
	for (it; it != this->karty_nieruchomosci.end(); it++)
	{
		delete it->second;
	}
}
void BazaDanych::Tworz_Szansa_Kasa_Spoleczna()
{
	int licznik = 1;
	string linia;
	this->plik_szansa_kasa.open("\dane/szansa_kasa_spoleczna.txt");
	if (plik_szansa_kasa)
	{
		while (!plik_szansa_kasa.eof())
		{
			Szansa_Kasa_Spoleczna* s = new Szansa_Kasa_Spoleczna;
			if (licznik < 17)                                           //jest 16 kart szansa
			{
				s->nazwa = "szansa";
				plik_szansa_kasa >> linia;
				if (!s->tekstura.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "nie mozna zaladowac grafiki - szansa";
				}
			}
			else
			{
				s->nazwa = "kasa_spoleczna";
				plik_szansa_kasa >> linia;
				if (!s->tekstura.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "nie mozna zaladowac grafiki - kasa_spoleczna";
				}
			}
			licznik++;
			karty_szansa_kasa.push_back(s);
		}
		plik_szansa_kasa.close();

		Szansa_Kasa_Spoleczna* domiar = new Szansa_Kasa_Spoleczna;    //dwie "wirtualne" karty szansa/kasa_spoleczna odpowiadaj¹ce polom - zap³aæ podatek dochodowy i domiar podatkowy
		domiar->nazwa = "domiar";
		karty_szansa_kasa.push_back(domiar);

		Szansa_Kasa_Spoleczna* podatek = new Szansa_Kasa_Spoleczna;
		podatek->nazwa = "podatek";
		karty_szansa_kasa.push_back(podatek);
	}
	else
	{
		std::cerr << "Nie udalo sie otworzyc pliku.";
	}

}
void BazaDanych::Usun_Szansa_Kasa_Spoleczna()
{
	for (int i = 0; i < karty_szansa_kasa.size(); i++)
	{
		delete karty_szansa_kasa[i];
	}
}
void BazaDanych::Tworz_Dworce()
{
	this->plik_ulice_dworce_uzyt.open("\dane/ulice_dworce_uzytek_pub.txt");
	string linia;
	if (plik_ulice_dworce_uzyt)
	{
		while (!plik_ulice_dworce_uzyt.eof())
		{
			plik_ulice_dworce_uzyt >> linia;                   //informacja o tym czy to ullica, dworzec czy obiekt UP
			if (linia == "dworzec")
			{
				Dworzec_Uzyt_Pub* d = new Dworzec_Uzyt_Pub;
				getline(plik_ulice_dworce_uzyt, linia);
				getline(plik_ulice_dworce_uzyt, d->nazwa);    //nazwa nieruchomosci

				plik_ulice_dworce_uzyt >> linia;               //cena nieruchomoœci
				d->cena = atoi(linia.c_str());

				for (int i = 0; i < 4; i++)
				{
					plik_ulice_dworce_uzyt >> linia;           //czynsz (w zaleznoœci od liczby posiadanych dworcow)
					d->czynsze.push_back(atoi(linia.c_str()));
				}

				plik_ulice_dworce_uzyt >> linia;                     //nazwa pliku z tekstur¹
				if (!d->tekstura.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}

				plik_ulice_dworce_uzyt >> linia;                      //nazwa pliku z tekstur¹ - miniatur¹
				if (!d->tekstura_min.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}
				this->karty_nieruchomosci[d->nazwa] = d;
			}
			else
			{
				
			}
		}
		plik_ulice_dworce_uzyt.close();
	}
	else
	{
		std::cerr << "Nie udalo sie otworzyc pliku z danymi.";
	}
}
void BazaDanych::Tworz_Obiekt_UP()
{
	this->plik_ulice_dworce_uzyt.open("\dane/ulice_dworce_uzytek_pub.txt");
	string linia;
	if (plik_ulice_dworce_uzyt)
	{
		while (!plik_ulice_dworce_uzyt.eof())
		{
			plik_ulice_dworce_uzyt >> linia;                   //informacja o tym czy to ullica, dworzec czy obiekt UP
			if (linia == "uzyt_pub")
			{
				Dworzec_Uzyt_Pub* ob = new Dworzec_Uzyt_Pub;
				getline(plik_ulice_dworce_uzyt, linia);
				getline(plik_ulice_dworce_uzyt, ob->nazwa);    //nazwa nieruchomosci

				plik_ulice_dworce_uzyt >> linia;               //cena nieruchomoœci
				ob->cena = atoi(linia.c_str());

				plik_ulice_dworce_uzyt >> linia;                     //nazwa pliku z tekstur¹
				if (!ob->tekstura.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}

				plik_ulice_dworce_uzyt >> linia;                      //nazwa pliku z tekstur¹ - miniatur¹
				if (!ob->tekstura_min.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}
				this->karty_nieruchomosci[ob->nazwa] = ob;
			}
			else
			{

			}
		}
		plik_ulice_dworce_uzyt.close();
	}
	else
	{
		std::cerr << "Nie udalo sie otworzyc pliku z danymi.";
	}
}
void BazaDanych::Tworz_Pola()
{
	string linia;
	string linia2;
	float liczba;
	this->plik_pola.open("\dane/pola.txt");
	if (plik_pola)
	{
		while (!plik_pola.eof())
		{
			for (int i = 0; i < 40; i++)
			{
				Pole p;
				getline(plik_pola, p.nazwa);

				for (int j = 0; j < 4; j++)
				{
					plik_pola >> linia;
					plik_pola >> linia2;
					p.pozycja.push_back(sf::Vector2f(stof(linia.c_str()), stof(linia2.c_str())));
				}

				if (i > 10 && i < 39)
				{
					p.karta = this->karty_nieruchomosci[p.nazwa];
				}
				if (i == 39)
				{
					for (int j = 0; j < 4; j++)
					{
						plik_pola >> linia;
						plik_pola >> linia2;
						p.pozycja.push_back(sf::Vector2f(stof(linia.c_str()), stof(linia2.c_str())));
					}
				}

				this->pola.push_back(p);
				getline(plik_pola, linia);
				getline(plik_pola, linia);
			}
		}
		plik_pola.close();
	}
	else
	{
		std::cerr << "Nie udalo sie otworzyc pliku.";
	}

}
void BazaDanych::Sortuj_Pola()
{
	std::swap(pola[1], pola[11]);
	std::swap(pola[2], pola[11]);
	std::swap(pola[3], pola[12]);
	std::swap(pola[4], pola[11]);
	std::swap(pola[5], pola[13]);
	std::swap(pola[6], pola[14]);
	std::swap(pola[7], pola[12]);
	std::swap(pola[8], pola[15]);
	std::swap(pola[9], pola[16]);
	std::swap(pola[10], pola[39]);
	std::swap(pola[11], pola[17]);
	std::swap(pola[12], pola[18]);
	std::swap(pola[13], pola[19]);
	std::swap(pola[14], pola[20]);
	std::swap(pola[15], pola[21]);
	std::swap(pola[16], pola[22]);
	std::swap(pola[18], pola[23]);
	std::swap(pola[19], pola[24]);
	std::swap(pola[20], pola[24]);
	std::swap(pola[21], pola[25]);
	std::swap(pola[22], pola[24]);
	std::swap(pola[23], pola[26]);
	std::swap(pola[24], pola[27]);
	std::swap(pola[25], pola[28]);
	std::swap(pola[26], pola[29]);
	std::swap(pola[27], pola[30]);
	std::swap(pola[28], pola[31]);
	std::swap(pola[29], pola[32]);
	std::swap(pola[30], pola[32]);
	std::swap(pola[31], pola[33]);
	std::swap(pola[32], pola[34]);
	std::swap(pola[34], pola[35]);
	std::swap(pola[35], pola[36]);
	std::swap(pola[38], pola[39]);
}
void BazaDanych::Stworz_Mnie(std::string nick, sf::IpAddress ip, bool isServer, Kolor_Planszy kolor)
{
	Uzytkownik ja(nick);
	this->IP = ip;
	this->kolor = kolor;
	this->isServer = isServer;
	gracze[nick] = ja;
}
void BazaDanych::Tworz_Pionki()
{
	Pionek p1("\grafiki/pionek1.png", 0);
	Pionek p2("\grafiki/pionek2.png", 1);
	Pionek p3("\grafiki/pionek3.png", 2);
	Pionek p4("\grafiki/pionek4.png", 3);
	this->pionki.push_back(p1);
	this->pionki.push_back(p2);
	this->pionki.push_back(p3);
	this->pionki.push_back(p4);
}