jugar:	main.o ataque.o Fire.o water.o Thunder.o move.o pokemon.o
	g++ main.o ataque.o Fire.o water.o Thunder.o move.o pokemon.o -lncurses -o jugar
main.o: main.cpp ataque.h Fire.h water.h Thunder.h move.h pokemon.h
	g++ -c main.cpp
ataque.o: ataque.h ataque.cpp move.h
	g++ -c ataque.cpp
Fire.o: Fire.h Fire.cpp move.h pokemon.h
	g++ -c Fire.cpp
Thunder.o: Thunder.h Thunder.cpp move.h pokemon.h
	g++ -c Thunder.cpp
water.o: water.h water.cpp move.h pokemon.h
	g++ -c water.cpp
move.o: move.h move.cpp
	g++ -c move.cpp
pokemon.o: pokemon.cpp pokemon.h move.h
	g++ -c pokemon.cpp