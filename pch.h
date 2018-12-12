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

using namespace std;

struct Miasto;
struct Droga
{
	int dlugosc;
	Miasto * miasto;
};

struct Miasto
{	
	string nazwa;
	Miasto * pPrawy = nullptr;
	Miasto * pLewy = nullptr;
	Lista<Droga> drogi;
	bool odwiedzone = false;
};

struct OdcinekTrasy {
	Miasto * miastoA = nullptr;
	Miasto * miastoB = nullptr;
	int odleglosc = 0;
};

struct Trasa {
	string miastoA, miastoB;
	Lista<OdcinekTrasy> trasa;
	Lista<OdcinekTrasy> mozliwaTrasa;
	int dlugosc = 0;
	int mozliwaDlugosc = 0;
};

class Miasta {
public:
	Miasto * pHead = nullptr;
	int size();
	Miasto *& operator[](string nazwa);
	void PrzygotujMiasta();
	void remove();
private:
	void PrzygotujMiasta(Miasto *& miasto);
	int size(Miasto * pHead);
	void remove(Miasto * & miasto);
};

class Mapa
{
public:
	Miasta miasta;
	Lista<Trasa> trasy;
	bool WczytajMape(string & nazwaPliku);
	bool WczytajTrasy(string & nazwaPliku);
	bool WytyczTrasy();
	bool SzukajTrasy(string & miasto1, string & miasto2, Trasa & trasa);
	void remove();
};

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif //PCH_H
