#include "MinKart.h"



MinKart::MinKart(int x, int y)
{


	renderTexture.create(x, y);
	res.SetW_res(x);
	res.SetH_res(y);
	scale = res.scale();



	kolortla.setFillColor(sf::Color::Transparent);
	kolortla.setSize({ 2000,2000 });
}
void MinKart::Wood()
{
	Resolution res1;

	sf::Vector2f pos = this->getPosition();
	deska.loadFromFile("\grafiki/deska2.jpg");
	back.setTexture(deska);
	back.setScale(res1.scale().x, res1.scale().y);
	//float qew = res.y(res.GetH_res() * pos.y / (renderTexture.getSize().y*res1.scale().y));
	float f3 = pos.y * 100 / res.GetH_res();
	back.setPosition(-res.x(2.6), - res.y(f3));    //
}
void MinKart::Render()
{
	renderTexture.clear();
	//renderTexture.draw(kolortla);
	renderTexture.draw(back);
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