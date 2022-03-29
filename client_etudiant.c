#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define ERROR -1

int main(int argc, char* argv[])
{
     int num_socket; //, num_connect, num_send, num_recv;
     struct sockaddr_in serveur;
      struct sockaddr_in client;
     int port=50001;
     char IP[16]="192.168.141.34";                     // @ Ip du serveur
     char requette[]="GET / HTTP/1.1\r\nHost: 192.168.141.34\r\n\r\n";                // Requette HTTP
     char reponse[1000];                         // Buffer pour la reception
    
    // Creation de la socket SOCK_STREAM
    num_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check socket validity
    if (ERROR == num_socket)
    {
        // Print error
        perror("ERROR SOCKET");
    }
    else
    {
        printf("Socket create \n\r");
        
        // client init
        client.sin_family      = AF_INET;
        client.sin_port        = htons(50000);
        client.sin_addr.s_addr = inet_addr("192.168.141.34");
        
        // Association de la socket à un port source et addresse IP source
        if (ERROR == bind(num_socket, (struct sockaddr*) &client, sizeof(struct sockaddr)))
        {
            // Print error
            perror("ERROR BIND");
        }
        else
        {
            printf("Bind OK \n\r");
            
            // serveur init
            serveur.sin_family      = AF_INET;
            serveur.sin_port        = htons(port);
            serveur.sin_addr.s_addr = inet_addr(IP);
            
            // Association de la socket à un port source et addresse IP dest
            if (ERROR == connect(num_socket, (struct sockaddr*)  &serveur, sizeof(struct sockaddr)))
            {
                // Print error
                perror("ERROR CONNECT");
            }
            else
            {
                printf("connect OK \n\r");
                /*****************  Requette : send() ****************************/
                if(ERROR == send(num_socket, &requette, strlen(requette), 0))
                {
                    // Print error
                    perror("ERROR SEND");
                }
                else
                {
                    printf("send OK \n\r");
                    /*****************  Réponse : rcv () ****************************/
                    if (ERROR == recv(num_socket, &reponse, strlen(reponse), 0))
                    {
                        // Print error
                        perror("RECV SOCKET");                    
                    }
                    else
                    {
                        printf("RCV OK \n\r");
                        printf("%s", reponse);
                        
                        /*****************  Fermeture socket : close() ******************/
                        close(num_socket);
                    }
                }
            }
        }
    }
    return 0;    
}
