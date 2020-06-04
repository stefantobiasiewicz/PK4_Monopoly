#pragma once
#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

class Karta : public sf::Sprite
{
public:
	Karta(const sf::Texture& tekstura, float x, float y);  //karta z automatu ma teksture i pozycje do wyswietlania na ekranie

};

class Ulica : public Karta
{
	string nazwa;
	int cena;
	int cena_dom;
	int cena_hotel;
	vector<int>czynsze;
public:
	Ulica(const sf::Texture& tekstura, float x, float y, int cena, int cena_dom, int cena_hotel, vector<int>& czynsze, string nazwa);
};

class Dworzec_Uzyt_Pub : public Karta
{
	int cena;
	vector<int>czynsze;
	string nazwa;
public:
	Dworzec_Uzyt_Pub(const sf::Texture& tekstura, float x, float y, int cena, vector<int>& czynsze, string nazwa);
};

class Szansa_Kasa_Spoleczna : public Karta
{
	string nazwa;            //szansa albo kasa_spoleczna
	void (*funkcja)(void);  //wskaŸnik na funkcjê spe³niaj¹c¹ funkcjonalnoœæ karty, na razie parametry void bo jeszcze nie wiem jakie bêd¹
public:
	Szansa_Kasa_Spoleczna(const sf::Texture& tekstura, float x, float y, string nazwa, void (*funkcja)(void));
};