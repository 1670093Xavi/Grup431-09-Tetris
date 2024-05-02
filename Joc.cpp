#include "Joc.h"
#include <fstream>
using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int tipus, fila, columna, gir;
		fitxer >> tipus >> fila >> columna >> gir;
		m_figura.inicialitza(TipusFigura(tipus), fila, columna);
		for (int i = 0; i < gir; i++)
			m_figura.gira(GIR_HORARI);

		ColorFigura taulerI[MAX_FILA][MAX_COL];
		int color;
		for (int i = 0; i < MAX_FILA; i++)
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> color;
				taulerI[i][j] = ColorFigura(color);
			}
		tauler.iniTauler(taulerI);
		fitxer.close();
	}
}

bool Joc::giraFigura(DireccioGir dir)
{
	m_figura.gira(dir);  //girem la figura
	bool colisiona = tauler.colisions(m_figura); // Comprovem si colisiona amb qualsevol part del tauler
	if (colisiona)
	{
		if (dir == GIR_HORARI) // Si colisiona i hem girat cap a la dreta el girem a l'esquerra una altra vegada perquè quedi en la posició que estaba
			dir = GIR_ANTI_HORARI;
		else
			dir = GIR_HORARI; // El mateix per amb l'altre gir
		m_figura.gira(dir);
	}
	return !colisiona;
}

bool Joc::mouFigura(int X)
{
	m_figura.mou(X); // movem la figura
	bool colisiona = tauler.colisions(m_figura); // Comprovem si colisiona amb qualsevol part del tauler
	if (colisiona)
		m_figura.mou(-X); // Si colisiona la tronem a deixar on estaba
	return !colisiona;
}

int Joc::baixaFigura()
{
	int nFiles = 0;
	m_figura.baixa(); // baixem la figura
	bool colisiona = tauler.colisions(m_figura); // Comprovem si colisiona amb qualsevol part del tauler
	if (colisiona)
	{
		m_figura.puja(); // Si colisiona pujem la figura per deixar-la on estaba
		nFiles = tauler.colocar(m_figura); // colocar la figura i retornar el num de files eliminades
		m_figura.inicialitza(NO_FIGURA, -1, -1); 
	}
	return nFiles;
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer); // Obrim un fitxer de escriptura 
	if (fitxer.is_open())
	{
		if (m_figura.getTipus() != NO_FIGURA) // Comprovem que la figura sigui d'un tipus 
			tauler.dibuixa(m_figura); // dibuixem la figura al tauler
		ColorFigura taulerG[MAX_FILA][MAX_COL];
		tauler.getTauler(taulerG);
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << int(taulerG[i][j]) << " "; // Escrivim el tauler del fitxer
			}
			fitxer << endl;
		}

		fitxer.close();
	}
}
