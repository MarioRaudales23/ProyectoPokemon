#include <string>
#include <sstream>
#include "move.h"
#include "ataque.h"
using std::string;
using std::stringstream;

Ataque::Ataque(string nombre,string tipo,int precision,int usos,string descripcion):Move(nombre,tipo,precision,usos,descripcion){
}
int Ataque::efecto(int vida1,int ataque1,int vida2,int defensa2,int debil){
	if(debil==1){
		return vida2-ataque1;
	}else if(debil==0){
		return vida2-(ataque1-defensa2);
	}else{
		return vida2-1;
	}
}
string Ataque::toString(){
	return Move::toString();
}