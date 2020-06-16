#include "Plansza.h"



Plansza::Plansza(std::string file)
{
	Resolution res;
	sf::Vector2f scale = res.scale();
	if (!this->tekstura.loadFromFile(file))
		std::cerr << "nie wczytano tekstury: planszy\n";

	Background.setTexture(this->tekstura);
	Background.setScale(scale.x, scale.y);
	//auto SizeB = tekstura.getSize();
	renderTexture.create(res.GetW_res(), res.GetH_res());		// trzeba usttawic wielkoœæ planszy 
}

void Plansza::SetObject(Obiekt_Na_Planszy* obj)
{
	this->Obiekty.push_back(obj);
}
void Plansza::RemoveObject(Obiekt_Na_Planszy* obj)
{
	std::vector<Obiekt_Na_Planszy*>::iterator remove = find(this->Obiekty.begin(), this->Obiekty.end(), obj);
	if (remove != this->Obiekty.end())
		this->Obiekty.erase(remove);
}

void Plansza::render()
{
	renderTexture.clear();
	renderTexture.draw(Background);					//namalowanie planszy 
	for (Obiekt_Na_Planszy* i : this->Obiekty)
	{
		renderTexture.draw(*i);	// narysowanie wszystkich obiektów
	}
	renderTexture.display();
	this->setTexture(renderTexture.getTexture());	//	ustawienie tekstury planszy
}

void Plansza::ClearObject()
{
	this->Obiekty.clear();
}