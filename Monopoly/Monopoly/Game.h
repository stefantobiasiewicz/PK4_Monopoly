#pragma once
#include "BazaDanych.h"
#include "Interfejs.h"
#include "Internet.h"
#include <vector>
#include <iostream>

// typ wyliczeniowy do zdefiniowania stanow gry
typedef enum { StanInicjalizacj, Stan1, Stan2, StanKoncowy, NUM_STATES } state_t;

class Game 
{

	// algorytmy wyszukiwania u¿ytowników ... dokonywanie transakcji ...  

public:
	bool EndOfGame;
	bool InternetStart;
	bool InterfejsStar;

	BazaDanych* baza;
	Internet* internet;
	Interfejs* interfejs;

	state_t cur_state;	// bierzacy stan maszyny
	void RunState(Game* gra);

	Game();
	void Run();
	~Game();
};

typedef state_t state_func_t(Game* gra);
// deklaracje wszystkich stanow
state_t DoStanInicjalizacj(Game* gra);
state_t DoStan1(Game* gra);
state_t DoStan2(Game* gra);
state_t DoStanKoncowy(Game* gra);
// tabela z wyszystkimi stanami gry 
state_func_t* const state_table[NUM_STATES] = {
	DoStanInicjalizacj, DoStan1, DoStan2, DoStanKoncowy
};