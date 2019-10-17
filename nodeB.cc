#include<iostream>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
using namespace std;

// This will be Bob
// Bob is a client
int main(int argc, char *argv[]){

 // error check
 if(sizeof(&argv) == 0) {
    cout << "\nPlease enter parameters [HOSTADDRESS] [PORT NUMBER]\n";
    exit(0);
 }

 cout << "\nThis is the hostIP entered: " << argv[1] << "\n";
 cout << "\nThis is the portNumber entered: " << argv[2] << "\n";

 char *host = argv[1];
 int portNumber = atoi(argv[2]);	
 // call server 
 int socketNode = socket(AF_INET, SOCK_STREAM, 0);

 if(socketNode < 0 ){
    cout << "ERROR: Cannot open socket.";
    exit(0);
 }

 struct sockaddr_in serv_addr;

 memset(&serv_addr, '0', sizeof(serv_addr));

 serv_addr.sin_family = AF_INET;

 serv_addr.sin_port = htons(portNumber);

 struct hostent *server; 

 server = gethostbyname(host);


 if(server == NULL){
    cout << "ERROR: No such host.\n";
    exit(0);
 }

 memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  /* Connect to the server*/
 int socketA = connect(socketNode,(struct sockaddr *) &serv_addr, sizeof(serv_addr));
 if (socketA < 0) {
    cout << "error connecting: exiting \n";
    exit(0);
 }
 // read what is sent    

 int x;
 int n = read(socketA,&x,sizeof(char *));

 if (n < 0) {
  cout << "Unable to Read message";
  exit(0);
 }

 close(socketNode);
 return socketNode;

}
