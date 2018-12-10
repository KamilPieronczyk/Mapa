#include "pch.h"
#include "Lista.h"

int main()
{
	Miasta miasta;
	Mapa mapa;
	string file = "Drogi.txt";
	mapa.WczytajMiasta(file, miasta);
	mapa.WczytajDrogi(file, miasta);
	string miasto1 = "Tarnow";
	string miasto2 = "Krakow";
	Trasa trasa;
	if (!mapa.SzukajTrasy2(miasta, miasto1, miasto2, trasa)) cout << "nieznalezione" << endl;
	cout << trasa.dlugosc << endl;
	cout << trasa.trasa.size() << endl;
}
