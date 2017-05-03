#include "tcp_net_socket.h"
//线程函数
void thread_1(void)  
{  
	time_t timep;  
    char s[30];  
    time(&timep);  
    strcpy(s,ctime(&timep));
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
	send(sdf, s, strlen(s), 0);
	recv(sdf, buf, sizeof(buf), 0);
	printf("%s\n",buf);
	close(sdf);
} 
//主函数
int main (int argc, char *argv[])
{
	config_file_testing(argv[0]);
	pthread_t id;
	int i,ret;
	for (i=0;i<2;i++){
		ret = pthread_create(&id,NULL,(void  *) thread_1,NULL);
		if (ret != 0){
			printf("Create pthread error!\n");  
			return -1;
		}
		pthread_join(id,NULL);
		sleep(1);
	}
return 0;
}