#pragma once
#include "pokemon.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string; 
class Thunder:public Pokemon
{
private:
	Move* especial;
public:
	Thunder(string,int,int,int,int,vector<Move*>);
	~Thunder();
	Move* getSpecialM();
};