#include "Figures.h"

Figures::~Figures()
{
	while (m_primer != nullptr)
		elimina();
}

Figures::Figures(const Figures& l)
{
	m_primer = nullptr;
	m_ultim = nullptr;
	NodeFigura* aux = l.m_primer;
	NodeFigura* aux_nova = m_primer;
	while (aux != nullptr)
	{
		aux_nova = insereix(aux->getValor());
		aux = aux->getNext();
	}

}

Figures& Figures::operator=(const Figures& f)
{
	if (this != &f)
	{
		while (m_primer != nullptr)
			elimina();
		NodeFigura* aux = f.m_primer;
		NodeFigura* aux_nova = m_primer;
		while (aux != nullptr)
		{
			aux_nova = insereix(aux->getValor());
			aux = aux->getNext();
		}
	}
	return *this;
}

NodeFigura* Figures::insereix(const InfoFigura& valor)
{
	NodeFigura* aux = new NodeFigura;
	if (aux != nullptr)
	{
		aux->setValor(valor);
		aux->setNext(nullptr);
		if (m_primer == nullptr)
		{
			m_primer = aux;
		}
		else
		{
			m_ultim->setNext(aux);
		}
		m_ultim = aux;
	}

	return aux;
}

void Figures::elimina()
{
	NodeFigura* aux;
	if (m_primer == m_ultim)
	{
		delete m_primer;
		m_primer = nullptr;
		m_ultim = nullptr;
	}
	else
	{
		aux = m_primer->getNext();
		delete m_primer;
		m_primer = aux;
	}
}

int Figures::getNElements() const
{
	int nElements = 0;
	NodeFigura* aux = m_primer;
	while (aux != NULL)
	{
		nElements++;
		aux = aux->getNext();
	}

	return nElements;
}