#include <ncurses.h>
#include "pokemon.h"
#include "move.h"
#include "ataque.h"
#include "proteccion.h"
#include "recover.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <stdlib.h>
using std::fstream;
using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::atoi;
char** traspaso(Pokemon);
int cargar(int);
void guardar(int);
int efectividad(string,string);
void vida(Pokemon,Pokemon);
void limpiar();
void grovyle(int);
void charmeleon();
void frogadier();
void pokebola(int);
void Combate(Pokemon,Pokemon);
vector<Pokemon*> generar_pokemons();
vector<Move*> generar_moves(string);
vector<Move*> oponent_moves(string);
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
		mvprintw(20,(y/2)-16,"*-----------------------------*");
		mvprintw(21,(y/2)-16,"|BIENVENIDO AL COMBATE POKEMON|");
		mvprintw(22,(y/2)-16,"*-----------------------------*");
		mvprintw(23,(y/2)-16,"|   (ENTER)Iniciar Combate    |");
		mvprintw(24,(y/2)-16,"|                             |");
		mvprintw(25,(y/2)-16,"|      (B)Instrucciones       |");
		mvprintw(26,(y/2)-16,"|                             |");
		mvprintw(27,(y/2)-16,"|         (ESC)salir          |");
		mvprintw(28,(y/2)-16,"|                             |");
		mvprintw(29,(y/2)-16,"*-----------------------------*");
		attroff(COLOR_PAIR(8));
		enter=getch();
		if(enter==10){
			vector<Pokemon*> pokemons=generar_pokemons();
			attron(COLOR_PAIR(2));
			limpiar();
			attroff(COLOR_PAIR(2));
			pokebola(5);
			int revision=1;
			Pokemon player;
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
				if((elegido-48)<pokemons.size()&&(elegido-48)>=0){
					player=Pokemon(pokemons[elegido-48]);
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
			vector<Move*> moves=generar_moves(player.getTipo());
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
				mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
				for (int i = 0; i < moves.size(); ++i)
				{	
					mvprintw(22+(i)*3,(y/2)-26,"%d-%s",i,moves[i]->toString().c_str());
					mvprintw(23+(i)*3,(y/2)-26,"   Precision:%d  Usos:%d",moves[i]->getPrecision(),moves[i]->getUsos());
					mvprintw(24+(i)*3,(y/2)-26,"Descripcion: %s",moves[i]->getDescripcion().c_str());
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
			oponente.setMoves(oponent_moves(oponente.getTipo()));
			Combate(player,oponente);
			refresh();
		}else if (enter==98)
		{
			attron(COLOR_PAIR(2));
			limpiar();
			attroff(COLOR_PAIR(2));
			pokebola(5);
			attron(COLOR_PAIR(8));
			mvprintw(0,(y/2)-25,"BIENVENIDO ENTRENADOR AL COMBATE POKEMON");
			mvprintw(1,(y/2)-30,"Registro de victorias: Charmeleon:%d   Frogadier:%d    Grovyle:%d",cargar(1),cargar(2),cargar(3));
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
int cargar (int pok){
	if(pok==1){
		string line;
		ifstream mfile ("fuego.txt");
		if (mfile.is_open())
		{
			getline(mfile,line);
			mfile.close();
		}
		return atoi(line.c_str());
	}else if(pok==2){
		string line;
		ifstream mfile ("agua.txt");
		if (mfile.is_open())
		{
			getline(mfile,line);
			mfile.close();
		}
		return atoi(line.c_str());
	}else{
		string line;
		ifstream mfile ("hoja.txt");
		if (mfile.is_open())
		{
			getline(mfile,line);
			mfile.close();
		}
		return atoi(line.c_str());
	}
}
void guardar(int pok){
	if(pok==1){
		int x=cargar(pok)+1;
		ofstream mfile;
		mfile.open("fuego.txt",std::ios::trunc);
		mfile << x;
		mfile.close();

	}else if(pok==2){
		int x=cargar(pok)+1;
		ofstream mfile;
		mfile.open("agua.txt",std::ios::trunc);
		mfile << x;
		mfile.close();
	}else{
		int x=cargar(pok)+1;
		ofstream mfile;
		mfile.open("hoja.txt",std::ios::trunc);
		mfile << x;
		mfile.close();
	}

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
			charmeleon();
			frogadier();
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Player:Charmeleon-Vida:%d  ",player.getVida());
			mvprintw(23,y-52,"Oponent:Frogadier-Vida:%d  ",cpu.getVida());
			attroff(COLOR_PAIR(8));
		}else{
			charmeleon();
			grovyle(0);
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Player:Charmeleon-Vida:%d  ",player.getVida());
			mvprintw(23,y-52,"Oponent:Grovyle-Vida:%d  ",cpu.getVida());
			attroff(COLOR_PAIR(8));
		}
	}else if(player.getNombre()=="Frogadier"){
		lado2=player.getVida();
		lado1=cpu.getVida();
		if(cpu.getNombre()=="Charmeleon"){
			charmeleon();
			frogadier();
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Oponent:Charmeleon-Vida:%d  ",cpu.getVida());
			mvprintw(23,y-52,"Player:Frogadier-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}else{
			frogadier();
			grovyle(1);
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Oponent:Grovyle-Vida:%d  ",cpu.getVida());
			mvprintw(23,y-52,"Player:Frogadier-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}
	}else{
		if(cpu.getNombre()=="Charmeleon"){
			lado1=cpu.getVida();
			lado2=player.getVida();
			charmeleon();
			grovyle(0);
			attron(COLOR_PAIR(8));
			mvprintw(23,0,"Oponent:Charmeleon-Vida:%d  ",cpu.getVida());
			mvprintw(23,y-52,"Player:Grovyle-Vida:%d  ",player.getVida());
			attroff(COLOR_PAIR(8));
		}else{
			lado1=player.getVida();
			lado2=cpu.getVida();
			frogadier();
			grovyle(1);
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
int efectividad(string,string);
void Combate(Pokemon player,Pokemon cpu){
	int avanzar;
	
	int control=0;
	charmeleon();
	frogadier();
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
		if(player.getMoves()[elegido]->getNombre()=="Protec"||cpu.getMoves()[elegido2]->getNombre()=="Protec"){
			attron(COLOR_PAIR(8));
			if (player.getMoves()[elegido]->getNombre()=="Protec"){
				mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
				avanzar=getch();
				if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
					mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
					avanzar=getch();
					if (cpu.getMoves()[elegido2]->getNombre()=="Protec")
					{
						mvprintw(20,(y/2)-30,"al usar los dos protec nadie se ve afectado,el Combate puede continuar");
						avanzar=getch();
					}else if (cpu.getMoves()[elegido2]->getNombre()=="Recover")
					{
						if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
							if(cpu.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"el oponente recupera parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
							}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
							}
							cpu.setVida(cpu.getMoves()[elegido2]->efecto(cpu.getVida(),0,0,0,0));
							vida(player,cpu);
							avanzar=getch();
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
							avanzar=getch();
						}
					}else{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"Pero es detenido por tu Protec                                                              ");
						attroff(COLOR_PAIR(8));
						avanzar=getch();
					}
				}else{
					mvprintw(20,(y/2)-30,"Pero fallo                                                      ");
					avanzar=getch();
					mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
					avanzar=getch();
					if (cpu.getMoves()[elegido2]->getNombre()=="Protec")
					{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"El oponente se protege pero al no ser atacado por ti nadie se ve afectado");
						attroff(COLOR_PAIR(8));
						avanzar=getch();
					}else if (cpu.getMoves()[elegido2]->getNombre()=="Recover")
					{
						if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
							if(cpu.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"el oponente recupera parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
							}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
							}  
							cpu.setVida(cpu.getMoves()[elegido2]->efecto(cpu.getVida(),0,0,0,0));
							vida(player,cpu);
							avanzar=getch();
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
							avanzar=getch();
						}
					}else{
						if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
							int debil=efectividad(player.getTipo(),cpu.getMoves()[elegido2]->getTipo());
							player.setVida(cpu.getMoves()[elegido2]->efecto(0,cpu.getAtaque(),player.getVida(),player.getDefensa(),debil));
						}else{
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
						}
						vida(player,cpu);
						avanzar=getch();
					}
				}
			}else{
				mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
				avanzar=getch();
				if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
					mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
					avanzar=getch();
					if (player.getMoves()[elegido]->getNombre()=="Protec")
					{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"al usar los dos protec nadie se ve afectado,el Combate puede continuar");
						avanzar=getch();
						attroff(COLOR_PAIR(8));
					}else if (player.getMoves()[elegido]->getNombre()=="Recover")
					{
						if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
							if(player.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"recuperas parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
							}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
							}
							player.setVida(player.getMoves()[elegido]->efecto(player.getVida(),0,0,0,0));
							vida(player,cpu);
							avanzar=getch();
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
							avanzar=getch();
						}
					}else{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"Pero es detenido por su Protec                                                              ");
						avanzar=getch();
						attroff(COLOR_PAIR(8));
					}
				}else{
					attron(COLOR_PAIR(8));
					mvprintw(20,(y/2)-30,"Pero fallo                                                      ");
					avanzar=getch();
					mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
					avanzar=getch();
					attroff(COLOR_PAIR(8));
					if (player.getMoves()[elegido]->getNombre()=="Protec")
					{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"te proteges pero al no ser atacado por el, nadie se ve afectado          ");
						avanzar=getch();
						attroff(COLOR_PAIR(8));
					}else if (player.getMoves()[elegido]->getNombre()=="Recover")
					{
						if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
							if(player.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"recuperas parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
							}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
							}
							player.setVida(player.getMoves()[elegido]->efecto(player.getVida(),0,0,0,0));
							vida(player,cpu);
							avanzar=getch();
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
							avanzar=getch();
						}
					}else{
						if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
							int debil=efectividad(cpu.getTipo(),player.getMoves()[elegido]->getTipo());
							cpu.setVida(player.getMoves()[elegido]->efecto(0,player.getAtaque(),cpu.getVida(),cpu.getDefensa(),debil));
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
						}
						vida(player,cpu);
						avanzar=getch();
					}
				}
			}
			int control2=0;
			attroff(COLOR_PAIR(8));
			if(player.getVida()>0&&cpu.getVida()>0){
				while(control2==0){
				attron(COLOR_PAIR(8));
				mvprintw(20,(y/2)-30,"             Que Desea hacer ahora?                                                ");
				mvprintw(21,(y/2)-30,"             0-Continuar el Combate");
				mvprintw(22,(y/2)-30,"             1-Terminar el Combate");
				avanzar=getch();
				if((avanzar-48)==0){
					control2=1;
				}else if ((avanzar-48)==1)
				{
					control2=1;
					control=3;
				}
				attroff(COLOR_PAIR(8));
				}
			}	
		}else if(player.getVelocidad()>cpu.getVelocidad()){
			attron(COLOR_PAIR(8));
			if(tiene1==false){
				mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
				avanzar=getch();
				if(player.getMoves()[elegido]->getNombre()=="Recover"){
					if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
						if(player.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"recuperas parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
						}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
						}
						player.setVida(player.getMoves()[elegido]->efecto(player.getVida(),0,0,0,0));
						vida(player,cpu);
						avanzar=getch();
					}else{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
						attroff(COLOR_PAIR(8));
						avanzar=getch();
					}
				}else{
					if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
						int debil=efectividad(cpu.getTipo(),player.getMoves()[elegido]->getTipo());
						cpu.setVida(player.getMoves()[elegido]->efecto(0,player.getAtaque(),cpu.getVida(),cpu.getDefensa(),debil));
					}else{
						mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
					}
					vida(player,cpu);
					avanzar=getch();
				}
			}else{
				mvprintw(20,(y/2)-30,"%s ha usado Struggle                                                      ",player.getNombre().c_str());
				cpu.setVida(cpu.getVida()-5);
				player.setVida(player.getVida()-8);
				vida(player,cpu);
				avanzar=getch();
			}
			attroff(COLOR_PAIR(8));
		}else{
			attron(COLOR_PAIR(8));
			if(tiene2==false){
				mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
				avanzar=getch();
				if(cpu.getMoves()[elegido2]->getNombre()=="Recover"){
					if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
						if(cpu.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"el oponente recupera parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
						}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
						}
						cpu.setVida(cpu.getMoves()[elegido2]->efecto(cpu.getVida(),0,0,0,0));
						vida(player,cpu);
						avanzar=getch();
					}else{
						attron(COLOR_PAIR(8));
						mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
						attroff(COLOR_PAIR(8));
						avanzar=getch();
					}
				}else{
					if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
						int debil=efectividad(player.getTipo(),cpu.getMoves()[elegido2]->getTipo());
						player.setVida(cpu.getMoves()[elegido2]->efecto(0,cpu.getAtaque(),player.getVida(),player.getDefensa(),debil));
					}else{
						mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
					}
					vida(player,cpu);
					avanzar=getch();
				}
			}else{
				mvprintw(20,(y/2)-30,"%s ha usado Struggle                                                      ",cpu.getNombre().c_str());
				player.setVida(player.getVida()-5);
				cpu.setVida(cpu.getVida()-8);
				vida(player,cpu);
				avanzar=getch();
			}
			attroff(COLOR_PAIR(8));
		}
		if(player.getVida()>0&&cpu.getVida()>0&&player.getMoves()[elegido]->getNombre()!="Protec"&&cpu.getMoves()[elegido2]->getNombre()!="Protec"){
			if(player.getVelocidad()<cpu.getVelocidad()){
				attron(COLOR_PAIR(8));
				if(tiene1==false){
					mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",player.getNombre().c_str(),player.getMoves()[elegido]->getNombre().c_str());
					avanzar=getch();
					if(player.getMoves()[elegido]->getNombre()=="Recover"){
						if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
							if(player.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"recuperas parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
							}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
							}
							player.setVida(player.getMoves()[elegido]->efecto(player.getVida(),0,0,0,0));
							vida(player,cpu);
							avanzar=getch();
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
							avanzar=getch();
						}
					}else{
						if((rand()%100)<=player.getMoves()[elegido]->getPrecision()){
							int debil=efectividad(cpu.getTipo(),player.getMoves()[elegido]->getTipo());
							cpu.setVida(player.getMoves()[elegido]->efecto(0,player.getAtaque(),cpu.getVida(),cpu.getDefensa(),debil));
						}else{
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
						}
						vida(player,cpu);
						avanzar=getch();
					}
				}else{
					mvprintw(20,(y/2)-30,"%s ha usado Struggle                                                      ",player.getNombre().c_str());
					cpu.setVida(cpu.getVida()-5);
					player.setVida(player.getVida()-8);
					vida(player,cpu);
					avanzar=getch();
				}
				attroff(COLOR_PAIR(8));
			}else{
				attron(COLOR_PAIR(8));
				if(tiene2==false){
					attron(COLOR_PAIR(8));
					mvprintw(20,(y/2)-30,"%s ha usado %s                                                      ",cpu.getNombre().c_str(),cpu.getMoves()[elegido2]->getNombre().c_str());
					attroff(COLOR_PAIR(8));
					avanzar=getch();
					if(cpu.getMoves()[elegido2]->getNombre()=="Recover"){
						if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
							if(player.getVida()!=50){
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"el oponente recupera parte de vida                                                          ");
								attroff(COLOR_PAIR(8));
							}else{
								attron(COLOR_PAIR(8));
								mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
								attroff(COLOR_PAIR(8));
							}
							cpu.setVida(cpu.getMoves()[elegido2]->efecto(cpu.getVida(),0,0,0,0));
							vida(player,cpu);
							avanzar=getch();
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
							avanzar=getch();
						}
					}else{
						if((rand()%100)<=cpu.getMoves()[elegido2]->getPrecision()){
							int debil=efectividad(player.getTipo(),cpu.getMoves()[elegido2]->getTipo());
							player.setVida(cpu.getMoves()[elegido2]->efecto(0,cpu.getAtaque(),player.getVida(),player.getDefensa(),debil));
						}else{
							attron(COLOR_PAIR(8));
							mvprintw(20,(y/2)-30,"Pero fallo                                                           ");
							attroff(COLOR_PAIR(8));
						}
						vida(player,cpu);
						avanzar=getch();
					}
				}else{
					attron(COLOR_PAIR(8));
					mvprintw(20,(y/2)-30,"%s ha usado Struggle                                                      ",cpu.getNombre().c_str());
					attroff(COLOR_PAIR(8));
					player.setVida(player.getVida()-5);
					cpu.setVida(cpu.getVida()-8);
					vida(player,cpu);
					avanzar=getch();
				}
				attroff(COLOR_PAIR(8));
			}
			if(player.getVida()<=0){
				control=2;
			}else if(cpu.getVida()<=0){
				control=1;
			}else{
				attron(COLOR_PAIR(8));
				int control2=0;
				while(control2==0){
					mvprintw(20,(y/2)-30,"                    Que Desea hacer ahora?                               ");
					mvprintw(21,(y/2)-30,"                    0-Continuar el Combate");
					mvprintw(22,(y/2)-30,"                    1-Terminar el Combate");
					avanzar=getch();
					if((avanzar-48)==0){
						control2=1;
					}else if ((avanzar-48)==1)
					{
						control2=1;
						control=3;
					}
				}
				attroff(COLOR_PAIR(8));
			}	
		}else if(player.getVida()<=0){
			control=2;
		}else if(cpu.getVida()<=0){
			control=1;
		}
		attroff(COLOR_PAIR(8));
	}
	if(control==1){
		attron(COLOR_PAIR(2));
		limpiar();
		attroff(COLOR_PAIR(2));
		pokebola(3);
		attron(COLOR_PAIR(8));
		mvprintw(0,(y/2)-20,"(presione cualquier tecla para continuar)");
		mvprintw(1,(y/2)-10,"!FELICIDADES HAS GANADO!");
		if(player.getNombre()=="Charmeleon"){
			guardar(1);
		}else if(player.getNombre()=="Frogadier"){
			guardar(2);
		}else{
			guardar(3);
		}
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
		if(cpu.getNombre()=="Charmeleon"){
			guardar(1);
		}else if(cpu.getNombre()=="Frogadier"){
			guardar(2);
		}else{
			guardar(3);
		}
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
vector<Move*> oponent_moves(string tipo){
	vector<Move*> moves;
	moves.push_back(new Proteccion("Protec","Normal",50,5,"movimiento que protege de todo ataque al usuario"));
	moves.push_back(new Recover("Recover","Normal",50,5,"movimientoque recupera vida del usuario(falla si el usuario no tiene dano alguno)"));
	if(tipo=="Agua"){
		moves.push_back(new Ataque("Aerial ace","Volador",100,8,"ataque aereo que nunca falla"));
		moves.push_back(new Ataque("Water pulse","Agua",99,5,"ataque que causa una onda acuatica que golpea al oponente"));
	}else if(tipo=="Fuego"){
		moves.push_back(new Ataque("Thunder puch","Electrico",95,8,"ataque que causa una descarga electrica de un golpe"));
		moves.push_back(new Ataque("Flamethrower","Fuego",99,5,"ataque que lanza fuego al oponente"));
	}else{
		
		moves.push_back(new Ataque("Rock tomb","Roca",90,10,"ataque que tumba rocas sobre el oponente"));
		moves.push_back(new Ataque("Leaf blade","Hoja",99,5,"ataque lanza hojas afiladas contra el oponente"));
	}
	return moves;
}
vector<Move*> generar_moves(string tipo){
	vector<Move*> moves;
	moves.push_back(new Ataque("Takle","Normal",100,15,"ataque simple que baja la vida del oponente con respecto a tu poder de ataque"));
	if(tipo=="Agua"){
		moves.push_back(new Ataque("Water pulse","Agua",99,5,"ataque que causa una onda acuatica que golpea al oponente"));
	}else if(tipo=="Fuego"){
		moves.push_back(new Ataque("Thunder puch","Electrico",95,8,"ataque que causa una descarga electrica de un golpe"));
		moves.push_back(new Ataque("Flamethrower","Fuego",99,5,"ataque que lanza fuego al oponente"));
	}else{
		moves.push_back(new Ataque("Thunder puch","Electrico",95,8,"ataque que causa una descarga electrica de un golpe"));
		moves.push_back(new Ataque("Leaf blade","Hoja",99,5,"ataque lanza hojas afiladas contra el oponente"));
	}
	moves.push_back(new Ataque("Rock tomb","Roca",90,10,"ataque que tumba rocas sobre el oponente"));	
	moves.push_back(new Ataque("Aerial ace","Volador",100,8,"ataque aereo que nunca falla"));
	moves.push_back(new Proteccion("Protec","Normal",50,5,"movimiento que protege de todo ataque al usuario"));
	moves.push_back(new Recover("Recover","Normal",50,5,"movimientoque recupera vida del usuario(falla si el usuario no tiene dano alguno)"));
	
	return moves;
}
vector<Pokemon*> generar_pokemons(){
	vector<Pokemon*> opciones;
	vector<Move*> moves1;
	vector<Move*> moves2;
	vector<Move*> moves3;
	opciones.push_back(new Pokemon("Charmeleon","Fuego",50,17,10,80,moves1));
	opciones.push_back(new Pokemon("Frogadier","Agua",50,15,11,90,moves2));
	opciones.push_back(new Pokemon("Grovyle","Hoja",50,16,12,85,moves3));
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
void charmeleon(){
attron(COLOR_PAIR(4));
	mvprintw(2,12,"  ");
	mvprintw(3,12,"    ");
	mvprintw(4,10,"      ");
	mvprintw(5,10,"      ");
	mvprintw(6,14,"  ");
	attroff(COLOR_PAIR(4));
	attron(COLOR_PAIR(1));
	mvprintw(1,12,"  ");
	mvprintw(2,10,"  ");
	mvprintw(2,14,"  ");
	mvprintw(3,10,"  ");
	mvprintw(3,16,"  ");
	mvprintw(4,16,"  ");
	mvprintw(5,16,"  ");
	mvprintw(6,16,"  ");
	mvprintw(4,8,"  ");
	mvprintw(5,8,"  ");
	mvprintw(6,10,"  ");
	mvprintw(7,6,"    ");
	mvprintw(8,4,"    ");
	mvprintw(9,2,"  ");
	mvprintw(10,0,"  ");
	mvprintw(11,0,"  ");
	mvprintw(12,0,"  ");
	mvprintw(13,0,"  ");
	mvprintw(7,14,"  ");
	mvprintw(8,12,"  ");
	mvprintw(9,10,"  ");
	mvprintw(10,8,"  ");
	mvprintw(11,8,"  ");
	mvprintw(12,10,"                                ");
	mvprintw(11,14,"              ");
	mvprintw(11,30,"              ");
	mvprintw(10,18,"          ");
	mvprintw(10,30,"              ");
	mvprintw(9,20,"                      ");
	mvprintw(8,20,"                    ");
	mvprintw(7,22,"                  ");
	mvprintw(6,24,"              ");
	mvprintw(5,24,"            ");
	mvprintw(4,22,"          ");
	mvprintw(3,22,"        ");
	mvprintw(2,24,"    ");
	mvprintw(13,10,"                              ");
	mvprintw(13,2,"  ");
	mvprintw(14,2,"                                        ");
	mvprintw(15,4,"              ");
	mvprintw(15,20,"          ");
	mvprintw(15,34,"      ");
	mvprintw(15,42,"  ");
	mvprintw(16,6,"                      ");
	mvprintw(16,36,"  ");
	mvprintw(16,40,"    ");
	mvprintw(17,8,"            ");
	mvprintw(17,22,"        ");
	mvprintw(17,38,"    ");
	mvprintw(18,8,"                    ");
	mvprintw(18,30,"  ");
	mvprintw(19,10,"                    ");
	mvprintw(20,10,"          ");
	mvprintw(21,10,"  ");
	mvprintw(21,18,"  ");
	mvprintw(22,12,"      ");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(3));
	mvprintw(6,12,"  ");
	mvprintw(7,12,"  ");
	mvprintw(14,24,"    ");
	mvprintw(15,22,"      ");
	mvprintw(16,24,"  ");
	mvprintw(17,24,"  ");
	mvprintw(18,22,"  ");
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(5));
	mvprintw(7,10,"  ");
	mvprintw(8,8,"    ");
	mvprintw(9,4,"      ");
	mvprintw(10,2,"      ");
	mvprintw(11,2,"      ");
	mvprintw(12,2,"        ");
	mvprintw(12,14,"            ");
	mvprintw(12,28,"            ");
	mvprintw(13,4,"      ");
	mvprintw(13,12,"      ");
	mvprintw(13,20,"        ");
	mvprintw(13,32,"    ");
	mvprintw(14,4,"              ");
	mvprintw(14,20,"    ");
	mvprintw(14,36,"    ");
	mvprintw(15,6,"  ");
	mvprintw(15,10,"        ");
	mvprintw(15,36,"    ");
	mvprintw(16,10,"            ");
	mvprintw(16,40,"  ");
	mvprintw(17,10,"          ");
	mvprintw(18,12,"      ");
	mvprintw(18,26,"  ");
	mvprintw(19,12,"        ");
	mvprintw(20,14,"  ");
	mvprintw(21,14,"  ");
	mvprintw(11,18,"    ");
	mvprintw(11,24,"  ");
	mvprintw(11,34,"        ");
	mvprintw(10,22,"      ");
	mvprintw(10,32,"          ");
	mvprintw(9,22,"      ");
	mvprintw(9,30,"          ");
	mvprintw(8,22,"                ");
	mvprintw(7,24,"              ");
	mvprintw(6,28,"    ");
	mvprintw(6,34,"  ");
	mvprintw(5,26,"    ");
	mvprintw(4,24,"      ");
	mvprintw(3,24,"    ");
	attroff(COLOR_PAIR(5));
	move(0,0);
}
void frogadier(){
	int x,y;
	getmaxyx(stdscr,x,y);
	attron(COLOR_PAIR(1));
	mvprintw(5,y-2,"  ");
	mvprintw(6,y-2,"  ");
	mvprintw(4,y-6,"    ");
	mvprintw(5,y-8,"  ");
	mvprintw(6,y-10,"    ");
	mvprintw(7,y-14,"    ");
	mvprintw(6,y-18,"    ");
	mvprintw(7,y-6,"    ");
	mvprintw(8,y-6,"  ");
	mvprintw(9,y-8,"    ");
	mvprintw(10,y-10,"    ");
	mvprintw(10,y-16,"  ");
	mvprintw(11,y-16,"      ");
	mvprintw(1,y-34,"  ");
	mvprintw(2,y-36,"      ");
	mvprintw(2,y-24,"      ");
	mvprintw(3,y-38,"        ");
	mvprintw(3,y-28,"          ");
	mvprintw(4,y-38,"                    ");
	mvprintw(5,y-40,"                    ");
	mvprintw(6,y-40,"                    ");
	mvprintw(7,y-42,"                        ");
	mvprintw(8,y-44,"  ");
	mvprintw(8,y-40,"                      ");
	mvprintw(9,y-44,"      ");
	mvprintw(9,y-36,"                  ");
	mvprintw(10,y-42,"                      ");
	mvprintw(11,y-40,"                  ");
	mvprintw(12,y-36,"          ");
	mvprintw(13,y-36,"  ");
	mvprintw(13,y-22,"  ");
	mvprintw(13,y-18,"  ");
	mvprintw(12,y-18,"  ");
	mvprintw(14,y-38,"        ");
	mvprintw(14,y-24,"          ");
	mvprintw(15,y-38,"                          ");
	mvprintw(16,y-40,"                            ");
	mvprintw(17,y-44,"          ");
	mvprintw(17,y-32,"                  ");
	mvprintw(18,y-46,"  ");
	mvprintw(18,y-42,"      ");
	mvprintw(18,y-30,"                  ");
	mvprintw(19,y-46,"  ");
	mvprintw(19,y-40,"  ");
	mvprintw(19,y-36,"  ");
	mvprintw(19,y-28,"                  ");
	mvprintw(20,y-44,"    ");
	mvprintw(20,y-38,"    ");
	mvprintw(20,y-30,"  ");
	mvprintw(20,y-26,"        ");
	mvprintw(20,y-16,"    ");
	mvprintw(21,y-30,"  ");
	mvprintw(21,y-24,"  ");
	mvprintw(21,y-20,"  ");
	mvprintw(22,y-28,"    ");
	mvprintw(22,y-22,"  ");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(6));
	mvprintw(5,y-28,"  ");
	mvprintw(6,y-30,"      ");
	mvprintw(7,y-30,"      ");
	mvprintw(8,y-30,"  ");
	mvprintw(9,y-42,"    ");
	mvprintw(10,y-40,"    ");
	mvprintw(11,y-36,"          ");
	mvprintw(10,y-24,"  ");
	mvprintw(14,y-36,"  ");
	mvprintw(15,y-36,"  ");
	mvprintw(16,y-38,"  ");
	mvprintw(17,y-38,"  ");
	mvprintw(15,y-32,"  ");
	mvprintw(16,y-32,"  ");
	mvprintw(17,y-30,"  ");
	mvprintw(16,y-28,"    ");
	mvprintw(14,y-22,"  ");
	mvprintw(15,y-22,"  ");
	mvprintw(16,y-22,"  ");
	mvprintw(17,y-24,"    ");
	mvprintw(18,y-24,"  ");
	mvprintw(15,y-18,"    ");
	mvprintw(16,y-18,"    ");
	mvprintw(17,y-18,"  ");
	mvprintw(18,y-20,"    ");
	mvprintw(19,y-16,"  ");
	attroff(COLOR_PAIR(6));
	attron(COLOR_PAIR(3));
	mvprintw(8,y-26,"  ");
	mvprintw(9,y-30,"  ");
	mvprintw(9,y-26,"  ");
	mvprintw(10,y-28,"  ");
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(7));
	mvprintw(17,y-40,"  ");
	mvprintw(18,y-42,"    ");
	mvprintw(19,y-24,"  ");
	mvprintw(20,y-26,"    ");
	mvprintw(19,y-20,"  ");
	mvprintw(19,y-14,"  ");
	mvprintw(2,y-34,"  ");
	mvprintw(3,y-36,"    ");
	mvprintw(4,y-36,"      ");
	mvprintw(5,y-38,"        ");
	mvprintw(6,y-38,"      ");
	mvprintw(7,y-38,"  ");
	mvprintw(7,y-34,"  ");
	mvprintw(8,y-40,"  ");
	mvprintw(8,y-36,"    ");
	mvprintw(9,y-36,"      ");
	mvprintw(10,y-36,"        ");
	mvprintw(10,y-26,"  ");
	mvprintw(3,y-24,"    ");
	mvprintw(4,y-28,"        ");
	mvprintw(5,y-26,"    ");
	mvprintw(6,y-24,"  ");
	mvprintw(7,y-24,"    ");
	mvprintw(8,y-24,"    ");
	mvprintw(9,y-24,"    ");
	attroff(COLOR_PAIR(7));
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
void grovyle(int lado){
	int x,y;
	getmaxyx(stdscr,x,y);
	if(lado ==1){
		attron(COLOR_PAIR(10));
		mvprintw(1,32,"        ");
		mvprintw(2,28,"              ");
		mvprintw(3,26,"                  ");
		mvprintw(4,24,"                    ");
		mvprintw(5,22,"                        ");
		mvprintw(6,22,"      ");
		mvprintw(6,30,"                ");
		mvprintw(7,20,"      ");
		mvprintw(7,28,"                  ");
		mvprintw(8,8,"    ");
		mvprintw(8,18,"      ");
		mvprintw(8,28,"                    ");
		mvprintw(9,8,"      ");
		mvprintw(9,18,"    ");
		mvprintw(9,26,"                      ");
		mvprintw(10,8,"        ");
		mvprintw(10,22,"                          ");
		mvprintw(11,2,"    ");
		mvprintw(11,10,"      ");
		mvprintw(11,20,"                          ");
		mvprintw(12,0,"                                      ");
		mvprintw(13,2,"                                        ");
		mvprintw(14,4,"                            ");
		mvprintw(14,34,"          ");
		mvprintw(15,6,"                            ");
		mvprintw(15,36,"      ");
		mvprintw(16,10,"                      ");
		mvprintw(16,38,"  ");
		mvprintw(17,14,"                  ");
		mvprintw(18,14,"                    ");
		mvprintw(19,16,"                ");
		mvprintw(20,14,"          ");
		mvprintw(21,16,"      ");
		attroff(COLOR_PAIR(10));
		attron(COLOR_PAIR(9));
		mvprintw(2,34,"      ");
		mvprintw(3,36,"      ");
		mvprintw(4,40,"  ");
		mvprintw(5,42,"  ");
		mvprintw(5,32,"        ");
		mvprintw(6,32,"            ");
		mvprintw(7,30,"              ");
		mvprintw(8,30,"  ");
		mvprintw(8,40,"      ");
		mvprintw(9,38,"        ");
		mvprintw(9,28,"    ");
		mvprintw(10,26,"      ");
		mvprintw(10,40,"  ");
		mvprintw(10,44,"  ");
		mvprintw(11,22,"        ");
		mvprintw(12,20,"    ");
		mvprintw(12,26,"  ");
		mvprintw(12,34,"  ");
		mvprintw(13,18,"  ");
		mvprintw(13,22,"  ");
		mvprintw(13,26,"  ");
		mvprintw(13,34,"    ");
		mvprintw(14,18,"  ");
		mvprintw(14,22,"    ");
		mvprintw(14,28,"  ");
		mvprintw(14,36,"    ");
		mvprintw(15,16,"      ");
		mvprintw(15,24,"        ");
		mvprintw(16,16,"      ");
		mvprintw(16,24,"    ");
		mvprintw(17,16,"    ");
		mvprintw(17,22,"    ");
		mvprintw(18,16,"      ");
		mvprintw(18,30,"  ");
		mvprintw(19,18,"  ");
		mvprintw(20,16,"      ");
		mvprintw(10,10,"  ");
		mvprintw(12,12,"  ");
		mvprintw(13,14,"  ");
		mvprintw(14,6,"  ");
		mvprintw(15,10,"    ");
		mvprintw(6,24,"  ");
		mvprintw(7,22,"  ");
		mvprintw(8,20,"  ");
		attroff(COLOR_PAIR(9));
		attron(COLOR_PAIR(6));
		mvprintw(2,32,"  ");
		mvprintw(3,28,"        ");
		mvprintw(4,26,"      ");
		mvprintw(5,24,"    ");
		mvprintw(9,10,"  ");
		mvprintw(10,12,"  ");
		mvprintw(11,12,"  ");
		mvprintw(12,14,"  ");
		mvprintw(12,2,"    ");
		mvprintw(13,4,"      ");
		mvprintw(14,8,"    ");
		mvprintw(14,40,"  ");
		mvprintw(15,38,"  ");
		attroff(COLOR_PAIR(6));
		attron(COLOR_PAIR(4));
		mvprintw(9,32,"  ");
		mvprintw(10,32,"      ");
		mvprintw(11,30,"    ");
		mvprintw(12,28,"    ");
		mvprintw(13,30,"  ");
		mvprintw(17,28,"  ");
		mvprintw(18,26,"  ");
		attroff(COLOR_PAIR(4));
		attron(COLOR_PAIR(3));
		mvprintw(7,32,"      ");
		mvprintw(8,34,"  ");
		mvprintw(8,38,"  ");
		attroff(COLOR_PAIR(3));
	}else{
		attron(COLOR_PAIR(10));
		mvprintw(1,y-40,"        ");
		mvprintw(2,y-42,"              ");
		mvprintw(3,y-44,"                  ");
		mvprintw(4,y-44,"                    ");
		mvprintw(5,y-46,"                        ");
		mvprintw(6,y-28,"      ");
		mvprintw(6,y-46,"                ");
		mvprintw(7,y-26,"      ");
		mvprintw(7,y-46,"                  ");
		mvprintw(8,y-12,"    ");
		mvprintw(8,y-24,"      ");
		mvprintw(8,y-48,"                    ");
		mvprintw(9,y-14,"      ");
		mvprintw(9,y-22,"    ");
		mvprintw(9,y-48,"                      ");
		mvprintw(10,y-16,"        ");
		mvprintw(10,y-48,"                          ");
		mvprintw(11,y-6,"    ");
		mvprintw(11,y-16,"      ");
		mvprintw(11,y-46,"                          ");
		mvprintw(12,y-38,"                                      ");
		mvprintw(13,y-42,"                                        ");
		mvprintw(14,y-32,"                            ");
		mvprintw(14,y-44,"          ");
		mvprintw(15,y-34,"                            ");
		mvprintw(15,y-42,"      ");
		mvprintw(16,y-32,"                      ");
		mvprintw(16,y-40,"  ");
		mvprintw(17,y-32,"                  ");
		mvprintw(18,y-34,"                    ");
		mvprintw(19,y-32,"                ");
		mvprintw(20,y-24,"          ");
		mvprintw(21,y-22,"      ");
		attroff(COLOR_PAIR(10));
		attron(COLOR_PAIR(9));
		mvprintw(2,y-40,"      ");
		mvprintw(3,y-42,"      ");
		mvprintw(4,y-42,"  ");
		mvprintw(5,y-44,"  ");
		mvprintw(5,y-40,"        ");
		mvprintw(6,y-44,"            ");
		mvprintw(7,y-44,"              ");
		mvprintw(8,y-32,"  ");
		mvprintw(8,y-46,"      ");
		mvprintw(9,y-46,"        ");
		mvprintw(9,y-32,"    ");
		mvprintw(10,y-32,"      ");
		mvprintw(10,y-42,"  ");
		mvprintw(10,y-46,"  ");
		mvprintw(11,y-30,"        ");
		mvprintw(12,y-24,"    ");
		mvprintw(12,y-28,"  ");
		mvprintw(12,y-36,"  ");
		mvprintw(13,y-20,"  ");
		mvprintw(13,y-24,"  ");
		mvprintw(13,y-28,"  ");
		mvprintw(13,y-38,"    ");
		mvprintw(14,y-20,"  ");
		mvprintw(14,y-26,"    ");
		mvprintw(14,y-30,"  ");
		mvprintw(14,y-40,"    ");
		mvprintw(15,y-22,"      ");
		mvprintw(15,y-32,"        ");
		mvprintw(16,y-22,"      ");
		mvprintw(16,y-28,"    ");
		mvprintw(17,y-20,"    ");
		mvprintw(17,y-26,"    ");
		mvprintw(18,y-22,"      ");
		mvprintw(18,y-32,"  ");
		mvprintw(19,y-20,"  ");
		mvprintw(20,y-22,"      ");
		mvprintw(10,y-12,"  ");
		mvprintw(12,y-14,"  ");
		mvprintw(13,y-16,"  ");
		mvprintw(14,y-8,"  ");
		mvprintw(15,y-14,"    ");
		mvprintw(6,y-26,"  ");
		mvprintw(7,y-24,"  ");
		mvprintw(8,y-22,"  ");
		attroff(COLOR_PAIR(9));
		attron(COLOR_PAIR(6));
		mvprintw(2,y-34,"  ");
		mvprintw(3,y-36,"        ");
		mvprintw(4,y-32,"      ");
		mvprintw(5,y-28,"    ");
		mvprintw(9,y-12,"  ");
		mvprintw(10,y-14,"  ");
		mvprintw(11,y-14,"  ");
		mvprintw(12,y-16,"  ");
		mvprintw(12,y-6,"    ");
		mvprintw(13,y-10,"      ");
		mvprintw(14,y-12,"    ");
		mvprintw(14,y-42,"  ");
		mvprintw(15,y-40,"  ");
		attroff(COLOR_PAIR(6));
		attron(COLOR_PAIR(4));
		mvprintw(9,y-34,"  ");
		mvprintw(10,y-38,"      ");
		mvprintw(11,y-34,"    ");
		mvprintw(12,y-32,"    ");
		mvprintw(13,y-32,"  ");
		mvprintw(17,y-30,"  ");
		mvprintw(18,y-28,"  ");
		attroff(COLOR_PAIR(4));
		attron(COLOR_PAIR(3));
		mvprintw(7,y-38,"      ");
		mvprintw(8,y-36,"  ");
		mvprintw(8,y-40,"  ");
		attroff(COLOR_PAIR(3));
	}
	move(0,0);
}
