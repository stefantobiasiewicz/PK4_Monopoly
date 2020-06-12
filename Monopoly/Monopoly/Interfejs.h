#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"

#include "BazaDanych.h"
#include "Resolution.h"
#include "Button.h"
#include "elementy_graficzne.h"

class Interfejs
{
	sf::RenderWindow* MainWindow;
	Plansza* PoleGry;
	BazaDanych* Dane;

	std::vector<Klikalny*> KlikObject;

public:


	Interfejs(BazaDanych* res);
	~Interfejs();

	void StartWindow();

	// funkcja tworzaca/usuwajaca nowe okno 
	void CreateMainWindow();
	void DeleteMainWindow();


	// funkcja zwraca czy okno jest otwarte
	bool IsOpen();


	// zastapienie petli glownej SFML-owskiej
	void MainFunction();


	// funkjca obslugujaca eventy
	void EventFunction();
	/*	mozna zrobic klase wirtualna do obslugi eventow
		kazda klasa ktora obsluguje te eventy ma funkcje event ktora zostaje nadpisana
		nasz interfejs ma wektor wskaznikow na obiekty klasy eventowej * w ktorym znajduja sie wszystkie pobiekty
		ktore maja byæ obsuiwane
	*/

	// funkcja rysjujaca okno
	void DrawFunction();


	// funkcja tworzaca/usuwajaca plansze
	void CreatePlansza(std::string = "\grafiki / planszaG.jpg");
	void DeletePlansza();

	// funkcja tworzaca przycisk
	void CreateButtons();

	// funkcja tworzaca textbaty
	void CreateTextbar();


	// funkcja tworzaca nowe okno z informacja
	void CreateMessageWindow(std::string tekst);

};


