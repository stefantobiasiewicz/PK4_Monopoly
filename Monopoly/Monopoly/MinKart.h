#pragma once
#include "SFML/Graphics.hpp"
#include "Resolution.h"
class MinKart : public sf::Sprite
{
protected:
	std::vector<sf::RectangleShape*> Obiekty;
	sf::RenderTexture renderTexture;	// obiekt potrzebny do renderowania widoku planszy
	Resolution res;
	sf::Vector2f scale;

	// tymczasowo
	sf::RectangleShape kolortla;

public:
	MinKart(int x, int y);
	void Render();
	void SetObject(sf::RectangleShape* obj);
	void RemoveObject(sf::RectangleShape* obj);
	void ClearObject();
};

