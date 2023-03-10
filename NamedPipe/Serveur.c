#include "ser_cli_fifo.h"
#include "handlers.h"

// Definition de handlers

void hand_wakeUpClt(int sig)
{

	printf("Bonne réception de la réponse!\n");
	printf("----------------------------------------------- \n");
}

void hand_endServ(int sig)
{

	printf("Fin de tâche! \n");
	exit(2);
}

int f1, f2;
int main()
{
	/*Déclarations */
	struct response rs;
	struct request rq;
	/* Création des tubes nommés */

	if (mkfifo(FILE1, 0666) == -1)
	{
		perror("Error lors de la création du tube 1 !");
	}
	if (mkfifo(FILE2, 0666) == -1)
	{
		perror("Error lors de la création du tube 2 !");
	}

	/*initialisation du générateur de nombres aléatoires*/

	srand(getpid());

	/* Ouverture des tubes nommés */

	f1 = open(FILE1, O_RDONLY);
	f2 = open(FILE2, O_WRONLY);
	if (f1 == -1 || f2 == -1)
	{
		printf(" Ouverture des tubes impossible \n");
		exit(-1);
	};
	/* Installation des Handlers */

	signal(SIGINT, hand_endServ);
	signal(SIGUSR1, hand_wakeUpClt);
	while (1)
	{
		printf("Je suis à l'écout !\n");
		/* lecture d’une question */
		read(f1, &rq, sizeof(struct request));
		close(f1);
		printf("Traitement pour Client qui a pour PID : %d \n", rq.id);
		printf(" Le nombre envoyé est n = %d\n", rq.n);
		/* construction de la réponse */
		int i;
		for (i = 0; i < rq.n; i++)
		{
			rs.t[i] = rand() % 10;
		}
		rs.idc = rq.id;
		rs.ids = getpid();

		/* envoi de la réponse */
		if (write(f2, &rs, sizeof(struct response)) < 0)
		{
			perror("Erreur d'ecriture!");
		};
		close(f2);
		/* envoi du signal SIGUSR1 au client concerné */
		kill(rs.idc, SIGUSR1);

		f1 = open(FILE1, O_RDONLY);
		f2 = open(FILE2, O_WRONLY);
	}
	return 0 ;
}
