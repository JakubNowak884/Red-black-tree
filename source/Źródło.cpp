#include <iostream>
#include <fstream>
#include <string>

#include "Struktury.h"
#include "Funkcje.h"

using namespace std;


int main(int argc, char* argv[]){

	if (argc > 2) cout << argv[1] << argv[2];
	if (argc > 2) {
		if (otworzPlik(argv[2]));
		else cout << "Nie uda³o siê otworzyæ pliku" << endl;
	//cout << "duppa";
//	cout << argv[2];
}
	//_CrtDumpMemoryLeaks();
	return(0);
}