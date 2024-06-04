#include "NodeMoviment.h"

class Moviments
{
public:
	Moviments() { m_primer = nullptr; }
	~Moviments();
	Moviments(const Moviments& m);
	Moviments& operator=(const Moviments& m);
	NodeMoviment* insereix(const TipusMoviment& pt);
	void elimina();
	int getNElements() const;
	TipusMoviment getPrimer() const { return m_primer->getValor(); }
	bool esBuida() const { return m_primer == nullptr; }

private:
	NodeMoviment* m_primer;
	NodeMoviment* m_ultim;
};
