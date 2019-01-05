#include "pch.h"
#include "MyException.h"
void Mapa::Inicjalizacja(int argc, char *argv[])
{
	int a = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i + 1]) {
			switch (argv[i][1]){
				case 'd':
					this->Drogi = argv[i + 1];
					a++;
					break;
				case 't':
					this->SzukaneTrasy = argv[i + 1];
					a++;
					break;
				case 'o':
					a++;
					this->Trasy = argv[i + 1];
					break;
			}
		}
	}
	if (a != 3) {
		throw (MyException(MyException::IncorectParameters, ""));
	}
	
}
bool Mapa::WczytajMape()
{
	ifstream plik(this->Drogi);
	if (!plik.is_open()) { throw(MyException(MyException::FileDoesNotExist, this->Drogi)); return false; };
	string s1, s2, miasto1, miasto2, sdlugosc;
	stringstream ss;
	int dlugosc;
	int i = 0;
	string exceptionMessage = "Bledy w pliku wejsciowym - " + this->Drogi;
	while (getline(plik, s1)) {
		if (strlen(s1.c_str()) == 0) continue;
		ss << s1;
		miasto1.clear();
		miasto2.clear();
		sdlugosc.clear();
		try {
			getline(ss, miasto1, ' ');
			getline(ss, miasto2, ' ');
			getline(ss, sdlugosc);
			dlugosc = stoi(sdlugosc);
			if (miasto1.length() == 0 || miasto2.length() == 0) throw(0);
		} catch (...) {
			throw(MyException(MyException::ErrorsInInputFile, this->Drogi)); 
			return false;
		}
		if (!this->miasta[miasto1]) this->miasta[miasto1] = new Miasto{ miasto1 };
		if (!this->miasta[miasto2]) this->miasta[miasto2] = new Miasto{ miasto2 };
		this->miasta[miasto1]->drogi.push_back({ dlugosc, this->miasta[miasto2] });
		ss.clear();
	}
	plik.close();
	return true;
}

bool Mapa::WczytajTrasy()
{
	ifstream plik(this->SzukaneTrasy);
	if (!plik.is_open()) { throw(MyException(MyException::FileDoesNotExist, this->SzukaneTrasy)); return false; };
	string s, miasto1, miasto2;
	stringstream ss;
	while (getline(plik, s)) {
		if (strlen(s.c_str()) == 0) continue;
		ss << s;
		miasto1.clear();
		miasto2.clear();
		try {			
			getline(ss, miasto1, ' ');
			getline(ss, miasto2);			
			if (miasto1.empty() || miasto2.empty()) throw(0);
		} catch (...) {
			throw(MyException(MyException::ErrorsInInputFile, this->SzukaneTrasy)); 
			return false;
		}
		this->trasy.push_back({ miasto1, miasto2 });
		ss.clear();
	}
	return true;
}

bool Mapa::WytyczTrasy()
{
	for (auto & trasa : this->trasy) {
		this->SzukajTrasy(trasa.miastoA, trasa.miastoB, trasa);
		this->miasta.PrzygotujMiasta();
	}
	return true;
}

bool szukajwLiscie(const string & szukane,Trasa & trasa2) {
	for (auto odcinekTrasy : trasa2.mozliwaTrasa) {
		if (odcinekTrasy.miastoA->nazwa == szukane) return true;
	}
	return false;
};

bool Mapa::SzukajTrasy(string & miasto1, string & miasto2, Trasa & trasa)
{
	bool znalezione = false;	
	if (miasto1 == miasto2) {
		if (trasa.dlugosc == 0 || trasa.mozliwaDlugosc < trasa.dlugosc) {
			trasa.dlugosc = trasa.mozliwaDlugosc;
			trasa.trasa = trasa.mozliwaTrasa;
			trasa.mozliwaTrasa.pHead = nullptr;
			for (auto odcinekTrasy : trasa.trasa) {
				trasa.mozliwaTrasa.push_back(odcinekTrasy);
			}
		};		
		return true;
	}
	else {
		trasa.mozliwaTrasa.push_back({miasta[miasto1]});
		for (auto droga : this->miasta[miasto1]->drogi) {
			if (trasa.dlugosc > trasa.mozliwaDlugosc + droga.dlugosc) continue;
			if (!droga.miasto->odwiedzone && !szukajwLiscie(droga.miasto->nazwa, trasa)) {
				trasa.mozliwaTrasa.top().miastoB = droga.miasto;
				trasa.mozliwaTrasa.top().odleglosc = droga.dlugosc;
				trasa.mozliwaDlugosc += droga.dlugosc;
				if (this->SzukajTrasy(droga.miasto->nazwa, miasto2, trasa)) {
					znalezione = true;
				}
				else {
					droga.miasto->odwiedzone = true;
				}
				trasa.mozliwaDlugosc -= droga.dlugosc;
			}
		}		
		trasa.mozliwaTrasa.pop();
	}
	return znalezione;
}

void Mapa::WypiszTrasy(ostream & stream)
{
	for (auto trasa : this->trasy) {
		if (trasa.trasa.size() > 0) {
			stream << "trasa: " << trasa.miastoA << " --> " << trasa.miastoB << " (" << trasa.dlugosc << "km):" << endl << endl;
			for (auto droga : trasa.trasa) {
				stream << "	" << droga.miastoA->nazwa << " --> " << droga.miastoB->nazwa << " " << droga.odleglosc << "km" << endl;
			}
		}
		else {
			stream << "trasa: " << trasa.miastoA << " --> " << trasa.miastoB << endl;
			stream << "	" << "TRASA NIEMOZLIWA DO WYZNACZENIA" << endl;
		}
		stream << endl;
		stream << endl;
	}
}

void Mapa::remove()
{
	for (auto trasa : this->trasy) {
		trasa.mozliwaTrasa.remove();
		trasa.trasa.remove();
	}
	this->trasy.remove();
	this->miasta.remove();
	this->Drogi.clear();
}