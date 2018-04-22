/*************************************************************************
	> File Name: distribute.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 22时56分31秒
 ************************************************************************/

#ifndef _DISTRIBUTE_H
#define _DISTRIBUTE_H

#include"./read_pro.h"
#include"./opt_do.h"


#define  LIMIT  100000         /*第一次哈希的散列区间*/

/*分布式转发核心算法*/

/*初始化虚拟节点核心算法*/
int init_virtual();

int add_virtual_node();

int del_virtual_node();

netinfo * find_send_node(int servernumber,int hash);

netinfo * find_real_node(int hash);

netinfo * find_virtual_node(int hash);





#endif
