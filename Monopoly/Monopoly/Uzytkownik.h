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
	std::string nick;     //nick u�ytkownika
	std::vector<std::string> karty_nieruchomosci;  //wektor kart posiadanych przez u�ytkownika, nazwy kart
	Pionek *pionek;      //pionek u�ytkownika
	int numer_pola;     //numer pola na kt�rym stoi u�ytkownik
	int portfel;        //stan portfela
	int wyrok = 0;    //informacja o tym ile kolejek gracz musi by� w wiezieniu od teraz, po przej�ciu do wiezienia ustawiana na 3

	
	Uzytkownik(std::string nick);
	Uzytkownik() {}


};

