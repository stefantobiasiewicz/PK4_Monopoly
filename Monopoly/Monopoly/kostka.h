#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "Resolution.h"
  
//klasa implementuj�ca rzut dwiema kostkami (w rzeczywistej grze s� dwie kostki)

class Kostka
{
	Resolution res;

public:

	sf::Text wynik_rzutu;

	Kostka(sf::Font& czcionka);
	~Kostka() {}
	int Rzuc();
};