#ifndef FUNKCJE_H
#define FUNCKJE_H

#include <iostream>
#include <fstream>
#include <string>

#include "Struktury.h"

using namespace std;

/** Funkcja dodaje iteracyjnie do drzewa czerwono-czarnego nowy w�ze�. W jego li�ciach nie s� przechowywane dane i wszystkie one s� symbolizowane jako jeden pusty Wartownik. Puste drzewo posiada tylko Wartownika.
@param korzen korze� drzewa
@param wartosc warto�� przechowywana w nowym w�le
@param Wartownik wartownik drzewa czerwono-czarnego
*/
void dodajWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik);

/** Funkcja wypisuje warto�ci przechowywane w drzewie czerwono-czarnym w kolejno�ci rosn�cej.
@param korzen korze� drzewa
@param Wartownik wartownik drzewa czerwono-czarnego
*/
void wypisz(WezelRB* korzen, WezelRB& Wartownik);

/** Funkcja wypisuje warto�ci przechowywane w drzewie czerwono-czarnym w postaci graficznej, czarne w�z�y wypisywwane s� w kwadratowych nawiasach, a czerwone w okr�g�ych
@param korzen korze� drzewa
@param Wartownik wartownik drzewa czerwono-czarnego
@p1 pomocnicza zmienna oceniaj�ca poziom wg��bienia w�z�a w drzewie czerwono-czarnym
*/
void wypiszGraf(WezelRB* korzen, WezelRB& Wartownik, int p1);

void usunWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik);

void rotP(WezelRB* korzen, WezelRB* A, WezelRB& Wartownik);

void rotL(WezelRB* korzen, WezelRB* A, WezelRB& Wartownik);

WezelRB* znajdzWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik);

WezelRB* zwrocNastepnik(WezelRB*& korzen, WezelRB* X, WezelRB& Wartownik);

bool otworzPlik(const char* nazwaPliku);

bool czyNapotkanoZnakNowegoWiersza(std::ifstream& plik);
#endif