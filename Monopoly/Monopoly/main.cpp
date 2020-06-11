#include <iostream>
#include <thread>



#include "Interfejs.h"
#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"

#include "Resolution.h"

#include "Internet.h"
#include "BazaDanych.h"
#include <chrono>
#include <Windows.h>

#include <conio.h>



#define WIDTH_MIN 0
#define HEIGHT_MIN 0

using namespace std;

int main()
{


    /*std::cout << "Monopoly\n\r";

    std::cout << "s - server , c - klijent\n";

    char type;
    std::cin >> type;

    if (type == 's')
    {
        Internet internet(type , sf::IpAddress::getLocalAddress());
        while (std::cin >> type)
        {
            internet.read();
            std::cout << internet.Packet_data.getData();
        }
    }
    else if (type == 'c')
    {
        Internet internet(type, sf::IpAddress::getLocalAddress());
        while (std::cin >> type)
        {
            std::cout << "wyslij cos \n";
            char data[32] = "dane wysylane    \n";
            data[15] = type;
            internet.Packet_data.append(data, 32);
            internet.write();
        }
    }


    return 0;
}*/

/*


    Interfejs gra;

//    gra.DrawThread();

    std::thread draw(&Interfejs::DrawThread , gra);

    draw.join();



    Obiekt_Na_Planszy obiekt("res/k.png", sf::Vector2f(200, 200));

    Plansza pole("res/p.png");

    pole.SetObject(&obiekt);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    std::cout << "left button\n";
                    pole.RemoveObject(&obiekt);

                }
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                {
                    std::cout << "right button\n";

                    pole.SetObject(&obiekt);
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        pole.render();

        window.draw(pole);

        // end the current frame
        window.display();
    }



    *******************************************************************************/



   /* std::cout << "podaj s to byc serverem ; c to byc klientem :";

    char serv;
    std::cin >> serv;

    if (serv == 's')
    {
        Internet internety(0, 64000);

        std::cout << "klijknij/uderz w kalwiature aby zatrzymac przyjmowanie klientow\n";
        while (!_kbhit())
        {
            if (internety.setConnection() == sf::Socket::Status::Done)
            {
                std::cout << "poloczono;\n";
            }
        }
        int liczbaKlientow = internety.getClientCount();
        std::cout << "liczba polaczonych klientow: " << liczbaKlientow << ";\n";
        for (int i = 0; i < liczbaKlientow; i++)
        {
            sf::Packet pakiet;
            pakiet << "hue hue\n" << 5 + i;
            internety.Send(pakiet, i);
        }

    }
    else
    {
        Internet internety(true, sf::IpAddress::getLocalAddress(), 64000);
        while (internety.setConnection() != sf::Socket::Status::Done)
        {
            cout << "proboje laczyc ponownie\n";
        }
        std::cout << "poloczono;\n";
        while (!_kbhit())
        {
            sf::Packet pakiet;
            if (internety.Recive(pakiet))
            {
                string s;
                int intrrr;
                pakiet >> s;
                pakiet >> intrrr;
                std::cout << "odebrano:" << s << "  " << intrrr;
            }

        }

    }*/
    /*
        else if (serv == 'c')
    {
        
        while (internety.setConnection() != sf::Socket::Status::Done)
        {
            internety.setConnection();
            std::cout << "lacze...\n";
        }
        cin >> serv;
        sf::Packet paket;
        int x = 0;
        paket << x;
        while (serv == 'a')
        {
            internety.Send(paket);
            std::cout << "podaj cyferke:";
            std::cin >> x;
            paket.clear();
            paket << x;
            cin >> serv;
        }
    }
    */




   // return 0;
    //*****************************************************************************
    BazaDanych Dorotka;
    Interfejs komunikacja(&Dorotka);

    komunikacja.StartWindow();

    return 0;

    BazaDanych baza;
    std::cout << sf::VideoMode::getDesktopMode().width - WIDTH_MIN << ", " << sf::VideoMode::getDesktopMode().height - HEIGHT_MIN << endl;

    sf::RenderWindow main_window(sf::VideoMode(sf::VideoMode::getDesktopMode().width - WIDTH_MIN, sf::VideoMode::getDesktopMode().height - HEIGHT_MIN), "Monopoly");
    main_window.setFramerateLimit(60);

    sf::Texture bg1;
    if (!bg1.loadFromFile("\grafiki/planszaG.jpg"))
        cout << "Nie otworzono tla 1." << endl;
    sf::Sprite bg1_s(bg1);

    sf::Texture pionek;
    if (!pionek.loadFromFile("\grafiki/pionek1.png"))
        cout << "Nie otworzono pionka." << endl;
    sf::Sprite pionek_s(pionek);

    sf::Texture pionek2;
    if (!pionek2.loadFromFile("\grafiki/pionek2.png"))
        cout << "Nie otworzono pionka." << endl;
    sf::Sprite pionek2_s(pionek2);

    sf::Texture pionek3;
    if (!pionek3.loadFromFile("\grafiki/pionek3.png"))
        cout << "Nie otworzono pionka." << endl;
    sf::Sprite pionek3_s(pionek3);

    sf::Texture pionek4;
    if (!pionek4.loadFromFile("\grafiki/pionek4.png"))
        cout << "Nie otworzono pionka." << endl;
    sf::Sprite pionek4_s(pionek4);

    Resolution pos;
    sf::Vector2f sc = pos.scale();  // wektor skalowania
    bg1_s.setScale(sc.x, sc.y);     // ustawienie skali wielkoœci tekstury
    pionek_s.setScale(sc.x, sc.y);
    pionek_s.setPosition(pos.x(baza.pola[18].pozycja[0].x), pos.y(baza.pola[18].pozycja[0].y));
    pionek2_s.setScale(sc.x, sc.y);
    pionek2_s.setPosition(pos.x(baza.pola[34].pozycja[1].x), pos.y(baza.pola[34].pozycja[1].y));
    pionek3_s.setScale(sc.x, sc.y);
    pionek3_s.setPosition(pos.x(baza.pola[18].pozycja[2].x), pos.y(baza.pola[18].pozycja[2].y));
    pionek4_s.setScale(sc.x, sc.y);
    pionek4_s.setPosition(pos.x(baza.pola[39].pozycja[3].x), pos.y(baza.pola[39].pozycja[3].y));
    int i = 0;

    sf::Event event;
    while (main_window.isOpen())
    {

        // Process events
        for (int i = 0; i < 40; i++)
        {
        while (main_window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                main_window.close();
        }
        
        // Clear screen
        main_window.clear();
        // Update the window
        main_window.draw(bg1_s);
        //home_s.setPosition(i * i * 1 / 26, 300);
        //i++;
        
        pionek_s.setPosition(pos.x(baza.pola[i].pozycja[0].x), pos.y(baza.pola[i].pozycja[0].y));
       
        pionek2_s.setPosition(pos.x(baza.pola[i].pozycja[1].x), pos.y(baza.pola[i].pozycja[1].y));
       
        pionek3_s.setPosition(pos.x(baza.pola[i].pozycja[2].x), pos.y(baza.pola[i].pozycja[2].y));
      
        pionek4_s.setPosition(pos.x(baza.pola[i].pozycja[3].x), pos.y(baza.pola[i].pozycja[3].y));
        
        main_window.draw(pionek_s);
        main_window.draw(pionek2_s);
        main_window.draw(pionek3_s);
        main_window.draw(pionek4_s);

        main_window.display();
        Sleep(1000);
        }
    }

 // BazaDanych baza;
 
  
   std::cout << baza.karty_nieruchomosci["ulica Wolska"]->nazwa;
   std::cout << baza.karty_nieruchomosci["ulica Konopacka"]->czynsze[0];
   std::cout << endl << baza.karty_szansa_kasa[15]->nazwa;
   std::cout << endl << baza.karty_nieruchomosci["Dworzec Gdanski"]->czynsze[3];
   std::cout << endl << baza.karty_nieruchomosci["Elektrownia"]->nazwa;
   std::cout << endl << baza.pola[5].nazwa;
    system("pause");
    return 0;

}





