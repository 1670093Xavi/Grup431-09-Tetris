#include "Tauler.h"
#include <iostream>
using namespace std;

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
        filasLibres[i] = MAX_COL;
    //inicialitzem les files lliures a 8

    for (int i = 0; i < MAX_FILA; i++)
    {
        tauler[i][0] = NO_COLOR;
        tauler[i][1] = NO_COLOR;
        tauler[i][MAX_COL + 2] = NO_COLOR;
        tauler[i][MAX_COL + 3] = NO_COLOR;

        for (int j = 0; j < MAX_COL; j++)
            tauler[i][j + 2] = COLOR_NEGRE;
    }
    //posem els marges a NO_COLOR i el tauler a COLOR_NEGRE

    for (int j = 0; j < MAX_COL + 4; j++)
    {
        tauler[MAX_FILA][j] = NO_COLOR;
        tauler[MAX_FILA + 1][j] = NO_COLOR;
    }


}

void Tauler::iniTauler(ColorFigura taulerI[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
        filasLibres[i] = MAX_COL;
    //inicialitzem les files lliures a 8

    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            tauler[i][j + 2] = taulerI[i][j]; //inicialitzem el tauler (+2 pels marges)
            if (taulerI[i][j] != COLOR_NEGRE)
                filasLibres[i]--;
        }
}

bool Tauler::colisions(const Figura& figura)
{
     //inits
    bool colision = false;
    int m[MAX_ALCADA][MAX_AMPLADA];
    figura.getMatriu(m);
    int filaM = 0;
    int fila = figura.getFila() - 1;

    while ((!colision) && (filaM < figura.getAlcada())) {
        int colM = 0;
        int col = figura.getColumna() + 1;
        
        while ((!colision) && (colM < figura.getAmplada())){
            // Comprovem si hi ha colisió
            if ((m[filaM][colM] * tauler[fila][col]) != 0) {
                colision = true;
            }
            
            colM++;
            col++;
        }

        filaM++;
        fila++;
    } 

    return colision;

}

int Tauler::colocar(const Figura & figura) 
{
        //declarem els atributs de la figura y de la matriu

        int fila = figura.getFila() - 1;
        int nFiles = 0;
        int m[MAX_ALCADA][MAX_AMPLADA];
        ColorFigura color = figura.getColor();
        figura.getMatriu(m);



        for (int filaM = 0; filaM < figura.getAlcada(); filaM++) {
            int col = figura.getColumna() + 1;

            for (int colM = 0; colM < figura.getAmplada(); colM++) {

                // Mirem si la posició está ocupada
                if (m[filaM][colM] > 0) {
                    tauler[fila][col] = color; // Si ho está coloquem la peça
                    filasLibres[fila]--;


                    if (filasLibres[fila] == 0) {  //Mirem si la fila ha quedat completa per eliminarla
                        nFiles++;
                        if (fila > 0) //nomes en casos on la fila no sigui la ultima
                        {
                            for (int i = fila; i > 0; i--)
                            {
                                for (int j = 0; j < MAX_COL; j++)
                                {
                                    tauler[i][j + 2] = tauler[i - 1][j + 2]; //desplaçem la fila a la de sota
                                }
                                filasLibres[i] = filasLibres[i - 1]; //alliberem la fila
                            }
                        }
                        for (int i = 0; i < MAX_COL; i++)
                            tauler[0][i + 2] = COLOR_NEGRE; //com hem baixat totes les files hem de posar la primera a COLOR_NEGRE
                        filasLibres[0] = MAX_COL;
                    }

                }
                col++;
            }
            fila++;
        }
        return nFiles;
}


void Tauler::dibuixa(const Figura& figura) {
    //declarem els atributs de la figura y de la matriu

    int fila = figura.getFila() - 1;
    int m[MAX_ALCADA][MAX_AMPLADA];
    ColorFigura color = figura.getColor();
    figura.getMatriu(m);



    for (int filaM = 0; filaM < figura.getAlcada(); filaM++) {
        int col = figura.getColumna() + 1;

        for (int colM = 0; colM < figura.getAmplada(); colM++) {

            // Mirem si la posició está ocupada
            if (m[filaM][colM] > 0) {
                tauler[fila][col] = color;
            }
            col++;
        }
        fila++;
    }
}

void Tauler::getTauler(ColorFigura taulerG[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            taulerG[i][j] = tauler[i][j + 2];
    }
}

void Tauler::dibuixar()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
    for (int i = 0; i < MAX_FILA; i++)
        for (int j = 0; j < MAX_COL; j++)
        {
            if (tauler[i][j + 2] != COLOR_NEGRE)
                dibuixaQuadrat(tauler[i][j + 2], POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + (i * MIDA_QUADRAT));
        }

}