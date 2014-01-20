#include "mojagrubaryba.h"
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

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
	
}

bool SmartAssComputer::wantBuy(std::string const& propertyName) { return true; }

bool SmartAssComputer::wantSell(std::string const& propertyName) { return false; }

DumbComputer::DumbComputer()
{
	incrNumberOfCompPlayers();
	ostringstream tmp;
	tmp << "Gracz" << getNumberOfCompPlayers();
	setName(tmp.str());
	setMoney(MojaGrubaRyba::startMoney);
}

bool DumbComputer::wantBuy(std::string const& propertyName) { return (movesNumber % 3) == 0; }

bool DumbComputer::wantSell(std::string const& propertyName) { return false; }

HumanPlayer::HumanPlayer(std::shared_ptr<Human> human): humanPtr(human)
{
	setName(human->getName());
	setMoney(MojaGrubaRyba::startMoney);
}

bool HumanPlayer::wantBuy(std::string const& propertyName) { return humanPtr->wantBuy(propertyName); }

bool HumanPlayer::wantSell(std::string const& propertyName) { return humanPtr->wantSell(propertyName); }

//Field::Field(string _name) : name(_name) { }
void Field::setName(string _name)
{
	name = _name;
}


Field::~Field()
{
	cout << "~Field() called\n";
}

string Field::getName() { return name; }

Wyspa::Wyspa() 
{
	setName("Wyspa");
}

void Wyspa::onStep(shared_ptr<Player> const p)
{
	
}

void Wyspa::onStop(shared_ptr<Player> const p)
{

	
}

Start::Start() 
{
	setName("Start");
}

void Start::onStep(shared_ptr<Player> const p)
{
	p->setMoney(p->getMoney() + 50);
}

void Start::onStop(shared_ptr<Player> const p)
{
	p->setMoney(p->getMoney() + 50);	
}



Board::Board()
{
	cout << "Board() called\n";
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Start>(new Start())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));
	fields.push_back(dynamic_pointer_cast<Field>( shared_ptr<Wyspa>(new Wyspa())));

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
		//cout << "Dice: " << (*die).roll() + (*die).roll() << endl;
		cout << "Runda: " << roundNumber << "-------------------------------------\n";
		
		for(auto it : players)
		{
			int rolls = die->roll() + die->roll();
			cout << "Rolls: " << rolls << "\n";
			
			for(int i = 1; i < rolls; i++)
				board.getField(it->getPosition() + i)->onStep(it);
			
			it->setPosition((it->getPosition() + rolls) % board.getMaxField());
			
			board.getField(it->getPosition())->onStop(it);
			cout << it->getName() << " pole: " << board.getField(it->getPosition())->getName() << " gotowka: " << it->getMoney() << "\n";
			
			
			
		}
		roundNumber++;
	}

}
