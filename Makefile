PORTNO=50000
LIB=`pkg-config --libs --cflags gtk+-2.0`
daemon : daem_ser.c second.c
	gcc daem_ser.c second.c -o daemon
	./daemon $(PORTNO)
client : client.c
	gcc -o client client.c $(LIB)
	./client
#REMEMBER TO CHANGE THE WORKING DIRECTORY FO DAEMON
	
	
