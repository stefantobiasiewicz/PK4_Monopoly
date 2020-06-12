#include "Interfejs.h"
#include "Textbox.h"


#define WX 800
#define WY 600

#define WIDTH_MIN 0
#define HEIGHT_MIN 0

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

    szer = szer - szer / 2;
    wys = wys - wys / 3;

    Kolor_Planszy kolor = Brak;

    sf::Text nick;
    nick.setString("Podaj nick:");
    nick.setCharacterSize(60 * sc.y);
    nick.setFont(czcionka);
    nick.setPosition(wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 80);
    nick.setFillColor({ 77, 0, 0 });

    sf::Text id;
    id.setString("Podaj swoje IP, do ktorego przylacza sie inni gracze:");
    id.setCharacterSize(60 * sc.y);
    id.setFont(czcionka);
    id.setPosition(wsp_x * pos.x(35) - 200, wsp_y * pos.y(50) - 80);
    id.setFillColor({ 77, 0, 0 });

    sf::Text id_c;
    id_c.setString("Podaj IP serwera:");
    id_c.setCharacterSize(60 * sc.y);
    id_c.setFont(czcionka);
    id_c.setPosition(wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 80);
    id_c.setFillColor({ 77, 0, 0 });

    sf::Text plansza;
    plansza.setString("Jako tworzacy gre, wybierz kolor planszy:");
    plansza.setCharacterSize(60 * sc.y);
    plansza.setFont(czcionka);
    plansza.setPosition(wsp_x * pos.x(22), wsp_y * pos.y(58));
    plansza.setFillColor({ 77, 0, 0 });

    Textbox nick_enter(40, sf::Color(77, 0, 0), false, 400, sf::Vector2f{ wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 10 }, sf::Color(204, 204, 204));
    nick_enter.setLimit(true, 15);
    nick_enter.setFont(czcionka);

    Textbox IP_enter(40, sf::Color(77, 0, 0), false, 400, sf::Vector2f{ wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 10 }, sf::Color(204, 204, 204));
    IP_enter.setLimit(true, 15);
    IP_enter.setFont(czcionka);

    Textbox IP_enter_c(40, sf::Color(77, 0, 0), false, 400, sf::Vector2f{ wsp_x * pos.x(50) - 200, wsp_y * pos.y(50) - 10 }, sf::Color(204, 204, 204));
    IP_enter_c.setLimit(true, 15);
    IP_enter_c.setFont(czcionka);

    Klik_Kolo zielony(30.f, sf::Vector2f{ wsp_x * pos.x(27), wsp_y * pos.y(67)}, sf::Color(179, 255, 218));
    Klik_Kolo niebieski(30.f, sf::Vector2f{ wsp_x * pos.x(47), wsp_y * pos.y(67)}, sf::Color(153, 235, 255));
    Klik_Kolo rozowy(30.f, sf::Vector2f{ wsp_x * pos.x(67), wsp_y * pos.y(67)}, sf::Color(255, 230, 255));
    Klik_Kolo_Button back(sf::Vector2f{ wsp_x * pos.x(5), wsp_y * pos.y(5) }, "\grafiki/button_back.png");
    zielony.setOutlineColor(sf::Color(0, 0, 0));
    niebieski.setOutlineColor(sf::Color(0, 0, 0));
    rozowy.setOutlineColor(sf::Color(0, 0, 0));
    back.setOutlineColor(sf::Color::Black);
    back.setSize(sf::Vector2f{20.f, 20.f});


    // dwa stany okna 
    // 1 okno wstêpne
    // 2 onko wpisywania adresu ip 
    int state = 0;

    


    button b1(szer, wys, sf::Vector2f(600.f, 160.f), sf::Vector2f(30,75), "\grafiki/button_stworz.jpg", "\grafiki/button_stworz2.jpg");
    button b2(szer, wys, sf::Vector2f(600.f,160.f), sf::Vector2f(70,75),"\grafiki/button_dolacz.jpg", "\grafiki/button_dolacz2.jpg");
    button b3(szer, wys, sf::Vector2f(600.f, 160.f), sf::Vector2f(50, 74),"\grafiki/button_dolacz.jpg", "\grafiki/button_dolacz2.jpg");
    button b4(szer, wys, sf::Vector2f(600.f, 160.f), sf::Vector2f(50, 87), "\grafiki/button_stworz.jpg", "\grafiki/button_stworz2.jpg");

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
                    if (!nick_enter.getText().empty())
                    {
                        if (!IP_enter_c.getText().empty())
                        {
                            this->Dane->Stworz_Mnie(nick_enter.getText(), IP_enter_c.getText(), 0);
                            return;
                        }
                    }
                }
                if (IP_enter_c.event(event) == true)
                {
                    std::cout << "nacisnieto textbox\n";
                }
                if (back.event(event) == true)
                {
                    state = 0;
                    std::cout << "nacisnieto klawisz wroc\n";
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
                    kolor = Zielona;
                }
                if (niebieski.event(event) == true)
                {
                    std::cout << "nacisnieto niebieski";
                    zielony.setSelected(false);
                    rozowy.setSelected(false);
                    kolor = Niebieska;
                }
                if (rozowy.event(event) == true)
                {
                    std::cout << "nacisnieto rozowy";
                    zielony.setSelected(false);
                    niebieski.setSelected(false);
                    kolor = Rozowa;
                }
                if (b4.event(event) == true)
                {
                    std::cout << "nacisnieto klawisz stworz gre\n";
                    if (!IP_enter.getText().empty())
                    {
                        if (!nick_enter.getText().empty())
                        {
                            if (kolor != Brak)
                            {
                                this->Dane->Stworz_Mnie(nick_enter.getText(), IP_enter.getText(), 1, kolor);
                                return;
                            }
                        }
                    }
                   
                }
                if (back.event(event) == true)
                {
                    state = 0;
                    std::cout << "nacisnieto klawisz wroc\n";
                }
            }

        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(backgroud);
        if (state == 0)
        {
            nick_enter.drawTo(window);
            window.draw(nick);

            b1.drawTo(window);
            b2.drawTo(window);

        }
        else if (state == 1)
        {
            b3.drawTo(window);
            IP_enter_c.drawTo(window);
            window.draw(id_c);
            back.drawTo(window);
        }
        else if (state == 2)
        {
            IP_enter.drawTo(window);
            window.draw(id);
            zielony.drawTo(window);
            niebieski.drawTo(window);
            rozowy.drawTo(window);
            window.draw(plansza);
            b4.drawTo(window);
            back.drawTo(window);
        }
        // end the current frame
        window.display();
    }
}



Interfejs::Interfejs(BazaDanych* res) : Dane(res)
{
    PoleGry = nullptr;
    MainWindow = nullptr;
}
Interfejs::~Interfejs()
{
    DeleteMainWindow();
    DeletePlansza();
}



void Interfejs::CreateMainWindow()
{
    MainWindow = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width - WIDTH_MIN, sf::VideoMode::getDesktopMode().height - HEIGHT_MIN), "Monopoly");
    MainWindow->setFramerateLimit(60);
}
void Interfejs::DeleteMainWindow()
{
    delete MainWindow;
    MainWindow = nullptr;
}

bool Interfejs::IsOpen()
{
    return MainWindow->isOpen();
}

void Interfejs::MainFunction()
{
    if (MainWindow->isOpen())
    {
        EventFunction();
        DrawFunction();
    }
}

void Interfejs::EventFunction()
{
    sf::Event event;
    while (MainWindow->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            MainWindow->close();
    }
}

void Interfejs::DrawFunction()
{
    MainWindow->clear(sf::Color::Blue);
    if (PoleGry)
    {
        PoleGry->render();
        MainWindow->draw(*PoleGry);
    }
    MainWindow->display();
}

void Interfejs::CreatePlansza(std::string file)
{
    PoleGry = new Plansza(file);
    Resolution pos;
    sf::Vector2f sc = pos.scale();  // wektor skalowania
    PoleGry->setScale(sc.x, sc.y);     // ustawienie skali wielkoœci tekstury
}
void Interfejs::DeletePlansza()
{
    delete PoleGry;
    PoleGry = nullptr;
}

void Interfejs::CreateButtons()
{

}
void Interfejs::CreateTextbar()
{

}

void Interfejs::CreateMessageWindow(std::string tekst)
{
    float szer = sf::VideoMode::getDesktopMode().width;
    float wys = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(
        sf::VideoMode(szer - szer / 1.5f, wys - wys / 1.4f),
        "Informacja dla urzytkownika",
        sf::Style::None
        );

    window.setFramerateLimit(60);
   
    //tutaj button i tekstbar

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // tutaj event buttona zamykajacy to okno
        }
        // clear the window with black color
        window.clear(sf::Color::Cyan);

        // draw everything here...


        // end the current frame
        window.display();
    }
}