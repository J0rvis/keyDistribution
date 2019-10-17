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

 int socketA = socket(AF_INET, SOCK_STREAM, 0);

 // error check
 if(socketA < 0) {
    cout << "\nERROR: oppening socket \n";
    exit(1);
 } else {
    cout << "\nOppening Socket: \n";
 }
 
 while (true){
   //accept sockets 
    listen(socketA, 5);

    int socketNode;
    struct sockaddr_in cli_addr;

    socklen_t client = sizeof(cli_addr);

    socketNode = accept(socketA, (struct sockaddr *) &cli_addr, &client);

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
 }

 sleep(3);
 cout << " Closing Server ... ...\n\n";
 close(socketA); 
 return 0;

}
