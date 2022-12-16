
all: clientSK serveurSK clientNP serveurNP mygtkapp
clientSK : Sockets/client.c
		gcc -o clientSK.o -c Sockets/client.c 
		gcc -o clientSK clientSK.o
serveurSK : Sockets/serveur.c
		gcc -o serveurSk.o -c Sockets/serveur.c 
		gcc -o serveurSK serveurSK.o

clientNP : NamedPipe/client.c
		gcc -o clientNP.o -c NamedPipe/client.c 
		gcc -o clientNP clientNP.o

serveurNP : NamedPipe/Serveur.c
		gcc -o serveurNP.o -c NamedPipe/Serveur.c 
		gcc -o serveurNP serveurNP.o

clean : clientSK.o serveurSK.o clientNP.o serveurNP.o
		rm *.o
		rm clientSK
		rm serveurSK
		rm clientNP
		rm serveurNP
		rm app
		
mygtkapp: interfaceapp.c
		gcc -o App interfaceapp.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic
