#include "Pole.h"


Pole::Pole(std::vector<sf::Vector2f>pozycja, Karta *karta)
{
	this->pozycja = pozycja;
	this->karta = karta;
	this->domy = 0;
}
Pole::Pole()
{
	this->karta = nullptr;
	domy = 0;
}

