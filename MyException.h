#pragma once
class MyException :	public exception
{
public:
	enum type
	{
		FileDoesNotExist,
		ErrorsInInputFile,
		IncorectParameters
	};
	MyException(type typ,const string& msg);
	virtual const char* what() const throw ();
	string errorMessage;
};

