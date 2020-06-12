#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"

#include "BazaDanych.h"
#include "Resolution.h"
#include "elementy_graficzne.h"

class Interfejs
{
	sf::RenderWindow* MainWindow;
	Plansza* PoleGry;
	BazaDanych* Dane;

	std::vector<Klikalny*> KlikObject;

	//zmienne potrzebne do skalowania
	float factorX = 1; // zmienne do podzielenia x i y myszki 
	float factorY = 1;

	float Szer = sf::VideoMode::getDesktopMode().width;
	float Wys = sf::VideoMode::getDesktopMode().height;

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
	// funkcja "skalujaca myszke" potrzebna do poprawnego dzialania programu po zmianie rozmiaru okna
	void EventScaleMouse(sf::Event& even);

	// funkcja rysjujaca okno
	void DrawFunction();


	// funkcja tworzaca/usuwajaca plansze
	void CreatePlansza(std::string = "\grafiki / planszaG.jpg");
	void DeletePlansza();

	// funkcja tworzaca/usuwajaca przyciski / lub texbary
	void CreateButtons();
	void DeleteButtons();

	//funkcja obslugujaca przyciski / elementy przyciskalne
	void ExecuteButtons(sf::Event &event);

	//funkcja rysujaca wszyskie klawisze
	void DrawButtons(sf::RenderWindow& window);

	// funkcja tworzaca nowe okno z informacja
	void CreateMessageWindow(std::string tekst);



};


