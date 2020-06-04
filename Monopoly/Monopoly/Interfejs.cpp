#include "Interfejs.h"
#include "Textbox.h"


#define WX 800
#define WY 600

void Interfejs::StartWindow()
{
    float szer = sf::VideoMode::getDesktopMode().width;
    float wys = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(szer - szer/2, wys - wys/3), "Monopoly Okno Startowe");
    sf::Texture window_tex;
    if ( !window_tex.loadFromFile("\grafiki/start.jpg") )
    {
        std::cerr << "blad ladowania tekstury tla ekranu startowego \n";
        cin.get();
        return;
    }
    sf::Sprite backgroud(window_tex);
    Resolution pos;
    sf::Vector2f sc = pos.scale();
    backgroud.scale(sc.x, sc.y);

    sf::Font czcionka;
    if (!czcionka.loadFromFile("BRLNSR.TTF"))
    {
        std::cerr << "Blad wczytania czcionki";
    }

    Textbox bar(20, sf::Color::White, true);
    bar.setPosition({ 100, 100 });
    bar.setLimit(true, 30);
    bar.setFont(czcionka);




    // dwa stany okna 
    // 1 okno wstêpne
    // 2 onko wpisywania adresu ip 
    bool state = 0;
    
    szer = szer - szer / 2;
    wys = wys - wys / 3;


    Button b1(sf::Vector2f(300.f * sc.x*2, 80.f * sc.y*2), "\grafiki/button_stworz.jpg", "\grafiki/button_stworz2.jpg", "Stwórz gre");
    Button b2(sf::Vector2f(300.f * sc.x*2, 80.f * sc.y*2), "\grafiki/button_dolacz.jpg", "\grafiki/button_dolacz2.jpg", "Do³¹cz");
    Button b3(sf::Vector2f(300.f * sc.x*2, 80.f * sc.y*2) ,"\grafiki/button_dolacz.jpg", "\grafiki/button_dolacz2.jpg", "Do³¹cz");
    b1.scale(sc.x * 2, sc.y*2);
    b2.scale(sc.x*2, sc.y*2);
    b3.scale(sc.x*2, sc.y*2);
    b1.setPosition(szer * 0.15, wys * 0.75);
    b2.setPosition(szer * 0.85 - (300.f * sc.x*2), wys * 0.75);
    b3.setPosition(szer * 0.5 - 300.f * sc.x, wys * 0.63);
    b1.frame_pos(szer * 0.15, wys * 0.75);
    b2.frame_pos(szer * 0.85 - (300.f * sc.x * 2), wys * 0.75);
    b3.frame_pos(szer * 0.5 - 300.f * sc.x, wys * 0.63);

    sf::Event event;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            bar.setSelected(true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            bar.setSelected(false);
        }
        
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                int prev_szer = szer;
                int prev_wys = wys;
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
                szer = event.size.width;
                wys = event.size.height;
                b1.frame_scale(b1.size_x * szer / prev_szer, b1.size_y * wys / prev_wys);
                b2.frame_scale(b2.size_x * szer / prev_szer, b2.size_y * wys / prev_wys);
                b3.frame_scale(b3.size_x * szer / prev_szer, b3.size_y * wys / prev_wys);
                b1.frame_pos(szer * 0.15, wys * 0.75);
                b2.frame_pos(szer * 0.85 - b1.size_x, wys * 0.75);
                b3.frame_pos(szer * 0.5 - b3.size_x/2, wys * 0.63);

               // window.setSize(sf::Vector2u(szer - szer / 2, wys - wys / 3));
            }
            if (event.type == sf::Event::MouseMoved)
            {
                    b1.mouse_move(event.mouseMove.x, event.mouseMove.y);
                    b2.mouse_move(event.mouseMove.x, event.mouseMove.y);
                    b3.mouse_move(event.mouseMove.x, event.mouseMove.y);
                    std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                    std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (state == 0)
                    {
                        if (b1.click(event.mouseButton.x, event.mouseButton.y) == true)
                        {
                            std::cout << "nacisnieto klawisz 1\n";
                        }
                        if (b2.click(event.mouseButton.x, event.mouseButton.y) == true)
                        {
                            state = 1;
                            std::cout << "nacisnieto klawisz 2\n";
                        }
                    }
                    else
                    {
                        if (b3.click(event.mouseButton.x, event.mouseButton.y) == true)
                        {
                            state = 0;
                            return;
                            std::cout << "nacisnieto klawisz 1\n";
                        }
                    }

                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                bar.typedOn(event);
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(backgroud);
        if (state == 0)
        {
           window.draw(b1);
           window.draw(b2);
           bar.drawTo(window);
        }
        else
        {
            window.draw(b3);
        }

        // end the current frame
        window.display();
    }

}


void Interfejs::DrawThread()
{
    while (this->MainWindow->isOpen())
    {
        // clear the window with black color
        this->MainWindow->clear(sf::Color::Black);

        // draw everything here...
        this->PoleGry->render();

        this->MainWindow->draw(*this->PoleGry);

        // end the current frame
        this->MainWindow->display();
    }
}





Button::Button(sf::Vector2f vect, std::string def_tex_string, std::string click_tex_string, std::string text) : sf::Sprite()
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
Button::Button(sf::Vector2f vect, sf::Texture def_tex, sf::Texture click_tex , std::string text) :  def_tex(def_tex ), click_tex(click_tex)
{
    size_x = vect.x;
    size_y = vect.y;

    this->set_change(false);
}
Button::~Button()
{
}

bool Button::mouse_move(int mouse_x_pos, int mouse_y_pos)
{
    sf::Vector2f pos = sf::Vector2f(this->frame_x,this->frame_y);
    if (mouse_x_pos > pos.x && mouse_x_pos < (pos.x + this->size_x) && mouse_y_pos > pos.y&& mouse_y_pos < (pos.y + this->size_y))
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
        this->setTexture(this->click_tex);
    }
    else
    {
        this->setTexture(this->def_tex);
    }

}

void Button::frame_scale(int x, int y)
{
    this->size_x = x;
    this->size_y = y;
}

void Button::frame_pos(int x, int y)
{
    this->frame_x = x;
    this->frame_y = y;
}