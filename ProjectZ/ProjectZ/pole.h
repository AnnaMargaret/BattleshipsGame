//Anna Dymowska
#pragma once
#include "statek.h"

class pole {
	friend class plansza;
private:
	statek* zawartosc;
	bool zaatakowane;
};