/*************************************************************************
	> File Name: message.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 17时03分28秒
 ************************************************************************/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include"./order.h"



#define  BUFFLEN 1024
#define  ODER    30
#define  KEYLEN  512
#define  VALLEN  512

#define  ALIVE   1

/********************************************命令类型*******************************/

#define  STRING  1 
#define  INT     2
#define  LIST    3
#define  HASH    4
#define  ZLIST   5
#define  SERVER  6
#define  WATCH   7

/***********************************************************************************/





typedef struct message{

    char buff_mo[ODER];     /*命令存储*/
    char buff_key[KEYLEN];  /*KEY 存储*/
    char buff_val[VALLEN];  /*VAL 存储*/
    int  flag ;             /*标志*/
    int  hash ;             /*哈希值*/
    int  Type ;             /*命令类型*/
    int  server_hash;       /*数据库ID*/
    char now_time[1];       /*设置时间*/
    char out_time[1];       /*过期时间*/
    
}Message;



#endif
