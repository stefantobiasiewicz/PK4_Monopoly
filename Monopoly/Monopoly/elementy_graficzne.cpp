#include "elementy_graficzne.h"

using namespace std;

bool Klikalny::event(sf::Event event)
{
	bool czy_klikniety = false;
	if (event.type == sf::Event::MouseMoved)
	{
		this->is_mouse_on(event.mouseMove.x, event.mouseMove.y);
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (this->click(event.mouseButton.x, event.mouseButton.y))
			{
				czy_klikniety = true;
			}
		}
	}
	return czy_klikniety;
}

Klik_Prostokat::Klik_Prostokat(sf::Vector2f size, sf::Vector2f pos, sf::Color color) : Klikalny()
{
	//this->frame_x = size.x;
	//this->frame_y = size.y;
	
	shape.setSize(size);
	shape.setPosition(pos);
	shape.setFillColor(color);
}

bool Klik_Prostokat::is_mouse_on(int mouse_x, int mouse_y)
{
	sf::Vector2f pos = this->shape.getPosition();
	if (mouse_x > pos.x&& mouse_x < (pos.x + this->getSize().x) && mouse_y > pos.y&& mouse_y < (pos.y + this->getSize().y))
	{
		shape.setOutlineThickness(20.f);
		return true;
	}
	else
	{
		shape.setOutlineThickness(0.f);
		return false;

	}
}

bool Klik_Prostokat::click(int mouse_x, int mouse_y)
{
	return this->is_mouse_on(mouse_x, mouse_y);
}

sf::Vector2f Klik_Prostokat::getPosition()
{
	return shape.getPosition();
}

sf::Vector2f Klik_Prostokat::getSize()
{
	return shape.getSize();
}

void Klik_Prostokat::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
}

void Klik_Prostokat::setSize(sf::Vector2f size)
{
	shape.setSize(size);
}

void Klik_Prostokat::setColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Klik_Prostokat::setOutlineColor(sf::Color color)
{
	shape.setOutlineColor(color);
}

void Klik_Prostokat::setOutlineThickness(float thick)
{
	shape.setOutlineThickness(thick);
}