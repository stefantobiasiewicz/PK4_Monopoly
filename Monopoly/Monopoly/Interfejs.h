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

public:
	sf::RenderWindow* MainWindow;
	Plansza * PoleGry;
	BazaDanych* resources;

	Interfejs(BazaDanych* res) : resources(res)
	{
		//MainWindow = new sf::RenderWindow(sf::VideoMode(1000, 800), "My window");
		//PoleGry = new Plansza(std::string("res/p.png"));
	}
	~Interfejs()
	{
		delete MainWindow;
		delete PoleGry;
	}

	void StartWindow();


	// funkcja do odpalenia przez w¹tek 
	void DrawThread();

};


