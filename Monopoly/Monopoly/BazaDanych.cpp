#include "BazaDanych.h"

BazaDanych::BazaDanych()
{

	DomekTekstura.loadFromFile("\grafiki/dom.png");
	HotelTekstura.loadFromFile("\grafiki/hotel.png");

	Tworz_Ulice();
	Tworz_Szansa_Kasa_Spoleczna();
	Tworz_Dworce();
	Tworz_Obiekt_UP();
	Tworz_Pola();
	Sortuj_Pola();
	Przypisz_Wirtualne_Karty();
	Tworz_Pionki();
	Tworz_Czcionke();
	Przypisz_Kolory_Ulicom();
}

BazaDanych::~BazaDanych()
{
	Usun_Nieruchomosci();
	Usun_Szansa_Kasa_Spoleczna();
	Usun_Pionki();
	for (Pole* p : this->pola)
	{
		delete p;
	}
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
				u->Duza_Karta.setTexture(&u->tekstura);

				plik_ulice_dworce_uzyt >> linia;                      //nazwa pliku z tekstur¹ - miniatur¹
				if (!u->tekstura_min.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}
				u->Miniatura.setTexture(&u->tekstura_min);
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
				s->Duza_Karta.setTexture(&s->tekstura);
			}
			else
			{
				s->nazwa = "kasa_spoleczna";
				plik_szansa_kasa >> linia;
				if (!s->tekstura.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "nie mozna zaladowac grafiki - kasa_spoleczna";
				}
				s->Duza_Karta.setTexture(&s->tekstura);
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
				d->Duza_Karta.setTexture(&d->tekstura);

				plik_ulice_dworce_uzyt >> linia;                      //nazwa pliku z tekstur¹ - miniatur¹
				if (!d->tekstura_min.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}
				d->Miniatura.setTexture(&d->tekstura_min);
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
				ob->Duza_Karta.setTexture(&ob->tekstura);

				plik_ulice_dworce_uzyt >> linia;                      //nazwa pliku z tekstur¹ - miniatur¹
				if (!ob->tekstura_min.loadFromFile("\grafiki/" + linia))
				{
					std::cerr << "blad ladowania danych - " << linia;
				}
				ob->Miniatura.setTexture(&ob->tekstura_min);
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
				Pole*p = new Pole;
					//this->DomekTekstura,this->HotelTekstura);
				getline(plik_pola, p->nazwa);

				for (int j = 0; j < 4; j++)
				{
					plik_pola >> linia;
					plik_pola >> linia2;
					p->pozycja.push_back(sf::Vector2f(res.x(stof(linia.c_str())), res.y(stof(linia2.c_str()))));
				}

				if (i > 10 && i < 39)
				{
					p->karta = this->karty_nieruchomosci[p->nazwa];
				}
				if (i == 39)
				{
					for (int j = 0; j < 4; j++)
					{
						plik_pola >> linia;
						plik_pola >> linia2;
						p->pozycja.push_back(sf::Vector2f(res.x(stof(linia.c_str())), res.y(stof(linia2.c_str()))));
					}
				}

				p->StworzDomki(&this->DomekTekstura, &this->HotelTekstura);

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
void BazaDanych::Przypisz_Wirtualne_Karty()
{
	this->pola[4]->karta = this->karty_szansa_kasa[33];
	this->pola[38]->karta = this->karty_szansa_kasa[32];
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
	sf::Vector2f scale = res.scale();
	Pionek* p = new Pionek("\grafiki/pionek1.png", 0);
	p->setScale(scale.x, scale.y);
	this->pionki.push_back(p);
	p = new Pionek("\grafiki/pionek2.png", 1);
	p->setScale(scale.x, scale.y);
	this->pionki.push_back(p);
	p = new Pionek("\grafiki/pionek3.png", 2);
	p->setScale(scale.x, scale.y);
	this->pionki.push_back(p);
	p = new Pionek("\grafiki/pionek4.png", 3);
	p->setScale(scale.x, scale.y);
	this->pionki.push_back(p);
}
void BazaDanych::Usun_Pionki()
{
	for (auto i : pionki)
	{
		delete i;
	}
}
void BazaDanych::unikalne_nicki(std::string& name)
{
	static int liczba_takich_samych = 0;
	for (std::map<std::string,Uzytkownik>::iterator it = this->gracze.begin() ; it != this->gracze.end() ; it++)
	{
		if (it->second.nick == name)
		{
			liczba_takich_samych++;
			name = name + std::to_string(liczba_takich_samych);
		}
	}
}
void BazaDanych::Tworz_Czcionke()
{
	if (!czcionka.loadFromFile("BRLNSR.TTF"))
	{
		std::cerr << "nie zaladowno czcionki\n";
	}
}
void BazaDanych::Przypisz_Kolory_Ulicom()
{
	std::map<std::string, Karta*>::iterator it = this->karty_nieruchomosci.begin();

	for (it; it != this->karty_nieruchomosci.end(); it++)
	{
		if (it->first == "ulica Konopacka" || it->first == "ulica Stalowa")
			it->second->kolor = Brazowe;
		else if (it->first == "ulica Radzyminska" || it->first == "ulica Targowa" || it->first == "ulica Jagiellonska")
			it->second->kolor = Niebieskie;
		else if (it->first == "ulica Grochowska" || it->first == "ulica Plowiecka" || it->first == "ulica Marsa")
			it->second->kolor = Rozowe;
		else if (it->first == "ulica Gorczewska" || it->first == "ulica Wolska" || it->first == "ulica Obozowa")
			it->second->kolor = Pomaranczowe;
		else if (it->first == "ulica Slowackiego" || it->first == "ulica Mickiewicza" || it->first == "plac Wilsona")
			it->second->kolor = Czerwone;
		else if (it->first == "ulica Swietokrzyska" || it->first == "Krakowskie Przedmiescie" || it->first == "Nowy Swiat")
			it->second->kolor = Zolte;
		else if (it->first == "ulica Marszalkowska" || it->first == "Plac Trzech Krzyzy" || it->first == "Aleje Jerozolimskie")
			it->second->kolor = Zielone;
		else if (it->first == "ulica Belwederska" || it->first == "Aleje Ujazdowskie")
			it->second->kolor = Granatowe;
	}
}



int BazaDanych::NumerPola(std::string NazwaPola)
{
	for (int i = 0; i < this->pola.size() ;i++)
	{
		if (pola[i]->nazwa == NazwaPola)
			return i;
	}
	return 100;		//niech zwroci 100 w razie bledu 
}