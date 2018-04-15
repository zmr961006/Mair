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
    }
    
    for(int t = 0;t < 10;t++ ){                          /*初始化存储链表的头节点*/
        for(int k  = 0;k < 100;k++){
            server_DB.ServerDB[t].DB[k] = (KeyVal *)malloc(sizeof(KeyVal));   
            server_DB.ServerDB[t].DB[k]->status = HEADNODE;
        }
    }

    return 0;
}


int database_choice(Message mess,char * order,int hash){
    
    int Flag = mess.Type;
    if(Flag == STRING){
        if((strcmp(mess.buff_mo,"SET") == 0) || (strcmp(mess.buff_mo,"set") == 0)){
            SET(mess,0);
            return STRING;
        }

    }else if(Flag == INT){

    }else if(Flag == LIST){

    }else if(Flag == ZLIST){

    }else if(Flag == SERVER){

    }else if(Flag == WATCH){
        
    }else{
        //pass
    }
    
    return 0;

}


