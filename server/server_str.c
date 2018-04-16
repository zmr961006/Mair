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
        
        KeyVal * temp = mess_to_kv(mess,0,0);
        add_KV_DB(temp,0);

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

/*Message 转换为KEYVAL*/
KeyVal * mess_to_kv(Message mess,int flag,int len){
    
    KeyVal * temp = (KeyVal *)malloc(sizeof(KeyVal));
    int mess_type = mess.Type;
    int llen = strlen(mess.buff_key);
    dystr_create2(temp->Key,mess.buff_key,llen);
    
    int vlen = strlen(mess.buff_val);

    temp->hash = mess.hash;
    temp->db_id = mess.server_hash;
    temp->table_id = mess.hash % 100;

    if(mess.Type == STRING){                              /*根据数据类型创建VAL的值*/
        
        temp->Val = (char *)malloc(sizeof(char)*vlen);
        strcpy(temp->Val,mess.buff_val);

    }else if(mess.Type == LIST){

    }else{

        //pass
    }

    return temp;
}


/*添加KV到键值存储系统*/
int add_KV_DB(KeyVal * temp,int flag){
    
    KeyVal * node ;
    KeyVal * head ;
    node = server_DB.ServerDB[temp->db_id].DB[temp->table_id];
    head = server_DB.ServerDB[temp->db_id].DB[temp->table_id];

    int index = server_DB.ServerDB[temp->db_id].sum_index[temp->table_id];


    for(int i = 0;i < index;i++){
        node = node->next;
    }    
    
    node->next = temp;
    head->tail = temp;
    
    temp->next = NULL;
    temp->head = head;
    temp->tail = head->tail;
    
    return 0;
    
}

KeyVal* GET(Message mess,int argc){

    if(EXIST(mess,argc) == KEXIST){
        
        int table_index = mess.hash % 100;
        int db_index    = mess.server_hash;
        int num_index   = server_DB.ServerDB[db_index].sum_index[table_index];
        KeyVal * temp = server_DB.ServerDB[db_index].DB[table_index];
        for(int i = 0; i < db_index ;i++){
            temp = temp->next;
        }
        
        return temp;

    }else{

        /*不存在,返回为空，防止误操作*/
        return NULL;
    }


}


int DEL(Message mess,int argc){
    
    if(EXIST(mess,argc) == KEXIST){
        
        int table_index = mess.hash % 100;
        int db_index    = mess.server_hash;
        int num_index   = server_DB.ServerDB[db_index].sum_index[table_index];
        KeyVal * temp = server_DB.ServerDB[db_index].DB[table_index];
        for(int i  = 0;i < db_index;i++){
            temp = temp -> next;
        }
        /*采用惰性删除的策略，不首先释放内存空间*/
        temp->status = DEAD;
        return 1;
    }else{

        /*不存在则返回NULL == 0，提示信息*/
        return 0;
    }


}


KeyVal * FIND(Message mess,char * temp,int len){
    





}
