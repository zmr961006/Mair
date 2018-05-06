/*************************************************************************
	> File Name: server_RDB.h
	> Author: 
	> Mail: 
	> Created Time: 2018年05月04日 星期五 09时33分29秒
 ************************************************************************/

#ifndef _SERVER_RDB_H
#define _SERVER_RDB_H

/*RDB 日志存储模式，将日志内容全部都存储在中间结构体中，然后以准备执行日志进行存储，回滚数据进行回复*/
/*数据存储的结构设计必须设计成为一种通用的结构最好能在存储AOF 与 RDB 的时候进行通用存储，以使得数据方便恢复*/
/*所以KV ，MESSAGE 都必须能转换为目标结构体，所以直接在开发的时候就应当采用一个兼容的设计结构*/

#include<string.h>
#include<stdlib.h>
#include"./server_mess.h"
#include"./server_DB.h"
#include"./server_str.h"

#define AOF       1             /*两个标志位*/
#define RDB       2
#define BUFFSIZE  1        /*一个BUFF默认存储10000条*/


/*AOF 与 RDB 通用存储结构*/
typedef struct LOG{

/*mess:*/
    char buff_mo[30];           /*指令存储*/
    char buff_key[512];         /*KEY存储*/
    char buff_val[512];         /*VAL存储*/
    char oob[30];               /*外带数据*/
    int  hash;                  /*KEY 的hash值*/
    int  hash_flag;          
    int  server_hash;           /*数据库存储ID*/
    int  Type;                  /*指令类型*/
    int  AOF_RDB;               /*用来指示是AOF 还是RDB 模式*/
    char dtime[1];              /*两个暂时没用的时间表示*/
    char ctime[1];
/*keyval:*/
    int Code;                   /*数据存储格式*/  
    short table_id;             /*表ID*/
    short db_id;                /*数据库ID*/
    short status;               /*存在性*/


}LOG;


/*日志存储结构*/
typedef struct LOGBUFF{

    LOG buff[BUFFSIZE];
    int sum;
    int free;

}LOGBUFF;



/*相关操作函数*/

/*创建一个通用存储结构，并返回一个这个类型的指针*/
LOG * log_create(void * temp,int type,int flag);

/*初始化日志模块存储结构*/
int init_log(int Type);

/*将存储内容定时刷入磁盘文件存储*/
int writetofile(int Type);

/*将存储内容刷入磁盘文件存储*/
int writetofilenow(int Type);

/*将数据从文件中读入内存准备恢复数据*/
int readfromfile(int Type);

/*写AOF接口*/

int w_aof(void * temp,int flag,int Type);

/*遍历RDB接口*/

int all_rdb();

/*写RDB接口*/
int w_rdb(void * temp,int flag,int Type);

/*打印内存日志*/
int watch_log();

/*LOG 转换接口*/


Message * log_to_mess(LOG * temp,int flag,int Type);



KeyVal * log_to_kv(LOG * temp,int flag,int Type);




#endif
