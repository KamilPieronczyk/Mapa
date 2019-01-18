#pragma once
/** Klasa obs³uguj¹ca b³edy */
class MyException :	public exception
{
public:
	/** Typ enum okreœlaj¹cy rodzaj b³edu */
	enum type
	{
		FileDoesNotExist,
		ErrorsInInputFile,
		IncorectParameters
	};

	/** Konstruktor klasy
	* @param rodzaj b³êdu
	* @param szczegó³y b³êdu
	*/
	MyException(type typ,const string& msg);

	/** Funkcja zwracaj¹ca informacje o b³edzie */
	virtual const char* what() const throw ();

	string errorMessage; /**< Zawiera wiadomoœæ informuj¹c¹ o b³êdzie */
};

