#include <iostream>
#include <fstream>
#include <string>

#include "Funkcje.h"
#include "Struktury.h"
bool B = true;
bool R = false;

using namespace std;

void dodajWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik)		//korzen drzewa zawsze czarny, wartosc z pliku, straznik jako ostatni potomek z pustymi wartosciami
{
	WezelRB* nowy; //utworzenie nowego w�z�a
	nowy = new WezelRB;	//inicjalizacja nowego w�z�a
	nowy->lewo = &Wartownik;
	nowy->prawo = &Wartownik;
	nowy->gora = korzen;
	nowy->wartosc = wartosc;
	nowy->kolor = R;
	//auto o = nowy->gora; //w�ze� ojciec nowego w�z�a
	if (nowy->gora == &Wartownik) { korzen = nowy; nowy->kolor = B; }  //je�li ojciec jest wartownikiem, czyli korze� jest pusty to nowy jako czarny w�ze� - korze�
	else
	{
		while (true)             // szukanie li�cia do zast�pienia przez nowy w�ze�
		{
			if (wartosc < nowy->gora->wartosc)
			{
				if (nowy->gora->prawo == &Wartownik) //warunek je�li prawy li�� jest pusty - reprezentowany przez wartownika
				{
					nowy->gora->prawo = nowy;  // zast�pienie prawego li�cia przez nowy w�ze�
					break;			// koniec p�tli
				}
				nowy->gora = nowy->gora->prawo;	//	

			}
			else
			{
				if (nowy->gora->lewo == &Wartownik) //warunek je�li lewy li�� jest pusty
				{
					nowy->gora->lewo = nowy; // zast�pienie lewego li�cia przez nowy w�ze�
					break;			// koniec p�tli
				}
				nowy->gora = nowy->gora->lewo; //

			}
		}
		while (nowy->gora->kolor == R)						//rozpatrzenie trzech warunk�w drzewa czerwono-czarnego
		{
			if (nowy->gora == nowy->gora->gora->lewo)	//wujek nowego w�z�a jest po prawej stronie
			{
				auto wuj = nowy->gora->gora->prawo;				//wujek lewgo w�z�a - prawy syn dziadka
				if (wuj->kolor == R)	//przypadek pierwszy - wujek jest czerwony
				{
					nowy->gora->kolor = B; wuj->kolor = B; //ojciec i wujek staj� si� czerwoni
					if (nowy->gora->gora == korzen) { nowy->gora->gora->kolor = B; break; } //dziadek staje si� czarny je�li jest korzeniem drzewa
					else { nowy->gora->gora->kolor = R;	nowy = nowy->gora->gora; } //je�li nie to czerwony sprawdzenie wypadk�w na wy�szym poziomie drzewa
					continue;	//sprawdzenie wypadk�w na wy�szym poziomie drzewa
				}
				if (nowy->gora->prawo == nowy) {		//przypadek drugi - wujek jest czarny, a nowy w�ze� jest prawym synem swojego ojca
					nowy = nowy->gora;
					rotL(korzen, nowy, Wartownik);
				}
				nowy->gora->kolor = B;
				nowy->gora->gora->kolor = R;
				rotP(korzen, nowy->gora->gora, Wartownik);
				if (nowy->gora == &Wartownik) korzen = nowy;
				if (nowy->gora->gora == &Wartownik) korzen = nowy->gora;
 				break;
			}
			else								
			{
				auto wuj = nowy->gora->gora->lewo;	//wujek nowego w�z�a jest po lewej stronie
				if (wuj->kolor == R)	//przypadek pierwszy - wujek jest czerwony
				{
					nowy->gora->kolor = B; wuj->kolor = B; //ojciec i wujek staj� si� czerwoni
					if (nowy->gora->gora == korzen) { nowy->gora->gora->kolor = B; break; } //dziadek staje si� czarny je�li jest korzeniem drzewa
					else { nowy->gora->gora->kolor = R;	nowy = nowy->gora->gora; } //je�li nie to czerwony sprawdzenie wypadk�w na wy�szym poziomie drzewa
					continue;	//sprawdzenie wypadk�w na wy�szym poziomie drzewa
				}

				if (nowy->gora->lewo == nowy) {		//przypadek drugi - wujek jest czarny, a nowy w�ze� jest lewym synem swojego ojca
					nowy = nowy->gora;
					rotP(korzen, nowy, Wartownik);
				}
				nowy->gora->kolor = B;
				nowy->gora->gora->kolor = R;
				rotL(korzen, nowy->gora->gora, Wartownik);
				if (nowy->gora == &Wartownik) korzen = nowy;
				if (nowy->gora->gora == &Wartownik) korzen = nowy->gora;
				break;	
			}
		}
	}
}

void usunWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik) {
	if (korzen != &Wartownik) {
		WezelRB* X;
		if (znajdzWezel(korzen, wartosc, Wartownik) == nullptr) cout << "Nie mozna usunac - wezel o wartosci " << wartosc << " nie znajduje sie w drzewie!" << endl << endl;
		else {
			X = znajdzWezel(korzen, wartosc, Wartownik);
			auto Y = zwrocNastepnik(korzen, X, Wartownik);
			if (X->lewo == &Wartownik and X->prawo != &Wartownik) // przypadek 1, w�ze� X nie ma lewego syna 
			{
				if (X->kolor == B)	X->prawo->kolor = B;
				if (X->gora->prawo == X) X->gora->prawo = X->prawo; else X->gora->lewo = X->prawo;
				X->prawo->gora = X->gora;
				if (X->gora == &Wartownik) { korzen = X->prawo; X->prawo->kolor = B; }
				delete X; return;
			}
			else if (X->prawo == &Wartownik and X->lewo == &Wartownik) {	//przypadek 3, w�ze� X nie ma syn�w
				if (X->gora == &Wartownik) korzen = &Wartownik;
				else {
					if (X->kolor = B) {
						X->gora->kolor = B; 
						if (X->gora->prawo == X and X->gora->lewo != &Wartownik) X->gora->lewo->kolor = R;
						else if (X->gora->prawo != &Wartownik) X->gora->prawo->kolor = R;
					}
					if (X->gora->prawo == X) X->gora->prawo = &Wartownik; else X->gora->lewo = &Wartownik;
				}
				delete X; return;
			}
			else if (X->prawo == &Wartownik and X->lewo != &Wartownik) // przypadek 3, w�ze� X nie ma prawego syna 
			{
				if (X->kolor == B)	X->lewo->kolor = B;
				if (X->gora->prawo == X) X->gora->prawo = X->lewo; else X->gora->lewo = X->lewo;
				X->lewo->gora = X->gora;
				if (X->gora == &Wartownik) { korzen = X->lewo; X->lewo->kolor = B; }
				delete X; return;
			}
			else if (X->prawo != &Wartownik and X->lewo != &Wartownik) // przypadek 4, w�ze� X ma dw�ch syn�w
			{
				auto pSyn = Y->lewo;
				if (pSyn == &Wartownik) { pSyn->gora = Y; Y->lewo = pSyn; }
				//pSyn->gora = Y->gora;
				if (Y == X->lewo) { 
					//Y->gora->prawo = Y->lewo;
					//Y->lewo->gora = Y->gora;
					//Y->lewo = X->lewo;
					//X->lewo->gora = Y;
					Y->prawo = X->prawo;
					X->prawo->gora = Y; 
					Y->gora = X->gora;
					if (X->gora == &Wartownik) korzen = Y;
					else { if (X->gora->lewo == X) X->gora->lewo = Y; else X->gora->prawo = Y; }
					//return;
				}
				else {
					Y->gora->prawo = Y->lewo;
					Y->lewo->gora = Y->gora;
					Y->lewo = X->lewo;
					X->lewo->gora = Y;
					Y->prawo = X->prawo;
					X->prawo->gora = Y;
					Y->gora = X->gora;
					if (X->gora == &Wartownik) korzen = Y;
					else { if (X->gora->lewo == X) X->gora->lewo = Y; else X->gora->prawo = Y; }
				}
				if (Y->kolor == B) {
					Y->kolor = X->kolor;
					delete X;
					WezelRB* brat;
					while (pSyn->kolor == B) {
						if (pSyn == pSyn->gora->lewo)
						{
							brat = pSyn->gora->prawo;
							//cout << Y->wartosc << "	" << Y->prawo->wartosc << "		" << brat->wartosc << "		" << pSyn->wartosc << "	";
							if (brat->kolor == R) {
								rotL(korzen, pSyn->gora, Wartownik);
								brat = pSyn->gora->prawo;
								pSyn->gora->kolor = R;
								pSyn->gora->gora->kolor = B;
								if (pSyn->gora->gora->gora == &Wartownik) korzen = pSyn->gora->gora;
							}
							if (brat->kolor == B and brat->lewo->kolor == B and brat->prawo->kolor == B) {
								brat->kolor = R;
								pSyn = pSyn->gora;
								if (pSyn == korzen) { pSyn->lewo->kolor = B; break; }
								continue;
							}
							if (brat->kolor == B and brat->lewo->kolor == R and brat->prawo->kolor == B) {
								rotP(korzen, brat, Wartownik);
								brat->kolor = R;
								brat->gora->kolor = B;
								brat = pSyn->gora->prawo;

							}
							if (brat->kolor == B and brat->prawo->kolor == R) {
								rotL(korzen, pSyn->gora, Wartownik);
								if (pSyn->gora->gora->gora == &Wartownik) korzen = pSyn->gora->gora;
								if (pSyn->gora->kolor == R) pSyn->gora->gora->kolor = R; else pSyn->gora->gora->kolor = B;
								pSyn->gora->kolor = B;
								pSyn->gora->gora->prawo->kolor = B;
								break;
							}
						}
						else
						{
							brat = pSyn->gora->lewo; 
							//cout << Y->wartosc << "	" << Y->prawo->wartosc << "		" << brat->wartosc << "		" << pSyn->wartosc << "	";
							//if (brat->kolor == B and brat->prawo->kolor == R) cout << "dupa"; break;
							if (brat->kolor == R) {
								rotP(korzen, pSyn->gora, Wartownik); 
								brat = pSyn->gora->lewo;
								pSyn->gora->kolor = R;
								pSyn->gora->gora->kolor = B;
								if (pSyn->gora->gora->gora == &Wartownik) korzen = pSyn->gora->gora;
							}
							if (brat->kolor == B and brat->lewo->kolor == B and brat->prawo->kolor == B) {
								brat->kolor = R;
								pSyn = pSyn->gora;
								if (pSyn == korzen) { pSyn->lewo->kolor = B; break; }
								continue;
							}
							if (brat->kolor == B and brat->prawo->kolor == R and brat->lewo->kolor == B) {
								rotL(korzen, brat, Wartownik);
								brat->kolor = R;
								brat->gora->kolor = B;
								brat = pSyn->gora->lewo;
							}
							if (brat->kolor == B and brat->lewo->kolor == R) {
								rotP(korzen, pSyn->gora, Wartownik);
								if (pSyn->gora->gora->gora == &Wartownik) korzen = pSyn->gora->gora;
								if (pSyn->gora->kolor == R) pSyn->gora->gora->kolor = R; else pSyn->gora->gora->kolor = B;
								pSyn->gora->kolor = B;
								pSyn->gora->gora->lewo->kolor = B;
								break;
							}
						}
					}
					pSyn->kolor = B;
				}
				else {
					Y->kolor = X->kolor;
					delete X;
				}
			}
		}
	}
}

void rotL(WezelRB* korzen, WezelRB* X, WezelRB& Wartownik) {		//rotacja w lewo wzgl�dem w�z�a X
	auto ojciec = X->gora;		//ojciec w�z�a X
	auto prawySyn = X->prawo;		//prawy syn w�z�a X
	if (prawySyn != &Wartownik) {	//rotacja je�li prawy syn istnieje
		X->prawo = prawySyn->lewo;	//dodanie nowej prawej �cie�ki do X
		if (X->prawo != &Wartownik) X->prawo->gora = X;	//naprawa prawej �cie�ki X	
		prawySyn->lewo = X;			//dodanie nowej lewej �cie�ki do prawego syna
		X->gora = prawySyn;			//naprawienie lewej �cie�ki prawego syna
		prawySyn->gora = ojciec;	//dodanie g�ry do prawego syna	
		if (ojciec != &Wartownik)	//naprawa g�ry do prawego syna
		{
			if (ojciec->lewo == X) ojciec->lewo = prawySyn; else ojciec->prawo = prawySyn;
		}
	}
}

void rotP(WezelRB* korzen, WezelRB* X, WezelRB& Wartownik) {		//rotacja w lewo wzgl�dem w�z�a X
	auto ojciec = X->gora;		//ojciec w�z�a X
	auto lewySyn = X->lewo;		//prawy syn w�z�a X
	if (lewySyn != &Wartownik) {	//rotacja je�li prawy syn istnieje
		X->lewo = lewySyn->prawo;	//dodanie nowej prawej �cie�ki do X
		if (X->lewo != &Wartownik) X->lewo->gora = X;	//naprawa prawej �cie�ki X	
		lewySyn->prawo = X;			//dodanie nowej lewej �cie�ki do prawego syna
		X->gora = lewySyn;			//naprawienie lewej �cie�ki prawego syna
		lewySyn->gora = ojciec;	//dodanie g�ry do prawego syna
		if (ojciec != &Wartownik)	//naprawa g�ra do prawego syna
		{
			if (ojciec->lewo == X) ojciec->lewo = lewySyn; else ojciec->prawo = lewySyn;
		}
	}
}

WezelRB* znajdzWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik) {
	WezelRB* X;
	X = korzen;
	while (X!=&Wartownik)	//p�tla poszukuj�ca w�z�a o warto�ci podanej w funckji
	{
		if (X->wartosc == wartosc)
			return X;
			if (wartosc < X->wartosc)
				X = X->prawo;	//przej�ciew w prawo
			else
				X = X->lewo;	//przej�cie w lewo
	}
	return nullptr;
}

WezelRB* zwrocNastepnik(WezelRB*& korzen, WezelRB* X, WezelRB& Wartownik)	//funckja zwraca nast�pnik danego w�z�a, czyli w�ze� z najmniejsza warto�ci� jego lewej ga��zi (z pustym lewym w�z�em)
{
	X = X->lewo;
	while (X != &Wartownik)	//p�tla poszukuj�ca w�z�a o warto�ci podanej w funckji
	{
		if (X->prawo == &Wartownik)
			return X;
		X = X->prawo;
	}
	return nullptr;
}

void wypisz(WezelRB* korzen, WezelRB& Wartownik)
{
	if (korzen != &Wartownik) // jezeli jest co wypisac - korzen nie jest wartownikiem
	{
		if (korzen->prawo == &Wartownik and korzen->lewo != &Wartownik) { cout << korzen->wartosc << " "; }	//wypisanie warto�ci z prawo w�z�a
		else	wypisz(korzen->prawo, Wartownik);																		//przej�cie w prawo
		if (korzen->prawo != &Wartownik and korzen->lewo != &Wartownik) { cout << korzen->wartosc << " "; }	//wypisanie korzenia drzewa
		if (korzen->lewo == &Wartownik and korzen->prawo != &Wartownik) { cout << korzen->wartosc << " "; }	//wypisanie warto�ci z lewego w�z�a
		else	wypisz(korzen->lewo, Wartownik);																	//przej�cie w lewo
		if (korzen->prawo == &Wartownik and korzen->lewo == &Wartownik) { cout << korzen->wartosc << " "; }	//wypisywanie warto�ci z skrajnych w�z��w
	}
}

void wypiszGraf(WezelRB* korzen, WezelRB& Wartownik, int p1) {		//zosta�a dodana zmienna pomocnicza o warto�ci -1 z ka�dym uruchomienie g�ownego programu, oceniaj�ca poziom wg��bienia w�z�a 
	p1++;
	if (korzen != &Wartownik) // jezeli jest co wypisac - korzen nie jest wartownikiem
	{
		if (korzen->prawo == &Wartownik and korzen->lewo != &Wartownik) {
			for (int i = 0; i < p1; i++) { cout << "	"; }
			if (korzen->kolor == false) cout << "(" << korzen->wartosc << ")" << endl; else cout << "[" << korzen->wartosc << "]" << endl;
		}	//wypisanie warto�ci z prawego w�z�a - w nawiasach okr�g�ych je�li w�ze� jest czerwony,  w kwadratowych je�li czarny
		else { wypiszGraf(korzen->prawo, Wartownik, p1); }																					//przej�cie w prawo
		if (korzen->prawo != &Wartownik and korzen->lewo != &Wartownik) {
			for (int i = 0; i < p1; i++) { cout << "	"; }
			if (korzen->kolor == false) cout << "(" << korzen->wartosc << ")" << endl; else cout << "[" << korzen->wartosc << "]" << endl;
		}	//wypisanie korzenia drzewa
		if (korzen->lewo == &Wartownik and korzen->prawo != &Wartownik) {
			for (int i = 0; i < p1; i++) { cout << "	"; }
			if (korzen->kolor == false) cout << "(" << korzen->wartosc << ")" << endl; else cout << "[" << korzen->wartosc << "]" << endl;
		}	//wypisanie warto�ci z lewego w�z�a
		else { wypiszGraf(korzen->lewo, Wartownik, p1); }
		if (korzen->prawo == &Wartownik and korzen->lewo == &Wartownik) {
			for (int i = 0; i < p1; i++) { cout << "	"; }
			if (korzen->kolor == false) cout << "(" << korzen->wartosc << ")" << endl; else cout << "[" << korzen->wartosc << "]" << endl;
		}	//wypisywanie warto�ci z skrajnych w�z��w	
			//przej�cie w lewo
	}
}

bool otworzPlik(const char* nazwaPliku) {		//funkcja otwiera plik i wykonuje operacje na nim
	ifstream plik;							//zainicjowanie pliku
	plik.open(nazwaPliku);			//otwarcie pliku
	if (plik.good()) 	//zwraca false jesli pliku nie udalo sie otworzyc
		 {
			WezelRB Wartownik;
			Wartownik.gora = &Wartownik;
			Wartownik.lewo = &Wartownik;
			Wartownik.prawo = &Wartownik;
			Wartownik.kolor = B;
			WezelRB* korzen = &Wartownik;
			int p1 = -1;
			int linijka = 1;
			while (true)
			{
				string rozkaz;
				float wartosc;

				plik >> rozkaz;
				if (!plik.fail()) {
					if (rozkaz == "add") {
						while (true) {
							if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; break; }
							plik >> wartosc;
							if (!plik.fail()) {
								dodajWezel(korzen, wartosc, Wartownik);
							}
							else {
								if (plik.bad()) return false;
								else {
									plik.clear();
									plik >> rozkaz;
									if (rozkaz == "%") {
										while (true) { plik >> rozkaz; if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; break; } }
										break;
									}
									else { cout << "Po rozkazie add moga wystepowac tylko liczby!" << endl << endl; break; }
								}
							}
						}
					}
					else if (rozkaz == "remove"){
						while (true) {
							if (czyNapotkanoZnakNowegoWiersza(plik) or (plik.eof())) { linijka++; break; }
							plik >> wartosc;
							if (!plik.fail()) {
								usunWezel(korzen, wartosc, Wartownik);
							}
							else {
								if (plik.bad()) return false;
								else {
									plik.clear();
									plik >> rozkaz;
									if (rozkaz == "%") {
										while (true) { plik >> rozkaz; if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; break; } }
										break;
									}
									else { cout << "Po rozkazie remove moga wystepowac tylko liczby!" << endl << endl; break; }
								}
							}
						}
					}
					else if (rozkaz == "graph") {
						if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) {
							if (!plik.fail()) {
								wypiszGraf(korzen, Wartownik, p1); cout << endl; linijka++;
							}
						}
						else {
							plik.clear(); plik >> rozkaz;
							if (rozkaz == "%") {
								while (true) { plik >> rozkaz; if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; break; } }
							}
							else {
								cout << "Po rozkazie graph nie moga wystepowac zadne wartosci!" << endl;
							}
						}
					}
					else if (rozkaz == "%") 
					{ 
						while (true) { 
							if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) break;
							plik >> rozkaz; 
						 } 
						linijka++;
					}
					else if (rozkaz == "print") {
						if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) {
							if (!plik.fail()) { wypisz(korzen, Wartownik); cout << endl << endl; continue; }
							else { cout << "dupa1" << endl << endl; break; }
						}
						plik >> rozkaz;
						if (rozkaz == "%") {
							if (!plik.fail()) { wypisz(korzen, Wartownik); cout << endl << endl; }
							else { cout << "dupa2" << endl << endl; break; }
							while (true) {
								plik >> rozkaz; if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; break; }
								break;
							}
						}
						else {
							ofstream nowyPlik;
							if (nowyPlik.good()) {
								nowyPlik.open(rozkaz.c_str());
								nowyPlik << "5 6 7 ";
								nowyPlik.close();
							}
							else { cout << "Nie udalo sie otworzyc/utworzyc pliku o podanej nazwie." << endl << endl; break; }
							if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; continue; }
							plik >> rozkaz;
							if (rozkaz == "%") {
								while (true) { plik >> rozkaz; if (czyNapotkanoZnakNowegoWiersza(plik) or plik.eof()) { linijka++; break; } }
							}
							else { cout << "Nalezy podac tylko jedna nazwe pliku!" << endl << endl; linijka++; break; }
						}
					}
					else { cout << "W " << linijka << " linijce pliku zostal podany nieprawidlowy rozkaz!" << endl; break; }
				}
				else
				{
					if (plik.bad())
						return false;
					if (plik.eof())
						break; 
				} 
			} 

			return true;
		 }
	  else return false;
		plik.close();
		return true;
}

bool czyNapotkanoZnakNowegoWiersza(ifstream& plik)
{
	char cZnak;
	for (;; ) //niesko�czona p�tla
	{
		plik.clear();
		cZnak = plik.peek(); //sprawdzamy jaki kolejny znak zostanie zwr�cony przez operacj� odczytu
		if (plik.fail())
			return false; //wyst�pi� b��d odczytu danych

		if (!isspace(cZnak))
			return false; //pobrany znak nie jest bia�ym znakiem

		plik.get(cZnak); //odczytujemy bia�y znak z pliku
		if (plik.fail())
			return false; //wyst�pi� b��d odczytu danych

		if (cZnak == '\n')
			return true;

	} //for
}