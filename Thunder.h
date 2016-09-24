#pragma once
#include pokemon.h

class Thunder:public pokemon{
	private:
		move* especial;
	public:
		Thunder();
		~Thunder();
		move* getSpecialM();
}