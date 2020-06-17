#pragma once

#include <chrono>
#include <random>
#include "Karta.h"
#include "Pole.h"
#include "BazaDanych.h"

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
	void zastaw(Uzytkownik* gracz, std::vector<std::string>nazwy_ulic, BazaDanych * baza);
	void dodaj_dom(int liczba);

};

class Funkcje_Kart_Dworzec : public Funkcje_Kart
{
public:
	Funkcje_Kart_Dworzec(Pole* pole) : Funkcje_Kart(pole) {}
	~Funkcje_Kart_Dworzec() {}

	int Czynsz();
};

class Funkcje_Kart_UP : public Funkcje_Kart
{
public:
	Funkcje_Kart_UP(Pole* pole) : Funkcje_Kart(pole) {}
	~Funkcje_Kart_UP() {}

	int Czynsz(int rzut);
};
class Funkcje_Kart_Kasa_Szansa : public Funkcje_Kart
{
public:
	Funkcje_Kart_Kasa_Szansa(Pole* pole) : Funkcje_Kart(pole) {}
	~Funkcje_Kart_Kasa_Szansa() {}

	int losujKASA();
	int losujSZANSA();

	void setKarta(Szansa_Kasa_Spoleczna* k);
};