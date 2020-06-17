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
