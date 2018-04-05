/*************************************************************************
	> File Name: message.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 17时03分28秒
 ************************************************************************/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include"./order.h"
#include"./opt_do.h"


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
    char now_time[1];
    char out_time[1];
    
}Message;



#endif