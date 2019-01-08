compile: server client
	echo done

run_server:
	./serv.out

run_client:
	./client.out localhost 8000


server:
	g++ -pthread serv/*.cpp serv/alg/*.cpp -o serv.out

client:
	g++ client/client_main.cpp -o client.out