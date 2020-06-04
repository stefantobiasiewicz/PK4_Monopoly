#pragma once
#include "SFML/Graphics.hpp"
#include "Obiekt_Na_Planszy.h"
#include <vector>
#include <algorithm>
class Plansza : public sf::Sprite
{
public:
	std::vector<Obiekt_Na_Planszy*> Obiekty;
	sf::Texture tekstura;	//  tekstura planszy
	sf::Sprite Background;
	sf::RenderTexture renderTexture;	// obiekt potrzebny do renderowania widoku planszy

	Plansza(std::string file = std::string("scierzka do pliku planszy"))
	{
		if (!this->tekstura.loadFromFile(file))
			std::cerr << "nie wczytano tekstury: apple\n";

		Background.setTexture(this->tekstura);
		renderTexture.create(800, 600);		// trzeba usttawic wielkoœæ planszy 
	}

	void SetObject(Obiekt_Na_Planszy* obj);
	void RemoveObject(Obiekt_Na_Planszy* obj);

	void render();	// zmien znazwe na render()

};

