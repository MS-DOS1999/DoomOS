/************************************/
/*shell by Julien MAGNIN a.k.a MSDOS*/
/************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
	char buffer[150];
	
	//prompt
	printf("Shell prototype/test\n\n Taper \"exit\" pour quitter");
	
	while(1){
		printf("DoomShell > ");
		//entrée std
		fgets(buffer, 150, stdin);
		//on delete le retour chariot
		buffer[strlen(buffer)-1]='\0';
		//exit
		if(strcmp("exit", buffer) == 0){
			exit(0);
		}
		
		//on compte les arguments, execution compris
		int compteur=0;
		int boucle;
		for(boucle=0; boucle<strlen(buffer); ++boucle){
			if(buffer[boucle]==' '){
				++compteur;
			}
		}
		
		//on stock les arguments
		char *arg_list[compteur+2];
		char *p = strdup(buffer);
		char *tmp = strtok(p, " ");
		int increment = 0;
		while(tmp != NULL){
			arg_list[increment]=strdup(tmp);
			increment++;
			tmp = strtok(NULL, " ");
		}
		arg_list[increment] = NULL;
		
		//creation du processus
		pid_t process=fork();
		if(process == 0){
			int retour = execvp(arg_list[0], arg_list);
			if(retour == -1){
				printf("%s\n", strerror(errno));
				exit(0);
			}
		}
		else{
			wait(&process);
		}
		
		//on libère la memoire
		increment = 0;
		while(arg_list[increment] != NULL){
			free(arg_list[increment]);
			increment++;
		}
		free(p);
	}
}

