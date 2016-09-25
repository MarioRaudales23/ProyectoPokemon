#include <ncurses.h>
#include "pokemon.h"
#include "move.h"
#include "Fire.h"
#include "Thunder.h"
#include "water.h"
#include "ataque.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <ctime>
#include <cstring>
#include <stdlib.h>
using namespace std;
char** traspaso(Pokemon);
void vida(Pokemon,Pokemon);
void limpiar();
void pokebola(int);
void Combate(Pokemon,Pokemon);
void cuadrosDeBatalla(Pokemon,vector<Move*>);
vector<Pokemon*> generar_pokemons();
vector<Move*> generar_moves(Pokemon);
vector<Move*> oponent_moves(Pokemon);
int main(int argc, char const *argv[])
{
	initscr();
	srand(time(NULL));
	noecho();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_WHITE);
	init_pair(3,COLOR_WHITE,COLOR_YELLOW);
	init_pair(4,COLOR_WHITE,COLOR_MAGENTA);
	init_pair(5,COLOR_WHITE,COLOR_RED);
	init_pair(6,COLOR_WHITE,COLOR_CYAN);
	init_pair(7,COLOR_WHITE,COLOR_BLUE);
	init_pair(8,COLOR_BLACK,COLOR_WHITE);
	init_pair(9,COLOR_GREEN,COLOR_GREEN);
	init_pair(10,COLOR_BLACK,COLOR_BLACK);
	attron(COLOR_PAIR(2));
	limpiar();
	attroff(COLOR_PAIR(2));
	int s,enter,avanzar;
	printw("Presione cualquier tecla diferente ESC para iniciar el programa");
	mvprintw(1,0,"Se le solicita al usuario que antes de iniciar con el uso de este programa tenga la terminal maximizada");
	while((s=getch()!=27)){
		attron(COLOR_PAIR(2));
		limpiar();
		attroff(COLOR_PAIR(2));
		pokebola(5);
		int x,y;
		getmaxyx(stdscr,x,y);
		attron(COLOR_PAIR(8));
		mvprintw(22,(y/2)-10,"Juego nuevo (ENTER)");
		mvprintw(26,(y/2)-10,"Instrucciones (I)");
		mvprintw(30,(y/2)-10,"Salir (ESC)");
		attroff(COLOR_PAIR(8));
		enter=getch();
		Pokemon player;
		/*Fire player;
		Water player;
		Thunder player;*/
		if(enter==10){
			vector<Pokemon*> pokemons=generar_pokemons();
			attron(COLOR_PAIR(2));
			limpiar();
			attroff(COLOR_PAIR(2));
			pokebola(5);
			int revision=1;
			while(revision==1){
				attron(COLOR_PAIR(8));
				mvprintw(20,(y/2)-20,"Que pokemon desea elegir como su combatiente?                                            ");
				mvprintw(21,(y/2)-26,"(presione la tecla del numero del pokemon que desea elegir de la lista)");
				for (int i = 0; i < pokemons.size(); ++i)
				{
					mvprintw(22+(i)*5,(y/2)-8,"%d-%s",i,pokemons[i]->getNombre().c_str());
					mvprintw(23+(i)*5,(y/2)-8,"-Vida:%d",pokemons[i]->getVida());
					mvprintw(24+(i)*5,(y/2)-8,"-Ataque:%d",pokemons[i]->getAtaque());
					mvprintw(25+(i)*5,(y/2)-8,"-Defensa:%d",pokemons[i]->getDefensa());
					mvprintw(26+(i)*5,(y/2)-8,"-Velocidad:%d",pokemons[i]->getVelocidad());
				}
				int elegido=getch();
				vector <Move*> movesVacio;
				if((elegido-48)==0){
					player=new Fire("Charmander",50,17,10,80,movesVacio);
					pokemons.erase(pokemons.begin()+(elegido-48));
					mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
					mvprintw(20,(y/2)-20,"Usted a elegido a %s como su Pokemon                                                              ",player.getNombre().c_str());	
					mvprintw(21,(y/2)-26,"                                                                                  ");
					revision=0;
					avanzar=getch();
				}else if((elegido-48)==1){
					player=new Thunder("Pikachu",50,15,11,90,movesVacio);
					pokemons.erase(pokemons.begin()+(elegido-48));
					mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
					mvprintw(20,(y/2)-20,"Usted a elegido a %s como su Pokemon                                                              ",player.getNombre().c_str());	
					mvprintw(21,(y/2)-26,"                                                                                  ");
					revision=0;
					avanzar=getch();
				}else if ((elegido-48)==2){
					player=new Water("Squirtle",50,16,12,85,movesVacio);
					pokemons.erase(pokemons.begin()+(elegido-48));
					mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
					mvprintw(20,(y/2)-20,"Usted a elegido a %s como su Pokemon                                                              ",player.getNombre().c_str());	
					mvprintw(21,(y/2)-26,"                                                                                  ");
					revision=0;
					avanzar=getch();
				}else{
					mvprintw(20,(y/2)-20,"El numero que ingreso no existe en la lista como opcion                                                             ");
					mvprintw(21,(y/2)-26,"                                                                                  ");
					avanzar=getch();
				}
				attroff(COLOR_PAIR(8));
			}
			vector<Move*> moves = generar_moves(player);
			vector<Move*> playerMoves;
			attron(COLOR_PAIR(2));
			limpiar();
			attroff(COLOR_PAIR(2));
			pokebola(5);
			attron(COLOR_PAIR(8));
			mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
			mvprintw(20,(y/2)-20,"ahora se le mostrara la lista de movimientos que podra elegir,solo podra elegir 4");
			avanzar=getch();
			attroff(COLOR_PAIR(8));
			while(revision==0){
				attron(COLOR_PAIR(2));
				limpiar();
				attroff(COLOR_PAIR(2));
				pokebola(5);
				attron(COLOR_PAIR(8));
				mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)%d",moves.size());
				for (int i = 0; i < moves.size(); ++i) {
					mvprintw(22+(i)*3,(y/2)-26,"%d-%s",i,moves.at(i)->toString().c_str());
					//mvprintw(23+(i)*3,(y/2)-26,"   Precision:%d  Usos:%d",moves.at(i)->getPrecision(),moves[i]->getUsos());
					//mvprintw(24+(i)*3,(y/2)-26,"Descripcion: %s",moves.at(i)->getDescripcion().c_str());
				}
				mvprintw(20,(y/2)-20,"Que movimiento desea elegir para que su pokemon lo aprenda?");
				mvprintw(21,(y/2)-26,"(presione la tecla del numero del movimiento que desea elegir de la lista)");
				int elegido=getch();
				if((elegido-48)<moves.size()&&(elegido-48)>=0){
					playerMoves.push_back(moves[elegido-48]);
					mvprintw(20,(y/2)-20,"Usted a elegido %s como nuevo movimiento para su pokemon                                                             ",moves[elegido-48]->getNombre().c_str());	
					mvprintw(21,(y/2)-26,"                                                                                  ");
					moves.erase(moves.begin()+(elegido-48));
					if(playerMoves.size()==4){
						mvprintw(20,(y/2)-20,"                                                                                  ");
						mvprintw(20,(y/2)-20,"Usted ya ha elegido los movimiento para su pokemon");
						revision=1;
					}
					avanzar=getch();
				}else{
					mvprintw(20,(y/2)-20,"El numero que ingreso no existe en la lista como opcion                                                             ");
					mvprintw(21,(y/2)-26,"                                                                                  ");
					avanzar=getch();
				}
				attroff(COLOR_PAIR(8));
			}
			player.setMoves(playerMoves);
			int oponent=rand()%pokemons.size();
			Pokemon oponente=Pokemon(pokemons[oponent]);
			oponente.setMoves(oponent_moves(oponente));
			Combate(player,oponente);
			refresh();
		}else if (enter==98){
			attron(COLOR_PAIR(2));
			limpiar();
			attroff(COLOR_PAIR(2));
			pokebola(5);
			attron(COLOR_PAIR(8));
			mvprintw(0,(y/2)-25,"BIENVENIDO ENTRENADOR AL COMBATE POKEMON");
			mvprintw(21,(y/2)-8,"Instrucciones");
			mvprintw(22,(y/2)-26,"-antes de iniciar el combate tendra que elegir 1 pokemon de los tres posibles");
			mvprintw(23,(y/2)-26,"-usted elegira los ataques de su pokemon");
			mvprintw(24,(y/2)-26,"-cada pokemon como sus ataques tiene un tipo que sera decisivo para el resultado de la batalla");
			mvprintw(25,(y/2)-26,"-los tipos son importante para saber que ataque es mas efectivo contra el oponente");
			mvprintw(26,(y/2)-24,"Ejemplo:");
			mvprintw(27,(y/2)-24,"*Fuego->Fuerte contra:Hoja  Debil contra: Agua y Roca" );
			mvprintw(28,(y/2)-24,"*Agua->Fuerte contra:Fuego  Debil contra: Hoja y Electrico" );
			mvprintw(29,(y/2)-24,"*Hoja->Fuerte contra:Agua  Debil contra: Fuego y Volador" );
			mvprintw(30,(y/2)-26,"-una vez iniciado el combate sera por turnos ,el pokemon con mayor Velocidad atacara siempre primero");
			mvprintw(31,(y/2)-26,"-cuando alguno de los dos pokemon use el movimiento protec en ese turno no importara la Velocidad y el lo hara primero");
			mvprintw(32,(y/2)-26,"-Es posible que cuando use unos de sus movimiento pueda fallar dependiendo de sus Precision");
			mvprintw(33,(y/2)-26,"-Cada movimiento posee cierta cantidad de usos y se gastan aunque falle al usarlo");
			mvprintw(34,(y/2)-26,"-cuando un pokemon ya ha agotado los usos de todos sus movimientos hara un movimiento llamado Struggle");
			mvprintw(35,(y/2)-26,"-Struggle es un ataque que todo pokemon posee ,pero al usarlo hace efecto tanto en el oponente como en el pokemon que lo uso");
			mvprintw(36,(y/2)-26,"-El combate termina hasta que cualquiera de los dos pokemon se quede sin puntos de vida o el usuario decida terminar el combate");
			attroff(COLOR_PAIR(8));
			avanzar=getch();
		}
	}
	endwin();
	return 0;
}

void cuadrosDeBatalla(Pokemon jugador1,Pokemon jugador2,vector<Move*> ataques){
	int y , x;
	getmaxyx (stdscr,y,x);
	const int vida1 = jugador1.getVida();
	const int vida2 = jugador2.getVida();
	mvprintw(21,(y/2)-16,"%s                     %d/%d                     %s                     %d/%d",jugador1.getNombre(),jugador1.getVida(),vida1,jugador2.getNombre(),jugador2.getVida(),vida2);
	mvprintw(22,(y/2)-16," ⛚________________________________⛚                      ⛚________________________________⛚");
	mvprintw(23,(y/2)-16,"  |  __________	    __________  |                        |  __________	     __________  |");
	mvprintw(24,(y/2)-16,"  | |          |     |          | |                        | |          |     |          | |");
	mvprintw(25,(y/2)-16,"  | |%s|	   |%s| |                        | |%s|	    |%s| |",jugador1.getMoves().at(0)->getNombre(),jugador1.getMoves().at(1)->getNombre(),jugador2.getMoves().at(0)->getNombre(),jugador2.getMoves().at(1)->getNombre());
	mvprintw(26,(y/2)-16,"  | |          |     |          | |                        | |          |     |          | |");
	mvprintw(27,(y/2)-16,"  |  ‾‾‾‾‾‾‾‾‾‾       ‾‾‾‾‾‾‾‾‾‾  |                        |  ‾‾‾‾‾‾‾‾‾‾       ‾‾‾‾‾‾‾‾‾‾  |");
	mvprintw(28,(y/2)-16,"  |  __________       __________  |                        |  __________       __________  |");
	mvprintw(29,(y/2)-16,"  | |          |     |          | |                        | |          |     |          | |");
	mvprintw(30,(y/2)-16,"  | |%s|	   |%s| |                        | |%s|	    |%s| |",jugador1.getMoves().at(2)->getNombre(),jugador1.getMoves().at(3)->getNombre(),jugador2.getMoves().at(2)->getNombre(),jugador2.getMoves().at(3)->getNombre());
	mvprintw(31,(y/2)-16,"  | |          |     |          | |                        | |          |     |          | |");
	mvprintw(32,(y/2)-16,"  |  ‾‾‾‾‾‾‾‾‾‾       ‾‾‾‾‾‾‾‾‾‾  |                        |  ‾‾‾‾‾‾‾‾‾‾       ‾‾‾‾‾‾‾‾‾‾  |");
	mvprintw(33,(y/2)-16," ⛚‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾⛚                      ⛚‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾⛚");
}

int efectividad(string pokemon,string move){
	int x,y;
	getmaxyx(stdscr,x,y);
	attron(COLOR_PAIR(8));
	if(pokemon=="Fuego"&&move=="Agua"||pokemon=="Fuego"&&move=="Roca"||pokemon=="Agua"&&move=="Electrico"||pokemon=="Agua"&&move=="Hoja"||pokemon=="Hoja"&&move=="Fuego"||pokemon=="Hoja"&&move=="Volador"){
		mvprintw(20,(y/2)-30,"                    Es super efectivo                                                       ");					
		return 1;
	}else if(move=="Fuego"&&pokemon=="Agua"||move=="Agua"&&pokemon=="Hoja"||move=="Hoja"&&pokemon=="Fuego"){		
		mvprintw(20,(y/2)-30,"                    No es muy efectivo...                                                    ");
		return 2;
	}else{
		mvprintw(20,(y/2)-30,"                     Es efectivo                                                               ");
		return 0;
	}
	attroff(COLOR_PAIR(8));
}
void vida(Pokemon player,Pokemon cpu){
	int x,y;
	getmaxyx(stdscr,x,y);
	attron(COLOR_PAIR(10));
	mvprintw(24,0,"                                                    ");
	mvprintw(25,0,"                                                    ");
	mvprintw(26,0,"                                                    ");
	mvprintw(24,y-52,"                                                    ");
	mvprintw(25,y-52,"                                                    ");
	mvprintw(26,y-52,"                                                    ");
	attroff(COLOR_PAIR(10));
	attron(COLOR_PAIR(8));
	int lado1,lado2;
	if(player.getNombre()=="Charmeleon"){
		lado1=player.getVida();
		lado2=cpu.getVida();
		if (cpu.getNombre()=="Frogadier")
		{
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Player:Charmeleon-Vida:%d  ",player.getVida());
			mvprintw(23,y-52,"Oponent:Frogadier-Vida:%d  ",cpu.getVida());
			attroff(COLOR_PAIR(8));
		}else{
			
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Player:Charmeleon-Vida:%d  ",player.getVida());
			mvprintw(23,y-52,"Oponent:Grovyle-Vida:%d  ",cpu.getVida());
			attroff(COLOR_PAIR(8));
		}
	}else if(player.getNombre()=="Frogadier"){
		lado2=player.getVida();
		lado1=cpu.getVida();
		if(cpu.getNombre()=="Charmeleon"){
			
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Oponent:Charmeleon-Vida:%d  ",cpu.getVida());
			mvprintw(23,y-52,"Player:Frogadier-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}else{
			
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Oponent:Grovyle-Vida:%d  ",cpu.getVida());
			mvprintw(23,y-52,"Player:Frogadier-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}
	}else{
		if(cpu.getNombre()=="Charmeleon"){
			lado1=cpu.getVida();
			lado2=player.getVida();
			
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Oponent:Charmeleon-Vida:%d  ",cpu.getVida());
			mvprintw(23,y-52,"Player:Grovyle-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}else{
			lado1=player.getVida();
			lado2=cpu.getVida();
			
			attron(COLOR_PAIR(8));
			mvprintw(23,y-52,"Oponent:Frogadier-Vida:%d  ",cpu.getVida());
			mvprintw(23,0,"Player:Grovyle-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}
	}
	attroff(COLOR_PAIR(8));
	attron(COLOR_PAIR(9));
	for (int i = 1; i <=lado1 ; ++i)
	{
		mvprintw(25,i," ");
	}
	for (int i = y-lado2-1; i < y-1; ++i)
	{
		mvprintw(25,i," ");
	}
	attroff(COLOR_PAIR(9));
}
void Combate(Pokemon player,Pokemon cpu){
	int avanzar;
	int control=0;
	int x,y;
	getmaxyx(stdscr,x,y);
	while(control==0){
		attron(COLOR_PAIR(2));
		limpiar();
		attroff(COLOR_PAIR(2));
		pokebola(5);
		attron(COLOR_PAIR(8));
		mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
		mvprintw(1,(y/2)-10,"!INICIO EN EL COMBATE!");
		attroff(COLOR_PAIR(8));
		vida(player,cpu);
		bool tiene1=false,tiene2=false;
		int revision=0,revision2=0;
		int elegido,elegido2;
		for (int i = 0; i < player.getMoves().size(); ++i)
		{
			if(player.getMoves()[i]->getUsos()>0){
				revision2=1;
			}
		}
		if (revision2==1)
		{
			attron(COLOR_PAIR(8));
			while(revision==0){
				mvprintw(20,(y/2)-30,"ingrese el numero del ataque que va ha usar contra el oponente");
				for (int i = 0; i < player.getMoves().size(); ++i)
				{
					mvprintw(22,(y/2)-30+15*i,"%d-%s",i,player.getMoves()[i]->getNombre().c_str());
					mvprintw(23,(y/2)-30+15*i,"usos:%d",player.getMoves()[i]->getUsos());		
				}
				elegido=getch();
				if((elegido-48)<player.getMoves().size()&&(elegido-48)>=0){
					if(player.getMoves()[elegido-48]->getUsos()>0){
						elegido=elegido-48;
						player.getMoves()[elegido]->setUsos(player.getMoves()[elegido]->getUsos()-1);
						revision=1;
					}
				}
				mvprintw(22,(y/2)-30,"                                                             ");
				mvprintw(23,(y/2)-30,"                                                             ");		
			}
			attroff(COLOR_PAIR(8));
		}else{
			attron(COLOR_PAIR(8));
			mvprintw(20,(y/2)-30,"ya no dispones de ataques que tengan usos");
			mvprintw(21,(y/2)-30,"tu pokemon atacara pero a cambio de hacerse dano a si mismo");
			avanzar=getch();
			tiene1=true;
			attroff(COLOR_PAIR(8));
		}
		attron(COLOR_PAIR(8));
		mvprintw(21,(y/2)-30,"                                                                           ");
		attroff(COLOR_PAIR(8));
		revision2=0;
		for (int i = 0; i < cpu.getMoves().size(); ++i)
		{
			if(cpu.getMoves()[i]->getUsos()>0){
				revision2=1;
			}
		}
		if(revision2==1){
			while(revision==1){
				elegido2=rand()%4;
				if(cpu.getMoves()[elegido2]->getUsos()>0){
					revision=0;
					cpu.getMoves()[elegido2]->setUsos(cpu.getMoves()[elegido2]->getUsos()-1);
				}
			}
		}else{
			tiene2=true;
		}
		
		if (player.getVelocidad()>cpu.getVelocidad())
		{
			mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
			avanzar=getch();
			if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
				string tipopoke = typeid(cpu).name();
				int debil=efectividad(tipopoke,player.getMoves()[elegido]->getTipo());
				cpu.setVida(player.getMoves()[elegido]->efecto(0,player.getAtaque(),cpu.getVida(),cpu.getDefensa(),debil));
			}else{
				mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
			}
			vida(player,cpu);
			avanzar=getch();
			mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
			avanzar=getch();
			if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
				string tipopoke = typeid(player).name();
				int debil=efectividad(tipopoke,cpu.getMoves()[elegido2]->getTipo());
				player.setVida(cpu.getMoves()[elegido2]->efecto(0,cpu.getAtaque(),player.getVida(),player.getDefensa(),debil));
			}else{
				mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
			}
			vida(player,cpu);
			avanzar=getch();
		}else{
			mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
			avanzar=getch();
			if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
				string tipopoke = typeid(player).name();
				int debil=efectividad(tipopoke,cpu.getMoves()[elegido2]->getTipo());
				player.setVida(cpu.getMoves()[elegido2]->efecto(0,cpu.getAtaque(),player.getVida(),player.getDefensa(),debil));
			}else{
				mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
			}
			vida(player,cpu);
			avanzar=getch();
			mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
			avanzar=getch();
			if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
				string tipopoke = typeid(cpu).name();
				int debil=efectividad(tipopoke,player.getMoves()[elegido]->getTipo());
				cpu.setVida(player.getMoves()[elegido]->efecto(0,player.getAtaque(),cpu.getVida(),cpu.getDefensa(),debil));
			}else{
				mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
			}
			vida(player,cpu);
			avanzar=getch();
		}
		if (player.getVida()>0&&cpu.getVida()<=0)
		{
			control = 1;
		}else if(player.getVida()<=0&&cpu.getVida()>0){
			 control = 2;
		}else{
			control = 0;
		}
	}
	if(control==1){
		attron(COLOR_PAIR(2));
		limpiar();
		attroff(COLOR_PAIR(2));
		pokebola(3);
		attron(COLOR_PAIR(8));
		mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
		mvprintw(1,(y/2)-10,"!FELICIDADES HAS GANADO!");
		attroff(COLOR_PAIR(8));
		avanzar=getch();
	}else if(control==2){
		attron(COLOR_PAIR(2));
		limpiar();
		attroff(COLOR_PAIR(2));
		pokebola(1);
		attron(COLOR_PAIR(8));
		mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
		mvprintw(1,(y/2)-15,"DERROTA,MEJOR SUERTE LA PROXIMA");
		attroff(COLOR_PAIR(8));
		avanzar=getch();	
	}else{
		attron(COLOR_PAIR(2));
		limpiar();
		attroff(COLOR_PAIR(2));
		pokebola(5);
		attron(COLOR_PAIR(8));
		mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
		mvprintw(1,(y/2)-10,"EL combate a terminado");
		attroff(COLOR_PAIR(8));
		avanzar=getch();			
	}
}
vector<Move*> oponent_moves(Pokemon pokemonElegido){
	vector<Move*> moves;
	if(typeid(pokemonElegido) == typeid(Fire)){
		moves.push_back(new Ataque("Flamethrower","Fuego",99,5,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Fire Punch","Fuego",100,8,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Iron Tail","Acero",75,7,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Dragon Claw","Fuego",95,6,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Fire Blast","Fuego",85,5,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Overheat","Fuego",90,4,"ataque que lanza fuego al oponente"));
	}else if(typeid(pokemonElegido) == typeid(Thunder)){
		moves.push_back(new Ataque("Thundershock","Electrico",100,4,"ataque que causa una descarga electrica mediante un trueno"));
		moves.push_back(new Ataque("Thunder puch","Electrico",95,8,"ataque que causa una descarga electrica de un golpe"));
		moves.push_back(new Ataque("Electro Ball","Electrico",100,5,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
		moves.push_back(new Ataque("Tail Whip","Electrico",100,8,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
		moves.push_back(new Ataque("Discharge","Electrico",100,6,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
		moves.push_back(new Ataque("Thunder Wave","Electrico",100,4,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
	}else if(typeid(pokemonElegido) == typeid(Water)){
		moves.push_back(new Ataque("Water pulse","Agua",99,5,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Blizzard","Agua",70,7,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Water gun","Agua",100,6,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Bubble Beam","Agua",95,6,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Counter","Lucha",100,4,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Body Slam","Normal",100,8,"ataque que causa una onda acuatica que golpea al oponente"));
	}
	return moves;
}
vector<Move*> generar_moves(Pokemon pokemonElegido){
	vector<Move*> moves;
	if(typeid(pokemonElegido) == typeid(Fire)){
		moves.push_back(new Ataque("Flamethrower","Fuego",99,5,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Fire Punch","Fuego",100,8,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Iron Tail","Acero",75,7,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Dragon Claw","Fuego",95,6,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Fire Blast","Fuego",85,5,"ataque que lanza fuego al oponente"));
		moves.push_back(new Ataque("Overheat","Fuego",90,4,"ataque que lanza fuego al oponente"));
	}else if(typeid(pokemonElegido) == typeid(Thunder)){
		moves.push_back(new Ataque("Thundershock","Electrico",100,4,"ataque que causa una descarga electrica mediante un trueno"));
		moves.push_back(new Ataque("Thunder puch","Electrico",95,8,"ataque que causa una descarga electrica de un golpe"));
		moves.push_back(new Ataque("Electro Ball","Electrico",100,5,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
		moves.push_back(new Ataque("Tail Whip","Electrico",100,8,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
		moves.push_back(new Ataque("Discharge","Electrico",100,6,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
		moves.push_back(new Ataque("Thunder Wave","Electrico",100,4,"ataque que crea una bola de electricidad golpeando con ella al oponente"));
	}else if(typeid(pokemonElegido) == typeid(Water)){
		moves.push_back(new Ataque("Water pulse","Agua",99,5,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Blizzard","Agua",70,7,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Water gun","Agua",100,6,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Bubble Beam","Agua",95,6,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Counter","Lucha",100,4,"ataque que causa una onda acuatica que golpea al oponente"));
		moves.push_back(new Ataque("Body Slam","Normal",100,8,"ataque que causa una onda acuatica que golpea al oponente"));
	}
	return moves;
}
vector<Pokemon*> generar_pokemons(){
	vector<Pokemon*> opciones;
	vector<Move*> moves1;
	vector<Move*> moves2;
	vector<Move*> moves3;
	opciones.push_back(new Fire("Charmander",50,17,10,80,moves1));
	opciones.push_back(new Thunder("Pikachu",50,15,11,90,moves2));
	opciones.push_back(new Water("Squirtle",50,16,12,85,moves3));
	return opciones;
}
void pokebola(int color){
	int x,y;
	getmaxyx(stdscr,x,y);
	attron(COLOR_PAIR(1));
	mvprintw(5,(y/2)-4,"        ");
	mvprintw(6,(y/2)-8,"                ");
	mvprintw(7,(y/2)-10,"                    ");
	mvprintw(8,(y/2)-12,"                        ");
	mvprintw(9,(y/2)-12,"                        ");
	mvprintw(10,(y/2)-14,"            ");
	mvprintw(10,(y/2)+2,"            ");
	mvprintw(11,(y/2)-14,"          ");
	mvprintw(11,(y/2)+4,"          ");
	mvprintw(12,(y/2)-14,"          ");
	mvprintw(12,(y/2)+4,"          ");
	mvprintw(13,(y/2)-14,"  ");
	mvprintw(13,(y/2)-4,"  ");
	mvprintw(13,(y/2)+2,"  ");
	mvprintw(13,(y/2)+12,"  ");
	mvprintw(14,(y/2)-12,"  ");
	mvprintw(14,(y/2)-2,"    ");
	mvprintw(14,(y/2)+10,"  ");
	mvprintw(15,(y/2)-12,"  ");
	mvprintw(15,(y/2)+10,"  ");
	mvprintw(16,(y/2)-10,"  ");
	mvprintw(16,(y/2)+8,"  ");
	mvprintw(17,(y/2)-8,"    ");
	mvprintw(17,(y/2)+4,"    ");
	mvprintw(18,(y/2)-4,"        ");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(color));
	mvprintw(6,(y/2)-4,"        ");
	mvprintw(7,(y/2)-8,"                ");
	mvprintw(8,(y/2)-10,"                    ");
	mvprintw(9,(y/2)-10,"        ");
	mvprintw(9,(y/2)+2,"        ");
	mvprintw(10,(y/2)-12,"        ");
	mvprintw(10,(y/2)+4,"        ");
	attroff(COLOR_PAIR(color));
	move(0,0);
}
void limpiar(){
	int x,y;
	getmaxyx(stdscr,x,y);
	for (int i = 0; i <y ; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			mvprintw(j,i," ");
		}
	}
	move(0,0);
}
