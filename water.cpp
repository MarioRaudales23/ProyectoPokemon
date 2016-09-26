#include "water.h"
#include "pokemon.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
Water::Water(){

}
Water::Water(string nombre,int vida,int ataque,int defensa,int velocidad,vector<Move*> moves):
Pokemon(nombre,vida,ataque,defensa,velocidad,moves){
	this->especial=new Move("Hidrobomba","Agua",80,5,"El enemigo es golpeado por un enorme volumen de agua lanzada bajo una gran presión.");
}
Water::~Water(){

}
//Castea el efecto especial nombrado en el constructor.
Move* Water::getSpecialM(){
	return especial;
}