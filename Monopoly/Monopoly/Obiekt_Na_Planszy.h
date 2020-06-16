#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>
#include"Resolution.h"

class Obiekt_Na_Planszy :
	public sf::Sprite
{
public:
	 Obiekt_Na_Planszy(sf::Texture * tekstura);
	 Obiekt_Na_Planszy()
	 {

	 }
};

class Domek :
	public Obiekt_Na_Planszy
{
public:
	Domek(sf::Texture* tekstura) : Obiekt_Na_Planszy(tekstura)
	{

	}

};


class Hotel :
	public Obiekt_Na_Planszy
{
public:
	Hotel(sf::Texture* tekstura) : Obiekt_Na_Planszy(tekstura)
	{

	}

};

class Pionek :
	public Obiekt_Na_Planszy
{
	sf::Texture tekstura;
public:
	int nr_pionka;
	Pionek(std::string file, int nr)
	{
		tekstura.loadFromFile(file);
		nr_pionka = nr;
		this->setTexture(tekstura);
	}
};