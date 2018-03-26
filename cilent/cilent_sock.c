/*************************************************************************
	> File Name: cilent_sock.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 14时38分23秒
 ************************************************************************/

#include"./cilent_sock.h"


int get_socket(int fd,int temp){

    int sockfd;
    struct sockaddr_in servaddr;

    char *ip = "127.0.0.1";
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(9001);
    //inet_pton(AF_INET,ip,&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    return sockfd;
    
    
}
