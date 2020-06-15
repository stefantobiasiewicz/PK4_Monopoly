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
    // 1 okno wst�pne
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
                if (nick_enter.event(event) == true)  //naci�ni�to textbox
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
    DeleteButtons();
    DeleteSprites();
}



void Interfejs::CreateMainWindow()
{
    MainWindow = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width - WIDTH_MIN, sf::VideoMode::getDesktopMode().height - HEIGHT_MIN), "Monopoly");
    MainWindow->setFramerateLimit(60);
    this->CreateButtons();
    this->CreateSprites();
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
        EventFunction(*this->opcjegry);
        UpdateFunction();
        DrawFunction();
    }
}

void Interfejs::EventFunction(OpcjeGry& opcje)
{
    sf::Event event;
    while (MainWindow->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            MainWindow->close();
        // skalowanie
        EventScaleMouse(event);
        // obsluga klawiszy
        ExecuteButtons(event, opcje);
    }
}
void Interfejs::EventScaleMouse(sf::Event& event)
{
    if (event.type == sf::Event::Resized)
    {
        factorX = (float)event.size.width / Szer;
        factorY = (float)event.size.height / Wys;
    }
    if (event.type == sf::Event::MouseMoved)
    {
        event.mouseMove.x /= factorX;
        event.mouseMove.y /= factorY;
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        event.mouseButton.x /= factorX;
        event.mouseButton.y /= factorY;
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
    //rysowanie wszystkich ksztaltow
    DrawSprites(*MainWindow);

    //rysowanie wszyskich klawiszy
    DrawButtons(*MainWindow);

    MainWindow->display();
}

void Interfejs::UpdateFunction()
{

    std::map<std::string, Uzytkownik>::iterator it = Dane->gracze.begin();
    int i = 0;
    for (it; it != Dane->gracze.end(); it++ )
    {
        miniatury[i]->ClearObject();
        for (std::string i_k : it->second.karty_nieruchomosci)
        {
            miniatury[i]->SetObject(&Dane->karty_nieruchomosci[i_k]->Miniatura);
        }
        i++;
    }
}

void Interfejs::CreatePlansza(std::string file)
{
    PoleGry = new Plansza(file);
 //   Resolution pos;
 //   sf::Vector2f sc = pos.scale();  // wektor skalowania
//   PoleGry->setScale(sc.x, sc.y);     // ustawienie skali wielko�ci tekstury
}
void Interfejs::DeletePlansza()
{
    delete PoleGry;
    PoleGry = nullptr;
}

void Interfejs::CreateButtons()
{
    Resolution res;
    sf::Vector2f scale = res.scale();
    // tu tworza sie wszyskie przyciski

    // przyckisk kupowania domku 
    Klik_Kolo_Button *kup_domek = new Klik_Kolo_Button(sf::Vector2f( res.x(56.82f) , res.y(5) ), "\grafiki/button_dom.png", "\grafiki/button_dom2.png");
    kup_domek->setSize({ scale.x * 100.f, scale.y * 100.f });
    KlikObject["zakup_domku"] = kup_domek;

    // przycisk kupowania hotelu 
    Klik_Kolo_Button* kup_hotel = new Klik_Kolo_Button(sf::Vector2f( res.x(56.82f) , res.y(17) ), "\grafiki/button_hotel.png", "\grafiki/button_hotel2.png");
    kup_hotel->setSize({ scale.x * 100.f, scale.y * 100.f });
    KlikObject["zakup_hotelu"] = kup_hotel;

    // przycisk zastawu
    button* zastaw = new button(sf::Vector2f{170,170}, sf::Vector2f{ 59.34f, 33 }, "\grafiki/button_zastaw.jpg", "\grafiki/button_zastaw2.jpg");
    KlikObject["zastaw"] = zastaw;

    // przycisk rzutu kostka
    button* kostki = new button(sf::Vector2f{170,170}, sf::Vector2f{ 59.34f, 43 }, "\grafiki/unnamed.png", "\grafiki/unnamed2.png");
    KlikObject["kostki"] = kostki;
}
void Interfejs::DeleteButtons()
{
    for (auto i : KlikObject)
    {
        delete i.second;
    }
}
void Interfejs::ExecuteButtons(sf::Event &event, OpcjeGry& opcje)
{
    std::map<std::string, Klikalny*>::iterator it = KlikObject.begin();
    for (it; it!= KlikObject.end(); it++)
    {
        if (it->first == "zakup_domku")
        {
            opcje.zakup_domku = it->second->event(event);
        }
        else if (it->first == "zakup_hotelu")
        {
            opcje.zakup_hotelu = it->second->event(event);
        }
        else if (it->first == "zastaw")
        {
            opcje.zastaw = it->second->event(event);
        }
        else if (it->first == "kostki")
        {
            opcje.kostki = it->second->event(event);
        }
        else if (it->first == "karty1")
        {
            opcje.karty1 = it->second->event(event);
        }
        else if (it->first == "karty2")
        {
            opcje.karty2 = it->second->event(event);
        }
    }
}
void Interfejs::DrawButtons(sf::RenderWindow& window)
{
    for (auto i : KlikObject)
    {
        i.second->drawTo(window);
    }
}
void Interfejs::CreateSprites()
{
    Resolution res;
    sf::Vector2f scale = res.scale();
    sf::RectangleShape  *button_bar = new sf::RectangleShape;           //szary pasek z buttonami
    button_bar->setFillColor({179, 179, 179});
    button_bar->setSize({ scale.x * 240.f,scale.y * 2160.f });
    button_bar->setPosition(res.x(56.25f), 0.f);
    button_bar->setOutlineColor({ 0,0,0 });
    button_bar->setOutlineThickness(scale.x * 5.f);
    

    sf::RectangleShape* deska = new sf::RectangleShape;
    sf::Texture deska_t;
    
   
    MinKart* Miniatury;
    button* Przycisk;
    // stworzenie nickow graczy , oraz miniatura pionka
    int IloscGraczy = this->Dane->ilosc_graczy;
    switch (IloscGraczy)
    {
    case 2:
        if (!deska_t.loadFromFile("\grafiki/deska2.jpg"))
        {
            std::cerr << "Nie wczytano deski.\n";
        }
        Miniatury = new MinKart(scale.x * 1440.f, scale.y * 900);
        Miniatury->setPosition(res.x(63.5f), res.y(8));
        Miniatury->Wood();
        miniatury.push_back(Miniatury);
        Miniatury = new MinKart(scale.x * 1440.f, scale.y * 900);
        Miniatury->setPosition(res.x(63.5f), res.y(58));
        Miniatury->Wood();
        miniatury.push_back(Miniatury);
        

        Przycisk = new button({  1440.f, 900 }, { 82.25f ,28.83f }, "\grafiki/transparent21.png", "\grafiki/transparent2.png");
        KlikObject["karty1"] = Przycisk;
        Przycisk = new button({1440.f, 900 }, { 82.25f , 78.83f }, "\grafiki/transparent21.png", "\grafiki/transparent2.png");
        KlikObject["karty2"] = Przycisk;
        break;
    case 3:
        if (!deska_t.loadFromFile("\grafiki/deska3.jpg"))
        {
            std::cerr << "Nie wczytano deski.\n";
        }
        
        break;
    case 4:
        if (!deska_t.loadFromFile("\grafiki/deska4.jpg"))
        {
            std::cerr << "Nie wczytano deski.\n";
        }
        
        break;
    default:
        if (!deska_t.loadFromFile("\grafiki/deska2.jpg"))
        {
            std::cerr << "Nie wczytano deski.\n";
        }
        
        break;
    }
    this->tekstury.push_back(deska_t);
    deska->setTexture(&tekstury[0]);
    deska->setSize({ scale.x * deska_t.getSize().x, scale.y * deska_t.getSize().y });
    deska->setPosition(res.x(62.5f), 0.f);
    this->ksztalty.push_back(deska);
    this->ksztalty.push_back(button_bar);
    CreateUserStats();



}

void Interfejs::CreateUserStats()
{
    Resolution res;
    sf::Vector2f scale = res.scale();
    int IloscGraczy = this->Dane->ilosc_graczy;
    
    sf::Text* UserName = new sf::Text;

    sf::Text* UserMoney = new sf::Text;

    sf::CircleShape* UserPionek = new sf::CircleShape;

   



    //todo  iterowanie po mapie w celu zdob���a nicku i ustawienie wszystkich statystyk 
    std::map<std::string, Uzytkownik>::iterator it = this->Dane->gracze.begin();

    switch (IloscGraczy)
    {
    case 2:
        //statystyka gracza 1
        UserName->setFont(Dane->czcionka);
        UserName->setCharacterSize(scale.y * 60.f);
        UserName->setFillColor(sf::Color(140, 0, 0));
        UserName->setString(it->first);
        UserName->setPosition(res.x(67), res.y(1.2));
        UserName->setOutlineColor(sf::Color::White);
        UserName->setOutlineThickness(scale.x * 4.f);
        this->teksty.push_back(UserName);

        UserMoney->setFont(Dane->czcionka);
        UserMoney->setCharacterSize(scale.y * 60.f);
        UserMoney->setFillColor(sf::Color(140, 0, 0));
        UserMoney->setString("portfel: 1500 PLN");
        UserMoney->setPosition(res.x(67), res.y(3.5));
        UserMoney->setOutlineColor(sf::Color::White);
        UserMoney->setOutlineThickness(scale.x * 4.f);
        this->pieniadze[UserName->getString()] = UserMoney;

        UserPionek->setRadius(scale.x * 60.f);
        UserPionek->setTexture(this->Dane->gracze[UserName->getString()].pionek->getTexture());
        UserPionek->setPosition(res.x(63.), res.y(1.8));
        this->ksztalty.push_back(UserPionek);

        PoleGry->SetObject(Dane->gracze[UserName->getString()].pionek);
        Dane->gracze[UserName->getString()].pionek->setPosition(Dane->pola[0].pozycja[0]);

        UserName = new sf::Text;

        UserMoney = new sf::Text;

        UserPionek = new sf::CircleShape;

        it++;

        UserName->setFont(Dane->czcionka);
        UserName->setCharacterSize(scale.y * 60.f);
        UserName->setFillColor(sf::Color(140, 0, 0));
        UserName->setString(it->first);
        UserName->setPosition(res.x(67), res.y(50.9f));
        UserName->setOutlineColor(sf::Color::White);
        UserName->setOutlineThickness(scale.x * 4.f);
        this->teksty.push_back(UserName);

        UserMoney->setFont(Dane->czcionka);
        UserMoney->setCharacterSize(scale.y * 60.f);
        UserMoney->setFillColor(sf::Color(140, 0, 0));
        UserMoney->setString("portfel: 1500 PLN");
        UserMoney->setPosition(res.x(67), res.y(53.7f));
        UserMoney->setOutlineColor(sf::Color::White);
        UserMoney->setOutlineThickness(scale.x * 4.f);
        this->pieniadze[UserName->getString()] = UserMoney;

        UserPionek->setRadius(scale.x * 60.f);
        UserPionek->setTexture(this->Dane->gracze[UserName->getString()].pionek->getTexture());
        UserPionek->setPosition(res.x(63.), res.y(51.8));
        this->ksztalty.push_back(UserPionek);

        PoleGry->SetObject(Dane->gracze[UserName->getString()].pionek);
        Dane->gracze[UserName->getString()].pionek->setPosition(Dane->pola[0].pozycja[1]);

      
        break;
    case 3:
        
        break;
    case 4:
        
        break;
    default:
        
        break;
    }


}

void Interfejs::DeleteSprites()
{
    for (auto i : ksztalty)
    {
        delete i;
    }
    for (std::map<std::string, sf::Text*>::iterator it = pieniadze.begin(); it != pieniadze.end(); it++)
    {
        delete it->second;
    }
    for (auto i : teksty)
    {
        delete i;
    }
    for (auto i : miniatury)
    {
        delete i;
    }
}
void Interfejs::DrawSprites(sf::RenderWindow& window)
{
    for (auto i : ksztalty)
    {
        window.draw(*i);
    }
    for (auto i : teksty)
    {
        window.draw(*i);
    }
    for (std::map<std::string, sf::Text*>::iterator it = pieniadze.begin(); it != pieniadze.end(); it++)
    {

        window.draw(*it->second);
    }
    for (auto i : miniatury)
    {
        i->Render();
        window.draw(*i);
    }
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

void Interfejs::CreateCardsWindow(std::string nick)
{
    float szer = sf::VideoMode::getDesktopMode().width;
    float wys = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(
        sf::VideoMode(szer - szer / 2.5f, wys - wys / 3.75f),
        "Karty gracza " + nick
    );
    Resolution res;
    res.SetW_res(szer - szer / 2.5f);
    res.SetH_res(wys - wys / 3.75f);



    window.setFramerateLimit(60);

    sf::View perspektywa(sf::FloatRect(0,0, res.GetW_res(), res.GetH_res()));

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // tutaj event buttona zamykajacy to okno
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    //w gore
                    perspektywa.move(0, -10);
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    //w dol
                    perspektywa.move(0, 10);
                }
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Cyan);

        // draw everything here...
        window.setView(perspektywa);
        
        sf::Vector2f scale = res.scale();
        for (int i = 0; i < Dane->gracze[nick].karty_nieruchomosci.size(); i++)
        {
            Dane->karty_nieruchomosci[Dane->gracze[nick].karty_nieruchomosci[i]]->Duza_Karta.setPosition(i % 3 * res.x(33.33) + res.x(1), i / 3 * res.y(70));
            Dane->karty_nieruchomosci[Dane->gracze[nick].karty_nieruchomosci[i]]->Duza_Karta.setSize({1200.f * scale.x, 1500.f * scale.y});

            window.draw(Dane->karty_nieruchomosci[Dane->gracze[nick].karty_nieruchomosci[i]]->Duza_Karta);
        }


        // end the current frame
        window.display();
    }

}

void Interfejs::SetOpcjeGry(OpcjeGry* opcje)
{
    this->opcjegry = opcje;
}

void Interfejs::CreateWaitingWindow(Internet* internet)
{
    float szer = sf::VideoMode::getDesktopMode().width;
    float wys = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(
        sf::VideoMode(szer - szer / 1.5f, wys - wys / 1.6f),
        "Informacja dla uzytkownika"
        //sf::Style::None
    );

    window.setFramerateLimit(60);

    szer = szer - szer / 1.5f;
    wys = wys - wys / 1.6f;
    //tutaj button i tekstbar
    button Zakoncz(szer , wys, { 400, 130 }, {50,80}, "\grafiki/button_zakoncz.jpg", "\grafiki/button_zakoncz2.jpg");

    Resolution res;
    sf::Vector2f scale = res.scale();
    res.SetH_res(wys);
    res.SetW_res(szer);

    sf::Font Czcionka;
    if (!Czcionka.loadFromFile("BRLNSR.TTF"))
    {
        std::cerr << "nie zaladownao czcionki : \"BRLNSR.TTF\" \n";
    }

    sf::Text Info;
    Info.setFont(Czcionka);
    Info.setCharacterSize(60 * scale.y);
    Info.setPosition(res.x(15), res.y(5));
    Info.setFillColor(sf::Color::Black);
    Info.setString("Aby zakonczyc czekanie na graczy\n \t kliknij \"zakoncz czekanie\"\n\nPoloczeni gracze:");

    sf::Text Gracz1;
    Gracz1.setFont(Czcionka);
    Gracz1.setCharacterSize(60 * scale.y);
    Gracz1.setPosition(res.x(22), res.y(40));
    Gracz1.setFillColor(sf::Color::Black);
    Gracz1.setString("* ");

    sf::Text Gracz2;
    Gracz2.setFont(Czcionka);
    Gracz2.setCharacterSize(60 * scale.y);
    Gracz2.setPosition(res.x(22), res.y(49));
    Gracz2.setFillColor(sf::Color::Black);
    Gracz2.setString("* ");

    sf::Text Gracz3;
    Gracz3.setFont(Czcionka);
    Gracz3.setCharacterSize(60 * scale.y);
    Gracz3.setPosition(res.x(22), res.y(58));
    Gracz3.setFillColor(sf::Color::Black);
    Gracz3.setString("* ");
    
    std::vector<sf::Text*> users = { &Gracz1 , &Gracz2 , &Gracz3 };


    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            // tutaj event buttona zamykajacy to okno
            if(Zakoncz.event(event))
                window.close();
        }
        // poloczenia z klientami 
               
        if (internet->setConnection() == sf::Socket::Status::Done)
         {
            std::cout << "poloczono;\n";
         }
        sf::Packet nick;
        
        for (int i = 0; i < internet->getClientCount(); i++)
        {
            if (internet->Recive(nick, i))
            {
                std::string name;
                nick >> name;
                this->Dane->unikalne_nicki(name);    //zapezpieczenie przed wpisaniem takich samych nick�w
                nick.clear();
                nick << name;
                internet->Send(nick, i);
                Uzytkownik user(name);
                this->Dane->gracze[name] = user;
                users[i]->setString("* " + name);
                // odebralismy dane od gracza i stowrzylismy usera nalezy jeszcze wyslac mu plansze i pionka
            }
        }
  


        // clear the window with black color
        window.clear(sf::Color(179, 255, 230));

        // draw everything here...

        window.draw(Info);
        window.draw(Gracz1);
        window.draw(Gracz2);
        window.draw(Gracz3);


        Zakoncz.drawTo(window);

        // end the current frame
        window.display();
        if (this->Dane->gracze.size() == 4)
        {
            Sleep(1000);
            window.close();
        }
    }
}