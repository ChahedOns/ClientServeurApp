#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <unistd.h> 
#include <sys/wait.h>// read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

struct response{
    int idc;
	int ids;
	int t[MAX];
};
struct request{
    int id;
	int n;
};