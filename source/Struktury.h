#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <iostream> 

struct WezelRB {			//wezel drzewa czerwono-czarnego
	WezelRB * gora;			//ojciec wêz³a
	WezelRB	* lewo,			//lewy potomek wêz³a
			* prawo;		//prawy potomek wêz³a
	float wartosc;			//wartoœæ przechowywana w wêŸle
	bool kolor;				//kolor wêz³a "B"-czarny i "R"-czerwony
};


#endif