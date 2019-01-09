compile: server client
	echo done

.PHONY: run_server run_client server client

run_server:
	./serv.out

run_client:
	./client.out localhost 8000

server:
	find server_side -name "*.cpp" > serv.txt
	find lib -name "*.cpp" > lib.txt
	g++ -std=c++14 -pthread @serv.txt @lib.txt -o serv.out
	rm lib.txt
	rm serv.txt

client:
	g++ client/client_main.cpp -o client.out
