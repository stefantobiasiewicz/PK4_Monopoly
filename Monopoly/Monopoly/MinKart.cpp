#include "MinKart.h"



MinKart::MinKart(int x, int y)
{
	renderTexture.create(x, y);
	res.SetW_res(x);
	res.SetH_res(y);
	scale = res.scale();

}
void MinKart::Render()
{
	renderTexture.clear();
	for (sf::RectangleShape* i : this->Obiekty)
	{
		renderTexture.draw(*i);	// narysowanie wszystkich obiektów
	}
	renderTexture.display();
	this->setTexture(renderTexture.getTexture());	//	ustawienie tekstury planszy
}
void MinKart::SetObject(sf::RectangleShape* obj)
{
	int kolumna = this->Obiekty.size() % 4;
	int wiersz = this->Obiekty.size() / 4;

	obj->setPosition(kolumna * res.x(25), wiersz * res.y(11.f));
	obj->setSize({600.f * scale.x, 200.f * scale.y});

	this->Obiekty.push_back(obj);
}
void MinKart::RemoveObject(sf::RectangleShape* obj)
{
	std::vector<sf::RectangleShape*>::iterator remove = find(this->Obiekty.begin(), this->Obiekty.end(), obj);
	if (remove != this->Obiekty.end())
		this->Obiekty.erase(remove);
}
void MinKart::ClearObject()
{
	this->Obiekty.clear();
}