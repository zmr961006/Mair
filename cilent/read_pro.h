/*************************************************************************
	> File Name: read_pro.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 10时32分08秒
 ************************************************************************/

#ifndef _READ_PRO_H
#define _READ_PRO_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "./message.h"


#define BUFFEXP  50
#define LOAD     10    /*默认三个节点*/

#define IPLEN    17   /*各个字段初始化长度*/
#define PORTLEN  5
#define STARTLEN 8
#define ENDLEN   8



/****************************配置文件*************************/
/*
 * [server][ip][port][hash_start][hash_end][status][virtual]
*/                                                           
/*************************************************************/



/*路由转发表结构*/

typedef struct netinfo{

    char *ip_char;          /*IP字符存储*/
    char *port_char;        /*端口字符存储*/
    int ip_int;             /*IP整形存储*/
    int port_int;           /*端口整形存储*/
    int hash_start;         /*哈希开始*/
    int hash_end;           /*哈希结束*/
    int status;             /*节点状态,是否是虚拟节点*/
    int virtual_server;     /*虚拟节点对应真实节点的指向*/
    struct netinfo *next;   /*链表*/

}netinfo;



/*路由转发表内存结构*/
typedef struct netmap {

    netinfo *networkmap;    /*路由转发表*/
    netinfo *tail;          /*表尾*/
    int node_num;           /*路由个数*/

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


/**********************服务器节点增加***********************/
int appendnode(Message mess,int flag);

int delnode(Message mess,int flag);

int _app_nodeinmap(Message mess,netinfo * temp);

int find_servernode(Message mess,int flag,int index[]);   /*删除所有节点包括虚拟节点*/

/***********************************************************/


/*********************服务器节点删除************************/


int delserver(int flag);         /*删除服务器路由节点*/

int setdelserver(int index);


/**********************************************************/


/********************服务器节点重写***********************/

int rewritefile();

/*********************************************************/






#endif
