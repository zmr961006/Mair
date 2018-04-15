/*************************************************************************
	> File Name: server_DB.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 12时16分38秒
 ************************************************************************/

#ifndef _SERVER_DB_H
#define _SERVER_DB_H

#include<stdio.h>
#include"./dystr.h"
#include"./server_mess.h"

/*************************************数据类型*************************************/
#define STRING  1
#define INT     2
#define LIST    3
#define HASH    4
#define ZLIST   5
#define SERVER  6
#define WATCH   7

/**********************************************************************************/


#define HEADNODE 101

/**********************************************************************************/


typedef struct KeyVal{           /*KV实例*/

    dystr Key;
    void *Val;
    int  hash;
    int  server_hash;
    int  Type;
    int  Code;
    short status;                /*指示头尾*/
    char ctime[1];
    char dtime[1];
    struct KeyVal * next;    /*本节点的下一个节点*/
    struct KeyVal * head;    /*本条存储链的头节点*/
    struct KeyVal * tail;    /*本条存储链的尾节点*/

}KeyVal;





typedef struct DataBase{                /*用户数据库*/

    KeyVal **DB;    
    int db_numbers;    /*默认一个数据库100条存储表*/
    int flag;
    int sum_numbers;   /*每个数据库总数*/
    int *sum_index;    /*每个数据库现在存储多少*/ 

}DataBase;






typedef struct Mair_DB{          /*数据库大类*/

    int DB_numbers;
    DataBase  ServerDB[10];
        

}Mair_DB;




int init_database();   /*初始化数据库*/
int database_choice(Message mess,char *order,int hash);  /*选择一个对应的函数操作*/

#endif
