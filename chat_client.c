#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
  /* code */
  int sockfd;
    char buffer[MAXLINE];
    char hello[MAXLINE];
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;
    int ch;
    char dummy;
    printf("Enter 1 to send a message to the server\nEnter 2 to stay in the application\nEnter 3 to quit: \n");
    scanf("%d", &ch);
    while(ch==1||ch==2){
      if(ch==1){
        scanf("%c",&dummy);
        memset(&buffer,0,sizeof(buffer));
        memset(&hello,0,sizeof(hello));
        printf("Enter the message you wanna send to the server:\n" );
        scanf("%[^\n]",hello);
        sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        printf("Message sent.\n");
      }
      if(ch==2){
        char chumma[]="2";
        sendto(sockfd,(const char *)chumma,strlen(chumma),MSG_CONFIRM,(const struct sockaddr *) &servaddr,len);
      }
      n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
      buffer[n] = '\0';
      if(strcmp(buffer,"2")){
          printf("Server : %s\n", buffer);
      }

      printf("Enter 1 to send a message to the server\nEnter 2 to stay in the application\nEnter 3 to quit: \n");
      scanf("%d", &ch);
    }
    close(sockfd);
  return 0;
}
