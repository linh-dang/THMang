//
//  main.c
//  Server
//
//  Created by Linh Dang on 11/11/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//


#include "my_global.h"
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <poll.h>
#define PORT "5500"
#define BUF_SIZE 500
#define BACKLOG 10
#define MAX_CLI 30
int str_process(int new_fd){
    ssize_t n;
    char buf[BUF_SIZE];
    int i;
    
    n = recv(new_fd, buf, BUF_SIZE, 0);
    if (n < 0)
        return -1;
    else
        if (n == 0){
            return -1;
        }
        else {
            printf("server received %d bytes \n",(int) n);
            for (i = 0; buf[i] != '\0'; i++)
                buf[i] = toupper(buf[i]);
            if ((n = send(new_fd, buf, strlen(buf),0))<0)
                fprintf(stderr, "Error sending response\n");
            printf("server send %d bytes\n",(int) n);
        }
    return 0;
}

int main(int argc, const char * argv[]) {
    // socket bind listen accept  [write read] read close
    int maxfd, listenfd , new_fd,optval;
    struct addrinfo hints, *server;
    struct sockaddr_in client;
    struct hostent *hostp;
    socklen_t sin_size;
    
    struct pollfd fds[MAX_CLI];
    int i, rv;
    
    
    
    //---------------------*********************************-------------------
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if ( getaddrinfo(NULL, PORT, &hints, &server)!= 0) {
        fprintf(stderr, "server: failed \n");
    }
    
    if((listenfd  = socket(server->ai_family, server->ai_socktype,server->ai_protocol)) ==-1)
        printf("ERROR socket\n");
    optval = 1;
    setsockopt(listenfd , SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(optval));
    
    int on = 1;
    if ((ioctl(listenfd, FIONBIO, (char *)&on))< 0)
    {
        perror("ioctl() failed");
        close(listenfd);
        exit(-1);
    }
    if (bind(listenfd , server->ai_addr, server->ai_addrlen) == -1) {
        close(listenfd );
        perror("ERROR bind");
    }
    if (listen(listenfd , BACKLOG) == -1) {
        perror("ERROR listen");
        exit(1);
    }
    freeaddrinfo(server);
    //--------------*************************************--------------------/
    
    //memset(fds, 0 , sizeof(fds));
    fds[0].fd = listenfd;
    fds[0].events = POLLRDNORM;
    for (i = 1; i < MAX_CLI ; i++)
    {fds[i].fd = -1;}
    
    printf("server: waiting for connections...\n");
    maxfd = 0;
    int timeout = 6 * 60 * 1000;
    while (1) {
        rv = poll(fds, maxfd + 1,timeout);
        
        sin_size = sizeof client;
        if (fds[0].revents & POLLRDNORM)
        {
            new_fd = accept(listenfd , (struct sockaddr *)&client, &sin_size);
            if (new_fd<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            
            for ( i = 1 ; i < MAX_CLI ; i++)
            {
                if ( fds[i].fd < 0){
                    fds[i].fd = new_fd;
                    fds[i].events = POLLRDNORM;
                    break;
                }
            }
            if (i == MAX_CLI)
                perror("too many clients");
            
            if (i > maxfd)
                maxfd = i;
            hostp = gethostbyaddr((const char *)&client.sin_addr.s_addr,sizeof(client.sin_addr.s_addr), hints.ai_family);
            printf("server got connection from  socket id %d (%s) port id: %d \n",new_fd, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            
            if (--rv <= 0)continue;
        }
        
        for (i = 1; i <=maxfd ; i++)
        {
            if (  fds[i].fd< 0)
                continue;
            if (fds[i].revents & (POLLRDNORM | POLLERR))
            {
                if(str_process(fds[i].fd)==-1)
                {
                    printf("disconnected , socket id %d \n",fds[i].fd);
                    close(fds[i].fd);
                    fds[i].fd =-1;
                    
                }
                if (--rv <=0)
                    break;
                
            }
        }
        
        
        
    }
    
    
    return 0;
}

