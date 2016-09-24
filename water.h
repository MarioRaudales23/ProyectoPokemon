#pragma once
#include "pokemon.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string; 

class Water:public Pokemon{
	private:
		Move* especial;
	public:
		Water(string,string,int,int,int,int,vector<Move*>);
		~Water();
		Move* getSpecialM();
};