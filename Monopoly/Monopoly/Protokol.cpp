#include "Protokol.h"

sf::Packet Protokol::getPakiet()
{
	return this->pakiet;
}

Protokol::Protokol(sf::Packet& otrzymany_pakiet)
{
	pakiet = otrzymany_pakiet;
//	this->rozpakuj();
}


Packet_Wiezienie::Packet_Wiezienie(int liczba_kolejek_do_odczekania) : Protokol()
{
	pakiet << WIEZIENIE;
	pakiet << liczba_kolejek_do_odczekania;
}

int Packet_Wiezienie::getLiczbaKolejek()
{
	return liczba_kolejek;
}

void Packet_Wiezienie::rozpakuj()
{
	pakiet >> liczba_kolejek;
}

Packet_Czynsz_Zap::Packet_Czynsz_Zap(int numer_pola, int portfel, std::string nick_plat, std::string nick_odb, int kwota)
{
	pakiet << CZYNSZ;
	pakiet << numer_pola;
	pakiet << portfel;
	pakiet << nick_plat;
	pakiet << kwota;
	pakiet << nick_odb;
}

void Packet_Czynsz_Zap::rozpakuj()
{
	pakiet >> numer_pola;
	pakiet >> portfel;
	pakiet >> nick_platnika;
	pakiet >> kwota;
	pakiet >> nick_wlasciciela;
}

int Packet_Czynsz_Zap::getPortfel()
{
	return portfel;
}


std::string Packet_Czynsz_Zap::getNickPlatnika()
{
	return nick_platnika;
}

std::string Packet_Czynsz_Zap::getNickOdbiorcy()
{
	return nick_wlasciciela;
}
int Packet_Czynsz_Zap::getKwota()
{
	return kwota;
}
int Packet_Czynsz_Zap::getNumerPola()
{
	return numer_pola;
}

Packet_Usun::Packet_Usun(int numer_pola, std::string nick)
{
	pakiet << USUN;
	pakiet << numer_pola;
	pakiet << nick;
}

std::string Packet_Usun::getNick()
{
	return nick;
}

int Packet_Usun::getNumerPola()
{
	return numer_pola;
}

void Packet_Usun::rozpakuj()
{
	pakiet >> numer_pola;
	pakiet >> nick;
}

Packet_Czynsz_Zastaw::Packet_Czynsz_Zastaw(int numer_pola, int portfel, std::string nick_platnika, int kwota, std::string nick_odbiorcy, std::vector<std::string>nazwy_ulic)
{
	pakiet << CZYNSZZASTAW;
	pakiet << numer_pola;
	pakiet << portfel;
	pakiet << nick_platnika;
	pakiet << kwota;
	pakiet << nick_odbiorcy;
	pakiet << nazwy_ulic.size();
	for (int i = 0; nazwy_ulic.size(); i++)
	{
		pakiet << nazwy_ulic[i];
	}
}

void Packet_Czynsz_Zastaw::rozpakuj()
{
	pakiet >> numer_pola;
	pakiet >> portfel;
	pakiet >> nick_platnika;
	pakiet >> kwota;
	pakiet >> nick_odbiorcy;
	pakiet >> liczba_ulic;
	for (int i = 0; i < liczba_ulic; i++)
	{
		std::string temp;
		pakiet >> temp;
		this->nazwy_ulic.push_back(temp);
	}
}

std::string Packet_Czynsz_Zastaw::getNickPlatnika()
{
	return nick_platnika;
}

std::string Packet_Czynsz_Zastaw::getNickOdbiorcy()
{
	return nick_odbiorcy;
}

int Packet_Czynsz_Zastaw::getNumerPola()
{
	return numer_pola;
}

int Packet_Czynsz_Zastaw::getKwota()
{
	return kwota;
}

std::vector<std::string> Packet_Czynsz_Zastaw::getNazwyUlic()
{
	return nazwy_ulic;
}

int Packet_Czynsz_Zastaw::getLiczbaUlic()
{
	return liczba_ulic;
}

int Packet_Czynsz_Zastaw::getPortfel()
{
	return portfel;
}


Packet_Brak_Zakupu::Packet_Brak_Zakupu(int numer_pola, int portfel)
{
	pakiet << BRAKZAKUPU;
	pakiet << numer_pola;
	pakiet << portfel;
}


void Packet_Brak_Zakupu::rozpakuj()
{
	pakiet >> numer_pola;
	pakiet >> portfel;
}

int Packet_Brak_Zakupu::getNumerPola()
{
	return numer_pola;
}

int Packet_Brak_Zakupu::getPortfel()
{
	return portfel;
}


Packet_Kupiono::Packet_Kupiono(int numer_pola, int portfel, std::string nick, std::string nazwa)
{
	pakiet << KUPIONO;
	pakiet << numer_pola;
	pakiet << portfel;
	pakiet << nick;
	pakiet << nazwa;
}

int Packet_Kupiono::getNumerPola()
{
	return numer_pola;
}

std::string Packet_Kupiono::getNickNabywcy()
{
	return nick_nabywcy;
}

std::string Packet_Kupiono::getNazwaNieruchomosci()
{
	return nazwa_nieruchomosci;
}

int Packet_Kupiono::getPortfel()
{
	return portfel;
}


void Packet_Kupiono::rozpakuj()
{
	pakiet >> numer_pola;
	pakiet >> portfel;
	pakiet >> nick_nabywcy;
	pakiet >> nazwa_nieruchomosci;
}


Packet_Nastepny::Packet_Nastepny(std::string nick_nastepnego)
{
	pakiet << NASTEPNY;
	pakiet << nick_nastepnego;
}

void Packet_Nastepny::rozpakuj()
{
	pakiet >> nastepny;
}

std::string Packet_Nastepny::GetNastepny()
{
	return this->nastepny;
}

Packet_Pierwszy::Packet_Pierwszy(int portfel, int numer_pola_domy, int liczba_domow, std::vector<std::string>nazwy)
{
	pakiet << PIERWSZY;
	pakiet << portfel;
	pakiet << numer_pola_domy;
	pakiet << liczba_domow;
	pakiet << nazwy.size();
	for (int i = 0; i < nazwy.size(); i++)
	{
		pakiet << nazwy[i];
	}
}

void Packet_Pierwszy::rozpakuj()
{
	pakiet >> portfel;
	pakiet >> numer_pola_domy;
	pakiet >> liczba_domow;
	pakiet >> liczba_ulic;
	for (int i = 0; i < liczba_ulic; i++)
	{
		std::string temp;
		pakiet >> temp;
		nazwy_ulic.push_back(temp);
	}
}

int Packet_Pierwszy::getPortfel()
{
	return portfel;
}
int Packet_Pierwszy::getNumerPolaDomy()
{
	return numer_pola_domy;
}
int Packet_Pierwszy::getLiczbaDomow()
{
	return liczba_domow;
}
int Packet_Pierwszy::getLiczbaUlic()
{
	return liczba_ulic;
}
std::vector<std::string> Packet_Pierwszy::getNazwyUlic()
{
	return nazwy_ulic;
}














