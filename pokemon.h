#pragma once
#include <string>
#include "move.h"
#include <vector>
using std::vector;
using std::string;

class Pokemon
{
	string nombre;
	int vida,ataque,defensa,velocidad;
	vector<Move*> moves;
public:
	Pokemon(string,int,int,int,int,vector<Move*>);
	Pokemon();
	Pokemon(const Pokemon*);
	string getNombre();
	int getVida();
	int getAtaque();
	int getDefensa();
	int getVelocidad();
	vector<Move*> getMoves();
	void setNombre(string);
	void setVida(int);
	void setAtaque(int);
	void setDefensa(int);
	void setVelocidad(int);
	void setMoves(vector<Move*>);
	string toString();
	
};