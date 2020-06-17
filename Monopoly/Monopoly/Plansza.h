#pragma once
#include "SFML/Graphics.hpp"
#include "Obiekt_Na_Planszy.h"
#include <vector>
#include <algorithm>
#include "Resolution.h"
class Plansza : public sf::Sprite
{
	std::vector<Obiekt_Na_Planszy*> Obiekty;
	sf::Texture tekstura;	//  tekstura planszy
	sf::Sprite Background;
	sf::RenderTexture renderTexture;	// obiekt potrzebny do renderowania widoku planszy
public:


	Plansza(std::string file = std::string("\grafiki/planszaG.jpg"));

	void SetObject(Obiekt_Na_Planszy* obj);
	void RemoveObject(Obiekt_Na_Planszy* obj);
	void ClearObject();
	void render();	// zmien znazwe na render()

};

