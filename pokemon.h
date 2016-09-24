#pragma once
#include <string>
#include "move.h"
#include <vector>
using std::vector;
using std::string;

class Pokemon
{
	string nombre;
	string tipo;
	int vida,ataque,defensa,velocidad;
	vector<Move*> moves;
public:
	Pokemon(string,string,int,int,int,int,vector<Move*>);
	Pokemon();
	Pokemon(const Pokemon*);
	string getNombre();
	int getVida();
	int getAtaque();
	int getDefensa();
	int getVelocidad();
	vector<Move*> getMoves();
	string getTipo();
	void setNombre(string);
	void setTipo(string);
	void setVida(int);
	void setAtaque(int);
	void setDefensa(int);
	void setVelocidad(int);
	void setMoves(vector<Move*>);
	string toString();
	
};