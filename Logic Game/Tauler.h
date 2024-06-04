#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 21;
const int MAX_COL = 11;

class Tauler
{
public:
    Tauler();
    void iniTauler(ColorFigura taulerI[MAX_FILA][MAX_COL]);
    void getTauler(ColorFigura taulerG[MAX_FILA][MAX_COL]);
    int colocar(const Figura& figura);
    bool colisions(const Figura& figura);
    void dibuixa(const Figura& figura);
    void dibuixar();
private:
    ColorFigura tauler[MAX_FILA + 2][MAX_COL + 4];
    int filasLibres[MAX_FILA];
};
#endif
