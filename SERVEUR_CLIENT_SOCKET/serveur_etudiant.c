#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <string.h>

#define PORT_SERVEUR 		50001		// port d'écoute du serveur
#define IP_SERVEUR		    "192.168.141.34"	//@IP serveur web
#define ERROR -1

int main(int argc, char* argv[])
{
	 int num_socket, num_accept; //num_bind, num_listen;
	 unsigned int size;
	// struct sockaddr_in client;
	 struct sockaddr_in serveur;
	 char requette;
	 char reponse0[]="Nous avons recu votre requete numero 0";
	 char reponse1[]="Nous avons recu votre requete numero 1";
	 size=sizeof(struct sockaddr_in);
	 
	 /******* Creation de la socket SOCK_STREAM : socket() ***************/
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
			
		/******* Association entre l'adresse IP et le port d'écoute : bind() ***/
		serveur.sin_family      = AF_INET;
		serveur.sin_port        = htons(PORT_SERVEUR);
		serveur.sin_addr.s_addr = inet_addr(IP_SERVEUR);

		// Association de la socket à un port source et addresse IP source
		if (ERROR == bind(num_socket, (struct sockaddr*) &serveur, sizeof(struct sockaddr)))
		{
			// Print error
			perror("ERROR BIND");
		}
		else 
		{
			printf("Bind OK \n\r");
			/******* Configuration des demandes de connexions : listen () ***/
			if (ERROR == listen(num_socket, 1))
			{
				// Print error
				perror("ERROR LISTEN");
			}
			else 
			{
				printf("LISTEN OK \n\r");

				while(1)
				{
					/******* Attente de nouvelle connexions : accept ()  **************/
					num_accept = accept(num_socket, NULL, NULL);
					if (ERROR == num_accept)
					{
						// Print error
						perror("ERROR ACCEPT");
					}
					else 
					{
						/*****************  Réception de la requette : recv() **************/
						if (ERROR == recv(num_accept, &requette, 1, 0))
						{
							// Print error
							perror("RECV SOCKET");					
						}
						else 
						{
							printf("RCV OK \n\r");
							if ('0' == requette)
							{
								printf("REQUEST 0\n\r");
								if(ERROR == send(num_accept, reponse0, strlen(reponse0)+1, 0))
								{
									// Print error
									perror("ERROR SEND");
								}
								else 
								{
									printf("RESPONSE 0 OK\n\r");
								}
							}
							else if ('1' == requette)
							{
								printf("REQUEST 1\n\r");
								if(ERROR == send(num_accept, reponse1, strlen(reponse1)+1, 0))
								{
									// Print error
									perror("ERROR SEND");
								}
								else 
								{
									printf("RESPONSE 1 OK\n\r");
								}							
							}
							else 
							{
								printf("WRONG REQUEST\n\r");
							}		
						
							/*********  Fermeture connexion avec le client : close() ***********/
							close(num_accept);
						}
					}
				}
			}
		}
	}
				
	/*****************  Fermeture socket : close() ******************/
	close(num_socket);
	return 0;
}
