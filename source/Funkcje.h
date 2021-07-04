#ifndef FUNKCJE_H
#define FUNCKJE_H

#include <iostream>
#include <fstream>
#include <string>

#include "Struktury.h"

using namespace std;

/** Funkcja dodaje iteracyjnie do drzewa czerwono-czarnego nowy wêze³. W jego liœciach nie s¹ przechowywane dane i wszystkie one s¹ symbolizowane jako jeden pusty Wartownik. Puste drzewo posiada tylko Wartownika.
@param korzen korzeñ drzewa
@param wartosc wartoœæ przechowywana w nowym wêŸle
@param Wartownik wartownik drzewa czerwono-czarnego
*/
void dodajWezel(WezelRB*& korzen, float& wartosc, WezelRB& Wartownik);

/** Funkcja wypisuje wartoœci przechowywane w drzewie czerwono-czarnym w kolejnoœci rosn¹cej.
@param korzen korzeñ drzewa
@param Wartownik wartownik drzewa czerwono-czarnego
*/
void wypisz(WezelRB* korzen, WezelRB& Wartownik);

/** Funkcja wypisuje wartoœci przechowywane w drzewie czerwono-czarnym w postaci graficznej, czarne wêz³y wypisywwane s¹ w kwadratowych nawiasach, a czerwone w okr¹g³ych
@param korzen korzeñ drzewa
@param Wartownik wartownik drzewa czerwono-czarnego
@p1 pomocnicza zmienna oceniaj¹ca poziom wg³êbienia wêz³a w drzewie czerwono-czarnym
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