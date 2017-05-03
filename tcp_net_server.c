#include "tcp_net_socket.h"
char mdfive (char md[5]);
int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf ("usage:./servertcp ip port");
		exit(-1);
	}
	//signalhandler();
	int sdf = tcp_init(argv[1], atoi(argv[2]));
	while(1)
	{
		int cfd = tcp_accept(sdf);
		char buf[100] = {0};
		char buf_one[250] = {0};
		if (recv(cfd, buf, sizeof(buf), 0) == -1)//从客户端接收数据存于buf中
		{
			perror("recv");
			close(cfd);
			close(sdf);
			exit(-1);
		}
		puts(buf);
		mdfive(buf);
		FILE *xp=fopen("ps_server.ini","r");
		fseek(xp,0L,SEEK_SET);
		fscanf(xp,"%[^EOF]%*c",&buf_one);
		fclose(xp);
		//system("rm -rf ps_server.ini");
		int x=0;
		int i;
		for (i=0;i<40;i++)
		{
			x=buf_one[i]+x;
		}
		if (x){
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
char mdfive (char md[20])
{
	char chars[40];
	sprintf(chars,"sh ps_server.sh %s",md);
	system(chars);
	return 0;
}
