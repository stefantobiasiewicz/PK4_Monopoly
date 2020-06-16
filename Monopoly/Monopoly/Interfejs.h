#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <Windows.h>

#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"

#include "BazaDanych.h"
#include "Resolution.h"
#include "elementy_graficzne.h"
#include "Internet.h"

#include "MinKart.h"
#include "kostka.h"
//struktura przechowujaca opcje gry 
//opcje gry sa zmieniane przez przyciski / koreluja z nimi
//przez ta strukture gra wie co chce zorobic gracz
typedef struct 
{
	// trzeba dodac opcje odpowiedzialne za wszystkie button
	bool zakup_domku = 0;
	bool zakup_hotelu = 0;
	bool zastaw = 0;
	bool kostki = 0;
	bool karty1 = 0;
	bool karty2 = 0;
	bool karty3 = 0;
	bool karty4 = 0;
	bool ok = 0;
	bool kup = 0;
	bool odrzuc = 0;
	bool szansa = 0;
	bool zachowaj = 0;
} OpcjeGry;

class Interfejs
{
	sf::RenderWindow* MainWindow;
	Plansza* PoleGry;
	BazaDanych* Dane;

	std::map<std::string, Klikalny*> KlikObject;
	std::vector<sf::Drawable*>ksztalty;
	std::vector<sf::Text*> teksty;
	std::vector<sf::Texture> tekstury;
	std::map<std::string, sf::Text*>  pieniadze;
	

	std::vector<MinKart*> miniatury;

	OpcjeGry* opcjegry;

	//zmienne potrzebne do skalowania
	float factorX = 1; // zmienne do podzielenia x i y myszki 
	float factorY = 1;

	float Szer = sf::VideoMode::getDesktopMode().width;
	float Wys = sf::VideoMode::getDesktopMode().height;

public:

	Kostka* kostka;
	sf::Text aktywny_gracz;

	Interfejs(BazaDanych* res);
	~Interfejs();

	void StartWindow();

	// funkcja tworzaca/usuwajaca nowe okno 
	void CreateMainWindow();
	void DeleteMainWindow();


	// funkcja zwraca czy okno jest otwarte
	bool IsOpen();


	// zastapienie petli glownej SFML-owskiej
	void MainFunction();


	// funkjca obslugujaca eventy
	void EventFunction(OpcjeGry& opcje);
	/*	mozna zrobic klase wirtualna do obslugi eventow
		kazda klasa ktora obsluguje te eventy ma funkcje event ktora zostaje nadpisana
		nasz interfejs ma wektor wskaznikow na obiekty klasy eventowej * w ktorym znajduja sie wszystkie pobiekty
		ktore maja byæ obsuiwane
	*/
	// funkcja "skalujaca myszke" potrzebna do poprawnego dzialania programu po zmianie rozmiaru okna
	void EventScaleMouse(sf::Event& even);

	// funkcja rysjujaca okno
	void DrawFunction();

	// funkcja aktualizujaca wszystkie zmiany w wygladzie interfejsy
	void UpdateFunction();

	// funkcja tworzaca/usuwajaca plansze
	void CreatePlansza(std::string = "\grafiki / planszaG.jpg");
	void DeletePlansza();

	// funkcja tworzaca/usuwajaca przyciski / lub texbary
	void CreateButtons();
	void DeleteButtons();
	void DeleteKostka();

	//funkcja obslugujaca przyciski / elementy przyciskalne
	void ExecuteButtons(sf::Event &event, OpcjeGry & opcje);

	//funkcja rysujaca wszyskie klawisze
	void DrawButtons(sf::RenderWindow& window);

	//funkcja tworz¹ca ksztalty do namalowania
	void CreateSprites();

	// funkcja tworzaca statystkiki gracza
	void CreateUserStats();

	//funkcja usuwaj¹ca kszta³ty
	void DeleteSprites();

	//fukcja rysuj¹ca wektor kszta³ty
	void DrawSprites(sf::RenderWindow& window);

	// funkcja tworzaca nowe okno z informacja, funkcja zwraca numer przycisku ktory zostal klikniety
	int CreateMessageWindow(std::string tekst, std::vector<button*> przyciski, Karta* KartaRysowana = nullptr);

	//funkcja tworz¹ca nowe okno pokazuj¹ce karty u¿ytkownika. 
	void CreateCardsWindow(std::string nick);

	// funkcja ustawiajaca wskaznik na OpcjeGry
	void SetOpcjeGry(OpcjeGry* opcje);

	// funkcja tworzaca okno poczeklani dla graczy ( tylko server ma taka opcje )
	void CreateWaitingWindow(Internet * internet);

	// funkcja tworzy i obsluguje zastaw nieruchomosci / zwraca false gdy zastaw odbyl sie poprawnie i true jesli gracz sie poddal
	bool CreateZastawWindow(bool CzyPrzymusowy, Uzytkownik* user);

};


