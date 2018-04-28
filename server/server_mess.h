/*************************************************************************
	> File Name: server_mess.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月03日 星期二 22时30分21秒
 ************************************************************************/

#ifndef _SERVER_MESS_H
#define _SERVER_MESS_H

#define  BUFFLEN 1024
#define  ODER    30
#define  KEYLEN  512
#define  VALLEN  512



typedef struct message{

    char buff_mo[ODER];        /*命令存储*/
    char buff_key[KEYLEN];     /*KEY存储*/
    char buff_val[VALLEN];     /*VALUE存储*/
    int  flag ;
    int  hash ;                /*哈希值*/
    int  Type ;                /*接受类型*/
    int  server_hash;          /*数据库ID*/
    char now_time[1];
    char out_time[1];
    char oob[30];              /*外带数据,一般作返回使用*/   
}Message;


#endif
