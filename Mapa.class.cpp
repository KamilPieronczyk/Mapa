#include "pch.h"

bool Mapa::WczytajMiasta(string & nazwaPliku, Miasta & miasta)
{
	ifstream plik(nazwaPliku);
	if (!plik.is_open()) return false;
	string s1, s2;
	stringstream ss;
	int i = 0;
	while (getline(plik, s1)) {
		ss << s1;
		while (getline(ss, s2, ' ')) {
			if (i % 3 < 2 && !miasta[s2]) miasta[s2] = new Miasto{ s2 };
			i++;
		}
		ss.clear();
	}
	return true;
}

bool Mapa::WczytajDrogi(string & nazwaPliku, Miasta & miasta)
{
	ifstream plik(nazwaPliku);
	if (!plik.is_open()) return false;
	string s, miasto1, miasto2, sdlugosc;
	int dlugosc;
	stringstream ss;
	int i = 0;
	while (getline(plik, s)) {
		ss << s;
		getline(ss, miasto1, ' ');
		getline(ss, miasto2, ' ');
		getline(ss, sdlugosc, ' ');
		dlugosc = stoi(sdlugosc);
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
	for (auto trasa : this->trasy) {
		this->SzukajTrasy2(miasta, trasa.miastoA, trasa.miastoB, trasa);
	}
	for (auto trasa : this->trasy) {
		cout << "trasa: " << trasa.miastoA << " --> " << trasa.miastoB << "(" << trasa.dlugosc << "km):" << endl;
		for (auto droga : trasa.trasa) {
			cout << droga.miastoA->nazwa << " --> " << droga.miastoB->nazwa << droga.odleglosc << "km" << endl;
		}
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

bool Mapa::SzukajTrasy2(Miasta & miasta, string & miasto1, string & miasto2, Trasa & trasa)
{
	bool znalezione = false;	
	if (miasto1 == miasto2) {
		if (trasa.dlugosc == 0 || trasa.mozliwaDlugosc < trasa.dlugosc) {
			trasa.dlugosc = trasa.mozliwaDlugosc;
			trasa.trasa = trasa.mozliwaTrasa;
			for (auto droga : trasa.trasa) {
				cout << droga.miastoA->nazwa << " --> " << droga.miastoB->nazwa << droga.odleglosc << "km" << endl;
			}
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
			if (!droga.miasto->odwiedzone && !szukajwLiscie(droga.miasto->nazwa, trasa)) {
				trasa.mozliwaTrasa.top().miastoB = droga.miasto;
				trasa.mozliwaTrasa.top().odleglosc = droga.dlugosc;
				trasa.mozliwaDlugosc += droga.dlugosc;
				if (this->SzukajTrasy2(miasta, droga.miasto->nazwa, miasto2, trasa)) {
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