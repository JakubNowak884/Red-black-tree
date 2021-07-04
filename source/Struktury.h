#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <iostream> 

struct WezelRB {			//wezel drzewa czerwono-czarnego
	WezelRB * gora;			//ojciec w�z�a
	WezelRB	* lewo,			//lewy potomek w�z�a
			* prawo;		//prawy potomek w�z�a
	float wartosc;			//warto�� przechowywana w w�le
	bool kolor;				//kolor w�z�a "B"-czarny i "R"-czerwony
};


#endif