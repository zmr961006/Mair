/*************************************************************************
	> File Name: server_watch.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 11时58分06秒
 ************************************************************************/

#ifndef _SERVER_WATCH_H
#define _SERVER_WATCH_H

#include"./dystr.h"
#include"./order.h"
#include"./server.h"
#include"./server_DB.h"
#include"./server_mess.h"
#include"./rlist.h"


int print_mess(Message mess);    /*打印消息结构信息*/

int print_kv(KeyVal * temp );    /*打印KV*/

int print_dbnum();               /*打印数据库存储情况,返回总数*/

int print_list();                /*专门打印LIST 的值*/

#endif
