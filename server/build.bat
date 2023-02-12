g++ -o ./obj/main.o -c ./src/main.cpp
g++ -o ../bin/sockServer.exe ./obj/main.o ./lib/libws2_32.a 
