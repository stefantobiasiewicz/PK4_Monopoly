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
	std::string nick;     //nick użytkownika
	std::vector<std::string> karty_nieruchomosci;  //wektor kart posiadanych przez użytkownika, nazwy kart
	Pionek pionek;      //pionek użytkownika
	int numer_pola;     //numer pola na którym stoi użytkownik
	int portfel;        //stan portfela

	
	Uzytkownik(std::string nick);
	Uzytkownik() {}


};

