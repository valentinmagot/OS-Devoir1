/*------------------------------------------------------------
Fichier: cpr.c

Nom: Valentin Magot
Numero d'etudiant: 8843488

Description: Ce programme contient le code pour la creation
             d'un processus enfant et y attacher un tuyau.
	     L'enfant envoyera des messages par le tuyau
	     qui seront ensuite envoyes a la sortie standard.

Explication du processus zombie
(point 5 de "A completer" dans le devoir):

	(s.v.p. completez cette partie);

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

/* Prototype */
void creerEnfantEtLire(int );

/*-------------------------------------------------------------
Function: main
Arguments: 
	int ac	- nombre d'arguments de la commande
	char **av - tableau de pointeurs aux arguments de commande
Description:
	Extrait le nombre de processus a creer de la ligne de
	commande. Si une erreur a lieu, le processus termine.
	Appel creerEnfantEtLire pour creer un enfant, et lire
	les donnees de l'enfant.
-------------------------------------------------------------*/

int main(int ac, char **av)
{
    int numeroProcessus; 

    if(ac == 2)
    {
       if(sscanf(av[1],"%d",&numeroProcessus) == 1)
       {
           creerEnfantEtLire(numeroProcessus);
       }
       else fprintf(stderr,"Ne peut pas traduire argument\n");
    }
    else fprintf(stderr,"Arguments pas valide\n");
    return(0);
}


/*-------------------------------------------------------------
Function: creerEnfantEtLire
Arguments: 
	int prcNum - le numero de processus
Description:
	Cree l'enfant, en y passant prcNum-1. Utilise prcNum
	comme identificateur de ce processus. Aussi, lit les
	messages du bout de lecture du tuyau et l'envoie a 
	la sortie standard (df 1). Lorsqu'aucune donnee peut
	etre lue du tuyau, termine.
-------------------------------------------------------------*/

void creerEnfantEtLire(int prcNum)
{

		// int pids[prcNum];

		// int i;
		// for(i = prcNum; i >=1 ; --i) {
		// 	int pid = pids[i];
		// 	pid = fork();
		// 	if(pid < 0){ /* error occured */

		// 		fprintf(stderr, "Error occured");
		// 		exit(-1);

		// 	}else if(pid == 0 ){ /*Prcessus enfant*/
		// 		// sleep(5);
		// 		// printf("Processus Termine : %d\n",  i);
		// 		// printf("Had PID %ld\n",(long) getpid());
		// 		printf("Child Processus Termine: %d\n", i);
		// 		exit(0);

		// 	}else if (pid > 0) { /*Processuc parent */
		// 		// printf("Processus Commence : %d\n",  i);
		// 		// printf("Has PID %ld\n",(long) getpid());
		// 		// sleep(5);
		// 		// // wait(NULL);
		// 		// printf("Processus Termine : %d\n",  i);
		// 		// printf("Had PID %ld\n",(long) getpid());
		// 		printf(" Parent Process ");
		// 		printf(" Processus Commence : %d\n", i);
		// 		printf(" Processus Termine : %d\n", i);
		// 		// exit(0); 	
		// 	}

		// }
		int pids[prcNum], pipes[prcNum], i;
		int ret;

		for (int i = prcNum; i > 1; --i)
		{
			ret = pipe(pipes[i]);
			if(ret == - 1) {
				fprintf(stderr, "Error" );
				exit(-1);
			}
			pids[i] = fork();
			if(pids[i] == -1){
				fprintf(stderr, "Error" );
				exit(-1);
			} 
			if(pids[i] == 0) { /*Child fork*/
				close(pipes[i]);
			} else { /*Parent fork*/
				printf("Processus Commence: %d\n", i);
				close(pipes[i]);
				sleep(5);
				printf("Processus Termine %d\n", i);

			}
		}
		


		

    /* S.V.P. completez cette fonction selon les
       instructions du devoirs. */
}
