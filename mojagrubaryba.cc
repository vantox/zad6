#include "mojagrubaryba.h"
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

void sellout(shared_ptr<Player> const p)
{
	// cout << "sellout(" << p->getName() << ") called, player have: $" << p->getMoney() << endl;
	p->sellProperties();
}

int Player::getMoney() { return money; }

int Player::getWait() { return wait; }

void Player::setName(string _name)
{
	name = _name;
}

void Player::setMoney(int  _money)
{
	money = _money;
}

void Player::setWait(int _wait)
{
	wait = _wait;
}

int Player::takeMoney(int _money)
{
	if(money >= _money) {
		setMoney(money - _money);
		return _money;
	}
	else {
		//bierzemy tyle ile ma jeśli nie ma całości
		int tmp = money;
		bankrupt();
		return tmp;
	}
}

void Player::giveMoney(int _money)
{
	setMoney(money + _money);
}

void Player::bankrupt()
{
}

void Player::setPosition(int _position)
{
	position = _position;
}

string const& Player::getName() const 
{
	return name;
}

int Player::getPosition() const 
{ 
	return position;
}

void Player::addProperty(Nieruchomosc& property)
{
	properties.push_back(&property);
}

void Player::sellProperties()
{
	for(auto it = properties.begin(); it < properties.end(); it++)
	{
		cout << getName() << " owns " << (*it)->getName() << endl;
		bool b = wantSell((*it)->getName());
		cout << "and does" << (b ? "" : "n't") << " want to sell it" << endl;
		//TODO moze wydzielic to wszystko do jednej metody w nieruchomosci?
		if(b)
		{
			money += ((*it)->getPrice()) / 2;
			(*it)->deleteOwner();
			properties.erase(it);
		}
	}
}

unsigned int ComputerPlayer::numberOfCompPlayers = 0;

void ComputerPlayer::incrNumberOfCompPlayers()
{
	numberOfCompPlayers++;
}

unsigned int ComputerPlayer::getNumberOfCompPlayers()
{
	return numberOfCompPlayers;
}

// TODO polaczyc z dumbcomputer()
SmartAssComputer::SmartAssComputer()
{
	incrNumberOfCompPlayers();
	ostringstream tmp;
	tmp << "Gracz" << getNumberOfCompPlayers();
	setName(tmp.str());
	setMoney(MojaGrubaRyba::startMoney);
	setWait(0);
}

bool SmartAssComputer::wantBuy(std::string const& propertyName) { return true; }

bool SmartAssComputer::wantSell(std::string const& propertyName) { return true; }
// bool SmartAssComputer::wantSell(std::string const& propertyName) { return false; } FIXME

DumbComputer::DumbComputer()
{
	incrNumberOfCompPlayers();
	ostringstream tmp;
	tmp << "Gracz" << getNumberOfCompPlayers();
	setName(tmp.str());
	setMoney(MojaGrubaRyba::startMoney);
	setWait(0);
}

bool DumbComputer::wantBuy(std::string const& propertyName) { return (movesNumber % 3) == 0; }

bool DumbComputer::wantSell(std::string const& propertyName) { return false; }

HumanPlayer::HumanPlayer(std::shared_ptr<Human> human): humanPtr(human)
{
	setName(human->getName());
	setMoney(MojaGrubaRyba::startMoney);
	setWait(0);
}

bool HumanPlayer::wantBuy(std::string const& propertyName) { return humanPtr->wantBuy(propertyName); }

bool HumanPlayer::wantSell(std::string const& propertyName) { return humanPtr->wantSell(propertyName); }

//Field::Field(string _name) : name(_name) { }
Field::~Field()
{
	cout << "~Field() called\n";
}

string Field::getName() { return name; }

void Nieruchomosc::changeOwnedState(bool b)
{
	owned - b;
}

void Nieruchomosc::setOwner(shared_ptr<Player> const p)
{
	changeOwnedState(true);
	owner = p;
}

void Nieruchomosc::deleteOwner()
{
	changeOwnedState(false);
	setOwner(shared_ptr<Player>());
}

shared_ptr<Player> Nieruchomosc::getOwner()
{
	return owner;
}

int Nieruchomosc::getPrice()
{
	return price;
}

int Nieruchomosc::getCharge()
{
	return charge;
}

bool Nieruchomosc::getOwned()
{
	return owned;
}

Wyspa::Wyspa(const string& _name)
{
	name = _name;
}

void Wyspa::onStep(shared_ptr<Player> const p)
{
	
}

void Wyspa::onStop(shared_ptr<Player> const p)
{

	
}

Start::Start(const string& _name)
{
	name = _name;
}

void Start::onStep(shared_ptr<Player> const p)
{
	p->giveMoney(50);
}

void Start::onStop(shared_ptr<Player> const p)
{
	p->giveMoney(50);
}

Depozyt::Depozyt(const string& _name) : gatheredMoney(0)
{
	name = _name;
}

void Depozyt::onStep(shared_ptr<Player> const p)
{
	gatheredMoney += p->takeMoney(15);
	cout << "Depozyt" << endl;
	sellout(p);
}

void Depozyt::onStop(shared_ptr<Player> const p)
{
	p->giveMoney(gatheredMoney);
	gatheredMoney = 0;
}

Nagroda::Nagroda(const string& _name, int _prize) : prize(_prize)
{
	name = _name;
}

void Nagroda::onStep(shared_ptr<Player> const p)
{
}

void Nagroda::onStop(shared_ptr<Player> const p)
{
	p->giveMoney(prize);
}

Kara::Kara(const string& _name, int _fine) : fine(_fine)
{
	name = _name;
}

void Kara::onStep(shared_ptr<Player> const p)
{
}

void Kara::onStop(shared_ptr<Player> const p)
{
	p->takeMoney(fine);
	cout << "Kara" << endl;
	sellout(p);
}

Akwarium::Akwarium(const string& _name, int _rounds) : rounds(_rounds)
{
	name = _name;
}

void Akwarium::onStep(shared_ptr<Player> const p)
{
}

void Akwarium::onStop(shared_ptr<Player> const p)
{
	p->setWait(rounds);
}

Koralowiec::Koralowiec(const string& _name, int _price)
{
	name = _name;
	charge = _price / 5;
	owned = false;
	owner = nullptr;
	price = _price;
}

Publiczny::Publiczny(const string& _name, int _price)
{
	name = _name;
	charge = _price * 2 / 5;
	owned = false;
	owner = nullptr;
	price = _price;
}

void Nieruchomosc::onStep(shared_ptr<Player> const p)
{
}

void Nieruchomosc::onStop(shared_ptr<Player> const p)
{
	if(owned) {
		owner->giveMoney(p->takeMoney(charge));
		//FIXME gracz A ma $100, po wejsciu ma oddac $200, ale nie posiada nieruchomosci
		//wiec wlasciciel powinien otrzymac $100, afaik mamy oddawanie pelnej kwoty
		cout << "Nieruchomosc" << endl;
		sellout(p);
	}
	else {
		if(p->getMoney() >= price) {
			if(p->wantBuy(getName())) {
				p->takeMoney(price);
				p->addProperty(*this);
				setOwner(p);
			}
		}
	}
}
		
Board::Board()
{
	/*
	 * 1. Start
	2. Anemonia
	* Koralowiec (ukwiał Anemonia), cena kupna 160
	3. Wyspa
	* Odpoczywasz na wyspie, nic się nie dzieje
	4. Aporina
	* Koralowiec (koral madreporowy Aporina), cena kupna 220
	5. Akwarium
	* Akwarium: wpadłeś do akwarium, czekasz 3 kolejki
	6. Grota
	* Obiekt użyteczności publicznej (hotel w zacisznej grocie), cena kupna 300
	7. Menella
	* Koralowiec (gorgonia Menella), cena kupna 280
	8. Laguna
	* Depozyt: przy przechodzeniu gubisz 15 rybkoinów; przy zatrzymaniu znajdujesz wszystkie zgubione rybkoiny
	9. Statek
	* Obiekt użyteczności publicznej (restauracja we wraku statku), cena kupna 250
	10. Blazenki
	* Nagroda: dostajesz wypłatę 120 rybkoinów
	11. Pennatula
	* Koralowiec (pióro morskie Pennatula), cena kupna 400
	12. Rekin
	* Kara: spotykasz rekina biznesu, żeby umknąć z życiem płacisz 180 rybkoinów
	*/

	cout << "Board() called\n";
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Start>(new Start("Start"))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Koralowiec>(new Koralowiec("Anemonia", 160))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa("Wyspa"))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Koralowiec>(new Koralowiec("Aporina", 220))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Akwarium>(new Akwarium("Akwarium", 3))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Publiczny>(new Publiczny("Grota", 300))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Koralowiec>(new Koralowiec("Menella", 280))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Depozyt>(new Depozyt("Laguna"))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Publiczny>(new Publiczny("Statek", 250))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Nagroda>(new Nagroda("Blazenki", 120))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Koralowiec>(new Koralowiec("Pennatula", 400))));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Kara>(new Kara("Rekin", 180))));
	
}

Board::~Board()
{
	cout << "~Board() called\n";
}

int Board::getMaxField() { return maxField; }
shared_ptr<Field> Board::getField(int nr) { return fields[nr]; }

MojaGrubaRyba::MojaGrubaRyba() : realPlayers(0), compPlayers(0)
{
	cout << "MojaGrubaRyba() called\n";

}

MojaGrubaRyba::~MojaGrubaRyba()
{
	cout << "~MojaGrubaRyba() called\n";
}

// Poziom gry komputera:
// DUMB - kupuje co trzecie pole, na którym stanie i jest możliwe do kupienia;
// SMARTASS - kupuje wszystkie pola, na których stanie i są możliwe do kupienia.

// Przekazuje prototypową kostkę do gry.
// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
void MojaGrubaRyba::setDie(std::shared_ptr<Die> _die)
{
	if(!_die)
		return;
	cout << "MojaGrubaRyba::setDie(...) called\n";
	die = _die;
}

// Dodaje nowego gracza komputerowego, który gra na zdefiniowanym poziomie.
// Nowy gracz komputerowy nazywa się Gracz<Numer>, gdzie <Numer> to numer pozycji,
// na której został dodany (numeracja pozycji od 1).
// TODO Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
void MojaGrubaRyba::addComputerPlayer(ComputerLevel level)
{
	if(level == GrubaRyba::ComputerLevel::DUMB)
		MojaGrubaRyba::players.push_back(dynamic_pointer_cast<Player>( shared_ptr<DumbComputer>(new DumbComputer())));

	if(level == GrubaRyba::ComputerLevel::SMARTASS)
		MojaGrubaRyba::players.push_back(dynamic_pointer_cast<Player>( shared_ptr<SmartAssComputer>(new SmartAssComputer())));

	MojaGrubaRyba::compPlayers++;

	cout << "players.size() = " << MojaGrubaRyba::players.size() << endl;
	cout << "MojaGrubaRyba::addComputerPlayer(...) called\n";
	cout << "name: " << (MojaGrubaRyba::players.back())->getName() << endl;
}

// Dodaje nowego gracza czlowieka.
// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
// TODO Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
void MojaGrubaRyba::addHumanPlayer(std::shared_ptr<Human> human)
{
	MojaGrubaRyba::players.push_back(dynamic_pointer_cast<Player>(shared_ptr<HumanPlayer>(new HumanPlayer(human))));
	MojaGrubaRyba::realPlayers++;
	cout << "players.size() = " << MojaGrubaRyba::players.size() << endl;
	cout << "MojaGrubaRyba::addHumanPlayer(...) called\n";
	//FIXME tutaj się sypie
	cout << "name: " << (MojaGrubaRyba::players.back())->getName() << endl;
}

// Przeprowadza rozgrywkę co najwyżej podanej liczby rund (rozgrywka może
// skończyć się wcześniej).
// Jedna runda obejmuje po jednym ruchu każdego gracza.
// Gracze ruszają się w kolejności, w której zostali dodani.
// Na początku każdej rundy wypisywany jest numer rundy,
// a na zakończenie informacje podsumowujące dla każdego gracza (format w przykładzie).
// TODO Rzuca NoDieException, jeśli nie przekazano kostki.
// TODO Rzuca TooFewPlayersException, jeśli liczba graczy nie pozwala na rozpoczęcie gry.
void MojaGrubaRyba::play(unsigned int rounds)
{
	cout << "MojaGrubaRyba::play(" << rounds << ") called\n";
	unsigned int roundNumber = 1;

	while(rounds >= roundNumber)
	{
		cout << "Runda: " << roundNumber << "-------------------------------------\n";
		int rolls;
		for(auto it : players)
		{
			if(!it->getWait()) {

				rolls = die->roll() + die->roll();

				for(int i = 1; i < rolls; i++)
					board.getField((it->getPosition() + i) % board.getMaxField())->onStep(it);

				it->setPosition((it->getPosition() + rolls) % board.getMaxField());

				board.getField(it->getPosition())->onStop(it);
			}
			if(!it->getWait()) {
				cout << it->getName() << " pole: " << board.getField(it->getPosition())->getName() << "("<<it->getPosition() << ")" << " gotowka: " << it->getMoney() << "\n";
				//cout << "Rolls: " << rolls << "\n";
			}
			else {
				cout << it->getName() << " pole: " << board.getField(it->getPosition())->getName() << "("<<it->getPosition() << ")" << " *** czekanie: " << it->getWait() << " ***\n";
				it->setWait(it->getWait() - 1);
			}
		}
		roundNumber++;
	}

}
