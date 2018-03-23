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

typedef struct message{

    char buff_mo[ODER];
    char buff_key[KEYLEN];
    char buff_val[VALLEN];
    int  flag ;
    
}message;



#endif
