#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Uzytkownik.h"
#include "Karta.h"
#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"
#include "Pole.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <vld.h>
#include <vld_def.h>
#include <utility>
#include "Resolution.h"


typedef enum {Zielona = 0, Niebieska, Rozowa, Brak} Kolor_Planszy;

struct Grupy_Ulic
{
	std::vector<std::vector<std::string>> grupy;

	Grupy_Ulic()
	{
		std::vector<std::string> brazowe = { "ulica Konopacka", "ulica Stalowa" };
		std::vector<std::string> niebieskie = { "ulica Radzyminska", "ulica Jagiellonska", "ulica Targowa" };
		std::vector<std::string> rozowe = { "ulica Grochowska", "ulica Plowiecka", "ulica Marsa" };
		std::vector<std::string> pomaranczowe = { "ulica Gorczeska", "ulica Obozowa", "ulica Wolska" };
		std::vector<std::string> czerwone = { "ulica Slowackiego", "plac Wilsona", "ulica Mickiewicza" };
		std::vector<std::string> zolte = { "Krakowskie Przedmiescie", "Nowy Swiat", "ulica Swietokrzyska" };
		std::vector<std::string> zielone = { "ulica Marszalkowska", "Plac Trzech Krzyzy", "Aleje Jerozolimskie" };
		std::vector<std::string> granatowe = { "ulica Belwederska", "Aleje Ujazdowskie" };

		grupy = { brazowe, niebieskie, rozowe, pomaranczowe, czerwone, zolte, zielone, granatowe };
	}
};

class BazaDanych
{
public:
	std::map<std::string, Karta*>karty_nieruchomosci;   //tablica asocjacyjna kart, kluczem nazwa karty
	std::vector<Pole>pola;                //tablica pól na planszy
	std::vector<Szansa_Kasa_Spoleczna*>karty_szansa_kasa;  //tablica kart 'szansa' i 'kasa spoleczna' 
	std::ifstream plik_ulice_dworce_uzyt; //strumien do pliku z danymi nieruchomosci
	std::ifstream plik_szansa_kasa;       //strumien do pliku z danymi o kartach 'szansa' i 'kasa spoleczna'
	std::ifstream plik_pola;              //strumien do pliku z danymi o polach na planszy
	std::map<std::string, Uzytkownik>gracze; //tablica graczy, indeksowana nickiem
	std::vector<Pionek*> pionki;				// wektor pionkow
	std::string moj_nick;                     //moj nick
	std::vector<std::string>nicki;             //wektor nicków
	sf::Font czcionka;
	Resolution res;
	Grupy_Ulic grupy_ulic;
	std::string nick_aktywnego_gracza;        //nick gracza który w³aœnie wykonuje ruch



	sf::IpAddress IP;                        //ip gry
	int ilosc_graczy;
	Kolor_Planszy kolor;
	bool isServer;                           //czy to jest server czy klient

	BazaDanych();
	~BazaDanych();
	void Stworz_Mnie(std::string nick, sf::IpAddress ip, bool isServer, Kolor_Planszy kolor = Zielona);
	void unikalne_nicki(std::string& name);

private:
	
	void Tworz_Ulice();
	void Usun_Nieruchomosci();
	void Tworz_Szansa_Kasa_Spoleczna();
	void Usun_Szansa_Kasa_Spoleczna();
	void Tworz_Dworce();
	void Tworz_Obiekt_UP();
	void Tworz_Pola();
	void Sortuj_Pola();
	void Tworz_Pionki();
	void Usun_Pionki();
	void Tworz_Czcionke();
	void Przypisz_Wirtualne_Karty();
	void Przypisz_Kolory_Ulicom();
};

