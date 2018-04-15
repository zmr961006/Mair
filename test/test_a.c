/*************************************************************************
	> File Name: test_a.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 22时36分27秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(){
    
    int *a ;
    a = (int *)malloc(sizeof(int)*10);
    for(int i  =  0;i < 10 ;i++){
        a[i] = i;
    }
    for(int j  = 0;j < 10;j++){
        printf("%d\n",a[j]);
    }
    
    return 0;

}
