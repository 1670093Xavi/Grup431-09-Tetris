#include "Partida.h"
#include "GraphicManager.h"
#include <fstream>

void Partida::inicialitza(const string& nomFitxerI, const string& nomFitxerF, const string& nomFitxerM)
{
    if (mode == MODE_NORMAL)
        finalJoc = joc.FiguraNova();
    else
    {
        joc.inicialitza(nomFitxerI);
        inicialitzaFigures(nomFitxerF);
        inicialitzaMoviments(nomFitxerM);
    }
}
void Partida::inicialitzaFigures(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        InfoFigura figura;
        int tipus;
        fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir;
        figura.tipus = TipusFigura(tipus);
        while (!fitxer.eof())
        {
            figures.insereix(figura);
            fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir;
            figura.tipus = TipusFigura(tipus);
        }
        fitxer.close();
    }
}

void Partida::inicialitzaMoviments(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        int tipus;
        fitxer >> tipus;
        while (!fitxer.eof())
        {
            moviments.insereix(TipusMoviment(tipus));
            fitxer >> tipus;
        }
        fitxer.close();
    }
}

void Partida::actualitza(double deltaTime)
{
    if (!finalJoc)
    {
        if (mode == MODE_NORMAL)  // metode actualitza si esta en mode_normal
        {
            if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
                joc.mouFigura(1);
            else
                if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
                    joc.mouFigura(-1);
            if (Keyboard_GetKeyTrg(KEYBOARD_UP))
                joc.giraFigura(GIR_HORARI);
            else
                if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
                    joc.giraFigura(GIR_ANTI_HORARI);
            int nFiles;
            if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
            {
                nFiles = joc.colocaFigura();
                actualitzaPunts(nFiles);
                finalJoc = joc.FiguraNova();
                temps = 0.0;
            }
            else
            {
                temps += deltaTime;
                if (temps > velocitat)
                {
                    nFiles = joc.baixaFigura();
                    if (nFiles != -1)
                    {
                        finalJoc = joc.FiguraNova();
                        actualitzaPunts(nFiles);
                    }
                    temps = 0.0;
                }
            }
        }
        else // sino executem el mode_test
        {
            temps += deltaTime;
            if (temps > velocitat)
            {
                temps = 0.0;
                TipusMoviment m;
                if (moviments.esBuida())
                {
                    finalJoc = true;
                }
                else
                {
                    m = moviments.getPrimer();
                    moviments.elimina();
                    int nFiles;
                    switch (m)
                    {
                    case MOVIMENT_DRETA:
                        joc.mouFigura(1);
                        break;
                    case MOVIMENT_ESQUERRA:
                        joc.mouFigura(-1);
                        break;
                    case MOVIMENT_GIR_HORARI:
                        joc.giraFigura(GIR_HORARI);
                        break;
                    case MOVIMENT_GIR_ANTI_HORARI:
                        joc.giraFigura(GIR_ANTI_HORARI);
                        break;
                    case MOVIMENT_BAIXA_FINAL:
                        nFiles = joc.colocaFigura();
                        actualitzaPunts(nFiles);
                        if (!figures.esBuida())
                        {
                            InfoFigura f = figures.getPrimer();
                            figures.elimina();
                            joc.FiguraNova(f);
                        }
                        else
                            finalJoc = true;
                        break;
                    case MOVIMENT_BAIXA:
                        nFiles = joc.baixaFigura();
                        if (nFiles != -1)
                        {
                            actualitzaPunts(nFiles);
                            if (!figures.esBuida())
                            {
                                InfoFigura f = figures.getPrimer();
                                figures.elimina();
                                joc.FiguraNova(f);
                            }
                            else
                                finalJoc = true;
                        }
                    }
                }
            }

        }
    }
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    joc.dibuixa();
    string msgPunts = "Punts: " + to_string(punts);
    string msgNivell = "Nivell: " + to_string(nivells);
    GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_PUNTUACIO, POS_Y_PUNTUACIO, 0.8, msgPunts);
    GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_NIVELL, POS_Y_NIVELL, 0.8, msgNivell);
    if (finalJoc)
    {
        string msgFinal = "HAS PERDUT!!!";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_FINAL_JOC, POS_Y_FINAL_JOC, 1.8, msgFinal);
    }
}

void Partida::actualitzaPunts(int nFiles)
{
    
    if (nFiles == 0)
        punts += PUNTS_FIGURA;
    else
    {
        punts += PUNTS_FILA;
        switch (nFiles)
        {
        case 2:
            punts += DOBLE_FILA;
            break;
        case 3:
            punts += TRIPLE_FILA;
            break;
        case 4:
            punts += QUADRUPLE_FILA;
            break;
        }
    }
    if (punts > (nivells * CANVI_NIVELL))
    {
        nivells += 1;
        velocitat = CANVI_VELOCITAT;
    }

}
    




