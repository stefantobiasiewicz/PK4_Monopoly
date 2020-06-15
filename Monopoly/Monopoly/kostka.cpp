#include "kostka.h"

int Kostka::Rzuc()
{
	std::default_random_engine silnik;
	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> liniowy(1, 6);

	int rzut = liniowy(silnik) + liniowy(silnik);      //dwie kostki, suma dwóch losowych liczb z zakresu 1-6
	this->wynik_rzutu.setString(std::to_string(rzut));
	return rzut;
}

Kostka::Kostka(sf::Font &czcionka)
{
	wynik_rzutu.setString("6");
	sf::Vector2f scale = res.scale();
	wynik_rzutu.setFont(czcionka);
	wynik_rzutu.setCharacterSize(scale.y * 220);
	wynik_rzutu.setFillColor({ 140, 0, 0 });
	wynik_rzutu.setOutlineColor({ 0, 0, 0 });
	wynik_rzutu.setOutlineThickness(scale.x * 7.);
	wynik_rzutu.setPosition(res.x(57), res.y(46));
}