zad6
====
=== Zadanie Gruba Ryba ===

Gruba Ryba to gra planszowa, w której celem gracza jest zostanie najbogatszą rybą Wielkiej Rafy
Koralowej. Gracz może się wzbogacać na handlu nieruchomościami takimi jak koralowce, groty, statki.
Uwaga: podobieństwo do gry Monopol jest nieprzypadkowe.

W grze może brać udział od 2 do 8 graczy. Każdy gracz dostaje na początku 1000 rybkoinów
i rozpoczyna grę na polu Start. Gracze poruszają się po cyklicznej planszy złożonej z 12 pól.
Podczas swojego ruchu, o ile gracz nie pauzuje, to:
* rzuca 2 kostkami do gry
* przesuwa się o liczbę pól równą sumie wyrzuconych wartości
* wykonuje akcję związaną z polem (o ile jakaś akcja jest związana z tym polem)

Są następujące typy pól z akcjami:
* Start - przy przejściu lub zatrzymaniu się na tym polu gracz dostaje 50 rybkoinów
* Nagroda - przy zatrzymaniu na tym polu gracz dostaje gotówkę
* Kara - przy zatrzymaniu się na tym polu gracz musi zapłacić gotówką
* Depozyt - przy przejściu przez to pole gracz musi wpłacić gotówkę do depozytu;
gracz, który zatrzyma się na tym polu, dostaje wypłatę zgromadzonej gotówki
* Akwarium - gracz czeka określoną liczbę kolejek
* Nieruchomość - jeśli pole jest wolne, to gracz może je kupić; jeśli jest zajęte,
to gracz, o ile nie jest właścicielem, musi zapłacić właścicielowi opłatę za postój.
Nieruchomością może być koralowiec albo obiekt użyteczności publicznej. Opłata
za postój na koralowcu wynosi 20% ceny kupna, a na obiekcie użyteczności publicznej 40%

Jeśli graczowi brakuje gotówki na opłaty (kara, opłata za postój) lub kupno nieruchomości,
to może zdecydować się na sprzedaż części swojego majątku. Cena sprzedaży nieruchomości to 50% ceny
kupna.

Jeśli gracz nie będzie miał gotówki na opłaty, to zbankrutuje. Bankructwo oznacza,
że kończy grę. Wtedy wszystkie jego nieruchomości zostają sprzedane, a gotówka ze sprzedaży
jest przeznaczona na pokrycie długu.

Każde pole planszy ma swoją nazwę. Są następujące pola:
1. Start
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

Należy dostarczyć implementację klasy MojaGrubaRyba dziedziczącej z klasy GrubaRyba,
która została zdefiniowana w nagłówku grubaryba.h, dostępnym w repozytorim w katalogu
common/zadanie6.

Wskazówki:
* należy zaprojektować potrzebne klasy wraz z ich hierarchiami; tam, gdzie jest to wskazane
należy wydzielić klasy reprezentujące interfejsy
* powinny się pojawić klasy reprezentujące co najmniej: pole, planszę, gracza
* projekt powinien uwzględniać:
** możliwość dodawania nowych poziomów graczy komputerowych
** możliwość dodawania nowych pól do planszy oraz zmiany układu pól
** wysokie prawdopodobieństwo zmiany interfejsu Human
* przy projektowaniu warto dbać o luźne powiązania (loose coupling) i wysoką spójność (high
cohesion) elementów
* zasady, które pomagają osiągnąć luźne powiązania i wysoką spójność to:
** wzorce GRASP
** zasady SOLID
** wzorce projektowe GoF
* w komentarzach należy wyjaśniać założenia projektowe

=== Przykład użycia ===

Przykład użycia jest dostępny w repozytorium w katalogu common/zadanie6.
Kod przykładu znajduje się w pliku grubaryba_example.cc, a wynik jego działania
w pliku grubaryba_example.out.

=== Ustalenia techniczne ===

Jako rozwiązanie należy dostarczyć pliki mojagrubaryba.h oraz mojagrubaryba.cc,
które należy umieścić w repozytorium w katalogu

grupaN/zadanie6/ab123456+cd123456

lub

grupaN/zadanie6/ab123456+cd123456+ef123456

gdzie N jest numerem grupy, a ab123456, cd123456, ef123456 są
identyfikatorami członków zespołu umieszczającego to rozwiązanie.
Katalog z rozwiązaniem nie powinien zawierać innych plików, ale może
zawierać podkatalog private, gdzie można umieszczać różne pliki, np.
swoje testy. Pliki umieszczone w tym podkatalogu nie będą oceniane.
