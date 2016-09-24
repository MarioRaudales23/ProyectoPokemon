#include <string>
#include <sstream>
#include <iostream>
#include "move.h"
using std::string;
using std::stringstream;
using std::endl;

Move::Move(string nombre,string tipo,int precision,int usos,string descripcion){
	this->nombre=nombre;
	this->tipo=tipo;
	this->precision=precision;
	this->usos=usos;
	this->descripcion=descripcion;
}
string Move::getNombre(){
	return nombre;
}
int Move::getPrecision(){
	return precision;
}
int Move::getUsos(){
	return usos;
}
string Move::getTipo(){
	return tipo;
}
string Move::getDescripcion(){
	return descripcion;
}
void Move::setNombre(string nombre){
	this->nombre=nombre;
}
void Move::setTipo(string tipo){
	this->tipo=tipo;
}
void Move::setDescripcion(string descripcion){
	this->descripcion=descripcion;
}
void Move::setUsos(int usos){
	this->usos=usos;
}
void Move::setPrecision(int precision){
	this->precision=precision;
}
int Move::efecto(int vida1,int ataque1,int vida2,int defensa2,int debil){
}
string Move::toString(){
	stringstream ss;
	ss<<nombre<<" -"<<tipo<<"-";
	return ss.str();
}