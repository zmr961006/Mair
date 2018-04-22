/*************************************************************************
	> File Name: cilent_sock.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 14时38分26秒
 ************************************************************************/

#ifndef _CILENT_SOCK_H
#define _CILENT_SOCK_H

#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include "./distribute.h"


int get_socket(int fd,int temp);




#endif
