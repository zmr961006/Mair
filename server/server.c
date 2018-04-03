/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月31日 星期六 21时02分00秒
 ************************************************************************/

#include<stdio.h>
#include"./server.h"
#include"./server_start.h"
#include"./server_init.h"

int main(int argc ,char **argv){

    if(argc < 2){
        printf("error opt\n");
        exit(0);
    }
    int temp = atoi(argv[1]);
    server_init(temp);
    test_net();
    server_start();
    //server_stop();

}





