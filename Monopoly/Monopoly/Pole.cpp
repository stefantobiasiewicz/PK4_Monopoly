#include "Pole.h"


Pole::Pole(std::vector<sf::Vector2f>pozycja, Karta *karta)
{
	this->pozycja = pozycja;
	this->karta = karta;
	this->domy = 0;

}
Pole::Pole()
{
/*
	for (int i = 0; i < 4; i++)
	{
		domki.push_back(Domek(dom));
		this->DomuHotele.push_back(&domki.back());
	}

	this->hotel.push_back(Hotel(hote));
	this->DomuHotele.push_back(&hotel.back());

*/


	this->karta = nullptr;
	domy = 0;
}
void Pole::StworzDomki(sf::Texture* dom, sf::Texture*hote)
{
	for (int i = 0; i < 4; i++)
	{
		domki.push_back(Domek(dom));
		domki[i].setPosition(this->pozycja[i]);
	}
	this->hotel.push_back(Hotel(hote));
	hotel[0].setPosition(this->pozycja[0]);
}

Pole::~Pole()
{

}
/*
std::vector<Obiekt_Na_Planszy*>::iterator it = this->DomuHotele.begin();
for (it; it != this->DomuHotele.end() ; it++)
{
	delete *it;
}

	for (int i = 0; i < this->DomuHotele.size(); i++)
	{
		Obiekt_Na_Planszy* tmp = this->DomuHotele[i];
		delete tmp;
	}
*/