#include "NodeFigura.h"

class Figures
{
public:
	Figures() { m_primer = nullptr; }
	~Figures();
	Figures(const Figures& l);
	Figures& operator=(const Figures& f);
	NodeFigura* insereix(const InfoFigura& pt);
	void elimina();
	int getNElements() const;
	InfoFigura getPrimer() const { return m_primer->getValor(); }
	bool esBuida() const { return m_primer == nullptr; }

private:
	NodeFigura* m_primer;
	NodeFigura* m_ultim;
};