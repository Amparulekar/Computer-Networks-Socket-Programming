// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <string>
#include <iostream>

using namespace std;

#define MAXLINE 1024 
    
// Driver code 
int main(int argc, char* argv[]) { 

    int RECEIVER_PORT = atoi(argv[1]);//stoi a pointer
    int SENDER_PORT = atoi(argv[2]);
    float PACKET_DROP_PROBABILITY = atof(argv[3]);

    int sockfd; 
    char packet[MAXLINE]; 
    // char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
    int x;
    int counter = 1;
    float random_variable;
        
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(RECEIVER_PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 


    while(1)
    {

        unsigned int len, n;
        len = sizeof(cliaddr);  //len is value/result 

        // if (n = recvfrom(sockfd, (char *)packet, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len)<0) 
        if (n = recvfrom(sockfd, (char *)packet, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len)<0) 
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        packet[n] = '\0'; 
        
        cout<<"Received";

        x = atoi(packet+7);//is this correct
        // printf(packet[20]);
        if( x == counter)
        {
            random_variable = rand()/RAND_MAX;
            if(random_variable > PACKET_DROP_PROBABILITY)
            {
                counter ++;
                // ack = "Acknowledgement:" + to_string(x);
                char ack[]="Acknowledgement:00000";
                sprintf(ack+16, "%d", x);
                // std::cout<<ack;
                // char ack_arr[ack.length()+1];
                // strcpy(ack_arr,ack.c_str());
                sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
            }
            else
            {
                cout<<"Packet dropped";
            }
        }
        else
        {
            // ack = "Acknowledgement:" + to_string(counter);
            char ack[]="Acknowledgement:00000";
            sprintf(ack+16, "%d", counter);
            // cout<<ack;
            // char ack_arr[ack.length()+1];
            // strcpy(ack_arr,ack.c_str());
            sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
        }

    }
    return 0; 
}