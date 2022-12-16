#include "ser_cli_fifo.h"
#include "handlers.h"

struct request rq;
struct response rs;
int f1, f2;
void hand_wakeUpClt(int sig)
{
	printf("Client réveillé !");
	printf("\n");
}

int main()
{
	/* Déclarations */

	int x;
	printf(" ----- Lancement du client avec PID : %d ----- \n", getpid());
	f1 = open(FILE1, O_WRONLY);
	f2 = open(FILE2, O_RDONLY);
	if (f1 == -1 || f2 == -1)
	{
		printf(" Ouverture des tubes impossible ");
		exit(-1);
	};
	srand(getpid());
	/* Installation des Handlers */
	signal(SIGUSR1, hand_wakeUpClt);

	/* Construction et envoi d’une question */
	x = rand() % 10;
	// Construcction de la question
	rq.id = getpid();
	rq.n = x;
	// envoi
	write(f1, &rq, sizeof(struct request));
	close(f1);
	/* Attente de la réponse */
	pause();
	/* Lecture de la réponse */
	read(f2, &rs, sizeof(struct response));
	close(f2);
	printf("Je suis le client avec un PID = %d \n", rs.idc);
	/* Envoi du signal SIGUSR1 au serveur */
	kill(rs.ids, SIGUSR1);
	/* Traitement local de la réponse */
	printf("La réponse du serveur est : ");
	int i;
	for (i = 0; i < x; i++)
	{
		printf("%d ", rs.t[i]);
	}
	printf("\n");
	return 0;
}
