#include "pch.h"
int Miasta::size()
{
	return this->size(this->pHead); // uruchamia funkcje size
}

int Miasta::size(Miasto * pHead){
	if (!pHead)
		return 0;
	return 1 + this->size(pHead->pLewy) + this->size(pHead->pPrawy);  
}


Miasto * & Miasta::operator[](string nazwa)
{
	Miasto * p = this->pHead;
	if (this->pHead == nullptr) { 
		return this->pHead;
	};
	while(p){ // wyszukiwanie miasta po drzewie miast
		if(nazwa == p->nazwa) {
			return p;
		}
		else if(nazwa < p->nazwa){
			if(p->pLewy != nullptr)
				p = p->pLewy;
			else return p->pLewy;	
		} else {
			if(p->pPrawy != nullptr)
				p = p->pPrawy;
			else return p->pPrawy;
		}
	}
}

void Miasta::PrzygotujMiasta()
{
	this->PrzygotujMiasta(this->pHead); // uruchamia funkcje PrzygotujMiasta
}

void Miasta::PrzygotujMiasta(Miasto *& miasto)
{
	if (miasto != nullptr) {
		miasto->odwiedzone = false;
		this->PrzygotujMiasta(miasto->pLewy);
		this->PrzygotujMiasta(miasto->pPrawy);
	}
}

void Miasta::remove()
{
	this->remove(this->pHead); // uruchamia funkcje remove
}

void Miasta::remove(Miasto * & pRoot)
{
	if (pRoot)
	{
		pRoot->drogi.remove();
		this->remove(pRoot->pLewy);
		this->remove(pRoot->pPrawy);
		delete pRoot;
		pRoot = nullptr;
	}
}