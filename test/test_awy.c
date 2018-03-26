/*************************************************************************
	> File Name: test_awy.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 15时48分58秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char **temp;


int main(){
    char * test = "hello world";
    temp = (char **)malloc(sizeof(char*)*10);
    int i = 0;
    for(i = 0;i < 10;i++){
        char * tmp = (char *)malloc(sizeof(char)*20);
        memcpy(tmp,test,12);
        temp[i] = tmp;
    }

    for(i = 0;i < 10;i++){
        printf("%s\n",temp[i]);
    }



}
