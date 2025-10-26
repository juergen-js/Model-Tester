#include "Datei.h"
#include "Attribute.h"


using namespace std;

CDatei::CDatei(string file, int acc , string auftraggeber)
: dateiname(file), access(acc), auftraggeber(auftraggeber)
{
	
	attribute = new CAttribute (file);
	
//	groessenliste = new CGroeessenliste ();

}

CDatei::~CDatei(void)
{
	delete attribute;
//	delete groessenliste;
}
