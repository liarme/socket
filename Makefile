client: tcp_net_client.o tcp_net_socket.o
	gcc -o client tcp_net_client.o tcp_net_socket.o

tcp_net_cliten.o: tcp_net_client.c
	gcc -c tcp_net_client.c

tcp_net_socket.o: tcp_net_socket.c
	gcc -c tcp_net_socket.c

clean:
