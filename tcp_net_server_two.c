#include "tcp_net_socket.h"
void init_daemon(void);//守护进程初始化函数
int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf ("usage:./servertcp ip port\n");
		exit(-1);
	}
	// init_daemon();
	int sdf = tcp_init(argv[1], atoi(argv[2]));
	while(1)
	{
		int cfd = tcp_accept(sdf);
		char buf[100] = {0};
		char buf_one[] = {0};
		if (recv(cfd, buf, sizeof(buf), 0) == -1)//从客户端接收数据存于buf中
		{
			perror("recv");
			close(cfd);
			close(sdf);
			exit(-1);
		}
		puts(buf);
		FILE *xp=fopen("server.ini","a+");
		// fprintf(xp,"%s",buf);
		fseek(xp,0L,SEEK_SET);
		fscanf(xp,"%[^EOF]",&buf_one);
		puts(buf_one);
		fclose(xp);
		if (1){
			if (send(cfd, buf_one, sizeof(buf_one), 0) == -1)//从buf中取向cfd客户端发送数据
			{
				perror("send");
				close(cfd);
				close(sdf);
				exit(-1);
			}
		}
		else{
			char no[]={"Parameter does not exist"};
			if (send(cfd, no, sizeof(no), 0) == -1)//从buf中取向cfd客户端发送数据
			{
				perror("send");
				close(cfd);
				close(sdf);
				exit(-1);
			}
		}
		close(cfd);
	}
	close(sdf);
	return 0;
}