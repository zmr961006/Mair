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
#include"./server_DB.h"
#include"./order.h"
#include"./server_bc.h"


int main(int argc ,char **argv){

    if(argc < 2){
        printf("error opt\n");
        exit(0);
    }
    int temp = atoi(argv[1]);
    server_init(temp);  /*初始化网络转发表*/
    init_database();    /*初始化数据存储系统*/
    init_order();       /*初始化命令结构*/
    server_bc_init();   /*初始化反馈信息*/
    init_log(AOF);      /*初始化AOF存储空间*/
    init_log(RDB);      /*初始化RDB存储空间*/
    server_info_show(); /*服务器启动信息提示*/
    test_net();         /*网络测试*/
    server_start();     /*服务启动*/
    //server_stop();

}


int server_info_show(){
    

    printf("/***************************************************************************/\n");
    printf("/***************************************************************************/\n");
    printf("/基于一致性哈希的分布式键值存储系统*****************************************/\n");
    printf("/Mair DB,2018.05 ***********************************************************/\n");
    printf("/***************************************************************************/\n");
    printf("/***************************************************************************/\n");

}




