//Anna Dymowska
#pragma once
#include "plansza.h"
#include "rozne.h"

class gracz {
	friend class gra;
	friend class czlowiek;
	friend class komputer;

protected:
	plansza* Plansza;
	plansza* Notes;
	statek* Trafiony;
	statek* Zatopiony;
	statek* Glowa;
public:
	virtual bool ustaw_statki() { return false;  }
	virtual bool ustaw_z_pliku();
	virtual bool atakuj(gracz* atakowany) { return false; }
	gracz(plansza* pla, plansza* notes) { Plansza = pla; Notes = notes; Trafiony = new statek(1, 1); Zatopiony = new statek(0, 0); Glowa = NULL; }

	void wypisz_statki_gracza() { Glowa->wypisz_statki();  }
	void kasuj_statki() { delete Glowa; }
};

bool gracz::ustaw_z_pliku() {
	bool ustawiony = 0;
	int x, y;

	int tab[10][3];

	FILE* wejscie;
	char nazwa[K];
	cout<<"Podaj nazwe pliku wejsciowego:";
	//wczytywanie_slowa(nazwa);
	cin >> nazwa;

	if (fopen_s(&wejscie, nazwa, "r") != 0) { cout<<"Nie udalo sie otworzyc pliku wejsciowego"; return 0; }
	char buf[K];
	int k = 0;
	while (!feof(wejscie) && k<10) {
		fscanf_s(wejscie, "%s", buf, (K - 1));
		tab[k][0] = atoi(buf);
		fscanf_s(wejscie, "%s", buf, (K - 1));
		tab[k][1] = atoi(buf);
		fscanf_s(wejscie, "%s", buf, (K - 1));
		tab[k][2] = atoi(buf);

		k++;
	}

	fclose(wejscie);

	//CZTEROMASZTOWIEC
	bool p = tab[0][0];
	statek* cztero = new statek(4, p);
	x = tab[0][1];
	y = tab[0][2];

	ustawiony = Plansza->ustaw_statek(x, y, cztero);
	if (!ustawiony) { cout<<"Bledny plik!"; return false; }
	//}
	Glowa = cztero;

	Plansza->rysuj_plansze();
	statek* wsk = cztero;

	//TROJMASZTOWCE
	for (int i = 0; i < 2; i++) {
		ustawiony = 0;
		bool p = tab[1 + i][0];
		wsk->nast = new statek(3, p);
		x = tab[1 + i][1];
		y = tab[1 + i][2];;

		ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
		if (!ustawiony) { cout<<"Bledny plik!"; return false; }
		//}
		wsk = wsk->nast;
		Plansza->rysuj_plansze();
	}

	//DWUMASZTOWCE
	for (int i = 0; i < 3; i++) {
		ustawiony = 0;
		bool p = tab[3 + i][0];
		wsk->nast = new statek(2, p);
		x = tab[3 + i][1];
		y = tab[3 + i][2];

		ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
		if (!ustawiony) { cout<<"Bledny plik!"; return false; }
		
		wsk = wsk->nast;
		Plansza->rysuj_plansze();
	}

	//JEDNOMASZTOWCE
	for (int i = 0; i < 4; i++) {
		ustawiony = 0;
		bool p = tab[6 + i][0];
		wsk->nast = new statek(1, p);
		x = tab[6 + i][1];
		y = tab[6 + i][2];

		ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
		if (!ustawiony) { cout<<"Zle wspolrzedne. Jeszcze raz."; }
		
		wsk = wsk->nast;
		Plansza->rysuj_plansze();
	}
	return true;

}

class czlowiek : public gracz {

public:
	czlowiek(plansza* pla, plansza* notes) : gracz(pla, notes) {}


	bool ustaw_statki(){
		int tab[10][3];

		bool ustawiony = 0;
		int x, y;
		//CZTEROMASZTOWIEC
		cout<<"\nUstaw czteromasztowiec:";
		cout<<"\nJesli chcesz ustawic pionowo podaj 0, jesli poziomo podaj 1:";
		bool p = wczytaj_int();	//bool p = 1;
		statek* cztero = new statek(4, p);
		while (!ustawiony) {
			cout<<"\nPodaj wspolrzedna pionowa dziobu:";
			x = wczytaj_int();
			cout<<"\nPodaj wspolrzedna pozioma dziobu:";
			y = wczytaj_int();

			ustawiony = Plansza->ustaw_statek(x, y, cztero);
			if (!ustawiony) { cout<<"Zle wspolrzedne. Jeszcze raz."; }
		}
		Glowa = cztero;

		tab[0][0] = p; tab[0][1] = x; tab[0][2] = y;

		Plansza->rysuj_plansze();
		statek* wsk = cztero;
		
		//TROJMASZTOWCE
		for (int i = 0; i < 2; i++) {
			ustawiony = 0;
			cout<<"\nUstaw trojmasztowiec:";
			cout<<"\nJesli chcesz ustawic pionowo podaj 0, jesli poziomo podaj 1:";
			bool p = wczytaj_int();	//bool p = 1;
			wsk->nast = new statek(3, p);
			while (!ustawiony) {
				cout<<"\nPodaj wspolrzedna pionowa dziobu:";
				x = wczytaj_int();
				cout<<"\nPodaj wspolrzedna pozioma dziobu:";
				y = wczytaj_int();
				
				ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
				if (!ustawiony) { cout<<"Zle wspolrzedne. Jeszcze raz."; }
			}
			wsk = wsk->nast;
			tab[1 + i][0] = p; tab[1+i][1] = x; tab[1+i][2] = y;
			Plansza->rysuj_plansze();
		}

		//DWUMASZTOWCE
		for (int i = 0; i < 3; i++) {
			ustawiony = 0;
			cout<<"\nUstaw dwumasztowiec:";
			cout<<"\nJesli chcesz ustawic pionowo podaj 0, jesli poziomo podaj 1:";
			bool p = wczytaj_int();	//bool p = 1;
			wsk->nast = new statek(2, p);
			while (!ustawiony) {
				cout<<"\nPodaj wspolrzedna pionowa dziobu:";
				x = wczytaj_int();
				cout<<"\nPodaj wspolrzedna pozioma dziobu:";
				y = wczytaj_int();

				ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
				if (!ustawiony) {cout<<"Zle wspolrzedne. Jeszcze raz."; }
			}
			wsk = wsk->nast;
			tab[3 + i][0] = p; tab[3 + i][1] = x; tab[3 + i][2] = y;
			Plansza->rysuj_plansze();
		}

		//JEDNOMASZTOWCE
		for (int i = 0; i < 4; i++) {
			ustawiony = 0;
			cout<<"\nUstaw jednomasztowiec:";
			bool p = 1;
			wsk->nast = new statek(1, p);
			while (!ustawiony) {
				cout<<"\nPodaj wspolrzedna pionowa dziobu:";
				x = wczytaj_int();
				cout<<"\nPodaj wspolrzedna pozioma dziobu:";
				y = wczytaj_int();

				ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
				if (!ustawiony) { cout<<"Zle wspolrzedne. Jeszcze raz."; }
			}
			wsk = wsk->nast;
			tab[6 + i][0] = p; tab[6 + i][1] = x; tab[6 + i][2] = y;
			Plansza->rysuj_plansze();
		}

		cout<<"Czy chcesz zapisac to ustawienie statkow na przyszlosc? 0 - nie, 1- tak";
		bool zapis = wczytaj_int();
		if (zapis) {
			FILE* wyjscie;
			char nazwa_out[K];
			cout<<"Podaj poczatek nazwy pliku wyjsciowego:";
			wczytywanie_slowa(nazwa_out);
			//cin >> nazwa_out;
			
			char nazwa_out1[2 * K];
			strcpy_s(nazwa_out1, nazwa_out);
			char koncowka[K];
			strcpy_s(koncowka, ".txt");
			strcat_s(nazwa_out1, koncowka);
			if (fopen_s(&wyjscie, nazwa_out1, "a+") != 0) { cout<<"Nie udalo sie otworzyc pliku wyjsciowego"; exit(1); }

			for (int k = 0; k < 10; k++) {
					fprintf(wyjscie, "%d\t%d\t%d\n", tab[k][0], tab[k][1], tab[k][2]); 
			}
		
			fclose(wyjscie);
		//koniec zapisu
		}
		return true;
	}

	bool atakuj(gracz* atakowany) {
		cout<<"\nAtakuj! ";
		int x = -1; int y =-1;
		bool zaatakowane = 1;
		
		while (zaatakowane) {
			x = -1; y = -1;
			while (x < 0 || x>9) {
				cout<<"\nPodaj wspolrzedna pionowa ataku:";
				x = wczytaj_int();
			}
			while (y < 0 || y>9) {
				cout<<"\nPodaj wspolrzedna pozioma ataku:";
				y = wczytaj_int();
			}

			zaatakowane = atakowany->Plansza->czy_bylo_atakowane(x,y) ;
			if (zaatakowane) {
				cout<<"\nTo pole bylo juz atakowane. Jeszcz raz.";
			}
		}

			int traf = atakowany->Plansza->przyjmij_atak(x, y);
			if (traf == 1) { Notes->notuj(x, y, Trafiony); }
			else if (traf == 2) { Notes->notuj(x, y, Zatopiony); }
			else { Notes->notuj(x, y, NULL); }

			return traf;

	}
	

};

class komputer : public gracz {

public:
	komputer(plansza* pla, plansza* notes) : gracz(pla, notes) {}

	bool ustaw_statki() {
		bool ustawiony = 0;
		int x, y;
		//CZTEROMASZTOWIEC
		bool p = 1;
		statek* cztero = new statek(4, p);
		while (!ustawiony) {
			x =0;
			y = 0;
			ustawiony = Plansza->ustaw_statek(x, y, cztero);
			if (!ustawiony) { printf("Zle wspolrzedne. Jeszcze raz."); }
		}
		Glowa = cztero;
		statek* wsk = cztero;
		//TROJMASZTOWCE
		for (int i = 0; i < 2; i++) {
			ustawiony = 0;
			bool p = 1;
			wsk->nast = new statek(3, p);
			while (!ustawiony) {
				x = 2+2*i;
				y = 0;
				ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
				if (!ustawiony) { printf("Zle wspolrzedne. Jeszcze raz."); }
			}
			wsk = wsk->nast;
		}
		//DWUMASZTOWCE
		for (int i = 0; i < 3; i++) {
			ustawiony = 0;
			bool p = 1;
			wsk->nast = new statek(2, p);
			while (!ustawiony) {
				x = 2+2*i;
				y = 4;
				ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
				if (!ustawiony) { printf("Zle wspolrzedne. Jeszcze raz."); }
			}
			wsk = wsk->nast;
		}
		//JEDNOMASZTOWCE
		for (int i = 0; i < 4; i++) {
			ustawiony = 0;
			bool p = 1;
			wsk->nast = new statek(1, p);
			while (!ustawiony) {
				x = 2 + 2 * i;
				y = 8;
				ustawiony = Plansza->ustaw_statek(x, y, wsk->nast);
				if (!ustawiony) { printf("Zle wspolrzedne. Jeszcze raz."); }
			}
			wsk = wsk->nast;
		}
		printf("Komputer ustawil statki. ");
		return true;
	}

	bool atakuj(gracz* atakowany) {
		int x = -1; int y = -1;
		bool zaatakowane = 1;

		while (zaatakowane) {
				srand(time(NULL));
				x = rand() % 10;
				srand(time(NULL));
				y = rand() % 10;
			zaatakowane = atakowany->Plansza->czy_bylo_atakowane(x, y);
		}

		int traf = atakowany->Plansza->przyjmij_atak(x, y);
		if (traf == 1) { Notes->notuj(x, y, Trafiony); }
		else if (traf == 2) { Notes->notuj(x, y, Zatopiony); }
		else { Notes->notuj(x, y, NULL); }

		return traf;
	}

};