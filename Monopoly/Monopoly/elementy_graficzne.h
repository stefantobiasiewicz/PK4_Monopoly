#pragma once
#include "SFML/Graphics.hpp"

class Klikalny
{
protected:
	Klikalny() {}
	virtual bool is_mouse_on(int mouse_x, int mouse_y)=0;
	virtual bool click(int mouse_x, int mouse_y) = 0;
	~Klikalny() {}
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
	sf::Texture texture;
	Klik_Prostokat(sf::Vector2f size = sf::Vector2f{ 0.f, 0.f }, sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, sf::Color color = sf::Color(0, 0, 0));
	Klik_Prostokat(sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, std::string texture_file = "");
public:
	sf::Vector2f pos = this->shape.getPosition();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(float thick);
	void drawTo(sf::RenderWindow& window);
	~Klik_Prostokat() {}
};

class Klik_Kolo : public Klik_Prostokat
{
	sf::CircleShape shape;
	bool isSelected = false;
	bool isOutline = false;
	
public:
	Klik_Kolo(sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, std::string texture_file = "");
	Klik_Kolo(float radius, sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, sf::Color color = sf::Color(0, 0, 0));
	void drawTo(sf::RenderWindow& window);
	~Klik_Kolo() {}
	bool is_mouse_on(int mouse_x, int mouse_y);
	float how_far(float ax, float ay, float bx, float by);
	bool click(int mouse_x, int mouse_y);
	void setSelected(bool sel);
	
};