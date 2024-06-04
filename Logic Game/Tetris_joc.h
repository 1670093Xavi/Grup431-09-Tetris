#ifndef TETRIS
#define TETRIS
#include "Partida.h"
#include <list>
using namespace std;

//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"

typedef struct
{
	string nom;
	int punts;
} Punts;

class Tetris_joc
{
public:
	Tetris_joc(const string& fitxerP);
	int Tetris(Screen& p, ModeJoc m, const string& nomFitxerI, const string& nomFitxerF, const string& nomFitxerM);
	void actualitzaPunts(const string& nom, int punts);
	void visualtzaPunts();
	void GuardaPunts(const string& nomFitxer);
private:
	Partida partida;
	list<Punts> puntuacio;
};

#endif