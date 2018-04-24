/*************************************************************************
	> File Name: rlist.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月24日 星期二 11时55分43秒
 ************************************************************************/

#ifndef _RLIST_H
#define _RLIST_H

#include<stdio.h>
#include<stdlib.h>
#include"./server_mess.h"


/*列表数据类型以及指令*/

#define LISTLEN  50

typedef struct rlist{

    int  elem_num ;
    char ** data  ;
    int  free_node;
    int  use_node ;
    int  flag     ;
    int  type     ;


}RLIST;


//设置链表                          LSIT KEY LEN
int CLIST(Message mess,int flag);

//将KEY小标为INDEX的元素设置为VALUE;LSET KEY INDEX:VALE
int LSET(Message mess,int flag);

//删除LIST 中的某个元素;删除某个列表中的元素; 
                                  //LDEL KEY INDEX:VALUE
int RDEL(Message mess,int flag);

//增加尾部的一个元素                LPUSH  key value
int LPUSH(Message mess,int flag);

//删除第一个元素                    LPOP   key value
int LPOP(Message mess,int flag);


int create_list(RLIST * temp,Message mess);


#endif
