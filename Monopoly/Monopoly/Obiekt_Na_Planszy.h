#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>


class Obiekt_Na_Planszy :
	public sf::Sprite
{
public:
	sf::Texture tekstura;

	 Obiekt_Na_Planszy(std::string file, sf::Vector2f pos);
	 
	 std::map<std::string, std::string> file_dir;	// mapa której kluczem bêdzie string (np:domek,hotel) a w wartosæi bêdzie œcie¿ka do danej tekstury

};

class Domek :
	public Obiekt_Na_Planszy
{
public:
	Domek(sf::Vector2f pos) : Obiekt_Na_Planszy(std::string("// scierzka do pliku tekstury"), pos) {}

};


class Hotel :
	public Obiekt_Na_Planszy
{
public:
	Hotel(sf::Vector2f pos) : Obiekt_Na_Planszy(std::string("// scierzka do pliku tekstury"), pos) {}

};

class Pionek :
	public Obiekt_Na_Planszy
{
public:
	Pionek() : Obiekt_Na_Planszy(std::string("// scierzka do pliku tekstury"), sf::Vector2f(0,0) ) {}
	Pionek(sf::Vector2f pos) : Obiekt_Na_Planszy(std::string("// scierzka do pliku tekstury"), pos) {}

};