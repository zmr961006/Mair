/*************************************************************************
	> File Name: server_to.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 22时59分39秒
 ************************************************************************/

#include<stdio.h>
#include"./server_to.h"


int server_to_server(int cmp,char *temp){

    int sockfd;
    struct sockaddr_in servaddr;
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9002);
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    write(sockfd,"hello",20);
    exit(0);



}
