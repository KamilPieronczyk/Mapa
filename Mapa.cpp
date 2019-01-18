#include "pch.h"
#include "Lista.h"
#include "MyException.h"

int main(int argc, char *argv[])
{	
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);

	Mapa * mapa = new Mapa();

	try {
		mapa->Inicjalizacja(argc, argv);
		mapa->WczytajMape();
		mapa->WczytajTrasy();
	}
	catch (const MyException & e){
		cout << e.what() << endl;
		mapa->remove();
		delete mapa;
		return 0;
	}

	ofstream plik(mapa->Trasy);

	mapa->WytyczTrasy();
	mapa->WypiszTrasy(cout);
	mapa->WypiszTrasy(plik);
	mapa->remove();

	plik.close();

	delete mapa;

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	_CrtDumpMemoryLeaks();
}
