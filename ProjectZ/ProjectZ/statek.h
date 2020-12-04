//Anna Dymowska
#pragma once

class statek {

	const int dlugosc;
	int ile_calych_masztow;
	const bool poziomo;

public:	
	statek* nast;
	
	statek(int n, bool p): dlugosc(n), poziomo(p) { ile_calych_masztow = n; nast = NULL; }

	int get_ile_maszt() { return ile_calych_masztow; };
	int get_dlugosc() { return dlugosc; };
	int get_poziom() { return poziomo; };
	void traf() { ile_calych_masztow--;  };

	void wypisz_statek() { printf("statek: %d %d %d ", dlugosc, ile_calych_masztow, poziomo); }
	void wypisz_statki() {
		statek* wsk = this;
		while (wsk != NULL) {
			wsk->wypisz_statek();
			wsk = wsk->nast;
		}
	};

	int licz_statki() {
		int ile = 0;
		statek* wsk = this;
		while (wsk != NULL) {
			if (wsk->get_ile_maszt() != 0) { ile++; }
			wsk = wsk->nast;
		}
		return ile;
	}

	~statek() { delete nast; };

};