#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024
#define PORT 8080

int main(){
    int sockfd;
    char buffer[MAXLINE];
    char hello[MAXLINE];

    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    sockfd= socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0 ) {
        perror("socket creation failed");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind failed");
    }

    int len, n;
    char dummy;
    len = sizeof(cliaddr);  //len is value/resuslt
    int ch=1;
    printf("Enter 1 to send a message to the client\nEnter 2 to stay in the application\nEnter 3 to quit: ");
    scanf("%d",&ch);
    while (ch==1||ch==2) {
      n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
      buffer[n] = '\0';
      printf("Client : %s\n", buffer);
      if(ch==1){
        scanf("%c",&dummy);
        memset(&buffer,0,sizeof(buffer));
        memset(&hello,0,sizeof(hello));
        printf("Enter the message you wanna send to the client:\n" );
        scanf("%[^\n]",hello);
        sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
        printf("Message sent.\n");
      }
      if(ch==2){
        char chumma[]="2";
        sendto(sockfd,(const char *)chumma,strlen(chumma),MSG_CONFIRM,(const struct sockaddr *) &cliaddr,len);
      }
      if(strcmp(buffer,"2")){
          printf("Client : %s\n", buffer);
      }
      printf("Enter 1 to send a message to the client\nEnter 2 to stay in the application\nEnter 3 to quit: ");
      scanf("%d",&ch);
    }


    return 0;
}
