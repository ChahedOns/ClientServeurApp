#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FILE1 "fifo1"
#define FILE2 "fifo2"
#define NMAX 10

// Structs
struct request
{
	int id;
	int n;
};
struct response
{
	int idc;
	int ids;
	int t[NMAX];
};
