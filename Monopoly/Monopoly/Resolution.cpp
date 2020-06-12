#include "Resolution.h"




Resolution::Resolution()
{
	w_res = sf::VideoMode::getDesktopMode().width;
	h_res = sf::VideoMode::getDesktopMode().height;
}
int Resolution::x(float width)
{
	return w_res * width * 0.01;
}
int Resolution::y(float height)
{
	return h_res * height * 0.01;
}
sf::Vector2f Resolution::scale()
{
	sf::Vector2f v;
	v.x = w_res / 3840.0f;
	v.y = h_res / 2160.0f;
	return v;
}

sf::Vector2f Resolution::setScale(int x, int y)
{
	sf::Vector2f v;
	v.x = w_res / 3840.0f;
	v.y = h_res / 2160.0f;
	return v;
}

int Resolution::GetW_res()
{
	return this->w_res;
}
int Resolution::GetH_res()
{
	return this->h_res;
}

void Resolution::SetW_res(int w)
{
	this->w_res = w;
}

void Resolution::SetH_res(int h)
{
	this->h_res = h;
}