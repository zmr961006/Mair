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

//ps:没有实现判断是否LIST 满


typedef struct rlist{

    int  elem_num ;        //统计一共有多少个元素
    char ** data  ;        //数据存储
    int  free_node;        //剩余可以使用的内容
    short bitmap[LISTLEN]; //位图
    int  use_node ;        //最后一个元素的下标
    int  flag     ;        //标记
    int  type     ;        //存储类型；预留


}RLIST;


//设置链表                          LSIT KEY LEN
int CLIST(Message mess,int flag,int fd);

//将KEY小标为INDEX的元素设置为VALUE;LSET KEY INDEX:VALE
int LSET(Message mess,int flag,int fd);

//删除LIST 中的某个元素;删除某个列表中的元素; 
                                  //LDEL KEY INDEX:VALUE
int RDEL(Message mess,int flag,int fd);

//增加尾部的一个元素                LPUSH  key value
int LPUSH(Message mess,int flag,int fd);

//删除尾部的一个元素                    LPOP   key value
int LPOP(Message mess,int flag,int fd);

//创建一个列表
int create_list(RLIST * temp,Message mess);


#endif
