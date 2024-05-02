#include "Figura.h"

void::Figura::reset()
{
	for (int i = 0; i < m_alcada; i++)
	{
		for (int j = 0; j < m_amplada; j++)
		{
			m_matriu[i][j] = 0;
		}	
	}
}

void Figura::inicialitzaTipusFigura(TipusFigura tipus)
{
	switch (tipus)
	{
	case FIGURA_J:
		m_amplada = 3;
		m_alcada = 3;
		reset();
		m_matriu[0][0] = 1;
		m_matriu[1][0] = 1;
		m_matriu[1][1] = 1;
		m_matriu[1][2] = 1;
		m_color = COLOR_BLAUFOSC;
		break;
	case FIGURA_L:
		m_amplada = 3;
		m_alcada = 3;
		reset();
		m_matriu[0][2] = 1;
		m_matriu[1][0] = 1;
		m_matriu[1][1] = 1;
		m_matriu[1][2] = 1;
		m_color = COLOR_TARONJA;
		break;
	case FIGURA_S:
		m_amplada = 3;
		m_alcada = 3;
		reset();
		m_matriu[0][1] = 1;
		m_matriu[0][2] = 1;
		m_matriu[1][0] = 1;
		m_matriu[1][1] = 1;
		m_color = COLOR_VERD;
		break;
	case FIGURA_Z:
		m_amplada = 3;
		m_alcada = 3;
		reset();
		m_matriu[0][0] = 1;
		m_matriu[0][1] = 1;
		m_matriu[1][1] = 1;
		m_matriu[1][2] = 1;
		m_color = COLOR_VERMELL;
		break;
	case FIGURA_T:
		m_amplada = 3;
		m_alcada = 3;
		reset();
		m_matriu[0][1] = 1;
		m_matriu[1][0] = 1;
		m_matriu[1][1] = 1;
		m_matriu[1][2] = 1;
		m_color = COLOR_MAGENTA;
		break;
	case FIGURA_I:
		m_amplada = 4;
		m_alcada = 4;
		reset();
		m_matriu[1][0] = 1;
		m_matriu[1][1] = 1;
		m_matriu[1][2] = 1;
		m_matriu[1][3] = 1;
		m_color = COLOR_BLAUCEL;
		break;
	case FIGURA_O:
		m_amplada = 2;
		m_alcada = 2;
		m_matriu[0][0] = 1;
		m_matriu[0][1] = 1;
		m_matriu[1][0] = 1;
		m_matriu[1][1] = 1;
		m_color = COLOR_GROC;
		break;
	}
}

void Figura::inicialitza(TipusFigura tipus, int fila, int columna)
{
	m_tipus = tipus;
	m_fila = fila;
	m_columna = columna;
	m_gir = 0;
	inicialitzaTipusFigura(tipus);
}

void Figura::getMatriu(int matriu[MAX_ALCADA][MAX_AMPLADA]) const
{
	for (int i = 0; i < m_alcada; i++)
	{
		for (int j = 0; j < m_amplada; j++)
		{
			matriu[i][j] = m_matriu[i][j];
		}
			
	}
		
}

void Figura::mou(int X)
{
	m_columna += X;
}

void Figura::baixa()
{
	m_fila += 1;
}

void Figura::puja()
{
	m_fila -= 1;
}

void Figura::gira(DireccioGir direccio)
{
	transposaMatriu();
	if (direccio == GIR_HORARI)
	{
		int PrimeraCol, UltimaCol;
		if (m_amplada != 2)
		{
			if (m_amplada == 3)
			{
				PrimeraCol = 0;
				UltimaCol = 2;

			}
			else
			{
				PrimeraCol = 1;
				UltimaCol = 2;
			}
			int NovaMatriu;
			for (int i = 0; i < m_alcada; i++)
			{
				NovaMatriu = m_matriu[i][PrimeraCol];
				m_matriu[i][PrimeraCol] = m_matriu[i][UltimaCol];
				m_matriu[i][UltimaCol] = NovaMatriu;
			}
		}
		m_gir = (m_gir + 1) % 4;
	}
	else
	{
		int PrimeraFila, UltimaFila;
		if (m_alcada != 2)
		{
			if (m_alcada == 3)
			{
				PrimeraFila = 0;
				UltimaFila = 2;

			}
			else
			{
				PrimeraFila = 1;
				UltimaFila = 2;
			}
			int NovaMatriu;
			for (int j = 0; j < m_amplada; j++)
			{
				NovaMatriu = m_matriu[PrimeraFila][j];
				m_matriu[PrimeraFila][j] = m_matriu[UltimaFila][j];
				m_matriu[UltimaFila][j] = NovaMatriu;
			}
		}
	}
		m_gir = (m_gir - 1) % 4;
}



void Figura::transposaMatriu()
{
	int NovaMatriu;
	for (int i = 1; i < m_alcada; i++)
		for (int j = 0; j < i; j++)
		{
			NovaMatriu = m_matriu[i][j];
			m_matriu[i][j] = m_matriu[j][i];
			m_matriu[j][i] = NovaMatriu;
		}
}
