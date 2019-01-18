// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln

#ifndef PCH_H
#define PCH_H

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Lista.h"
#include <cstdlib>
#include <crtdbg.h>
#include <stdexcept>

using namespace std;

struct Miasto;
/** Struktura przechowująca droge do miasta i wskaźnik na nie */
struct Droga
{
	int dlugosc; /**< dlugosc drogi */
	Miasto * miasto; /**< wskaźnik na miasto do którego prowadzi droga */
};


/** Struktura gałęzi drzewa miast */
struct Miasto
{	
	string nazwa; /**< nazwa miasta */
	Miasto * pPrawy = nullptr; /**< wskaźnik na miasto po prawej */
	Miasto * pLewy = nullptr; /**< wskaźnik na miasto po lewej */
	Lista<Droga> drogi; /**< Lista dróg wychodzących z miasta */
	bool odwiedzone = false;
};
/** Struktura zawierająca dane na temat odcinka wytyczanej trasy pomiedzy dwoma miastami */
struct OdcinekTrasy {
	Miasto * miastoA = nullptr; /**< wskaźnik na miasto początkowe */
	Miasto * miastoB = nullptr; /**< wskaźnik na miasto końcowe */
	int odleglosc = 0; /**< Odległość pomięzdy dwoma miastami */
};

/** Struktura zawierająca dane na temat wytyczanej trasy pomiędzy miastami */
struct Trasa {
	string miastoA, /**< Nazwa miasta początkowego */
		   miastoB; /**< Nazwa miasto końcowego */
	Lista<OdcinekTrasy> trasa; /**< Lista odcinków trasy */
	Lista<OdcinekTrasy> mozliwaTrasa; /**< Lista możliwych odcinków trasy (pomocnicza) */
	int dlugosc = 0; /**< Odleglość z miastaA do miastaB */
	int mozliwaDlugosc = 0; /**< Możliwa odleglość z miastaA do miastaB */
};

/** Klasa Miasta jest odpowiedzialna za wszelkie operacje na drzewie miast */
class Miasta {
public:
	Miasto * pHead = nullptr; /**< wskaźnik na pierwsze miasto */

	/** Wielkość drzewa
	* @return Zwraca ilość miast w drzewie (int)
	*/
	int size();

	/**
	* @param nazwa - nazwa miasta
	* @return Zwraca referencje do miasta
	*/
	Miasto *& operator[](string nazwa);

	/** Ustawia wartość odwiedzone miast na false */
	void PrzygotujMiasta();

	/** Czyści drzewo */
	void remove();
private:
	void PrzygotujMiasta(Miasto *& miasto);
	int size(Miasto * pHead);
	void remove(Miasto * & miasto);
};

class Mapa
{
public:
	Miasta miasta; /**< Drzewo miast */

	Lista<Trasa> trasy; /**< Lista tras zawierająca wyznaczone trasy */

	string Drogi, SzukaneTrasy, Trasy; /**< Pliki */

	/** Funckja inicjalizująca program, sprawdza parametry wejściowe
	* @param argc - ilość argumentów w tablicy
	* @param argv - tablica argumentów
	*/
	void Inicjalizacja(int argc,char *argv[]);

	/** Wczytuje miasta i drogi z pliku
	* @return Zwraca true jeśli się powiodło
	*/
	bool WczytajMape();

	/** Wczytuje trasy do wyznaczenia z pliku
	* @return Zwraca true jeśli się powiodło
	*/
	bool WczytajTrasy();

	/** Uruchamia algorytm szukania trasy dla każdej z tras do wyznaczenia
	* @return Zwraca true jeśli się powiodło
	*/
	bool WytyczTrasy();

	/** Rekurencyjny algorytm wytyczania najkrótszej trasy z miasta A do miasta B
	* @param Miasto startowe
	* @param Miasto szukane
	* @param Obiekt zawierający dane na temat szukanej trasy
	* @return Zwraca true jeśli trasa została znaleziona
	*/
	bool SzukajTrasy(string & miasto1, string & miasto2, Trasa & trasa);

	/** Wypisuje szczególy wytyczonych tras	*/
	void WypiszTrasy(ostream & stream);

	/** Uruchamia algorytmy czyszczące listy i drzewa */
	void remove();
};

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif //PCH_H
