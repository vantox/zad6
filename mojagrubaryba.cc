#include "mojagrubaryba.h"
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

bool debug = false;

int Player::getMoney()
{
	return money;
}

int Player::getWait()
{
	return wait;
}

bool Player::isPlayerActive()
{
	return isActive;
}

void Player::setName(string const& _name)
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
	// Gracz posiada dostateczna liczbe pieniedzy na splate dlugu
	if(money >= _money)
	{
		money -= _money;
		if(debug) cout << "Gracz " << getName() << " oddaje " << _money << endl;
		return _money;
	}
	// Spieniezamy majatek gracza
	sellProperties();
	if(money < _money)
		bankrupt();
	if(debug) cout << "Gracz " << getName() << " oddaje " << min(_money, money) << endl;
	return min(_money, money);
}

void Player::giveMoney(int _money)
{
	money += _money;
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

void Player::sellProperty(vector<Nieruchomosc*>::iterator it)
{
	if(debug) cout << "Gracz " << getName() << " sprzedaje " << (*it)->getName() << " z zyskiem " << ((*it)->getPrice()) / 2 << endl;
	money += ((*it)->getPrice()) / 2;
	(*it)->deleteOwner();
	properties.erase(it);
}

// Metoda sprzedajaca wszystkie nieruchomosci gracza
void Player::sellProperties()
{
	for(auto it = properties.begin(); it < properties.end(); it++)
	{
		// TODO po usunieciu kodu debugujacego usunac deklaracje bool b
		if(debug) cout << getName() << " owns " << (*it)->getName() << endl;
		bool b = wantSell((*it)->getName());
		if(debug) cout << "and does" << (b ? "" : "n't") << " want to sell it" << endl;
		if(b)
			sellProperty(it);
	}
}
// TODO bankructwo wszystkich graczy??
// TODO czy w przypadku bankructwa graczy na pewno chcemy zeby pieniadze wracaly do wlasciciela?
// Metoda odpowiadajaca za bankructwo gracza, iterujemy po wszystkich nieruchomosciach spieniezajac je
void Player::bankrupt()
{
	if(debug) cout << name << " bankrutuje" << endl;
	for(auto it = properties.begin(); it < properties.end(); it++)
		sellProperty(it);
	isActive = false;
}

Player::Player(int _money, int _wait, int _position) :
money(_money), wait(_wait), position(_position), isActive(true) { }

// TODO delegating constructors, czy to jest ok?
Player::Player( ): Player(0, 0, 0) { }

ComputerPlayer::ComputerPlayer(int nr) : Player()
{
	setMoney(MojaGrubaRyba::startMoney);
	ostringstream tmp;
	tmp << "Gracz" << nr;
	setName(tmp.str());
}

SmartAssComputer::SmartAssComputer(int nr) : ComputerPlayer(nr) { }

bool SmartAssComputer::wantBuy(std::string const& propertyName) { return true; }

bool SmartAssComputer::wantSell(std::string const& propertyName) { return true; }

DumbComputer::DumbComputer(int nr) : ComputerPlayer(nr), movesNumber(1) { }

bool DumbComputer::wantBuy(std::string const& propertyName) { return (movesNumber++ % 3) == 0; }

bool DumbComputer::wantSell(std::string const& propertyName) { return false; }

HumanPlayer::HumanPlayer(std::shared_ptr<Human> human) : Player(), humanPtr(human) 
{
	setName(human->getName());
	setMoney(MojaGrubaRyba::startMoney);
}

bool HumanPlayer::wantBuy(std::string const& propertyName) { return humanPtr->wantBuy(propertyName); }

bool HumanPlayer::wantSell(std::string const& propertyName) { return humanPtr->wantSell(propertyName); }

Field::Field(const string& _name) : name(_name) { }

Field::~Field()
{
	if(debug) cout << "~Field() called\n";
}

string const& Field::getName() const
{
	return name;
}

void Field::onStep(shared_ptr<Player> const p) { }
void Field::onStop(shared_ptr<Player> const p) { }

void Nieruchomosc::setOwner(shared_ptr<Player> const p)
{
	owner = p;
}

void Nieruchomosc::deleteOwner()
{
	setOwner(nullptr);
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


Wyspa::Wyspa(const string& _name) : Field(_name) { }

Start::Start(const string& _name) : Field(_name) { }

void Start::onStep(shared_ptr<Player> const p)
{
	p->giveMoney(50);
}

void Start::onStop(shared_ptr<Player> const p)
{
	p->giveMoney(50);
}

Depozyt::Depozyt(const string& _name) : Field(_name), gatheredMoney(0) { }

void Depozyt::onStep(shared_ptr<Player> const p)
{
	gatheredMoney += p->takeMoney(15);
	if(debug) cout << "Depozyt" << endl;
}

void Depozyt::onStop(shared_ptr<Player> const p)
{
	p->giveMoney(gatheredMoney);
	gatheredMoney = 0;
}

Nagroda::Nagroda(const string& _name, int _prize) : Field(_name), prize(_prize) { }

void Nagroda::onStop(shared_ptr<Player> const p)
{
	p->giveMoney(prize);
}

Kara::Kara(const string& _name, int _fine) : Field(_name), fine(_fine) { }

void Kara::onStop(shared_ptr<Player> const p)
{
	p->takeMoney(fine);
	if(debug) cout << "Kara" << endl;
	
}

Akwarium::Akwarium(const string& _name, int _rounds) : Field(_name), rounds(_rounds) { }

void Akwarium::onStop(shared_ptr<Player> const p)
{
	p->setWait(rounds);
}

Nieruchomosc::Nieruchomosc(const string& _name, int _price, double tax) :
	Field(_name), owner(nullptr), price(_price), charge(static_cast<int>(tax * _price)) { }

Koralowiec::Koralowiec(const string& _name, int _price) : Nieruchomosc(_name, _price, 0.2) { }

Publiczny::Publiczny(const string& _name, int _price) : Nieruchomosc(_name, _price, 0.4) { }

void Nieruchomosc::onStop(shared_ptr<Player> const p)
{	
	if(debug) cout << "gracz " << p->getName() << " zatrzymal sie na polu " << name << "\n";
	if(owner != nullptr)
	{
		if(debug) cout << owner->getName() << " dostaje " << charge << " od " << p->getName() << "\n";
		owner->giveMoney(p->takeMoney(charge));
		if(debug) cout << "Nieruchomosc" << endl;
	}
	else
	{
		if(debug) cout << "pole " << name << " jest wolne\n";
		if(p->getMoney() >= price) {
			if(p->wantBuy(getName())) {
				if(debug) cout << "Gracz " << p->getName() << " kupuje " << getName() << " za " << getPrice() << endl;
				p->takeMoney(price);
				p->addProperty(*this);
				setOwner(p);
			}
		}
	}
}

Board::Board()
{
	if(debug) cout << "Board() called\n";
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
	if(debug) cout << "~Board() called\n";
}

int Board::getMaxField() { return maxField; }
shared_ptr<Field> Board::getField(int nr) { return fields[nr]; }

MojaGrubaRyba::MojaGrubaRyba() : activePlayers(0)
{
	if(debug) cout << "MojaGrubaRyba() called\n";

}

MojaGrubaRyba::~MojaGrubaRyba()
{
	if(debug) cout << "~MojaGrubaRyba() called\n";
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
	if(debug) cout << "MojaGrubaRyba::setDie(...) called\n";
	die = _die;
}

// Dodaje nowego gracza komputerowego, który gra na zdefiniowanym poziomie.
// Nowy gracz komputerowy nazywa się Gracz<Numer>, gdzie <Numer> to numer pozycji,
// na której został dodany (numeracja pozycji od 1).
// TODO Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
void MojaGrubaRyba::addComputerPlayer(ComputerLevel level)
{
	int nr = players.size() + 1;
	if(level == GrubaRyba::ComputerLevel::DUMB)
		players.push_back(dynamic_pointer_cast<Player>( shared_ptr<DumbComputer>(new DumbComputer(nr))));

	if(level == GrubaRyba::ComputerLevel::SMARTASS)
		players.push_back(dynamic_pointer_cast<Player>( shared_ptr<SmartAssComputer>(new SmartAssComputer(nr))));

	
	activePlayers++;

	if(debug) cout << "players.size() = " << MojaGrubaRyba::players.size() << endl;
	if(debug) cout << "MojaGrubaRyba::addComputerPlayer(...) called\n";
	if(debug) cout << "name: " << (MojaGrubaRyba::players.back())->getName() << endl;
}

// Dodaje nowego gracza czlowieka.
// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
// TODO Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
void MojaGrubaRyba::addHumanPlayer(std::shared_ptr<Human> human)
{
	if((int)players.size() == maxPlayers)
		throw TooManyPlayersException(maxPlayers);
	players.push_back(dynamic_pointer_cast<Player>(shared_ptr<HumanPlayer>(new HumanPlayer(human))));
	activePlayers++;
	if(debug) cout << "players.size() = " << MojaGrubaRyba::players.size() << endl;
	if(debug) cout << "MojaGrubaRyba::addHumanPlayer(...) called\n";
	if(debug) cout << "name: " << (MojaGrubaRyba::players.back())->getName() << endl;
	
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
	if(debug) cout << "MojaGrubaRyba::play(" << rounds << ") called\n";
	if((int)players.size() < minPlayers)
		throw TooFewPlayersException(minPlayers);
	if(!die)
		throw NoDieException();
	unsigned int roundNumber = 1;
	while((rounds >= roundNumber) && (activePlayers > 1))
	{
		cout << "Runda: " << roundNumber << "\n";
		int rolls;
		for(auto it : players)
		{
			if(activePlayers == 1)
				break;
			// Jezeli gracz zbankrutowal pomijamy go w kolejnych turach
			if(!it->isPlayerActive())
			{
				continue;
			}
			if(it->getWait())
				it->setWait(it->getWait() - 1);
			
			if(!it->getWait()) {

				rolls = die->roll() + die->roll();

				for(int i = 1; i < rolls; i++)
					if(it->isPlayerActive())
						board.getField((it->getPosition() + i) % board.getMaxField())->onStep(it);
					else 
						continue;
					
				if(activePlayers == 1)
					break;
				
				if(it->isPlayerActive())
					it->setPosition((it->getPosition() + rolls) % board.getMaxField());
				else
					continue;

				board.getField(it->getPosition())->onStop(it);
				
			}
			if(!it->isPlayerActive())
				activePlayers--;
			
			
		}
		
		for(auto it : players){
			if(!it->isPlayerActive()){
				cout << it->getName() << " *** bankrut *** " << endl;
			}
			else if(!it->getWait()) {
				cout << it->getName() << " pole: " << board.getField(it->getPosition())->getName() << " gotowka: " << it->getMoney() << "\n";
			}
			else {
				
				cout << it->getName() << " pole: " << board.getField(it->getPosition())->getName() << " *** czekanie: " << it->getWait() << " *** " << "\n";
				
			}
		}
		roundNumber++;
	}
}
