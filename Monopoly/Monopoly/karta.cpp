#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Karta.h"

using namespace std;


	Karta::Karta(const sf::Texture& tekstura, float x, float y) : sf::Sprite(tekstura)   //karta z automatu ma teksture i pozycje do wyswietlania na ekranie
	{
		sf::Sprite::setPosition(x, y);
	};



	Ulica::Ulica(const sf::Texture& tekstura, float x, float y, int cena, int cena_dom, int cena_hotel, vector<int>& czynsze, string nazwa) : Karta(tekstura, x, y)
	{
		this->cena = cena;
		this->cena_dom = cena_dom;
		this->cena_hotel = cena_hotel;
		this->czynsze = czynsze;
		this->nazwa;

	};



	Dworzec_Uzyt_Pub::Dworzec_Uzyt_Pub(const sf::Texture& tekstura, float x, float y, int cena, vector<int>& czynsze, string nazwa) : Karta(tekstura, x, y)
	{
		this->cena = cena;
		this->czynsze = czynsze;
		this->nazwa = nazwa;
	};


	Szansa_Kasa_Spoleczna::Szansa_Kasa_Spoleczna(const sf::Texture& tekstura, float x, float y, string nazwa, void (*funkcja)(void)) : Karta(tekstura, x, y)
	{
		this->nazwa = nazwa;
		this->funkcja = funkcja;
	};
