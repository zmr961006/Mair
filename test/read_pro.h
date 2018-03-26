/*************************************************************************
	> File Name: read_pro.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 10时32分08秒
 ************************************************************************/

#ifndef _READ_PRO_H
#define _READ_PRO_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


#define  BUFFEXP   100


int read_server(int temp1,char *temp2);
int write_server(int temp1,char *temp2);
int explex(char **infoex,int temp);




#endif
