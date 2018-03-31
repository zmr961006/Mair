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

#define BUFFEXP  50
#define LOAD     10    /*默认三个节点*/

#define IPLEN    17   /*各个字段初始化长度*/
#define PORTLEN  5
#define STARTLEN 8
#define ENDLEN   8





typedef struct netinfo{

    char *ip_char;
    char *port_char;
    int ip_int;
    int port_int;
    int hash_start;
    int hash_end;
    int status;
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



#endif
