#pragma once
#include "pokemon.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
Fire::Fire(string nombre,string tipo,int vida,int ataque,int defensa,int velocidad,vector<Move*> moves):
pokemon(nombre,tipo,vida,ataque,defensa,velocidad,moves){
	this->especial=new Move("Anillo igneo","Fuego",90,5,"
El enemigo es arrasada por una explosión de fuego. El usuario debe descansar en el siguiente turno.");
}
Fire::~Fire(){

}
Move* Fire::getSpecialM(){
	return especial;
}