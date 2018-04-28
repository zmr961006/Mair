/*************************************************************************
	> File Name: server_bc.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月28日 星期六 20时42分45秒
 ************************************************************************/

#include<stdio.h>
#include"./server_bc.h"



char bc_info[12][30];    /*反馈信息存储*/

int server_bc_init(){

    memcpy(bc_info[0],"there is nothing",16);
    memcpy(bc_info[1],"This KV is exist",16);
    memcpy(bc_info[2],"This KV add ok!!",16);
    memcpy(bc_info[3],"This KV NO exist",16);
    memcpy(bc_info[4],"This KV get ok!!",16);
    memcpy(bc_info[5],"This KV del ok!!",16);
    memcpy(bc_info[6],"This LKV set ok!",16);
    memcpy(bc_info[7],"This KV push ok!",16);
    memcpy(bc_info[8],"This KV pop ok!!",16);
    memcpy(bc_info[9],"This KV del ok!!",16);
    memcpy(bc_info[10],"Node  add  ok!!",16);
    memcpy(bc_info[11],"NODE  del  ok!!",16);


}


int server_bc(Message mess,char *info,int flag,int fd){

    Message messbc;
    memcpy(&messbc,&mess,sizeof(mess));
    memset(messbc.oob,0,30);
    memcpy(messbc.oob,bc_info[flag],16);
    send(fd,(const void *)&messbc,sizeof(Message),0);
    printf("KVbc = %s\n",messbc.oob);
    return 0;

}



