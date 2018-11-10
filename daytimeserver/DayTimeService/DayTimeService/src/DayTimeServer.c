//
//  DayTimeServer.c
//  DayTimeService
//
//  Created by zhutc on 2018/11/10.
//  Copyright © 2018年 zhuoApp. All rights reserved.
//

#include "DayTimeServer.h"
#include <netinet/in.h> // socket
#include <time.h> // time
#include <unistd.h> // write
#include <string.h> //strlen

#define    LISTENQ        1024    /* 2nd argument to listen() */
#define    MAXLINE        4096    /* max text line length */

void startDayTimeServer(void)
{
    int listenFD , connectFD;
    struct sockaddr_in serverAddress;
    char buff[MAXLINE];
    time_t ticks;
    
    //create socket
    listenFD = socket(AF_INET, SOCK_STREAM, 0);
    
    //create fail
    if (listenFD < 0) {
        printf("Create Socket Error!!");
        return ;
    }
    
    // fill zero
    bzero(&serverAddress , sizeof(serverAddress));
    
    // config ip port
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(1234);
    
    if (bind(listenFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Bind Socket Error");
        return;
    }
    printf("Bind Success");
    // change to listen socket
    if (listen(listenFD, LISTENQ) < 0) {
        printf("Listen Error~~");
        return;
    }
    do {
        // wait for client connect
        connectFD = accept(listenFD, NULL, NULL);
        if (connectFD < 0) {
            printf("Accept Error");
            return;
        }
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        printf("Buff is %s" , buff);
        // send to client 
        size_t length = strlen(buff);
        size_t writeLength = write(connectFD, buff, length);
        if (length != writeLength) {
            printf("Write Error!!");
            return;
        }
        
    } while (1);
    
    
}
