#include <stdio.h>
#include <stdlib.h>
void main (){
	printf("1");
	printf ("2");
	char *ip,*port;
	FILE *xp=fopen("cliten.ini","r");
	// if (xp != NULL){
		fseek(xp,0L,SEEK_SET);
		fscanf(xp,"%[^\n]",ip);
		// fseek(xp,0L,SEEK_SET);
		// fscanf(xp,"%[^\n]",port);
		// fclose(xp);
		printf ("3");
	// }else {
		// printf ("open file error");
		fclose(xp);
	// }
	printf ("4");
	printf ("%s\n",ip);
	// printf ("%s\n",port);
}