/*************************************************************************
	> File Name: server_init.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月03日 星期二 21时32分14秒
 ************************************************************************/

#ifndef _SERVER_INIT_H
#define _SERVER_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "./server_mess.h"

#define BUFFEXP  50
#define LOAD     10    /*默认三个节点*/

#define IPLEN    17   /*各个字段初始化长度*/
#define PORTLEN  5
#define STARTLEN 8
#define ENDLEN   8


#define  LIMIT  100000         /*第一次哈希的散列区间*/

/*路由转发表*/
typedef struct netinfo{

    char *ip_char;
    char *port_char;
    int ip_int;
    int port_int;
    int hash_start;
    int hash_end;
    int status;
    int virtual_server;
    struct netinfo *next;

}netinfo;



typedef struct netmap {

    netinfo *networkmap;
    netinfo *tail;
    int node_num;

}netmap;

int read_server(int temp1,char *temp2);
int write_server(int temp1,char *temp2);
int explex(char **infoex,int temp);
int init_info(char * temp1,int temp);
int _init_info();
int add_nodeinmap(char * buffer,int temp1);
int _add_nodeinmap(char * buf,netinfo * tem);
int proc_profile();
int test_net();
int server_init(int server_init);
int read_server(int temp1,char *temp2);




/**********************服务器节点增加***********************/
int appendnode(Message mess,int flag);

int delnode(Message mess,int flag);

int _app_nodeinmap(Message mess,netinfo * temp);

int find_servernode(Message mess,int flag,int index[]);

/***********************************************************/


/*********************服务器节点删除************************/


int delserver(int flag);         /*删除服务器路由节点*/

int setdelserver(int index);
/**********************************************************/


/********************服务器节点重写***********************/

int rewritefile();

/*********************************************************/



/*******************虚拟服务器相关***************************/


/*分布式转发核心算法*/

/*初始化虚拟节点核心算法*/
int init_virtual();

int add_virtual_node();

int del_virtual_node();

netinfo * find_send_node(int servernumber,int hash);

netinfo * find_real_node(int hash);

netinfo * find_virtual_node(int hash);



#endif
