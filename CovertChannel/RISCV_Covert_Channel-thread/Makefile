all:
	gcc -DC910 -march=rv64gc sender.c -o sender -static -pthread -lpthread
	gcc -DC910 -march=rv64gc receiver.c -o receiver -static -pthread -lpthread

clean:
	rm -f sender
	rm -f receiver
