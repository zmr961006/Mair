/*************************************************************************
	> File Name: server_str.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 15时11分58秒
 ************************************************************************/


#include"./server_str.h"
#include"./server_DB.h"

extern Mair_DB server_DB;

/*SET string*/
int SET(Message mess,int argc){
 
    if(EXIST(mess,0) == NOTEXIST){             /*不存在则增加；存在则修改VAL*/
        
        KeyVal * temp = (KeyVal *)malloc(sizeof(KeyVal));
        strcpy(temp->Key.dystr_data,mess.buff_key);
        int len = strlen(mess.buff_val);
        temp->Val = (char *)malloc(sizeof(char)*len);
        strcpy(temp->Val,mess.buff_val);
        

    }else{


    }
    

}

int EXIST(Message mess,int argc){
 
    int data_base  = mess.server_hash;  /*数据库编号*/
    int data_table = mess.hash % 100 ;  /*存储表编号*/
    int index = server_DB.ServerDB[data_base].sum_index[data_table];  /*此表中有多少个KV*/
    KeyVal * temp = server_DB.ServerDB[data_base].DB[data_table];     /*指向目标表链*/
    if(index == 0){
        return NOTEXIST;
    }
    for(int i = 0;i < index;i++){
        if(strcmp(mess.buff_key,temp->Key.dystr_data) == 0){
            return KEXIST;
        }else{
            temp = temp->next;
        }

    }
    return NOTEXIST;

}

