#include "pch.h"
#include "Lista.h"

//template<typename T>
//int Lista<T>::size()
//{
//	//Element * p = this->pHead;
//	int i = 0;
//	//while (p) {
//	//	p = p->pNext;
//	//	i++;
//	//}
//	return i;
//}
//
//template<typename T>
//void Lista<T>::push_back(T element)
//{
//	this->push_back(element, this->pHead);
//}
//
//template<typename T>
//void Lista<T>::push_back(T element, Element * & pHead)
//{
//	if (pHead)
//		this->push_back(element, pHead->pNext);
//	else {
//		pHead = new Element{ element };
//	}
//}
//
//template<typename T>
//T & Lista<T>::top()
//{
//	if(this->size() == 0)
//		this->pHead = new Element;
//	return this->top(this->pHead);
//}
//
//template<typename T>
//T & Lista<T>::top(Element *& pHead)
//{
//	if (pHead->pNext)
//		this->top(pHead->pNext);
//	else {
//		return pHead->obiekt;
//	}
//}
//
//template<typename T>
//void Lista<T>::pop()
//{
//	if (!this->pHead) return;
//	this->pop(this->pHead);
//}
//
//template<typename T>
//void Lista<T>::pop(Element *& pHead)
//{
//	if (pHead->pNext->pNext) {
//		this->pop(pHead->pNext);
//	}
//	else if (pHead->pNext) {
//		Element * p2 = pHead;
//		p2 = p2->pNext;
//		delete p2;
//		pHead->pNext = nullptr;
//	}
//	else {
//		delete pHead;
//		pHead = nullptr;
//	}
//}
//
//template<typename T>
//T & Lista<T>::operator[](int i)
//{
//	if (i < 0 || i >= this->size())
//		cout << "Out of range" << endl;
//	if (this->size() == 0 || i < 0 || i >= this->size)
//		return this->top();
//	if (this->size() - 1 == i)
//		return this->top();
//	Element * p = this->pHead;
//	while (i - 1 > 0) {
//		p = p->pNext;
//		i--;
//	}
//	return p->obiekt;
//}