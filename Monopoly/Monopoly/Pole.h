#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Obiekt_Na_Planszy.h"

//#include "inc.h"
#include "Karta.h"

class Pole
{
public:
	string nazwa;                           //nazwa taka sama jak nazwa odpowiadaj¹cej karty_nieruchomosci
	std::vector<sf::Vector2f>pozycja;   //wspó³rzêdne gdzie nale¿y narysowaæ dany pionek w ka¿dym z czterech segmentów pola
	std::vector<Pionek>gracze;           //wektor pionków stoj¹cych na tym polu
	Karta* karta;                      //karta przypisana temu polu, null jesli nie ma karty do tego pola
	
	std::vector<Domek> domki;
	std::vector<Hotel> hotel;


	int domy;                      //liczba domów, 5 domów jest traktowane jak hotel

public:
	Pole();
	Pole(std::vector<sf::Vector2f>pozycja, Karta* karta);
	void StworzDomki(sf::Texture* dom, sf::Texture* hote);
	~Pole();
};

