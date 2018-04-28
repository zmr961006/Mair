/*************************************************************************
	> File Name: server_ser.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 13时52分08秒
 ************************************************************************/

#include"./server_ser.h"



int ADDNODE(Message mess,int flag,int fd){
    int bc = 0;
    printf("---------------------------------------------\n");
    test_net();
    printf("ADDNODE : %s : %s\n",mess.buff_key,mess.buff_val);
    appendnode(mess,flag);
    bc = 10;
    server_bc(mess,NULL,bc,fd);
    test_net();
    printf("---------------------------------------------\n");

}


int DELNODE(Message mess,int flag,int fd){
    int bc = 0; 
    test_net();
    printf("DELNODE : %s: %s\n",mess.buff_key,mess.buff_val);
    delnode(mess,flag);
    bc = 11;
    server_bc(mess,NULL,bc,fd);
    test_net();

}

int REWRITEFILE(){
    
    int number;
    number = rewritefile();

    return number;
}

