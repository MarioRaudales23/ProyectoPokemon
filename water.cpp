#include "water.h"
#include "pokemon.h"
#include "move.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
Water::Water(string nombre,string tipo,int vida,int ataque,int defensa,int velocidad,vector<Move*> moves):
Pokemon(nombre,tipo,vida,ataque,defensa,velocidad,moves){
	this->especial=new Move("Hidrobomba","Agua",80,5,"El enemigo es golpeado por un enorme volumen de agua lanzada bajo una gran presión.");
}
Water::~Water(){

}
Move* Water::getSpecialM(){
	return especial;
}