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

string const& Player::getName() const { return name; }

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
}

bool SmartAssComputer::wantBuy(std::string const& propertyName) { return true; }

bool SmartAssComputer::wantSell(std::string const& propertyName) {return false; }

DumbComputer::DumbComputer()
{
	incrNumberOfCompPlayers();
	ostringstream tmp;
	tmp << "Gracz" << getNumberOfCompPlayers();
	setName(tmp.str());
}

bool DumbComputer::wantBuy(std::string const& propertyName) { return (movesNumber % 3) == 0; }

bool DumbComputer::wantSell(std::string const& propertyName) {return false; }

Field::Field()
{
	cout << "Field() called\n";
}

Field::~Field()
{
	cout << "~Field() called\n";
}

string Field::getName() { return name; }


Board::Board()
{
	cout << "Board() called\n";
}

Board::~Board()
{
	cout << "~Board() called\n";
}

int Board::getMaxField() { return maxField; }
// shared_ptr<Field> Board::getField(int nr) { return fields[nr]; }

MojaGrubaRyba::MojaGrubaRyba()
{
	cout << "MojaGrubaRuba() called\n";
}

MojaGrubaRyba::~MojaGrubaRyba()
{
	cout << "~MojaGrubaRuba() called\n";
}

// Poziom gry komputera:
// DUMB - kupuje co trzecie pole, na którym stanie i jest możliwe do kupienia;
// SMARTASS - kupuje wszystkie pola, na których stanie i są możliwe do kupienia.

// Przekazuje prototypową kostkę do gry.
// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
void MojaGrubaRyba::setDie(std::shared_ptr<Die> _die)
{
	if(_die)
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
	MojaGrubaRyba::players.push_back(dynamic_pointer_cast<Player>(human));
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
	unsigned int roundNumber = 1;

	while(rounds >= roundNumber)
	{
		for(auto it = MojaGrubaRyba::players.begin(); it != MojaGrubaRyba::players.end(); it++)
		{
			cout << (*it)->getName() << endl;
		}
		cout << "Runda: " << roundNumber << endl;
		roundNumber++;
	}
	cout << "MojaGrubaRyba::play(" << rounds << ") called\n";
}
