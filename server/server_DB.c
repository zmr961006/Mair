/*************************************************************************
	> File Name: server_DB.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 12时16分42秒
 ************************************************************************/

#include"./server_DB.h"

Mair_DB server_DB;    /*全局数据存储系统*/



int init_database(){     /*初始数据库10个*/

    server_DB.DB_numbers = 10;

}
