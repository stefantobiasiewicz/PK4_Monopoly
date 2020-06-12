#pragma once
#include "SFML/Graphics.hpp"
#include "Resolution.h"

class Klikalny
{
protected:
	Klikalny() {}
	virtual bool is_mouse_on(int mouse_x, int mouse_y)=0;
	virtual bool click(int mouse_x, int mouse_y) = 0;

public:
	bool event(sf::Event event);
	virtual void drawTo(sf::RenderWindow& window) = 0;
	~Klikalny() {}
};

class Klik_Prostokat : public Klikalny
{
	//float frame_x;
	//float frame_y;
	
protected:
	bool is_mouse_on(int mouse_x, int mouse_y);
	bool click(int mouse_x, int mouse_y);
	sf::RectangleShape shape;
	sf::Texture texture;
	Klik_Prostokat(sf::Vector2f size, sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, sf::Color color = sf::Color(0, 0, 0));
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
protected:
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
	void setOutlineColor(sf::Color color);
	bool getSelected();
	
	
};

class Klik_Kolo_Button : public Klik_Kolo
{
public:
	Klik_Kolo_Button(sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, std::string texture_file = "");
	Klik_Kolo_Button(float radius, sf::Vector2f pos = sf::Vector2f{ 0.f, 0.f }, sf::Color color = sf::Color(0, 0, 0));
	~Klik_Kolo_Button() {}
	bool click(int mouse_x, int mouse_y);
	void setSize(sf::Vector2f size);
	sf::Vector2f getSize();
	bool is_mouse_on(int mouse_x, int mouse_y);
};

class button : public Klik_Prostokat
{
	sf::Texture def_text;
	sf::Texture click_text;
protected:
	bool is_mouse_on(int mouse_x, int mouse_y);
public:
	button(sf::Vector2f size, sf::Vector2f pos, std::string def_texture_file, std::string click_texture_file);
	button(int win_res_x, int win_res_y, sf::Vector2f size, sf::Vector2f pos, std::string def_texture_file, std::string click_texture_file);
	~button() {}

	
};