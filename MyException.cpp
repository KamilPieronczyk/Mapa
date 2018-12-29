#include "pch.h"
#include "MyException.h"

MyException::MyException(type typ, const string & msg)
{
	switch (typ)
	{
	case MyException::FileDoesNotExist:
		this->errorMessage = "Plik '" + msg + "' nie istnieje";
		break;
	case MyException::ErrorsInInputFile:
		this->errorMessage = "Bledy w pliku wejsciowym - " + msg;
		break;
	case MyException::IncorectParameters:
		this->errorMessage = "Niezdefiniowano poprawnie parametrow";
		break;
	}
}

const char * MyException::what() const throw()
{
	return this->errorMessage.c_str();
}
