/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月29日 星期四 16时57分33秒
 ************************************************************************/

#include<stdio.h>

typedef struct node{
    char buf[10];

}node;


int main(){

    node n;
    memcpy(n.buf,"zmr",5);
    printf("%s\n",n);



}
