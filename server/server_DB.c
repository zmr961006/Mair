/*************************************************************************
    > File Name: server_DB.c
    > Author: 
    > Mail: 
    > Created Time: 2018年04月14日 星期六 12时16分42秒
 ************************************************************************/

#include"./server_DB.h"
#include"./server_str.h"

Mair_DB server_DB;    /*全局数据存储系统*/



int init_database(){     /*初始数据库10个,每个数据库100条存储表*/

    server_DB.DB_numbers = 10;
    for(int i = 0;i < 10;i++){                           /*初始化10个数据库，每个库100条数据连*/
        server_DB.ServerDB[i].db_numbers = 100;
    }
    for(int j = 0;j < 10;j++){                               
        server_DB.ServerDB[j].DB = (KeyVal **)malloc(sizeof(KeyVal *)*100);
        server_DB.ServerDB[j].sum_numbers = 0 ;          /*每个数据存储链的计数初始化0*/
        server_DB.ServerDB[j].sum_index = (int *)malloc(sizeof(int) * 100); 
        /*当前每一个链存储0个KV,使用数组存储每条链表的情况*/
    }
    
    for(int t = 0;t < 10;t++ ){                          /*初始化存储链表的头节点*/
        for(int k  = 0;k < 100;k++){
            server_DB.ServerDB[t].DB[k] = (KeyVal *)malloc(sizeof(KeyVal));   
            server_DB.ServerDB[t].DB[k]->status = HEADNODE;                   /*存储链表的头结点标志*/
            server_DB.ServerDB[t].DB[k]->next = NULL;                         /*初始化next;head;tail 指针*/
            server_DB.ServerDB[t].DB[k]->head = server_DB.ServerDB[t].DB[k]->tail = server_DB.ServerDB[t].DB[k];
                                                                              /*head = tail =  self ;next = NULL'*/
        }
    }
    
    

    return 0;
}


int database_choice(Message mess,char * order,int hash){
    
    int Flag = mess.Type;
    if((Flag == STRING)||(Flag == COMMON)){
        if((strcmp(mess.buff_mo,"SET") == 0) || (strcmp(mess.buff_mo,"set") == 0)){
            SET(mess,0);
            return STRING;
        }else if((strcmp(mess.buff_mo,"EXIST") == 0) || (strcmp(mess.buff_mo,"exist") == 0)){
            EXIST(mess,0);
            return STRING;
        }else if((strcmp(mess.buff_mo,"GET") == 0) || (strcmp(mess.buff_mo,"get") == 0)){
            GET(mess,0);
	        return STRING;
        }else if((strcmp(mess.buff_mo,"DEL") == 0) || (strcmp(mess.buff_mo,"del") == 0)){
            DEL(mess,0);
	    return STRING;
        }else{
            //pass;
        }
    }else if(Flag == INT){
            //pass
    }else if((Flag == LIST)||(Flag == COMMON)){

	    if((strcmp(mess.buff_mo,"CLIST") == 0) || (strcmp(mess.buff_mo,"clist") == 0)){
            CLIST(mess,0);
            return LIST;
        }else if((strcmp(mess.buff_mo,"LSET") == 0) || (strcmp(mess.buff_mo,"lset") == 0)){
            LSET(mess,0);
            return LIST;
        }else if((strcmp(mess.buff_mo,"RDEL") == 0) || (strcmp(mess.buff_mo,"RDEL") == 0)){
            RDEL(mess,0);
            print_list(NULL);
	        return LIST;
        }else if((strcmp(mess.buff_mo,"LPUSH") == 0) || (strcmp(mess.buff_mo,"LPUSH") == 0)){
            LPUSH(mess,0);
            print_list(NULL);
	        return LIST;
        }else if((strcmp(mess.buff_mo,"LPOP") == 0) ||(strcmp(mess.buff_mo,"lpop") == 0)){
            LPOP(mess,0);
            return LIST;
        }else if((strcmp(mess.buff_mo,"EXIST") == 0) || (strcmp(mess.buff_mo,"exist") == 0)){
            EXIST(mess,0);
            return LIST;
        }else{
            //pass
        }

    }else if(Flag == ZLIST){

    }else if(Flag == SERVER){
        
	    if((strcmp(mess.buff_mo,"ADDNODE") == 0) || (strcmp(mess.buff_mo,"addnode") == 0)){
                ADDNODE(mess,0);
                REWRITEFILE();
                return SERVER;
        }else if((strcmp(mess.buff_mo,"DELNODE") == 0) || (strcmp(mess.buff_mo,"delnode") == 0)){
                DELNODE(mess,0);
                REWRITEFILE();
            return SERVER;
        }else{
            //pass
        }
    }else if(Flag == WATCH){
        
    }else{
        //pass
    }
    
    return 0;

}


