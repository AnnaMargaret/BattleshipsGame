//Anna Dymowska
#define K 40 // dlugosc slow
#include "biblioteki.cpp"
#include "gracz.h"
#include "plansza.h"


class gra {
public:
	gracz* Gracz1;
	gracz* Gracz2;
	gracz *Atakujacy;
	gracz* Atakowany;

	plansza* PlanszaG1;
	plansza* NotesG1;
	plansza* PlanszaG2;
	plansza* NotesG2;

	bool vsAI;

public:	
	void wyswietlPlansze() { PlanszaG1->rysuj_plansze(); };

	//tworzy puste plansze i notatniki
	void buduj_plansze() { 
		PlanszaG1 = new plansza; PlanszaG1->tworz_plansze(); 
		NotesG1 = new plansza; NotesG1->tworz_plansze();
		PlanszaG2 = new plansza; PlanszaG2->tworz_plansze();
		NotesG2 = new plansza; NotesG2->tworz_plansze();
	};

	//gra moze byc z komputerem lub dla dwojga graczy
	gra(bool AI){ 
		vsAI = AI;
		buduj_plansze();
		czlowiek* G1 = new czlowiek(PlanszaG1, NotesG1); Gracz1 = G1;
		if (!AI) { czlowiek* G2 = new czlowiek(PlanszaG2, NotesG2); Gracz2 = G2; } 
		else { komputer* G2 = new komputer(PlanszaG2, NotesG2); Gracz2 = G2;}
		Atakujacy = Gracz1; Atakowany = Gracz2;
	};

	void tura() {
		bool ruch = 1;
		while (ruch && !this->czy_wygrana() ) {
			
			cout<<"Twoja plansza:\n ";
			Atakujacy->Plansza->rysuj_plansze();
			cout<<"Twoj notes:\n ";
			Atakujacy->Notes->rysuj_plansze();

			if (Atakujacy == Gracz1) { cout<<"Ruch Gracza 1: "; }
			else {cout<<"Ruch Gracza 2: "; }
			ruch = Atakujacy->atakuj(Atakowany);
		}

		//ZAMIANA graczy
		gracz* tmp;
		tmp = Atakujacy;
		Atakujacy = Atakowany;
		Atakowany = tmp;

	};

	//sprawdzanie czy gra jest zakonczona
	bool czy_wygrana() {
		int a = Atakujacy->Glowa->licz_statki();
		if (Gracz1->Glowa->licz_statki() == 0) { cout<<"Wygral Gracz 2 ! "; return true; }
		if (Gracz2->Glowa->licz_statki() == 0) { cout<<"Wygral Gracz 1 ! "; return true; }
		return false; 
	};

};



int main(){
	//LEGENDA
	cout << "~ - morze | S - statek | x - trafienie w wode | $ - trafiony statek | zatopione statki: +++ lub $+$$ (juz jeden plus na statku oznacza statek stracony)";
	int AI;

	//Wybor czy gra z komputerem czy graczem
	cout<< "\nJesli chcesz grac z innym graczem podaj 0, jesli z komputerem podaj 1:";
	AI = wczytaj_int();
	if (AI) { 
		cout<<"Grasz z komputerem.\n"; 
	}
	else {
		cout<<"Gra dla dwoch graczy.\n"; 
	}

	gra Gra(AI);
	Gra.wyswietlPlansze();

	//USTAWIANIE STATKOW NA PLANSZY z pliku lub recznie
	cout<<"Gracz1, czy chcesz wczytac plansze z pliku? 0 - nie, np. 1 - tak:";
	bool z_pliku = wczytaj_int();

	if (z_pliku) { bool ok_plik = Gra.Gracz1->ustaw_z_pliku(); if (!ok_plik) { return 1; } }
	else { Gra.Gracz1->ustaw_statki(); }
	//Gra.Gracz1->wypisz_statki_gracza();

	bool z_pliku2 = 0;
	if (!AI) { 
		cout<<"Gracz2, czy chcesz wczytac plansze z pliku? 0 - nie, np. 1 - tak:";
	}
	else {
		cout<<"Czy chcesz wczytac plansze dla komputera z pliku? 0 - nie, np. 1 - tak:";
	}
	z_pliku2 = wczytaj_int();	

	if (z_pliku2) { bool ok_plik = Gra.Gracz2->ustaw_z_pliku(); if (!ok_plik) { return 1; } }
	else { Gra.Gracz2->ustaw_statki(); }
	//koniec ustawiania statkow

	int wygrana = 0;

	while (!wygrana) {
		Gra.tura();
		wygrana = Gra.czy_wygrana();
	}

	//usuwanie list statkow
	Gra.Gracz1->kasuj_statki();
	Gra.Gracz2->kasuj_statki();

	cout << "\nKoniec gry.";
}