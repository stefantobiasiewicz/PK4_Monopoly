#pragma once
#include "SFML/Graphics.hpp"

class Klikalny
{
protected:
	Klikalny() {}
	virtual bool is_mouse_on(int mouse_x, int mouse_y)=0;
	virtual bool click(int mouse_x, int mouse_y) = 0;
public:
	bool event(sf::Event event);
};

class Klik_Prostokat : public Klikalny
{
	//float frame_x;
	//float frame_y;
	
protected:
	virtual bool is_mouse_on(int mouse_x, int mouse_y);
	virtual bool click(int mouse_x, int mouse_y);
	sf::RectangleShape shape;
	Klik_Prostokat(sf::Vector2f size = sf::Vector2f{ 0.f, 0.f }, sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, sf::Color color = sf::Color(0, 0, 0));
public:
	sf::Vector2f pos = this->shape.getPosition();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(float thick);
};