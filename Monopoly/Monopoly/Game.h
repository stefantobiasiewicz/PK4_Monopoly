#pragma once
#include "BazaDanych.h"
#include "Interfejs.h"
#include "Internet.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include "Funkcje_Kart.h"
#include "Protokol.h"



// typ wyliczeniowy do zdefiniowania stanow gry
typedef enum { StanInicjalizacji, InicjalizacjaSerwer, InicjalizacjaKlient , ExecuteButtons, StartGrySerwer, StartGryKlient, RuszaSie, Czeka, Wysylanie, DelegujDoRuchu, Stan1, Stan2, StanKoncowy, NUM_STATES } state_t;





class Game 
{

	// algorytmy wyszukiwania u¿ytowników ... dokonywanie transakcji ...  

public:
	bool EndOfGame;
	bool InternetStart;
	bool InterfejsStart;

	BazaDanych* baza;
	Internet* internet;
	Interfejs* interfejs;
	OpcjeGry opcjegry;
	bool czy_rzucone_kostki = 0;
	sf::Packet Dane_Do_Wyslania;
	sf::Packet Dane_Odebrane;


	state_t cur_state;	// bierzacy stan maszyny
	void RunState(Game* gra);

	Game();
	void Run();
	~Game();
};

typedef state_t state_func_t(Game* gra);
// deklaracje wszystkich stanow
state_t DoStanInicjalizacji(Game* gra);
state_t DoInicjalizacjaSerwera(Game* gra);
state_t DoInicjalizacjaKlienta(Game* gra);
state_t DoStan1(Game* gra);
state_t DoStan2(Game* gra);
state_t DoStanKoncowy(Game* gra);
state_t DoExecuteButtons(Game* gra);
state_t DoStartGrySerwer(Game* gra);
state_t DoStartGryKlient(Game* gra);
state_t DoRuszaSie(Game* gra);
state_t DoCzeka(Game* gra);
state_t DoWysylanie(Game* gra);
state_t DoDelegujDoRuchu(Game* gra);

// tabela z wyszystkimi stanami gry 
state_func_t* const state_table[NUM_STATES] = {
	DoStanInicjalizacji,
	DoInicjalizacjaSerwera,
	DoInicjalizacjaKlienta,
	DoExecuteButtons,
	DoStartGrySerwer,
	DoStartGryKlient,
	DoRuszaSie,
	DoCzeka,
	DoWysylanie,
	DoDelegujDoRuchu,
	DoStan1,
	DoStan2,
	DoStanKoncowy
};