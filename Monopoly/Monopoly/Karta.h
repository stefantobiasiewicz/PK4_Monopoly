#pragma once
#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Uzytkownik.h"




//#include "inc.h"

using namespace std;

class Karta : public sf::Sprite
{
public:
	string nazwa;
	void (*funkcja)(void);  //wskaŸnik na funkcjê spe³niaj¹c¹ funkcjonalnoœæ karty_nieruchomosci, na razie parametry void bo jeszcze nie wiem jakie bêd¹
	sf::Texture tekstura;
	sf::Texture tekstura_min;
	sf::RectangleShape Miniatura;
	sf::RectangleShape Duza_Karta;
	int cena;
	int cena_dom;
	vector<int>czynsze;
	Uzytkownik * wlasciciel;     //nick wlasciciela nieruchomosci, jeœli takowa nieruchomoœæ zosta³a ju¿ kupiona
	
	virtual void obsluga_ruchu(Uzytkownik &uzyt)=0;

protected:
	Karta() {}
	Karta(const sf::Texture& tekstura, float x, float y);  //karta z automatu ma teksture i pozycje do wyswietlania na ekranie

};

class Ulica : public Karta
{
public:
	Ulica() {}
	Ulica(sf::Texture& tekstura, float x, float y, int cena, int cena_dom, vector<int>& czynsze, string nazwa);
	void obsluga_ruchu(Uzytkownik& uzyt);
	bool zakupy(Uzytkownik &uzyt);

};

class Dworzec_Uzyt_Pub : public Karta
{
public:

	Dworzec_Uzyt_Pub() {}
	Dworzec_Uzyt_Pub(sf::Texture& tekstura, float x, float y, int cena, vector<int>& czynsze, string nazwa);
	void obsluga_ruchu(Uzytkownik &uzyt) {};
};

class Szansa_Kasa_Spoleczna : public Karta
{
public:

	Szansa_Kasa_Spoleczna() {}
	Szansa_Kasa_Spoleczna(sf::Texture& tekstura, float x, float y, string nazwa, void (*funkcja)(void));
	void obsluga_ruchu(Uzytkownik& uzyt) {};
};

