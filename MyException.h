#pragma once
/** Klasa obs�uguj�ca b�edy */
class MyException :	public exception
{
public:
	/** Typ enum okre�laj�cy rodzaj b�edu */
	enum type
	{
		FileDoesNotExist,
		ErrorsInInputFile,
		IncorectParameters
	};

	/** Konstruktor klasy
	* @param rodzaj b��du
	* @param szczeg�y b��du
	*/
	MyException(type typ,const string& msg);

	/** Funkcja zwracaj�ca informacje o b�edzie */
	virtual const char* what() const throw ();

	string errorMessage; /**< Zawiera wiadomo�� informuj�c� o b��dzie */
};

