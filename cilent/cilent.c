/*************************************************************************
	> File Name: cilent.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 22时34分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<errno.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include"./opt_do.h"
#include"./order.h"
#include"./read_pro.h"

extern order orders;


int main(int argc,char **argv){

    //int sockfd;
    //struct sockaddr_in servaddr;
    /*if(argc != 2){
        printf("tcp : ip \n");
        return -1;
    }*/

    //char * ip = "127.0.0.1";

    //sockfd = socket(AF_INET,SOCK_STREAM,0);
    //bzero(&servaddr,sizeof(servaddr));
    //servaddr.sin_family = AF_INET;
    //servaddr.sin_port = htons(9001);
    //inet_pton(AF_INET,ip,&servaddr.sin_addr);
    //connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    //init_cilent();  /*init order list*/
    read_server(0,NULL);
    //opt(NULL,NULL,0);  /*chunk and send message*/
    //write(sockfd,"hello",20);
    exit(0);

}
