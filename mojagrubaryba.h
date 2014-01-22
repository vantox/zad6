#ifndef MOJAGRUBARYBA_H
#define MOJAGRUBARYBA_H

#include <vector>
#include "grubaryba.h"
#include <string>

using namespace std;

const int MAX_PLAYERS = 8;

class Nieruchomosc;
class Player {
	private:
		int money;
		int wait;
		int position;
		//TODO const
		string name;
		//z shared jest double free bo tu trzymamy tylko pola dla ktorych
		//potem i tak sie destruktory wywolaja
		vector<Nieruchomosc*> properties;

	protected:
		//TODO const&
		void setName(string _name);
	public:
		void addProperty(Nieruchomosc& property);
		void sellProperties();
		void bankrupt();
		void setPosition(int _position);
		void setMoney(int _money);
		void setWait(int _wait);
		int getMoney();
		int getPosition() const;
		int getWait();
		int takeMoney(int _money);
		void giveMoney(int _money);
		virtual ~Player() {}

		// Zwraca imię człowieka.
		string const& getName() const;

		// Zwraca true, jeśli człowiek chce kupić daną posiadłość.
		virtual bool wantBuy(std::string const& propertyName) = 0;

		// Zwraca true, jeśli człowiek chce sprzedać daną posiadłość.
		// Wywoływane w przypadku, gdy brakuje człowiekowi pieniędzy na zakup lub opłaty.
		virtual bool wantSell(std::string const& propertyName) = 0;
};

void sellout(shared_ptr<Player> const p);

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
		//TODO const dalem protected żeby można było konstruktorem z podklasy przypisać
		//string name;
	protected:
		string name;
	public:
		//Field(string _name);
		~Field();
		string getName();
		// co się dzieje po przejściu przez pole
		virtual void onStep(shared_ptr<Player> const p) = 0;
		// co się dzieje po zatrzymaniu na polu
		virtual void onStop(shared_ptr<Player> const p) = 0;
};

class Wyspa : public Field {
	public:
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
		Wyspa(const string& _name);
};

class Start : public Field {
	public:
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
		Start(const string& _name);
};

class Depozyt : public Field {
	private:
		int gatheredMoney;
	public:
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
		Depozyt(const string& _name);
};

class Akwarium : public Field {
	private:
		int rounds;
	public:
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
		Akwarium(const string& _name, int _rounds);
};

class Nagroda : public Field {
	private:
		int prize;
	public:
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
		Nagroda(const string& _name, int _prize);
};

class Kara : public Field {
	private:
		int fine;
	public:
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
		Kara(const string& _name, int _fine);
};

class Nieruchomosc : public Field {
	protected:
		bool owned;
		shared_ptr<Player> owner;
		int price, charge;
	public:
		void changeOwnedState(bool b);
		void setOwner(shared_ptr<Player> const p);
		void deleteOwner();
		shared_ptr<Player> getOwner();
		int getPrice();
		bool getOwned();
		int getCharge();
		void onStep(shared_ptr<Player> const p);
		void onStop(shared_ptr<Player> const p);
};

class Koralowiec : public Nieruchomosc {
	public:
		Koralowiec(const string& _name, int _price);
};

class Publiczny : public Nieruchomosc {
	public:
		Publiczny(const string& _name, int _price);
};

/*
class FieldWithAction : public Field {
};

class FieldWithoutAction : public Field {
	public:
		virtual void onStep(Player const& p);
		virtual void onStop(Player const& p);
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
*/

class Board {
	private:
		//TODO chwilowo do testow potem sie zmieni
		int maxField = 12;
		vector< shared_ptr<Field> > fields;
	public:
		//Board(vector<Field>& allFields);
		// Board(vector<int>& allFields);
		Board();
		~Board();
		int getMaxField();
		// unique_ptr<Field> getField(int nr);
		shared_ptr<Field> getField(int nr);
};

class MojaGrubaRyba : public GrubaRyba {
	private:
		int realPlayers, compPlayers;
		vector< shared_ptr<Player> > players;
		Board board;
		shared_ptr<Die> die;
	public:
		static const int minPlayers = 2;
		static const int maxPlayers = 8;
		static const int startMoney = 1000;
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
