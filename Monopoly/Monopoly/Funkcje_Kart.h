#pragma once
#include "Karta.h"
#include "Pole.h"

class Funkcje_Kart
{
protected:
	Karta* karta;
	Pole* pole;
	Funkcje_Kart(Pole*pole);
	~Funkcje_Kart() {}
};

class Funkcje_Kart_Ulica : public Funkcje_Kart
{
public:
	Funkcje_Kart_Ulica(Pole* pole) : Funkcje_Kart(pole) {}
	~Funkcje_Kart_Ulica() {}

	int Czynsz();
	void zaplata_czynszu(int kwota, Uzytkownik* platnik);
	void kup(Uzytkownik* nabywca);

};