#pragma once
#include <string>

using namespace std;

class CDatei
{
public:
	CDatei(string file, int acc , string auftraggeber);
	
	~CDatei(void);
private:
	int id;
	string dateiname;
	int access;
	string auftraggeber;
	class CAttribute* attribute;
	class CGroeessenliste* groessenliste;


};
