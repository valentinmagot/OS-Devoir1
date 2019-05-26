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
#include <sys/types.h> 
#include <string.h> 
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

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

		char write_msg[BUFFER_SIZE] = "commence"; 
		char read_msg[BUFFER_SIZE]; 
		pid_t pid; 
		int fd[2];

		/* create the pipe */
	if (pipe(fd)  == -1)  { 
	fprintf(stderr,"Pipe failed") ; 
	exit(-1); 
	} 
	/* now fork a child process */
	pid = fork() ; 
	if (pid < 0)  { 
		fprintf(stderr, "Fork failed") ; 	
		exit(-1);
	} 
	if (pid >  0)  {   /* parent process */
		/* close the unused end of the pipe */
		close(fd[READ_END]) ; 
		/* write to the pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg) +1) ;  
		/* close the write end of the pipe */
		close(fd[WRITE_END]) ; 
	} 
	else {  /* child process */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]) ;
		printf("Processus commence :  %d\n", 1) ;  
		/* read from the pipe */
		read(fd[READ_END], read_msg, BUFFER_SIZE) ; 
		printf("child read ; Processus 2 :  %s\n",read_msg) ; 
		/* close the write end of the pipe */
		close(fd[READ_END]) ; 
	} 

		

    /* S.V.P. completez cette fonction selon les
       instructions du devoirs. */
}
