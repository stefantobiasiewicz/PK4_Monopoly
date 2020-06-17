#pragma once
#include <SFML/Network.hpp>

#define WIEZIENIE "WIEZIENIE"
#define CZYNSZ "CZYNSZ"
#define USUN "USUN"
#define CZYNSZZASTAW "CZYNSZZASTAW"
#define BRAKZAKUPU "BRAKZAKUPU"
#define KUPIONO "KUPIONO"
#define NASTEPNY "NASTEPNY"
#define PIERWSZY "PIERWSZY"

class Protokol
{
protected:
	sf::Packet pakiet;
	Protokol() {}
	Protokol(sf::Packet& otrzymany_pakiet);
	~Protokol() {}
	virtual void rozpakuj() {}
public:
	sf::Packet getPakiet();
};

class Packet_Wiezienie : public Protokol
{
	int liczba_kolejek;

	virtual void rozpakuj();

public:
	Packet_Wiezienie(int liczba_kolejek_do_odczekania);
	Packet_Wiezienie(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Wiezienie() {}
	int getLiczbaKolejek();
};

class Packet_Czynsz_Zap : public Protokol
{
	int numer_pola;
	std::string nick_platnika;
	std::string nick_wlasciciela;
	int kwota;
	int portfel;

	virtual void rozpakuj();

public:
	Packet_Czynsz_Zap(int numer_pola, int portfel, std::string nick_plat, std::string nick_odb, int kwota);
	Packet_Czynsz_Zap(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Czynsz_Zap() {}
	std::string getNickPlatnika();
	std::string getNickOdbiorcy();
	int getKwota();
	int getNumerPola();
	int getPortfel();
};

class Packet_Usun : public Protokol
{
	int numer_pola;
	std::string nick;

	virtual void rozpakuj();

public:
	Packet_Usun(int numer_pola, std::string nick);
	Packet_Usun(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Usun() {}
	std::string getNick();
	int getNumerPola();
};

class Packet_Czynsz_Zastaw : public Protokol
{
	int numer_pola;
	std::string nick_platnika;
	std::string nick_odbiorcy;
	int kwota;
	std::vector<std::string> nazwy_ulic;
	int liczba_ulic;
	int portfel;

	virtual void rozpakuj();

public:
	Packet_Czynsz_Zastaw(int numer_pola, int portfel, std::string nick_platnika, int kwota, std::string nick_odbiorcy, std::vector<std::string>nazwy_ulic);
	Packet_Czynsz_Zastaw(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Czynsz_Zastaw() {}
	
	std::string getNickPlatnika();
	std::string getNickOdbiorcy();
	int getNumerPola();
	int getKwota();
	std::vector<std::string> getNazwyUlic();
	int getLiczbaUlic();
	int getPortfel();


};

class Packet_Brak_Zakupu : public Protokol
{
	int numer_pola;
	int portfel;

	virtual void rozpakuj();

public:
	Packet_Brak_Zakupu(int numer_pola, int portfel);
	Packet_Brak_Zakupu(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Brak_Zakupu() {}

	int getNumerPola();
	int getPortfel();

};

class Packet_Kupiono : public Protokol
{
	int numer_pola;
	std::string nick_nabywcy;
	std::string nazwa_nieruchomosci;
	int portfel;


	virtual void rozpakuj();

public:
	Packet_Kupiono(int numer_pola, int portfel, std::string nick, std::string nazwa);
	Packet_Kupiono(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Kupiono() {}

	int getNumerPola();
	std::string getNickNabywcy();
	std::string getNazwaNieruchomosci();
	int getPortfel();

};

class Packet_Nastepny : public Protokol
{

	std::string nastepny;
	virtual void rozpakuj();

public:
	Packet_Nastepny(std::string nick_nastepnego);
	Packet_Nastepny(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Nastepny() {}

	std::string GetNastepny();

};

class Packet_Pierwszy : public Protokol
{

	int portfel;
	int numer_pola_domy;
	int liczba_domow;
	int liczba_ulic;
	std::vector<std::string> nazwy_ulic;


	virtual void rozpakuj();

public:
	Packet_Pierwszy(int portfel, int numer_pola_domy, int liczba_domow, std::vector<std::string>nazwy);
	Packet_Pierwszy(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Pierwszy() {}

	int getPortfel();
	int getNumerPolaDomy();
	int getLiczbaDomow();
	int getLiczbaUlic();
	std::vector<std::string> getNazwyUlic();

};