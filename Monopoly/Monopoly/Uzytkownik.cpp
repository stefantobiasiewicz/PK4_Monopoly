#include "Uzytkownik.h"


Uzytkownik::Uzytkownik(std::string nick)
{
	this->nick = nick;
	this->numer_pola = 0;
	this->portfel = 1500;
}

bool Uzytkownik::CzyMaKarte(std::string karta)
{
    for (int i = 0; i < this->karty_nieruchomosci.size(); i++)
    {
        if (this->karty_nieruchomosci[i] == karta)
        {
            return true;
        }
    }
    return false;
}

void Uzytkownik::UsunKarte(std::string karta)
{
    for (int i = 0; i < this->karty_nieruchomosci.size(); i++)
    {
        if (this->karty_nieruchomosci[i] == karta)
        {
            this->karty_nieruchomosci.erase(this->karty_nieruchomosci.begin() + i);
        }
    }
}