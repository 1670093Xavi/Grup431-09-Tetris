#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	Joc() {}
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir dir);
	bool mouFigura(int X);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);

private:
	Tauler tauler;
	Figura m_figura;
};
#endif
