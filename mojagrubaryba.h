#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include <vector>
#include "grubaryba.h"
#include <string>

using namespace std;

const int MAX_PLAYERS = 8;

class Player {
	private:
		int money;
		int wait;
		//TODO const
		string name;

	protected:
		//TODO const&
		void setName(string _name);
	public:
		int getMoney();

		int getWait();

		virtual ~Player() {}

		// Zwraca imię człowieka.
		string const& getName() const;

		// Zwraca true, jeśli człowiek chce kupić daną posiadłość.
		virtual bool wantBuy(std::string const& propertyName) = 0;

		// Zwraca true, jeśli człowiek chce sprzedać daną posiadłość.
		// Wywoływane w przypadku, gdy brakuje człowiekowi pieniędzy na zakup lub opłaty.
		virtual bool wantSell(std::string const& propertyName) = 0;
};

// TODO zintegrowac z humanem z grubaryba.h
class HumanPlayer : public Player {
	public:
		HumanPlayer(std::shared_ptr<Human> human);
		bool wantBuy(std::string const& propertyName);

		bool wantSell(std::string const& propertyName);
	private:
		std::shared_ptr<Human> humanPtr;
};

class ComputerPlayer : public Player {
	private:
		static unsigned int numberOfCompPlayers;
	protected:
		unsigned int getNumberOfCompPlayers();
		void incrNumberOfCompPlayers();
};

// SMARTASS - kupuje wszystkie pola, na których stanie i są możliwe do kupienia.
class SmartAssComputer : public ComputerPlayer {
	public:
		SmartAssComputer();
		~SmartAssComputer() {}

		bool wantBuy(std::string const& propertyName);

		bool wantSell(std::string const& propertyName);
};

// DUMB - kupuje co trzecie pole, na którym stanie i jest możliwe do kupienia;
class DumbComputer : public ComputerPlayer {
	private:
		int movesNumber;
	public:
		DumbComputer();
		~DumbComputer() {}

		bool wantBuy(std::string const& propertyName);

		bool wantSell(std::string const& propertyName);
};

class Field {
	private:
		//TODO const
		string name;
	public:
		Field(string _name);
		~Field();
		string getName();
		// co się dzieje po przejściu przez pole
		virtual void onStep(Player const& p) = 0;
		// co się dzieje po zatrzymaniu na polu
		virtual void onStop(Player const& p) = 0;
};

class FieldWithAction : Field {
};

class FieldWithoutAction : Field {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Start : public FieldWithoutAction {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Nagroda : public FieldWithAction {
};

class Kara : public FieldWithAction {
};

class Depozyt : public FieldWithAction {
};

// TODO zamienic na konkretna implementacje
class Akwarium : public FieldWithAction {
};

class Nieruchomosc : public FieldWithAction {
};

class Koralowiec : public Nieruchomosc {
};

class Publiczny : public Nieruchomosc {
};

class Anemonia : public Koralowiec {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

//TODO
class Wyspa : public FieldWithoutAction {
};

class Grota : public Publiczny {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Menella : public Koralowiec {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Laguna : public Depozyt {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Statek : public Publiczny {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Blazenki : public Nagroda {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Pennatula : public Koralowiec {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Rekin : public Kara {
	public:
		void onStep(Player const& p);
		void onStop(Player const& p);
};

class Board {
	private:
		int maxField;
		vector< shared_ptr<Field> > fields;
	public:
		// Board(vector<Field>& allFields);
		// Board(vector<int>& allFields);
		Board();
		~Board();
		int getMaxField();
		// unique_ptr<Field> getField(int nr);
};

class MojaGrubaRyba : public GrubaRyba {
	private:
		int realPlayers, compPlayers;
		vector< shared_ptr<Player> > players;
		Board board;
		shared_ptr<Die> die;
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
