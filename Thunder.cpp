#include "pokemon.h"
#include "move.h"
#include "Thunder.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
Thunder::Thunder(){

}
Thunder::Thunder(string nombre,int vida,int ataque,int defensa,int velocidad,vector<Move*> moves):
Pokemon(nombre,vida,ataque,defensa,velocidad,moves){
	this->especial=new Move("Electro bola","Electrico",100,10,"Se cierra un clúster eléctrica en el oponente. Cuanto más rápido es que su oponente, mayor es el poder.");
}
Thunder::~Thunder(){

}
Move* Thunder::getSpecialM(){
	return especial;
}