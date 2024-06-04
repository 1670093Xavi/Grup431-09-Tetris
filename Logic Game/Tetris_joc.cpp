#include "Tetris_joc.h"
#include <fstream>
#include <iostream>
using namespace std;

//Definicio necesaria per poder incloure la llibreria i que trobi el main
//#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"

Tetris_joc::Tetris_joc(const string& fitxerP)
{
	ifstream fitxer;
	fitxer.open(fitxerP);
	if (fitxer.is_open())
	{
		Punts p;
		fitxer >> p.nom >> p.punts;
		while (!fitxer.eof())
		{
			puntuacio.push_back(p);
			fitxer >> p.nom >> p.punts;
		}
		fitxer.close();
	}
}

void Tetris_joc::visualtzaPunts()
{
	list<Punts>::iterator it = puntuacio.begin();
	int o = 1;
	cout << endl;
	cout << "LLISTA DE PUNTS" << endl;
	cout << "---------------" << endl;
	while (it != puntuacio.end())
	{
		cout << o << ". " << it->nom << " " << it->punts << endl;
		o++;
		it++;
	}
	cout << endl;
}

void Tetris_joc::GuardaPunts(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	list<Punts>::iterator it = puntuacio.begin();
	while (it != puntuacio.end())
	{
		fitxer << it->nom << " " << it->punts << endl;
		it++;
	}
	fitxer.close();
}

void Tetris_joc::actualitzaPunts(const string& nom, int p)
{
	list<Punts>::iterator it = puntuacio.begin();
	bool trobat = false;
	while (!trobat && (it != puntuacio.end()))
	{
		if (it->punts > p)
			trobat = true;
		else
			it++;
	}
	Punts punt;
	punt.nom = nom;
	punt.punts = p;
	puntuacio.insert(it, punt);
}

int Tetris_joc::Tetris(Screen& p, ModeJoc m, const string& nomFitxerI, const string& nomFitxerF, const string& nomFitxerM)
{
	//Mostrem per pantalla
	p.show();
	Partida joc(m);
	joc.inicialitza(nomFitxerI, nomFitxerF, nomFitxerM);

	Uint64  PRIMER = SDL_GetPerformanceCounter();
	Uint64 ULTIM = 0;
	double deltaTemps = 0;

	do
	{
		ULTIM = PRIMER;
		PRIMER = SDL_GetPerformanceCounter();
		deltaTemps = (double)((PRIMER - ULTIM) / (double)SDL_GetPerformanceFrequency());

		// Captura tots els events de ratolí i teclat de l'ultim cicle
		p.processEvents();

		joc.actualitza(deltaTemps);

		// Actualitza la pantalla
		p.update();
	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
		//Sortim al presionar ESC
	int punts = joc.getPunts();

	return punts;
}