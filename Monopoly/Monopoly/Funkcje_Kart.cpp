#include "Funkcje_Kart.h"

Funkcje_Kart::Funkcje_Kart(Pole* pole)
{
	karta = pole->karta;
	this->pole = pole;
}

int Funkcje_Kart_Ulica::Czynsz()
{
	return karta->czynsze[pole->domy];
}

void Funkcje_Kart_Ulica::zaplata_czynszu(int kwota, Uzytkownik* platnik)
{
	platnik->portfel = platnik->portfel - kwota;
	karta->wlasciciel->portfel = karta->wlasciciel->portfel + kwota;
}

void Funkcje_Kart_Ulica::kup(Uzytkownik* nabywca)
{
	nabywca->portfel = nabywca->portfel - karta->cena;
	nabywca->karty_nieruchomosci.push_back(karta->nazwa);
	karta->wlasciciel = nabywca;
}

int Funkcje_Kart_Dworzec::Czynsz()
{
	int ile_dworcow = 0;
	
	if (karta->wlasciciel->CzyMaKarte("Dworzec Gdanski"))
		ile_dworcow++;
	if (karta->wlasciciel->CzyMaKarte("Dworzec Wschodni"))
		ile_dworcow++;
	if (karta->wlasciciel->CzyMaKarte("Dworzec Zachodni"))
		ile_dworcow++;
	if (karta->wlasciciel->CzyMaKarte("Dworzec Centralny"))
		ile_dworcow++;

	return ile_dworcow * 25;

}

int Funkcje_Kart_UP::Czynsz(int rzut)
{
	int ile_UP = 0;

	if (karta->wlasciciel->CzyMaKarte("Elektrownia"))
		ile_UP++;
	if (karta->wlasciciel->CzyMaKarte("Wodociagi"))
		ile_UP++;

	if (ile_UP == 1)
	{
		return 4 * rzut;
	}
	else
	{
		return 10 * rzut;
	}
}

int Funkcje_Kart_Kasa_Szansa::losujKASA()
{
	std::default_random_engine silnik;
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int>liniowy(16, 31);

	int los = liniowy(silnik);

	return los;
}

int Funkcje_Kart_Kasa_Szansa::losujSZANSA()
{
	std::default_random_engine silnik;
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int>liniowy(0, 15);

	int los = liniowy(silnik);

	return los;
}


void Funkcje_Kart_Kasa_Szansa::setKarta(Szansa_Kasa_Spoleczna* k)
{
	karta = k;
}




