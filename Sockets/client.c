#include "ser_cli.h"
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
void hand_wakeUpClt(int sig)
{
	printf("Client réveillé !");
	printf("\n");
}
void hand_endClient(int sig)
{

	printf("Fin de tâche! \n");
	exit(2);
}
void func(int sockfd)
{
    struct response rs;
    struct request rq;
    srand(getpid());
	int x;
	printf(" ----- Lancement du client avec PID : %d ----- \n", getpid());
    /* Construction et envoi d’une question */
	x = rand() % 10;
	// Construcction de la question
	rq.id = getpid();
	rq.n = x;
	// envoi
	write(sockfd, &rq, sizeof(struct request));
    printf("Envoi avec succées du nombre n = %d ",rq.n);
	/* Lecture de la réponse */	
	read(sockfd, &rs, sizeof(struct response));
	/* Envoi du signal SIGUSR1 au serveur */
	/* Traitement local de la réponse */
	printf("\n La réponse du serveur est : ");
	int i;
	for (i = 0; i < x; i++)
	{
		printf("%d ", rs.t[i]);
	}
	printf("\n");
	
}

int main()
{

	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

    signal(SIGUSR1, hand_wakeUpClt);

	// function for chat
    
	func(sockfd);

	// close the socket
	close(sockfd);
}
