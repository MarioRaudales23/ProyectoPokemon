#pragma once
#include "pokemon.h"
#include "Fire.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
//Constructores.
Fire::Fire(){
}
Fire::Fire(string nombre,int vida,int ataque,int defensa,int velocidad,vector<Move*> moves):
Pokemon(nombre,vida,ataque,defensa,velocidad,moves){
	this->especial=new Move("Anillo igneo","Fuego",90,5,"El enemigo es arrasada por una explosión de fuego. El usuario debe descansar en el siguiente turno.");
}
//Destructor.
Fire::~Fire(){

}
//Castea el efecto especial nombrado en el constructor cual deja al enemigo quemado por una explosion y no se puede mover hasta el siguiente turno.
Move* Fire::getSpecialM(){
	return especial;
}