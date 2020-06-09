#pragma once
#include "SFML/Graphics.hpp"
#include "Uzytkownik.h"
#include "Karta.h"
#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"
#include "Pole.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <vld.h>
#include <vld_def.h>
#include <utility>



class BazaDanych
{
public:
	// klasa zawierajaca wszystkie obiekty do u�ytku przez program ( Zasoby ) wymagaj�ce pewnej implementacji z racji zasad gry 

	// tu bedzie tablica wska�nik�w na funkcje ( dla kart ) algorytmy dzia�ania kart
	// wektor / tablica p�l ( obiekt�w )

	std::map<std::string, Karta*>karty_nieruchomosci;   //tablica asocjacyjna kart, kluczem nazwa karty
	std::vector<Pole>pola;                //tablica p�l na planszy
	std::vector<Karta*>karty_szansa_kasa;  //tablica kart 'szansa' i 'kasa spoleczna' 
	std::ifstream plik_ulice_dworce_uzyt; //strumien do pliku z danymi nieruchomosci
	std::ifstream plik_szansa_kasa;       //strumien do pliku z danymi o kartach 'szansa' i 'kasa spoleczna'
	std::ifstream plik_pola;              //strumien do pliku z danymi o polach na planszy
	std::map<std::string, Uzytkownik>gracze; //tablica graczy, indeksowana nickiem

public:
	BazaDanych();
	~BazaDanych();
	void Tworz_Ulice();
	void Usun_Nieruchomosci();
	void Tworz_Szansa_Kasa_Spoleczna();
	void Usun_Szansa_Kasa_Spoleczna();
	void Tworz_Dworce();
	void Tworz_Obiekt_UP();
	void Tworz_Pola();
	void Sortuj_Pola();
};

