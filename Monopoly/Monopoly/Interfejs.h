#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"

#include "BazaDanych.h"
#include "Resolution.h"
#include "Button.h"

class Interfejs
{
	sf::RenderWindow* MainWindow;
	Plansza* PoleGry;
	BazaDanych* Dane;
public:


	Interfejs(BazaDanych* res) : Dane(res)
	{

	}
	~Interfejs()
	{
		
	}

	void StartWindow();

	// funkcja tworzaca/usuwajaca nowe okno 
	void CreateMainWindow();
	void DeleteMainWindow();

	// funkjca obslugujaca eventy
	void EventFunction();
	/*	mozna zrobic klase wirtualna do obslugi eventow
		kazda klasa ktora obsluguje te eventy ma funkcje event ktora zostaje nadpisana
		nasz interfejs ma wektor wskaznikow na obiekty klasy eventowej * w ktorym znajduja sie wszystkie pobiekty
		ktore maja byæ obsuiwane
	*/

	// funkcja rysjujaca okno
	void DrawFunction();


	// funkcja do odpalenia przez w¹tek 
	void DrawThread();

};


