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
	string nazwa;                           //nazwa taka sama jak nazwa odpowiadaj�cej karty_nieruchomosci
	std::vector<sf::Vector2f>pozycja;   //wsp�rz�dne gdzie nale�y narysowa� dany pionek w ka�dym z czterech segment�w pola
	std::vector<Pionek>gracze;           //wektor pionk�w stoj�cych na tym polu
	Karta* karta;                      //karta przypisana temu polu, null jesli nie ma karty do tego pola
	
	std::vector<Domek> domki;
	std::vector<Hotel> hotel;


	int domy;                      //liczba dom�w, 5 dom�w jest traktowane jak hotel

public:
	Pole();
	Pole(std::vector<sf::Vector2f>pozycja, Karta* karta);
	void StworzDomki(sf::Texture* dom, sf::Texture* hote);
	~Pole();
};

