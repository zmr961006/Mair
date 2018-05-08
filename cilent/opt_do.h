/*************************************************************************
	> File Name: opt_do.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 14时44分42秒
 ************************************************************************/

#ifndef _OPT_DO_H
#define _OPT_DO_H

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

#include"./message.h"


int opt(char * temp1,char *temp2,int argc);

int chunk(char *temp1);

int do_send();

int init_cilent();

int send_to(int fd);

//int _send_to(int fd,Message mess);

int get_hash(char *data,int len);

int get_ordernum(char * order);    /*获取命令类型*/

int get_server(int hash);

int do_local(int Type,Message message);            /*与服务器相关的预处理*/  

int ADDNODE(Message mess,int flag);                /*增加服务器节点*/ 

int DELNODE(Message mess,int flag);                /*删除服务器节点*/

int REWRITEFILE();                                 /*将更新的服务器端点和节点重新写入配置文件*/

int print_bc(Message mess);

/*RDB & AOF 服务存储*/

int rdb_aof_send(Message mess,int flag);

/*展示统计所有已经存在的数据*/

int show_shut_send(Message message,int flag);

#endif
