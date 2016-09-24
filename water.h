#pragma once
#include pokemon.h

class Water:public pokemon{
	private:
		move* especial;
	public:
		Water();
		~Water();
		move* getSpecialM();
}