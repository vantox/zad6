#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include<vector>
#include "grubaryba.h"

using namespace std;

const int MAX_PLAYERS = 8;

class Field {
	private:
		string name;
	public:
		string getName(){return name;}
		virtual void onStep(Player& p);//co się dzieje po przejściu przez pole
		virtual void onStop(Player& p);//co się dzieje po zatrzymaniu na polu
}

class Board {
	private:
		int maxField;
		vector<Field> fields;
		
	public:
		Board(vector<Field>& allFields) : fields(allFields){}
		int getMaxField() {return maxField;}
		Field& getField(int nr) {return fields[nr];}
}

class Player {
	private:
		int money;
		int wait; //ile kolejek jeszcze musi czekać
	public:
		int getMoney() {return money;}
		int getWait() {return wait;}
		virtual bool wantBuy(string const& propertyName);
		virtual bool wantSell(string const& propertyName);
}

class HumanPlayer : public Player {

	
}

class ComputerPlayer : public Player {
	
}

		

class MojaGrubaRyba : public GrubaRyba {
	private:
		int realPlayers, compPlayers;
		vector<Player> players;
		Board board;
	public:
		MojaGrubaRyba();
		~MojaGrubaRyba();

		// Poziom gry komputera:
		// DUMB - kupuje co trzecie pole, na którym stanie i jest możliwe do kupienia;
		// SMARTASS - kupuje wszystkie pola, na których stanie i są możliwe do kupienia.

		// Przekazuje prototypową kostkę do gry.
		// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
		void setDie(std::shared_ptr<Die> die);

		// Dodaje nowego gracza komputerowego, który gra na zdefiniowanym poziomie.
		// Nowy gracz komputerowy nazywa się Gracz<Numer>, gdzie <Numer> to numer pozycji,
		// na której został dodany (numeracja pozycji od 1).
		// Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
		void addComputerPlayer(ComputerLevel level);

		// Dodaje nowego gracza czlowieka.
		// Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji (ale nie ma błędu).
		// Rzuca TooManyPlayersException, jeśli osiągnięto już maksymalną liczbę graczy.
		void addHumanPlayer(std::shared_ptr<Human> human);

		// Przeprowadza rozgrywkę co najwyżej podanej liczby rund (rozgrywka może
		// skończyć się wcześniej).
		// Jedna runda obejmuje po jednym ruchu każdego gracza.
		// Gracze ruszają się w kolejności, w której zostali dodani.
		// Na początku każdej rundy wypisywany jest numer rundy,
		// a na zakończenie informacje podsumowujące dla każdego gracza (format w przykładzie).
		// Rzuca NoDieException, jeśli nie przekazano kostki.
		// Rzuca TooFewPlayersException, jeśli liczba graczy nie pozwala na rozpoczęcie gry.
		void play(unsigned int rounds);
};

#endif