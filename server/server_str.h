/*************************************************************************
	> File Name: server_str.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 15时11分45秒
 ************************************************************************/

#ifndef _SERVER_STR_H
#define _SERVER_STR_H

#include<stdio.h>
#include"./server_mess.h"
#include"./server_DB.h"
#include"./server_watch.h"
#include"./rlist.h"

#define NOTEXIST   0       /*KV不存在*/
#define KEXIST     1       /*KV存在*/
#define DEAD       (-1)    /*KV暂时性死亡*/
#define ALIVE      1       /*KV存活*/

/*SET 指令；字符串设置*/

int SET(Message mess,int argc);

/*测试KV是否存在*/
int EXIST(Message mess,int argc);

/*MESSAGE 转换为 KEYVAL*/
KeyVal * mess_to_kv(Message mess,int flag,int len);

/*增加KV到DB中*/
int add_KV_DB(KeyVal * temp,int flag);

/*获取其中的一个存在KV*/
KeyVal* GET(Message mess,int argc);

/*删除某个KV */
int DEL(Message mess,int argc);

/*打印所有的KV*/
KeyVal * FINDALL();



#endif
