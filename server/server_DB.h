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
#include"./server_ser.h"

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

    dystr Key;                   /*动态字符存储KEY*/
    void *Val;                   /*无类型存储VAL*/
    int  hash;                   /*哈希值*/
    int  server_hash;            /*数据库ID*/
    int  Type;                   /*指令类型*/
    int  Code;                   /*存储编码类型*/
    short table_id;              /*数据库ID*/
    short db_id;                 /*存储表ID*/
    short status;                /*指示头尾*/
    char ctime[1];               /*存在时间*/
    char dtime[1];               /*删除时间*/
    struct KeyVal * next;    /*本节点的下一个节点*/
    struct KeyVal * head;    /*本条存储链的头节点*/
    struct KeyVal * tail;    /*本条存储链的尾节点*/

}KeyVal;





typedef struct DataBase{                /*用户数据库*/

    KeyVal **DB;    
    int db_numbers;    /*默认一个数据库100条存储表*/
    int flag;
    int sum_numbers;   /*此数据库总数*/
    int *sum_index;    /*每个数据库现在存储计数*/ 

}DataBase;






typedef struct Mair_DB{          /*数据库大类*/

    int DB_numbers;
    DataBase  ServerDB[10];      /*数据库10个实例*/
        

}Mair_DB;




int init_database();   /*初始化数据库*/
int database_choice(Message mess,char *order,int hash);  /*选择一个对应的函数操作*/

#endif
