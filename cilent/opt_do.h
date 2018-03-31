/*************************************************************************
	> File Name: opt_do.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 14时44分42秒
 ************************************************************************/

#ifndef _OPT_DO_H
#define _OPT_DO_H

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include"./message.h"


int opt(char * temp1,char *temp2,int argc);

int chunk(char *temp1);

int do_send();

int init_cilent();


int send_to(int fd);

int _send_to(int fd,Message mess);


int get_hash(char *data,int len);


int get_server(int hash);

#endif
