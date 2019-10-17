#include<iostream>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
using namespace std;

// This will be Alice
// Alice is a server 
int main(int argc, char *argv[]){
 // struct sockAddress_in address;
 // error check 
 if(sizeof(&argv) == 0) {
    cout << "\nPlease enter parameters [HOSTADDRESS]\n";
    exit(0);
 }

 cout << "\nPlease enter string to be sent using tcp: \n";

 string message;
 cin >> message; 
 cout << "\nThis was the strings entered: " << message << "\n"; 
 cout << "\nThis is the hostIP entered: " << argv[1] << "\n";
 cout << "\nThis is the portNumber entered: " << argv[2] << "\n";

   // char *host = argv[1];
   int portNumber = atoi(argv[2]);
   int socketA = socket(AF_INET, SOCK_STREAM, 0);

 // error check
   if(socketA < 0) {
    cout << "\nERROR: oppening socket \n";
    exit(1);
   } else {
    cout << "\nOppening Socket: \n";
   }
 
   struct sockaddr_in serv_addr;
   memset(&serv_addr, '0', sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;

   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   serv_addr.sin_port = htons(portNumber);

   /* Bind the socket to the given port*/
   if (bind(socketA, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    cout << "error on binding";
    exit(1);
   }

    int is = 1;
	  setsockopt(socketA,SOL_SOCKET,SO_REUSEADDR,&is,sizeof(int)); 

    //end setup 

   //accept sockets 
    cout << "Still opening socket";
    int listenResult = listen(socketA, 5);
    cout << "Listened for socket: " << listenResult << "\n";
    int socketNode;
    struct sockaddr_in cli_addr;

    socklen_t client = sizeof(cli_addr);

    cout << "waiting for that call";
    socketNode = accept(socketA, (struct sockaddr *) &cli_addr, &client);
    cout << "accepted \n";

    if(socketNode < 0){
      cout << "Error on accept \n";
      exit(1);
    } else {
      cout << "Request Accepted. \n";
      cout << "Writing to socket : " << message << "\n";
      int n = write(socketNode, &message,sizeof(message));

         if (n < 0) {
            printf("ERROR writing to socket\n");
            exit(0);
         }

      return socketNode;
    }

 sleep(3);
 cout << " Closing Server ... ...\n\n";
 close(socketA); 

 return 0;

}
