#include <string>
#include <sstream>
#include "pokemon.h"
#include <iostream>
#include <vector>
using std::vector;
using std::string;
using std::stringstream;
using std::endl;
//Constructores.
Pokemon::Pokemon(string nombre,int vida,int ataque,int defensa,int velocidad,vector<Move*> moves){
	this->nombre=nombre;
	this->vida=vida;
	this->ataque=ataque;
	this->defensa=defensa;
	this->velocidad=velocidad;
	this->moves=moves;
}
Pokemon::Pokemon(){
}
Pokemon::Pokemon(const Pokemon* r){
	this->nombre=r->nombre;
	this->vida=r->vida;
	this->ataque=r->ataque;
	this->defensa=r->defensa;
	this->velocidad=r->velocidad;
	this->moves=r->moves;
}

//Getters y Setters.
string Pokemon::getNombre(){
	return nombre;
}
int Pokemon::getVida(){
	return vida;
}
int Pokemon::getAtaque(){
	return ataque;
}
int Pokemon::getDefensa(){
	return defensa;
}
int Pokemon::getVelocidad(){
	return velocidad;
}
void Pokemon::setNombre(string nombre){
	this->nombre=nombre;
}
vector<Move*> Pokemon::getMoves(){
	return moves;
}
void Pokemon::setVida(int vida){
	this->vida=vida;
}
void Pokemon::setAtaque(int ataque){
	this->ataque=ataque;
}
void Pokemon::setDefensa(int defensa){
	this->defensa=defensa;
}
void Pokemon::setVelocidad(int velocidad){
	this->velocidad=velocidad;
}
void Pokemon::setMoves(vector<Move*> moves){
	this->moves=moves;
}
//toString.
string Pokemon::toString(){
	stringstream ss;
	ss<<"Pokemon:"<<nombre<<endl;
	return ss.str();
}
