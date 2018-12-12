#include "pch.h"

bool Mapa::WczytajMape(string & nazwaPliku, Miasta & miasta)
{
	ifstream plik(nazwaPliku);
	if (!plik.is_open()) return false;
	string s1, s2, miasto1, miasto2, sdlugosc;
	stringstream ss;
	int dlugosc;
	int i = 0;
	while (getline(plik, s1)) {
		ss << s1;
		getline(ss, miasto1, ' ');
		getline(ss, miasto2, ' ');
		getline(ss, sdlugosc, ' ');
		dlugosc = stoi(sdlugosc);
		if (!miasta[miasto1]) miasta[miasto1] = new Miasto{ miasto1 };
		if (!miasta[miasto2]) miasta[miasto2] = new Miasto{ miasto2 };
		miasta[miasto1]->drogi.push_back({ dlugosc, miasta[miasto2] });
		ss.clear();
	}
	return true;
}

bool Mapa::WczytajTrasy(string & nazwaPliku)
{
	ifstream plik(nazwaPliku);
	if (!plik.is_open()) return false;
	string s, miasto1, miasto2;
	stringstream ss;
	while (getline(plik, s)) {
		ss << s;
		getline(ss, miasto1, ' ');
		getline(ss, miasto2, ' ');
		this->trasy.push_back({ miasto1, miasto2 });
		ss.clear();
	}
	return true;
}

bool Mapa::WytyczTrasy(Miasta & miasta)
{
	for (auto & trasa : this->trasy) {
		this->SzukajTrasy(miasta, trasa.miastoA, trasa.miastoB, trasa);
		miasta.PrzygotujMiasta();
	}
	for (auto trasa : this->trasy) {
		cout << "trasa: " << trasa.miastoA << " --> " << trasa.miastoB << " (" << trasa.dlugosc << "km):" << endl << endl;
		for (auto droga : trasa.trasa) {
			cout << "	" << droga.miastoA->nazwa << " --> " << droga.miastoB->nazwa << " " << droga.odleglosc << "km" << endl;
		}
		cout << endl;
		cout << endl;

	}
	return true;
}

bool szukajwLiscie(const string & szukane,Trasa & trasa2) {
	for (auto odcinekTrasy : trasa2.mozliwaTrasa) {
		if (odcinekTrasy.miastoA->nazwa == szukane) return true;
	}
	return false;
};

bool Mapa::SzukajTrasy(Miasta & miasta, string & miasto1, string & miasto2, Trasa & trasa)
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
		for (auto droga : miasta[miasto1]->drogi) {
			if (trasa.dlugosc > trasa.mozliwaDlugosc + droga.dlugosc) continue;
			if (!droga.miasto->odwiedzone && !szukajwLiscie(droga.miasto->nazwa, trasa)) {
				trasa.mozliwaTrasa.top().miastoB = droga.miasto;
				trasa.mozliwaTrasa.top().odleglosc = droga.dlugosc;
				trasa.mozliwaDlugosc += droga.dlugosc;
				if (this->SzukajTrasy(miasta, droga.miasto->nazwa, miasto2, trasa)) {
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