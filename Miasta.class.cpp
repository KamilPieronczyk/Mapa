#include "pch.h"

int Miasta::size()
{
	return this->size(this->pHead);
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
	while(p){
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
	this->PrzygotujMiasta(this->pHead);
}

void Miasta::PrzygotujMiasta(Miasto *& miasto)
{
	if (miasto != nullptr) {
		miasto->odwiedzone = false;
		this->PrzygotujMiasta(miasto->pLewy);
		this->PrzygotujMiasta(miasto->pPrawy);
	}
}