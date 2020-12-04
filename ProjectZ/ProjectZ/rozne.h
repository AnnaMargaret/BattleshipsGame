//ADymowska
#pragma once
#include "biblioteki.cpp"

int wczytaj_int(void) {
	int n;
	while (true)
	{
		cin >> n;
		if (cin.fail() && n!='\n')
		{
			cin.clear(); 
			cin.ignore(512, '\n');
			cout << "Blad. Tylko wartosci numeryczne sa dopuszczalne.\nPodaj liczbe." << endl;
		}
		else if (n == '\n') {}
		else break;
	}
	return n;
}

//STARA WERSJA dla scanf
//int wczytaj_int(void) {
//	int n;
//	while (scanf_s(" %d", &n) != 1 || getchar() != '\n') {
//		printf("Bledne dane! Popraw1\n");
//		while (getchar() != '\n') {}
//	}
//	return n;
//}

void wczytywanie_slowa(char* s) {
	while (scanf_s("%s", s, (K - 1)) != 1 || getchar() != '\n') {
		while (getchar() != '\n') {}
		printf("Blad. Sprobuj ponownie.");
	}
}

