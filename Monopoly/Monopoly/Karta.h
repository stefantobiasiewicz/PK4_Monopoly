#pragma once
#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Uzytkownik.h"


typedef enum { Brazowe = 0, Niebieskie, Rozowe, Pomaranczowe, Czerwone, Zolte, Zielone, Granatowe, BezKoloru } Kolor_ulicy;


//#include "inc.h"

using namespace std;

class Karta : public sf::Sprite
{
public:
	string nazwa;
	//void (*funkcja)(void);  //wskaŸnik na funkcjê spe³niaj¹c¹ funkcjonalnoœæ karty_nieruchomosci, na razie parametry void bo jeszcze nie wiem jakie bêd¹
	sf::Texture tekstura;          //tekstura pe³nej karty
	sf::Texture tekstura_min;      //tekstura miniaturki karty wyœwietlanej w panelu u¿ytkownika
	sf::RectangleShape Miniatura;   //kszta³t malowalny - miniatura
	sf::RectangleShape Duza_Karta;   //kszta³t malowalny - karta o pe³nych rozmiarach
	int cena;                        //cena kupna obiektu
	int cena_dom;                     //cena postawienia domu na tym obiekcie
	vector<int>czynsze;              //tablica czynszów [0] - dla 0 domów, [1] - dla jednego domu, [2] - dla 2 domów, ... , [5] - z hotelem
	Uzytkownik * wlasciciel;     //nick wlasciciela nieruchomosci, jeœli takowa nieruchomoœæ zosta³a ju¿ kupiona
	Kolor_ulicy kolor = BezKoloru;
	
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

