#include "tcp_net_socket.h"
int tcp_init(const char* ip,int port)//用于初始化操作
{
	int sdf = socket(AF_INET, SOCK_STREAM, 0);
	if (sdf == 1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = inet_addr(ip);//或INADDR_ANY
	//将新的socket与定制的ip,port绑定
	if(bind(sdf, (struct sockaddr*)&serveraddr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		close(sdf);
		exit(-1);
	}
	if(listen(sdf, 10) == -1)
	{
		perror("listen");
		close(sdf);
		exit (-1);
	}
	return sdf;
}
int tcp_accept(int sdf)//用于服务端的接收
{
	struct sockaddr_in clientaddr;
	memset(&clientaddr, 0, sizeof(struct sockaddr));
	int addrlen = sizeof (struct sockaddr);
	int new_fd = accept(sdf, (struct sockaddr*)&clientaddr, &addrlen);
	//sdf接受客户端的连接，并创建新的socket伪new_fd，将请求的客户端IP、port保存在结构体clientaddr中
	if (new_fd == -1)
	{
		perror("accept");
		close(sdf);
		exit(-1);
	}
	printf ("%s %d success connect...\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	return new_fd;
}
int tcp_connect(const char* ip, int port)//用于客户端的连接
{
	int sdf = socket(AF_INET, SOCK_STREAM, 0);
	if(sdf == -1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	//将sdf连接至指定的服务器网络地址serveraddr
	if(connect(sdf,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr)) == -1)
	{
		perror("connect");
		close(sdf);
		exit(-1);
	}
	return sdf;
}
void signalhandler(void)//用于信号处理，让服务端在按下ctrl+c或Ctrl+\时不会推出
{
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGINT);
	sigaddset(&sigSet,SIGQUIT);
	sigprocmask(SIG_BLOCK,&sigSet,NULL);
}
void config_file_testing (char *program_filename)//用于程序检测配置文件 服务端server.ini 客户端cliten.ini
{
	if (!strcmp(program_filename,"./client")){
		char filename[] = "client.ini";
		if (access(filename,F_OK)==-1)
		{
			if(creat(filename,0755)<0){
				printf("create file %s failure!\n",filename);
			}else{
				write_config_file(filename);
				printf("create file %s success!\n",filename);
			}
		}
	}else if(!strcmp(program_filename,"./server")){
		char filename[] = "server.ini";
		if (access(filename,F_OK)==-1)
		{
			if(creat(filename,0755)<0){
				printf("create file %s failure!\n",filename);
			}else{
				write_config_file(filename);
				printf("create file %s success!\n",filename);
			}
		}
	}else{
		printf ("程序必须名为server或client,并且用 ./ 运行\n");
		exit(0);
	}
}
void write_config_file (char *role)//用于新建配置文件后写入配置信息
{
	char ip[] = "139.129.31.144";
	char port[] = "8888";
	FILE *xp = fopen (role,"r+");
	if (xp != NULL){
		fprintf(xp,"%s %s",ip,port);
		fclose(xp);
	}else 
		printf ("open flie error");
}