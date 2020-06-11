#include <cmath>
#include <iostream>
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
	shape.setSize(size);
	shape.setPosition(pos);
	shape.setFillColor(color);
}

Klik_Prostokat::Klik_Prostokat(sf::Vector2f pos, std::string texture_file) : Klikalny()
{
	if (!this->texture.loadFromFile(texture_file))
	{
		std::cerr << "Nie zaladowno grafiki";
	}
	this->shape.setTexture(&texture);
	shape.setPosition(pos);
	this->setSize({ (float)texture.getSize().x, (float)texture.getSize().y });
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

Klik_Kolo::Klik_Kolo(sf::Vector2f pos, std::string texture_file) : Klik_Prostokat(pos, texture_file)
{
	if (!this->texture.loadFromFile(texture_file))
	{
		std::cerr << "Nie ma pliku grafiki";
	}
	float size_x = texture.getSize().x;
	float size_y = texture.getSize().y;
	this->shape.setTexture(&texture);
	shape.setRadius(size_x / 2);
	shape.setPosition(pos);
	this->setSize({ size_x, size_y });
}
Klik_Kolo::Klik_Kolo(float radius, sf::Vector2f pos, sf::Color color) : Klik_Prostokat(sf::Vector2f{radius, radius}, pos, sf::Color::Transparent)
{
	float size_x = radius * 2;
	float size_y = radius * 2;
	this->shape.setRadius(radius);
	this->shape.setPosition(pos);
	this->setSize({ size_x, size_y });
	this->shape.setFillColor(color);
	this->shape.setOutlineColor(sf::Color(204, 204, 204));
}

bool Klik_Kolo::is_mouse_on(int mouse_x, int mouse_y)
{
	sf::Vector2f pos = this->shape.getPosition();
	float center_x = pos.x + this->getSize().x / 2;
	float center_y = pos.y + this->getSize().y / 2;
	float promien = this->getSize().x / 2;
	
	if (this->how_far(mouse_x, mouse_y, center_x, center_y) <= promien)
	{
		shape.setOutlineThickness(5.f);
		return true;
	}
	else
	{
		if (!isSelected)
		{
			shape.setOutlineThickness(2.f);
		}
		return false;
	}
}

float Klik_Kolo::how_far(float ax, float ay, float bx, float by)
{
	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

void Klik_Prostokat::drawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
}

void Klik_Kolo::drawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
}

bool Klik_Kolo::click(int mouse_x, int mouse_y)
{
	if (is_mouse_on(mouse_x, mouse_y))
		isSelected = true;
	else if (!is_mouse_on(mouse_x, mouse_y) && isSelected == true)
		isSelected == true;
	return isSelected;
}

void Klik_Kolo::setSelected(bool sel)
{
	isSelected = sel;
}

