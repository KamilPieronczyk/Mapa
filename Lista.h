#pragma once
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

template<typename T>
class Lista
{
	struct Element {
		T obiekt;
		Element * pNext;
	};
	struct OstatnioSzukanyElement {
		Element * element = nullptr;
		int id = 0;
	};
	class Iterator {
		Element * element;
	public:
		Iterator(Element * _element) :element(_element) {};
		T& operator*() { return element->obiekt; }
		Iterator& operator++() { element = element->pNext; return *this; }
		bool operator!=(const Iterator& it) const { return element ? true : false; };
	};
public:
	Element * pHead = nullptr;
	int size();
	void push_back(T element);
	T & top();
	void pop();
	T & operator [](int i);
	Iterator begin() { return { pHead }; };
	Iterator end() { return { nullptr }; }
	void remove();
private:
	T & top(Element * & pHead);
	void pop(Element * & pHead);
	void push_back(T element, Element * & pHead);
	OstatnioSzukanyElement ostatnioSzukanyElement;	
	Element * ElementNumer(const int id);
};

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

template<typename T>
int Lista<T>::size()
{
	Element * p = this->pHead;
	int i = 0;
	while (p) {
		p = p->pNext;
		i++;
	}
	return i;
}

template<typename T>
void Lista<T>::push_back(T element)
{
	this->push_back(element, this->pHead);
}

template<typename T>
void Lista<T>::push_back(T element, Element * & pHead)
{
	if (pHead)
		this->push_back(element, pHead->pNext);
	else {
		pHead = new Element{ element };
	}
}

template<typename T>
T & Lista<T>::top()
{
	if (this->size() == 0) {
		cout << "Error: Lista::top() - lista jest pusta" << endl;
		T temp;
		return temp;
	}		
	return this->top(this->pHead);
}

template<typename T>
T & Lista<T>::top(Element *& pHead)
{
	if (pHead->pNext)
		this->top(pHead->pNext);
	else {
		return pHead->obiekt;
	}
}

template<typename T>
void Lista<T>::pop()
{
	if (!this->pHead) return;
	this->pop(this->pHead);
}

template<typename T>
void Lista<T>::pop(Element *& pHead)
{
	Element * p = pHead;
	int i = this->size() - 1;
	if (i == 0) {
		delete pHead;
		pHead = nullptr;
		return;
	}
	while (i - 1 > 0) {
		p = p->pNext;
		i--;
	}
	Element *& p2 = p->pNext;
	delete p2;
	p->pNext = nullptr;
}

template<typename T>
T & Lista<T>::operator[](int i)
{
	if (i < 0 || i >= this->size())
		cout << "Out of range" << endl;
	if (this->size() == 0 || i < 0 || i >= this->size())
		return this->top();
	if (this->size() - 1 == i)
		return this->top();
	Element * p = this->ElementNumer(i-1);
	return p->obiekt;
}

template<typename T>
typename Lista<T>::Element * Lista<T>::ElementNumer(const int id)
{
	Element * p = nullptr;
	if (this->ostatnioSzukanyElement.id <= id && this->ostatnioSzukanyElement.id > 0) {
		p = this->ostatnioSzukanyElement.element;
	}
	else {
		p = this->pHead;
	}
	for (int i = 1 + this->ostatnioSzukanyElement.id; i <= id; i++)
	{
		p = p->pNext;
	}
	this->ostatnioSzukanyElement = { p , id };
	return p;
}

template<typename T>
inline void Lista<T>::remove()
{
	int size = this->size();
	for (int i = 0; i < size; i++) {
		this->pop();
	}
}



