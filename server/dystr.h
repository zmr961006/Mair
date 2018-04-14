/*************************************************************************
	> File Name: dystr.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 12时38分42秒
 ************************************************************************/

#ifndef _DYSTR_H
#define _DYSTR_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct dystr{

    char  * dystr_data;  /*内容*/
    int   len;           /*数据长度*/
    int   bix;           /*编码类型*/
    int   plen;         /*预计长度*/

}dystr;


int dystr_create2(dystr temp,char *data,int len);
dystr * dystr_create(char * data,int len);
int dystr_free(dystr * temp);
int dystr_mod(dystr * temp,char *data,int  len);




#endif
