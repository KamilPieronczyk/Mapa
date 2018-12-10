#include "pch.h"

int Drogi::size()
{
	Droga * p = pHead;
	int i = 0;
	while (p) {
		p = p->pNext;
		i++;
	}
	return i;
}

Droga * & Drogi::operator[](int i)
{
	if (i < 0 || i > this->size()) {
		cout << "Out of range" << endl;
		return this->pHead;
	}
	else if (i == this->size()) {
		if (i == 0) return this->pHead;
		return this->DrogaNumer(i - 1)->pNext;
	}
	else {
		return this->DrogaNumer(i);
	}
}

void Drogi::push_back(Droga element, Droga * & pHead)
{
	if (pHead)
		this->push_back(element, pHead->pNext);
	else {
		pHead = new Droga(element);
	}
}

Droga * & Drogi::DrogaNumer(const int id)
{
	Droga * p = nullptr;
	if (this->ostatnioSzukanaDroga.id <= id && this->ostatnioSzukanaDroga.id > 0) {
		p = this->ostatnioSzukanaDroga.droga;
	}
	else {
		p = this->pHead;
	}
	for (int i = 1 + this->ostatnioSzukanaDroga.id; i <= id; i++)
	{
		p = p->pNext;
	}
	this->ostatnioSzukanaDroga = { p , id };
	return p;
}
