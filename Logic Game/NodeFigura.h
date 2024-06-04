    #pragma once
#include <stdlib.h>
#include "InfoJoc.h"


class NodeFigura
{
public:
    NodeFigura() { seguent = nullptr; };
    ~NodeFigura() {};
    NodeFigura(const InfoFigura& valor) { m_valor = valor; seguent = nullptr; }
    NodeFigura* getNext() { return seguent; }
    void setNext(NodeFigura* next) { seguent = next; }
    InfoFigura getValor() { return m_valor; }
    void setValor(const InfoFigura& valor) { m_valor = valor; }
private:
    InfoFigura m_valor;
    NodeFigura* seguent;
};
