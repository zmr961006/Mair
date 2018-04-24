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
        FINDALL();               /*展示所有存在的KV*/

    }else{

        printf("This KV is already EXIST\n");

    }
    

}

int EXIST(Message mess,int argc){
 
    //printf("in EXIST\n");
    int data_base  = mess.server_hash;  /*数据库编号*/
    int data_table = mess.hash % 100 ;  /*存储表编号*/


    int index = server_DB.ServerDB[data_base].sum_index[data_table];  /*此表中有多少个KV*/
    KeyVal * temp = server_DB.ServerDB[data_base].DB[data_table];     /*指向目标表链*/
    if(index == 0){
        return NOTEXIST;
    }
    
    while(temp->next != NULL ){
        temp = temp->next;
        if(strcmp(mess.buff_key,temp->Key.dystr_data) == 0){
            printf("this key is already exist\n");
            return KEXIST;
        }

    }    

    return NOTEXIST;

}

/*Message 转换为KEYVAL*/
KeyVal * mess_to_kv(Message mess,int flag,int len){
    
    KeyVal * temp = (KeyVal *)malloc(sizeof(KeyVal));
    int mess_type = mess.Type;
    int llen = strlen(mess.buff_key);
    dystr_create3(&temp->Key,mess.buff_key,llen);   /*注意这里要传入地址*/
    //printf("in create %s\n",temp->Key.dystr_data);
    int vlen = strlen(mess.buff_val);

    temp->hash = mess.hash;
    temp->db_id = mess.server_hash;
    temp->table_id = mess.hash % 100;
    temp->status   = ALIVE;
    temp->Type    = mess.Type;

    if(mess.Type == STRING){                              /*根据数据类型创建VAL的值*/
        
        temp->Val = (char *)malloc(sizeof(char)*vlen);
        strcpy(temp->Val,mess.buff_val);

    }else if(mess.Type == LIST){
        RLIST * clist;
        clist = (RLIST *)malloc(sizeof(RLIST));
        create_list(clist,mess);
        temp->Val = clist;

    }else{

        //pass
    }

    return temp;
}


/*添加KV到键值存储系统*/
int add_KV_DB(KeyVal * temp,int flag){
    
    KeyVal * node ;
    KeyVal * head ;
    KeyVal * Flag ;

    //printf("temp->db_id:%d,temp->table_id:%d\n",temp->db_id,temp->table_id);
    node = server_DB.ServerDB[temp->db_id].DB[temp->table_id];              /*获取头尾节点准备进行插入操作*/
    head = server_DB.ServerDB[temp->db_id].DB[temp->table_id];
    Flag = server_DB.ServerDB[temp->db_id].DB[temp->table_id];
    
    int index = server_DB.ServerDB[temp->db_id].sum_index[temp->table_id];
    server_DB.ServerDB[temp->db_id].sum_index[temp->table_id] += 1       ;  /*计数+1*/             
    int all = server_DB.ServerDB[temp->db_id].sum_index[temp->table_id]  ;  /*计数+1*/     

    //printf("index : %d,all :%d\n",index,all);

    if(index == 0){  /*如果是连存储第一个元素*/
        
        node ->next = temp;
        node ->tail = temp;
        temp->head  = head;
        temp->tail  = temp;
        temp->next  = NULL;
         
    }else{           /*非第一个元素*/

        for(int i = 0;i < index;i++){
            Flag = Flag->next;   
        }

        Flag->next = temp;
        node->tail = temp;
        Flag->tail = temp;
        temp->head = node;
        temp->next = NULL;

    }
    
    return 0;
    
}

KeyVal* GET(Message mess,int argc){

    if(EXIST(mess,argc) == KEXIST){
        
        int table_index = mess.hash % 100;
        int db_index    = mess.server_hash;
        int num_index   = server_DB.ServerDB[db_index].sum_index[table_index];
        KeyVal * temp = server_DB.ServerDB[db_index].DB[table_index];
        
        while(temp->next != NULL ){
            temp = temp->next;
            if(strcmp(mess.buff_key,temp->Key.dystr_data) == 0){
                print_kv(temp);
                return temp;
            }
        }

    }else{
        printf("this KV is not exist\n");
        /*不存在,返回为空，防止误操作*/
        return NULL;
    }


}


int DEL(Message mess,int argc){
    
    if(EXIST(mess,argc) == KEXIST){
        
        int table_index = mess.hash % 100 ;   /*存储表ID*/
        int db_index    = mess.server_hash;   /*数据库ID*/

        int num_index   = server_DB.ServerDB[db_index].sum_index[table_index];
        KeyVal * temp = server_DB.ServerDB[db_index].DB[table_index];
        
        while(temp->next != NULL ){
            temp = temp->next;
            if(strcmp(mess.buff_key,temp->Key.dystr_data) == 0){
                printf("DEL this key\n");
                temp->status = DEAD;
                return 1;
            }
        } 
        /*采用惰性删除的策略，不首先释放内存空间*/
        
    }else{

        /*不存在则返回NULL == 0，提示信息*/
        printf("this KV is NOTEXIST\n");
        return 0;
    }


}

/*打印所有的KV 内容,暂时*/

KeyVal * FINDALL(){
    
    int sum = 0;
    for(int i  = 0;i < 10;i++){
        for(int j = 0;j < 100;j++){
            if(server_DB.ServerDB[i].sum_index[j] != 0){
                KeyVal * temp = server_DB.ServerDB[i].DB[j];
                printf("ServerDB[%d].DB[%d] have %d KVs\n",i,j,server_DB.ServerDB[i].sum_index[j]);
                for(int k = 0;k < server_DB.ServerDB[i].sum_index[j];k++){
                    temp = temp->next;
                    if(temp != NULL){
                        print_kv(temp);
                        sum++;
                    }
                
                }
            }
        }    
    
    }


    printf("all database show you\n");
    printf("all database have %d\nKVs",sum);

    return NULL;

}



