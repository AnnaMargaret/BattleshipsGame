//Anna Dymowska
#pragma once

#include "pole.h"
#define N 10 //wielkosc planszy

class plansza {
	pole tabela[N][N];

public:

	void rysuj_plansze();
	void tworz_plansze();

	//ustawianie statkow
	bool ustaw_statek(int x, int y, statek *wsk); // TRUE jesli ustawi
	bool jest_miejsce(int x, int y, int n, int p);

	int przyjmij_atak(int x, int y); // 1 jesli zostal trafiony statek, 2 - zaatopiony, 0 - spudlowany strzal
	void notuj(int x, int y, statek* seg);

	bool czy_bylo_atakowane(int x, int y); // czy dane pole bylo juz zaatakowane

};


