/*************************************************************************
	> File Name: server_watch.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 12时06分10秒
 ************************************************************************/

#include"./server_watch.h"

/*检测模块*/

int print_mess(Message mess){

    printf("|order|Key|Vale|Type|Hash|\n");
    printf("|%s|%s|%s|%d|%d|\n",mess.buff_mo,mess.buff_key,mess.buff_val,mess.Type,mess.hash);
    return 0;

}
