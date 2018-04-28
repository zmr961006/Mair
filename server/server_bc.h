/*************************************************************************
	> File Name: server_bc.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 20时41分02秒
 ************************************************************************/

#ifndef _SERVER_BC_H
#define _SERVER_BC_H

#include<sys/types.h>
#include<sys/socket.h>

#include"./dystr.h"
#include"./order.h"
#include"./rlist.h"
#include"./server_mess.h"



/*回射服务器处理结果*/
int server_bc(Message mess,char *info,int flag,int fd);

/*初始化反馈信息*/
int server_bc_init(); 

#endif

