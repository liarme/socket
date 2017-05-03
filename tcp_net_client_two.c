#include "tcp_net_socket.h"

int main (int argc, char *argv[])
{
	config_file_testing(argv[0]);
	char ip[15],port[5];
	FILE *xp=fopen("cliten.ini","r");
	if (xp != NULL){
		fseek(xp,0L,SEEK_SET);
		fscanf(xp,"%s %s",ip,port);
		fclose(xp);
	}else {
		printf ("open file error");
		exit(0);
	}
	char buf[100]={0};
    int sdf = tcp_connect(ip,atoi(port));
	send(sdf, "1", strlen("1"), 0);
	recv(sdf, buf, sizeof(buf), 0);
	printf("%s\n",buf);
	close(sdf);
return 0;
}