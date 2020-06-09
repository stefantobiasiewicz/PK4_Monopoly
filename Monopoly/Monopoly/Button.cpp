#include "Button.h"



Button::Button(sf::Vector2f vect, std::string def_tex_string, std::string click_tex_string, std::string text)
{

    if (!this->def_tex.loadFromFile(def_tex_string))
    {
        std::cerr << "blad ladowania tekstury przycisku ekranu startowego \n";
        return;
    }
    if (!this->click_tex.loadFromFile(click_tex_string))
    {
        std::cerr << "blad ladowania tekstury przycisku ekranu startowego \n";
        return;
    }


    size_x = vect.x;
    size_y = vect.y;

    this->set_change(false);
}

Button::~Button()
{
}

bool Button::mouse_move(int mouse_x_pos, int mouse_y_pos)
{
    sf::Vector2f pos = this->button.getPosition();
    //sf::Vector2f(this->frame_x,this->frame_y);
    if (mouse_x_pos > pos.x&& mouse_x_pos < (pos.x + this->size_x) && mouse_y_pos > pos.y&& mouse_y_pos < (pos.y + this->size_y))
    {
        this->set_change(true);
        return true;
    }
    else
    {
        this->set_change(false);
        return false;

    }
}

bool Button::click(int mouse_x_pos, int mouse_y_pos)
{
    return this->mouse_move(mouse_x_pos, mouse_y_pos);
}


void Button::set_change(bool on)
{
    if (on == 1)
    {
        this->button.setTexture(this->click_tex);
    }
    else
    {
        this->button.setTexture(this->def_tex);
    }
}

bool Button::event(sf::Event event)
{
    bool  b = false;
    if (event.type == sf::Event::MouseMoved)
    {
        this->mouse_move(event.mouseMove.x, event.mouseMove.y);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (this->click(event.mouseButton.x, event.mouseButton.y) == true)
            {
                b = true;
            }
        }
    }
    return b;
}
void Button::scale(float factorX, float factorY)
{
    this->button.scale(factorX, factorY);
    //    this->set_frame_scale(factorX, factorY);
}
void Button::setPosition(float x, float y)
{
    this->button.setPosition(x, y);
}
void Button::drawTo(sf::RenderWindow& window) {
    window.draw(this->button);
}
