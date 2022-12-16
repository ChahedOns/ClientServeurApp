#include "ser_cli.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int j;
// Function designed for chat between client and server.
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
void func(int connfd)
{
    struct request rq;
    struct response rs;
    srand(getpid());
	// read the message from client and copy it in buffer
		read(connfd,&rq,sizeof(struct request));
		// print buffer which contains the client contents
		printf("\t Un  client a envoyé un msg  \n ");
		for (int i = 0; i < rq.n; i++)
		{
			rs.t[i] = rand() % 10;
		}
		rs.idc = rq.id;
		rs.ids = getpid();
		// and send that buffer to client
       
		write(connfd,&rs, sizeof(struct response));
        printf("\t Réponse envoyée ! \n");

	
}

// Driver function
int main()
{

	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Creation de socket a échouée...\n");
		exit(0);
	}
	else{
		printf("Socket serveur crée avec succées..\n");
		}
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Erreur lors d'effectuée la liaison...\n");
		exit(0);
	}
	else
	{
		printf("Liaison effectuée avec succés..\n");
	}
	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Erreur lors l'ecout...\n");
		exit(0);
	}
	
	printf("Server en écoute..\n");
	len = sizeof(cli);
	// Accept the data packet from client and verification.
    while (1)
	{
    signal(SIGINT, hand_endServ);
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
		printf("Acceptation du client éronée!...\n");
		exit(0);
	}
	else
	{
        j++;
        int p1= fork();
        if (p1 <0 ){
            perror("Erreur lors de creation du fils!");
        }
		else if (p1 > 0 )
		{
		printf("Client accepté...\n");
        signal(SIGINT, hand_endServ);
	    signal(SIGUSR1, hand_wakeUpClt);
        // Function for chatting between client and server
	    func(connfd);
        printf("--------------------------------------------------\n");
        }
		else
		{
            printf("\n");
        }
    }   
	}
	close(sockfd);
		
}
