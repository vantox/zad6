#include "mojagrubaryba.h"
#include<iostream>

using namespace std;

MojaGrubaRyba::MojaGrubaRyba()
{
	
}

MojaGrubaRyba::~MojaGrubaRyba() 
{
	
}

// Poziom gry komputera:
// DUMB - kupuje co trzecie pole, na którym stanie i jest możliwe do kupienia;
// SMARTASS - kupuje wszystkie pola, na których stanie i są możliwe do kupienia.

// Przekazuje prototypową kostkę do gry.
// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
void MojaGrubaRyba::setDie(std::shared_ptr<Die> die)
{
	
}

// Dodaje nowego gracza komputerowego, który gra na zdefiniowanym poziomie.
// Nowy gracz komputerowy nazywa się Gracz<Numer>, gdzie <Numer> to numer pozycji,
// na której został dodany (numeracja pozycji od 1).
// Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
void MojaGrubaRyba::addComputerPlayer(ComputerLevel level)
{
	
}

// Dodaje nowego gracza czlowieka.
// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
// Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
void MojaGrubaRyba::addHumanPlayer(std::shared_ptr<Human> human)
{
	
}

// Przeprowadza rozgrywkę co najwyżej podanej liczby rund (rozgrywka może
// skończyć się wcześniej).
// Jedna runda obejmuje po jednym ruchu każdego gracza.
// Gracze ruszają się w kolejności, w której zostali dodani.
// Na początku każdej rundy wypisywany jest numer rundy,
// a na zakończenie informacje podsumowujące dla każdego gracza (format w przykładzie).
// Rzuca NoDieException, jeśli nie przekazano kostki.
// Rzuca TooFewPlayersException, jeśli liczba graczy nie pozwala na rozpoczęcie gry.
void MojaGrubaRyba::play(unsigned int rounds)
{
	
}
