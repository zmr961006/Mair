/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 20时46分58秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


typedef struct node{

    int a;
    struct node * next;

}node;


typedef struct No{
    
    node **temp;
    int num;
}No;



int main(){
    
    No temp;
    temp.temp = (node **)malloc(sizeof(node *) * 5);
    temp.num  = 5;
    for(int j = 0;j < 5;j++){
    
        temp.temp[j] = (node *)malloc(sizeof(node));
    }

    temp.temp[0]->a = 0;
    temp.temp[1]->a = 1;
    temp.temp[2]->a = 2;
    temp.temp[3]->a = 3;
    temp.temp[4]->a = 4;
    

    for(int i = 0;i < 5;i++){
        printf("%d\n",temp.temp[i]->a);
    }

}
