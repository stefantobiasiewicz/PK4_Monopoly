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


class Uzytkownik
{
public:
	std::string nick;     //nick u¿ytkownika
	std::vector<std::string> karty_nieruchomosci;  //wektor kart posiadanych przez u¿ytkownika, nazwy kart
	Pionek pionek;      //pionek u¿ytkownika
	int numer_pola;     //numer pola na którym stoi u¿ytkownik
	int portfel;        //stan portfela

public:
	Uzytkownik(std::string nick);


};

