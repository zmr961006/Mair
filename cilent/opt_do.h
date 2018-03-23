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


#define BUFFLEN  1024
#define ODER     30
#define KEYLEN   512
#define VALLEN   512


int opt(char * temp1,char *temp2,int argc);

int chunk(char *temp1);

int do_send();

int init_cilent();


int send_to(int fd);

#endif
