#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>



char* randomSaying()
{
    srand(time(0)); //time as seed
    int num = (rand() % //numbers between 0 and 9 
    (9 - 0 + 1)) + 0;
    
    switch(num){
        case 0:
            return "Dikensiz gül olmaz\n";
            break;
        case 1:
            return "Damlaya damlaya göl olur\n";
            break;
        case 2:
            return "Denize düşen yılana sarılır\n";
            break;

        case 3:
            return "Besle kargayı oysun gözünü\n";
            break;

        case 4:
            return "Laf ile peynir gemisi yürümez\n";
            break;

        case 5:
            return "Ne ekersen onu biçersin\n";
            break;

        case 6:
            return "Öfkeyle kalkan zararla oturur\n";
            break;

        case 7:
            return "İyilik eden iyilik bulur\n";
            break;

        case 8:
            return "Huylu huyundan vazgeçmez\n";
            break;

        case 9:
            return "Gün doğmadan neler doğar\n";
            break;

    }

}




int main(int argc, char *argv[]) {


    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in simpleServer;

    if (2 != argc) {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);

    }

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
	    fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for listening */
    simplePort = atoi(argv[1]);

    /* setup the address structure */
    /* use INADDR_ANY to bind to all local addresses  */
    bzero(&simpleServer, sizeof(simpleServer)); 
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
	    fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
	close(simpleSocket);
	exit(1);
    }

    /* lets listen on the socket for connections      */
    returnStatus = listen(simpleSocket, 5);

    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
	close(simpleSocket);
        exit(1);
    }

    while (1)

    {

        struct sockaddr_in clientName = { 0 };
	int simpleChildSocket = 0;
	int clientNameLength = sizeof(clientName);

	/* wait here */

        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

	if (simpleChildSocket == -1) {

            fprintf(stderr, "Cannot accept connections!\n");
	    close(simpleSocket);
	    exit(1);

	}

        /* handle the new connection request  */
	/* write out our message to the client */
    char* msg = randomSaying(); //random saying
	write(simpleChildSocket, msg, strlen(msg));
        close(simpleChildSocket);

    }

    close(simpleSocket);
    return 0;

}