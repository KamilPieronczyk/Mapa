#include "pch.h"
#include "Lista.h"

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);

	Mapa mapa;
	string * file = new string("Drogi.txt");
	string * file2 = new string( "SzukaneTrasy.txt");

	mapa.WczytajMape(*file);
	mapa.WczytajTrasy(*file2);
	mapa.WytyczTrasy();
	mapa.remove();

	delete file;
	delete file2;

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	_CrtDumpMemoryLeaks();
}
