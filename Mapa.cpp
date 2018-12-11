#include "pch.h"
#include "Lista.h"

int main()
{
	Miasta miasta;
	Mapa mapa;
	string file = "Drogi.txt";
	string file2 = "SzukaneTrasy.txt";
	Lista<int> lista;

	mapa.WczytajMiasta(file, miasta);
	mapa.WczytajDrogi(file, miasta);
	mapa.WczytajTrasy(file2);
	mapa.WytyczTrasy(miasta);
}
