#include "Karta.h"


using namespace std;


	Karta::Karta(const sf::Texture& tekstura, float x, float y) : sf::Sprite(tekstura)   //karta z automatu ma teksture i pozycje do wyswietlania na ekranie
	{
		sf::Sprite::setPosition(x, y);
	};



	Ulica::Ulica(sf::Texture& tekstura, float x, float y, int cena, int cena_dom, vector<int>& czynsze, string nazwa) : Karta(tekstura, x, y)
	{
		this->cena = cena;
		this->cena_dom = cena_dom;
		this->czynsze = czynsze;
		this->nazwa = nazwa;

	};



	Dworzec_Uzyt_Pub::Dworzec_Uzyt_Pub(sf::Texture& tekstura, float x, float y, int cena, vector<int>& czynsze, string nazwa) : Karta(tekstura, x, y)
	{
		this->cena = cena;
		this->czynsze = czynsze;
		this->nazwa = nazwa;

	};


	Szansa_Kasa_Spoleczna::Szansa_Kasa_Spoleczna(sf::Texture& tekstura, float x, float y, string nazwa, void (*funkcja)(void)) : Karta(tekstura, x, y)
	{
		this->nazwa = nazwa;
		this->funkcja = funkcja;
	};

	void Ulica::obsluga_ruchu(Uzytkownik& uzyt)
	{
		if (this->wlasciciel == nullptr && uzyt.portfel >= this->cena)
		{
			zakupy(uzyt);
		}
		else
		{
			if (this->wlasciciel != &uzyt)
			{
				//pobierz_czynsz();
			}
			else
			{
				std::cout << "Nie mozesz kupic tego obiektu!";
			}
		}
	}

	bool Ulica::zakupy(Uzytkownik& uzyt)
	{
		bool decyzja;
		std::cout << "Czy chcesz zakupic obiekt o nazwie: " << this->nazwa << "?" << std::endl;
		cin >> decyzja;
		if (decyzja)
		{
			uzyt.portfel = uzyt.portfel - this->cena;
			uzyt.karty_nieruchomosci.push_back(this->nazwa);
			this->wlasciciel = &uzyt;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
