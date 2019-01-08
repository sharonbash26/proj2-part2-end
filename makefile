compile: server client
	echo done

run_server:
	./serv.out

run_client:
	./client.out localhost 8000


server:
	g++ -std=c++14 -pthread serv/*.cpp serv/alg/*.cpp -o serv.out

client:
	g++ -std=c++14 client/client_main.cpp -o client.out
