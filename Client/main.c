//
//  main.c
//  Client
//
//  Created by Linh Dang on 11/11/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT "5500"
#define BUF_SIZE 1501
#define BACKLOG 10
void str_process(int new_fd){
        n = send(new_fd, buf, strlen(buf),0);
    if (n < 0)
        perror("ERROR writing to socket");
    printf("client send %d bytes: %s \n",(int) n, buf);
    
    bzero(buf, BUF_SIZE);
    printf("--");
    n = recv(new_fd, buf, BUF_SIZE,0);
    if (n < 0)
        perror("ERROR reading from socket");
    printf("Echo from server: %s \n", buf);
    printf("client received %d bytes from server \n",(int) n);
    
}
int main(int argc, const char * argv[]) {
    // socket connect [write read] read close
    int sockfd = -1;
    struct addrinfo hints, *server, *rp;
    struct hostent *hostp;
    char s[20];
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    char hostname[]="localhost";
    if ( getaddrinfo("localhost", PORT, &hints, &server)!= 0) {
        fprintf(stderr, "ERROR failed \n");
        return 1;
    }
    
    for (rp = server; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);//socket
        if (sockfd == -1){
            perror("client: socket");
            continue;
        }
        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1)//connect
            break;
        close(sockfd);
    }
    if (rp == NULL) {
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }
    hostp = gethostbyname(hostname);
    strcpy(s,inet_ntoa(*(struct in_addr *)hostp->h_addr_list[0]));
    printf("client: connecting to %s (%s)\n",hostp->h_name, s);
    freeaddrinfo(server);
    
    
    str_process(sockfd);
    close(sockfd);          //close
    return 0;
}

