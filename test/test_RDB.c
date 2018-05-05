/*************************************************************************
	> File Name: test_RDB.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月05日 星期六 10时01分48秒
 ************************************************************************/

#include<stdio.h>
#include"server_RDB.h"

extern LOGBUFF LOGAOF;
extern LOGBUFF LOGRDB;




int main(){


    init_log(AOF);
    init_log(RDB);
    
    for(int i = 0;i < 201;i++){
        //KeyVal temp;
        Message temp;
        //temp.Key.dystr_data = "hhh";
        //temp.Val = (char *)malloc(sizeof(char*));
        temp.hash =  100;
        w_aof(&temp,0,0);
        
    }
    readfromfile(AOF);
    //watch_log(AOF);
    



}


