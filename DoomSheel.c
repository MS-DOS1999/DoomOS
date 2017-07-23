/************************************/
/*shell by Julien MAGNIN a.k.a MSDOS*/
/************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	char buffer[150];
	
	printf("Shell prototype/test\n\n Taper \"exit\" pour quitter");
	
	while(1){
		printf("Prompt: ");
		fgets(buffer, 150, stdin);
		buffer[strlen(buffer)-1]='\0';
		if(strcmp("exit", buffer) == 0){
			exit(0);
		}
		printf("%s\n", buffer);
		system(buffer);
	}
}

