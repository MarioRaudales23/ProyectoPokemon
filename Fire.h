#pragma once
#include "pokemon.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string;

class Fire: public Pokemon{
private:
	Move* especial;
public:
	Fire();
	Fire(string,int,int,int,int,vector<Move*>);
	~Fire();
	Move* getSpecialM();
};