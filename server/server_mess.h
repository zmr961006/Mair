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

#define  ALIVE   1

typedef struct message{

    char buff_mo[ODER];
    char buff_key[KEYLEN];
    char buff_val[VALLEN];
    int  flag ;
    int  hash ;
    int  Type ;                /*接受类型*/
    char now_time[1];
    char out_time[1];
    
}Message;


#endif
