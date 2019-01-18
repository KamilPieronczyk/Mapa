#pragma once
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

/** Szablon listy */
template<typename T>
class Lista
{
	/** Element listy */
	struct Element {
		T obiekt; /**< Element listy */
		Element * pNext; /**< WskaŸnik na kolejny element w liœcie */
	};

	/** Ostatnio szukany element w liœcie */
	struct OstatnioSzukanyElement {
		Element * element = nullptr; /**< WskaŸnik na ostatnio szukany element w liœcie */
		int id = 0; /**< Jego id w liœcie */
	};

	/** Klasa Iterator zapewnia klasie listy integralnoœæ z pêtl¹ for */
	class Iterator {
		Element * element; /**< WskaŸnik na element listy*/
	public:
		/** Konstruktor klasy */
		Iterator(Element * _element) :element(_element) {};

		/** Funkcja odpowiedzialan za aktualnego elementu listy*/
		T& operator*() { return element->obiekt; }

		/** Operator do przeskoczenia na kolejny element w liœcie */
		Iterator& operator++() { element = element->pNext; return *this; }

		/** Operator sprawdzaj¹cy warunek stopu w liœcie */
		bool operator!=(const Iterator& it) const { return element ? true : false; };
	};
public:
	Element * pHead = nullptr; /**< WskaŸnik na pierwszy element */
	/** Zwraca wielkoœæ listy */
	int size();

	/** Dodaje element na koniec listy 
	* @param Element typu T
	*/
	void push_back(T element);

	/** Zwraca referencje na ostatni element w liœcie */
	T & top();

	/** Usuwa ostatni element listy */
	void pop();

	/** Zwraca i-ty element listy*/
	T & operator [](int i);

	/** Zwraca pierwszy element z listy */
	Iterator begin() { return { pHead }; };

	/** Zwraca wartoœæ okreœlaj¹c¹ koniec listy */
	Iterator end() { return { nullptr }; };

	/** Usuwa liste */
	void remove();
private:
	/** Zwraca referencje na ostatni element w liœcie
	* @param pHead - pierwszy element z listy
	*/
	T & top(Element * & pHead);

	/** Usuwa ostatni element listy 
	* @param pHead - pierwszy element z listy
	*/
	void pop(Element * & pHead);

	/** Dodaje element na koniec listy
	* @param Element typu T
	* @param pHead - pierwszy element z listy
	*/
	void push_back(T element, Element * & pHead);

	OstatnioSzukanyElement ostatnioSzukanyElement;

	/** Zwraca element z listy o podanym indeksie
	* @param id - indeks elementu na liœcie
	*/
	Element * ElementNumer(const int id);
};

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

template<typename T>
int Lista<T>::size()
{
	Element * p = this->pHead;
	int i = 0;
	while (p) { // while poruszaj¹cy siê po liœcie
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
	if (this->size() == 0) { // Je¿eli lista jest pusta to zwraca imitacje elementu listy
		T temp;
		return temp;
	}		
	return this->top(this->pHead); // uruchamia funkcje top
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
	this->pop(this->pHead); // uruchamia funkcje pop
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
	while (i - 1 > 0) { // wyszukuje przedostatni element z listy
		p = p->pNext;
		i--;
	}
	Element *& p2 = p->pNext;
	delete p2; // usuwa ostatni element
	p->pNext = nullptr;
}

template<typename T>
T & Lista<T>::operator[](int i)
{
	if (i < 0 || i >= this->size()) // sprawdza czy element o podanym indeksie istnieje
		cout << "Out of range" << endl;
	if (this->size() == 0 || i < 0 || i >= this->size()) // zwraca top z listy gdy jest Ÿle podany indeks elementu
		return this->top();
	if (this->size() - 1 == i) // sprawdza czy szukany element jest ostatni w liœcie
		return this->top();
	Element * p = this->ElementNumer(i-1);
	return p->obiekt;
}

template<typename T>
typename Lista<T>::Element * Lista<T>::ElementNumer(const int id)
{
	Element * p = nullptr;
	if (this->ostatnioSzukanyElement.id <= id && this->ostatnioSzukanyElement.id > 0) { // jezeli ostatnio szukany element jest po indeksach blizej szukanego niz element pierwszy to automatycznie pHead jest zmieniany na niego
		p = this->ostatnioSzukanyElement.element;
		for (int i = 1 + this->ostatnioSzukanyElement.id; i <= id; i++)
		{
			p = p->pNext;
		}
	}
	else {
		p = this->pHead;
		for (int i = 0; i <= id; i++)
		{
			p = p->pNext;
		}
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



