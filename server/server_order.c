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
    orders.orders[6] = "EXIST";
    orders.orders[7] = "exist";
    orders.orders[8] = "ADDNODE";
    orders.orders[9] = "addnode";
    orders.orders[10]= "DELNODE";
    orders.orders[11]= "delnode";
    
    orders.orders[12]= "CLIST";
    orders.orders[13]= "rlist";
    orders.orders[14]= "LSET";
    orders.orders[15]= "lset";
    orders.orders[16]= "RDEL";
    orders.orders[17]= "rdel";
    orders.orders[18]= "LPUSH";
    orders.orders[19]= "lpush";
    orders.orders[20]= "LPOP";
    orders.orders[21]= "lpop";
    orders.orders[22]= "SCHUNK";
    orders.orders[23]= "schunk";

    orders.orders[24]= "AOF";
    orders.orders[25]= "aof";
    orders.orders[26]= "RDB";
    orders.orders[27]= "rdb";
    orders.orders[28]= "SHOW";
    orders.orders[29]= "show";
    orders.orders[30]= "SHUTDOWN";
    orders.orders[31]= "shutdown";

    orders.num = 32;


}


