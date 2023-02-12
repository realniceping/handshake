g++ -o ./obj/main.o -c ./src/main.cpp
g++ -o ./debug/sockServer.exe ./obj/main.o ./lib/libws2_32.a 
