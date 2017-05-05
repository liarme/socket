#include "tcp_net_socket.h"

int main(int argc, char* argv[])
{
	// init_daemon();
	config_file_testing(argv[0]);
	char ip[15],port[5];
	FILE *xp=fopen("server.ini","r");
	if (xp != NULL){
		fseek(xp,0L,SEEK_SET);
		fscanf(xp,"%s %s",ip,port);
		fclose(xp);
	}else {
		printf ("open file error");
		exit(0);
	}
	int sdf = tcp_init(ip, atoi(port));
	while(1)
	{
		int cfd = tcp_accept(sdf);
		char buf[100] = {0};
		char buf_one[100] = {0};
		if (recv(cfd, buf, sizeof(buf), 0) == -1)//从客户端接收数据存于buf中
		{
			perror("recv");
			close(cfd);
			close(sdf);
			exit(-1);
		}
		puts(buf);
		mysql_server(buf);
		if (send(cfd, buf, sizeof(buf), 0) == -1)//从buf中取向cfd客户端发送数据
		{
			perror("send");
			close(cfd);
			close(sdf);
			exit(-1);
		}
		char no[]={"Parameter does not exist"};
		if (send(cfd, no, sizeof(no), 0) == -1)//从buf中取向cfd客户端发送数据
		{
			perror("send");
			close(cfd);
			close(sdf);
			exit(-1);
		}
		close(cfd);
	}
	close(sdf);
	return 0;
}
