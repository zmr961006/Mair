/*************************************************************************
	> File Name: server_ser.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 13时48分58秒
 ************************************************************************/

#ifndef _SERVER_SER_H
#define _SERVER_SER_H

#include"./server_mess.h"
#include"./server_init.h"

int ADDNODE(Message mess,int flag);

int DELNODE(Message mess,int flag);

int REWRITEFILE();



#endif
