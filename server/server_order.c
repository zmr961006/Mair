/*************************************************************************
	> File Name: server_order.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 23时00分56秒
 ************************************************************************/

#include"./order.h"

order orders;            /*初始化命令列表,暂时6*/

int init_order(){

    orders.orders[0] = "DEL";
    orders.orders[1] = "GET";
    orders.orders[2] = "SET";
    orders.orders[3] = "del";
    orders.orders[4] = "get";
    orders.orders[5] = "set";
    orders.num = 6;



}


