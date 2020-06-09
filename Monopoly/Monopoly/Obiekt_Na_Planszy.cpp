#include "Obiekt_Na_Planszy.h"

Obiekt_Na_Planszy::Obiekt_Na_Planszy(std::string file, sf::Vector2f pos)
{
	if (!this->tekstura.loadFromFile(file))
		std::cerr << "nie wczytano tekstury: apple\n";

	this->setTexture(this->tekstura);
	this->setPosition(pos);

}