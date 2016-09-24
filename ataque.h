#pragma once
#include <string>
#include "move.h"
using std::string;

class Ataque:public Move
{
public:
	Ataque(string,string,int,int,string);
	int efecto(int,int,int,int,int);
	string toString();	
};