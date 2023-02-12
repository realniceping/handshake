g++ -o ./client/obj/main.o -c ./client/src/main.cpp
g++ -o ./client/debug/sockClient.exe ./client/obj/main.o ./client/lib/libws2_32.a 
g++ -o ./server/obj/main.o -c ./server/src/main.cpp
g++ -o ./server/debug/sockServer.exe ./server/obj/main.o ./server/lib/libws2_32.a 
