//Anna Dymowska
#include "biblioteki.cpp"
#define K 40 // dlugosc slow
#include "pole.h"
#include "plansza.h"

void plansza::tworz_plansze() {
		for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tabela[i][j].zawartosc = NULL;
			tabela[i][j].zaatakowane = 0;
		}
	}
};

bool plansza::czy_bylo_atakowane(int x, int y) { return this->tabela[x][y].zaatakowane; };

void plansza::rysuj_plansze() {
	printf("\n 0123456789\n");

	for (int i = 0; i < N; i++) {
		printf("%d", i);
		for (int j = 0; j < N; j++) {

			if (tabela[i][j].zaatakowane == 0) {
				if (tabela[i][j].zawartosc == NULL) {
					printf("~");
				}
				else { printf("S"); }
			}
			else {
				if (tabela[i][j].zawartosc == NULL) {
					printf("x");
				}
				else { 
					if (tabela[i][j].zawartosc->get_ile_maszt() == 0) { printf("+"); }
					else {printf("$");}
					 
				}			
			}
		}
		printf("\n");
	}

};

bool plansza::jest_miejsce(int x, int y, int n, int p) {
	if(x<0 || x>9 || y<0 || y>9) { return false; }

	if (p == 0) {
		for (int i = 0; i < n+2; i++) {
			if ( (x-1+i >= 0 && x - 1 + i <= 9) && (tabela[x - 1 + i][y].zawartosc != NULL)) {return false;}
			if ((x - 1 + i >= 0 && x - 1 + i <= 9) && (y-1 >= 0) && (tabela[x - 1 + i][y-1].zawartosc != NULL)) { return false; }
			if ((x - 1 + i >= 0 && x - 1 + i <= 9) && (y + 1 <= 9) && (tabela[x - 1 + i][y + 1].zawartosc != NULL)) { return false; }
			if (x + n > N) { return false; }
		}
	}
	else {
		for (int i = 0; i < n + 2; i++) {
			if ((y - 1 + i >= 0 && y - 1 + i <= 9) &&  tabela[x][y - 1 + i].zawartosc != NULL) {return false;}
			if ((y - 1 + i >= 0 && y - 1 + i <= 9) && (x + 1 <= 9) &&  tabela[x+1][y - 1 + i].zawartosc != NULL) { return false; }
			if ((y - 1 + i >= 0 && y - 1 + i <= 9) && (x - 1 >= 0) &&  tabela[x-1][y - 1 + i].zawartosc != NULL) { return false; }
			if (y + n > N) { return false; }
		}

	}
	return true;
};

bool plansza::ustaw_statek(int x, int y, statek* wsk) {
	
	int n = wsk->get_dlugosc();
	bool p = wsk->get_poziom();

	if (!jest_miejsce(x, y, n, p)) { return false; }

	if (p == 0) { //poziomo
		for (int i = 0; i < n; i++) {
			tabela[x + i][y].zawartosc = wsk;
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			tabela[x][y + i].zawartosc = wsk;
		}

	}

	return true;
};

int plansza::przyjmij_atak(int x, int y) {
	tabela[x][y].zaatakowane = 1;

	if (tabela[x][y].zawartosc != NULL) {
		tabela[x][y].zawartosc->traf();

		if (tabela[x][y].zawartosc->get_ile_maszt() == 0) { return 2; }
		else return 1;
	}

	return 0;
};

void plansza::notuj(int x, int y, statek* seg) {
	tabela[x][y].zawartosc = seg;
	tabela[x][y].zaatakowane = 1;
};

