#include "Interfejs.h"
#include "Textbox.h"


#define WX 800
#define WY 600

void Interfejs::StartWindow()
{
    float szer = sf::VideoMode::getDesktopMode().width;
    float wys = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(szer - szer / 2, wys - wys / 3), "Monopoly Okno Startowe");
    window.setFramerateLimit(60);
    sf::Texture window_tex;
    if (!window_tex.loadFromFile("\grafiki/start.jpg"))
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


    float wsp_x = (szer - szer / 2) / szer;
    float wsp_y = (wys - wys / 3) / wys;

    sf::Text nick;
    nick.setString("Podaj nick:");
    nick.setCharacterSize(30);
    nick.setFont(czcionka);
    nick.setPosition(wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 80);
    nick.setFillColor({ 77, 0, 0 });

    sf::Text id;
    id.setString("Podaj swoje IP, do ktorego przylacza sie inni gracze:");
    id.setCharacterSize(30);
    id.setFont(czcionka);
    id.setPosition(wsp_x * pos.x(35) - 200, wsp_y * pos.y(50) - 80);
    id.setFillColor({ 77, 0, 0 });

    sf::Text plansza;
    plansza.setString("Jako tworzacy gre, wybierz kolor planszy:");
    plansza.setCharacterSize(30);
    plansza.setFont(czcionka);
    plansza.setPosition(wsp_x * pos.x(22), wsp_y * pos.y(58));
    plansza.setFillColor({ 77, 0, 0 });

    Textbox nick_enter(40, sf::Color(77, 0, 0), false, 400, sf::Vector2f{ wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 10 }, sf::Color(204, 204, 204));
    nick_enter.setLimit(true, 15);
    nick_enter.setFont(czcionka);

    Textbox IP_enter(40, sf::Color(77, 0, 0), false, 400, sf::Vector2f{ wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 10 }, sf::Color(204, 204, 204));
    IP_enter.setLimit(true, 15);
    IP_enter.setFont(czcionka);

    Klik_Kolo zielony(30.f, sf::Vector2f{ wsp_x * pos.x(27), wsp_y * pos.y(67)}, sf::Color(179, 255, 218));
    Klik_Kolo niebieski(30.f, sf::Vector2f{ wsp_x * pos.x(47), wsp_y * pos.y(67)}, sf::Color(153, 235, 255));
    Klik_Kolo rozowy(30.f, sf::Vector2f{ wsp_x * pos.x(67), wsp_y * pos.y(67)}, sf::Color(255, 230, 255));
    zielony.setOutlineColor(sf::Color(0, 0, 0));
    niebieski.setOutlineColor(sf::Color(0, 0, 0));
    rozowy.setOutlineColor(sf::Color(0, 0, 0));


    // dwa stany okna 
    // 1 okno wstêpne
    // 2 onko wpisywania adresu ip 
    int state = 0;

    szer = szer - szer / 2;
    wys = wys - wys / 3;


    button b1(sf::Vector2f(300.f * sc.x * 2, 80.f * sc.y * 2), sf::Vector2f( szer * 0.15, wys * 0.75 ), "\grafiki/button_stworz.jpg", "\grafiki/button_stworz2.jpg");
    button b2(sf::Vector2f(300.f * sc.x * 2, 80.f * sc.y * 2), sf::Vector2f(szer * 0.85 - (300.f * sc.x * 2), wys * 0.75),"\grafiki/button_dolacz.jpg", "\grafiki/button_dolacz2.jpg");
    button b3(sf::Vector2f(300.f * sc.x * 2, 80.f * sc.y * 2), sf::Vector2f(szer * 0.5 - 300.f * sc.x, wys * 0.63),"\grafiki/button_dolacz.jpg", "\grafiki/button_dolacz2.jpg");
    //b1.scale(sc.x * 2, sc.y * 2);
    //b2.scale(sc.x * 2, sc.y * 2);
    //b3.scale(sc.x * 2, sc.y * 2);
    //b1.setPosition(szer * 0.15, wys * 0.75);
    //b2.setPosition(szer * 0.85 - (300.f * sc.x * 2), wys * 0.75);
    //b3.setPosition(szer * 0.5 - 300.f * sc.x, wys * 0.63);




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
                    std::cout << "nacisnieto klawisz stworz gre\n";
                    state = 2;
                }
                if (b2.event(event) == true)
                {
                    state = 1;
                    std::cout << "nacisnieto klawisz dolacz do gry\n";
                }
                if (nick_enter.event(event) == true)  //naciœniêto textbox
                {
                    std::cout << "nacisnieto nick_enter";
                }
            }
            else if (state == 1)
            {
                if (b3.event(event) == true)
                {
                    state = 0;
                    std::cout << "nacisnieto klawisz dolacz do gry\n";
                }
            }
            else if (state == 2)
            {
                if (IP_enter.event(event) == true)
                {
                    std::cout << "Nacisnieto IP_enter";
                }
                if (zielony.event(event) == true)
                {
                    std::cout<<"nacisnieto zielony";
                    niebieski.setSelected(false);
                    rozowy.setSelected(false);
                }
                if (niebieski.event(event) == true)
                {
                    std::cout << "nacisnieto niebieski";
                    zielony.setSelected(false);
                    rozowy.setSelected(false);
                }
                if (rozowy.event(event) == true)
                {
                    std::cout << "nacisnieto niebieski";
                    zielony.setSelected(false);
                    niebieski.setSelected(false);
                }
            }

        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(backgroud);
        if (!state)
        {
            nick_enter.drawTo(window);
            window.draw(nick);

            b1.drawTo(window);
            b2.drawTo(window);

        }
        else if (state == 1)
        {
            b3.drawTo(window);
        }
        else if (state == 2)
        {
            IP_enter.drawTo(window);
            window.draw(id);
            zielony.drawTo(window);
            niebieski.drawTo(window);
            rozowy.drawTo(window);
            window.draw(plansza);
        }
        // end the current frame
        window.display();
    }
}


/*void Interfejs::DrawThread()
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
}*/



