#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h> 

using namespace std;
#define MAXLINE 1024 


int main(int argc, char const* argv[])
{
    printf("hi1");
    int sockfd; 
    char ackno[MAXLINE]; 
    int RECEIVER_PORT = atoi(argv[2]);
    int SENDER_PORT = atoi(argv[1]);
    float RETRANSMISSION_TIMER = stof(argv[3]);
    int NO_OF_PACKETS = atoi(argv[4]);
    int n, valrea;
    int valread, client_fd;
    struct sockaddr_in servaddr; 
    string pack;
    int y=1;
    int num = NO_OF_PACKETS;
    float random_variable;
    string ack;
    printf("hi2");   
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(SENDER_PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        printf("hi3");   

    struct timeval timeout;      
    timeout.tv_sec = RETRANSMISSION_TIMER;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof timeout);
    
    while(num>0)
    {

        unsigned int len;
        int n0; 

        // pack= "Packet:"+ to_string(y);
        char pack[]="Packet:000000";
		sprintf(pack+7, "%d", y);
        sendto(sockfd, (const char *)pack, strlen(pack), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
        cout<<"Packet sent "<<y;

        n0 = recvfrom(sockfd, ackno, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        if (n0==-1)
            {
                continue;
            }
        else
            {
            ackno[n0] = '\0'; 
                
            if (atoi(ackno+16)==y)
            {
                y=y+1;
                num=num-1;
                cout<<pack;        
                cout<<"Ack Received";            
            }
         }

    }   
 }




    
    
    

    
 
    
 
    


    

