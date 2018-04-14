/*************************************************************************
	> File Name: server_DB.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 12时16分38秒
 ************************************************************************/

#ifndef _SERVER_DB_H
#define _SERVER_DB_H

#include<stdio.h>


/*************************************数据类型*************************************/
#define STRING  1
#define INT     2
#define LIST    3
#define HASH    4
#define ZLIST   5


/**********************************************************************************/



typedef struct KeyVal{           /*KV实例*/

    dystr Key;
    void *Val;
    int  hash;
    int  server_hash;
    int  Type;
    int  Code;
    char ctime[1];
    char dtime[1];
    struct KeyVal * next;

}KeyVal;





typedef struct DataBase{                /*用户数据库*/

    KeyVal **DB;    
    int db_numbers;
    int flag;
    int sum_numbers;   /*每个数据库总数*/
    

}DataBase;






typedef struct Mair_DB{          /*数据库大类*/

    int DB_numbers;
    Database[10];
        

}Mair_DB;




int init_database();   /*初始化数据库*/
int databse_choice();  /*选择一个对应的函数操作*/

#endif
