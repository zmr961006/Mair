/*************************************************************************
	> File Name: server_start.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月31日 星期六 21时29分21秒
 ************************************************************************/

#ifndef _SERVER_START_H
#define _SERVER_START_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include "./server_to.h"
#include "./server_mess.h"
#include "./server_watch.h"
#include "./server_str.h"
#include "./server_RDB.h"


#define BUFSIZE    2048
#define SERV_PORT  8000
#define OPEN_MAX   1024
#define PORT       9001
#define RECEVLEN   1480


int server_start();

int mess_exl(char *buf,int len,int fd);

int test_mess(Message mess);


#endif
