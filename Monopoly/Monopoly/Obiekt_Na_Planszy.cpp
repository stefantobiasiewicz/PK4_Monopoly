#include "Obiekt_Na_Planszy.h"


Obiekt_Na_Planszy::Obiekt_Na_Planszy(sf::Texture* tekstura)
{
	Resolution res;
	this->setTexture(*tekstura);
	this->setScale(res.scale().x * 0.2, res.scale().y * 0.2);	
}