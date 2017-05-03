#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>
#include<sys/types.h>
#include<sys/wait.h>
int main ()
{
	int a = 5;
	int b = 2;
	pid_t pid;
	pid = vfork();
	if (pid == 0){
		a = a-4;
		printf ("%d ",a);
		exit(0);
	}else if (pid < 0 ){
		perror("fork");
	}else{
		printf ("%d %d %d",pid,a,b);
	}
	return 0;
}