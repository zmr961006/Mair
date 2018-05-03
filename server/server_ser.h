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
#include"./server_bc.h"

int ADDNODE(Message mess,int flag,int fd);

int DELNODE(Message mess,int flag,int fd);

int REWRITEFILE();

/*服务器效验指令,负责将自己的版本转发和统一路由转发表*/
int SCHUNK(Message mess,int flag,int fd);

/*客户端请求更新自己的路由转发表*/
int UPDATE(Message mess,int flag,int fd);

/*re设置hash服务范围,根据最新修改的数据*/
int set_hash(Message mess,int FLAG);


#endif
