#pragma once
#include pokemon.h

class Fire:public pokemon{
	private:
		move* especial;
	public:
		Fire();
		~Fire();
		move* getSpecialM();
}