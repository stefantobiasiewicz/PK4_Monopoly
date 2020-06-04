#include "Interfejs.h"


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




    sf::Event event;
    float factor_x = 1; // zmienne do podzielenia x i y myszki 
    float factor_y = 1;

    while (window.isOpen())
    {
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                 factor_x = (float)event.size.width / szer;
                 factor_y = (float)event.size.height / wys;
            }
            if (event.type == sf::Event::MouseMoved)
            {
                event.mouseMove.x /= factor_x;
                event.mouseMove.y /= factor_y;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                event.mouseButton.x /= factor_x;
                event.mouseButton.y /= factor_y;
            }




            if (state == 0)
            {
                if (b1.event(event) == true)
                {
                    std::cout << "nacisnieto klawisz 1\n";
                }
                if (b2.event(event) == true)
                {
                    state = 1;
                    std::cout << "nacisnieto klawisz 2\n";
                }
            }
            else
            {
                if (b3.event(event) == true)
                {
                    state = 0;
                    return;
                    std::cout << "nacisnieto klawisz 1\n";
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(backgroud);
        if (state == 0)
        {
            b1.drawTo(window);
            b2.drawTo(window);
        }
        else
        {
            b3.drawTo(window);
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



