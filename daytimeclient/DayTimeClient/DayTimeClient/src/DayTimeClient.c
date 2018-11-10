//
//  DayTimeClient.c
//  DayTimeClient
//
//  Created by ChuTing on 2018/11/10.
//  Copyright © 2018年 Opple. All rights reserved.
//

#include "DayTimeClient.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#define MAXLINE 4096
void startRequestTime(char* ip , int port)
{
    int socketFD , n;
    struct sockaddr_in socketAddress;
    
    char receiveLine[MAXLINE + 1];
    
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        printf("Create Scoket error!");
        return;
    }
    
    bzero(&socketAddress , sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &socketAddress.sin_addr) <= 0) {
        printf("Inet_pton ip error : %s",ip);
        return;
    }
    if (connect(socketFD, (struct sockaddr *)&socketAddress, sizeof(socketAddress)) < 0) {
        printf("Connect error~ , %d" , errno);
        return;
    }
    n = read(socketFD, receiveLine, MAXLINE);
    while (n > 0) {
        receiveLine[n] = 0;
        if (fputs(receiveLine, stdout) == EOF) {
            printf("fputs error");
        }
        n = read(socketFD, receiveLine, MAXLINE);
    }
    if (n < 0) {
        printf("Read error");
    }
    
}
