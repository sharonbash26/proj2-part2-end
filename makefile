compile: server client
	echo done

run_server:
	./serv.out

run_client:
	./client.out localhost 8000

lib:
	find lib -name "*.cpp" > lib.txt
	g++ -std=c++14 -pthread lib.txt -c -o lib.o
	rm lib.txt
	
server: lib
	find server_side -name "*.cpp" > serv.txt
	g++ -std=c++14 -pthread @sources.txt lib.o -o serv.out

client:
	g++ client/client_main.cpp -o client.out