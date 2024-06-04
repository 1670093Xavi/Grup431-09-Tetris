#ifndef PARTIDA
#define PARTIDA

#include "./Joc.h"
#include "./InfoJoc.h"
#include "Figures.h"
#include "Moviments.h"
#include <ctime>

const int PUNTS_FIGURA = 10;
const int PUNTS_FILA = 100;
const int DOBLE_FILA = 50;
const int TRIPLE_FILA = 75;
const int QUADRUPLE_FILA = 100;

const int CANVI_NIVELL = 200;
const double VELOCITAT_INICIAL = 1.0;
const double CANVI_VELOCITAT = 0.75;

typedef enum
{
    MODE_NORMAL,
    MODE_TEST
} ModeJoc;


using namespace std;

class Partida
{
public:
    Partida() : mode(MODE_NORMAL), temps(0.0), punts(0), nivells(1), velocitat(VELOCITAT_INICIAL), finalJoc(false)
    {
        srand(time(0));
    }
    Partida(ModeJoc mode) : mode(mode), temps(0.0), punts(0), nivells(1), velocitat(VELOCITAT_INICIAL), finalJoc(false)
    {
        srand(time(0));
    }
    void inicialitza(const string& nomFitxerI, const string& nomFitxerF, const string& nomFitxerM);
    void actualitza(double deltaTime);
    int getPunts() const { return punts; }
    void actualitzaPunts(int nFiles);
private:
    double temps;
    Joc joc;
    ModeJoc mode;
    int punts;
    int nivells;
    double velocitat;
    bool finalJoc;
    Figures figures;
    Moviments moviments;

    void inicialitzaFigures(const string& nomFitxer);
    void inicialitzaMoviments(const string& nomFitxer);

};

#endif 
