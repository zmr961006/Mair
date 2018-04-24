/*************************************************************************
	> File Name: rlist.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月24日 星期二 12时24分21秒
 *************************************************************************/


#include"./rlist.h"
#include"./server_str.h"

extern Mair_DB  server_DB;

//设置链表 LSIT KEY LEN
int CLIST(Message mess,int flag){
    
    printf("IN CLIST\n");
    if(EXIST(mess,0) == NOTEXIST){
    
        KeyVal * temp = mess_to_kv(mess,0,0);
        add_KV_DB(temp,0);
        FINDALL();

    }else{
        
        printf("This KV is already EXIST\n");
    }



}

//将KEY小标为INDEX的元素设置为VALUE; LSET KEY INDEX:VALE
int LSET(Message mess,int flag){
    
}

//删除LIST 中的某个元素;删除某个列表中的元素; LDEL KEY VALUE
int RDEL(Message mess,int flag){

    
}

//增加尾部的一个元素    LPUSH  key value
int LPUSH(Message mess,int flag){

    if(EXIST(mess,0) != NOTEXIST){
        printf("IN LPUSH\n");       
        //FINDALL();
        int table_index = mess.hash % 100;
        int db_index    = mess.server_hash;
        int num_index   = server_DB.ServerDB[db_index].sum_index[table_index];
        KeyVal * temp   = server_DB.ServerDB[db_index].DB[table_index];
        printf("SDB[%d].DB[%d]\n",db_index,table_index);
        //print_kv(temp->next);
        for(int k = 0; k < server_DB.ServerDB[db_index].sum_index[table_index];k++){
            temp = temp->next;
            if(temp != NULL){  
                if(strcmp(mess.buff_key,temp->Key.dystr_data) == 0){
                    //print_kv(temp);
                    printf("I want  find BUG\n");
                    strcpy(((RLIST*)(temp->Val))->data[((RLIST*)(temp->Val))->use_node + 1],mess.buff_val);
                    ((RLIST*)(temp->Val))->free_node--;
                    ((RLIST*)(temp->Val))->use_node++;
                    printf("push finish\n");
                    return 0;
                }
            }
        
        }
    
    }else{
        
        printf("This KV is not  EXIST\n");
    }
    
}

//删除第一个元素        LPOP   key value
int LPOP(Message mess,int flag){
    

}

/*创建头结点后向内容中添加元素*/

int create_list(RLIST * temp,Message mess){

    int list_len = atoi(mess.buff_val);
    int elem = list_len * 2;
    temp->data = (char **)malloc(sizeof(char *)*elem);
    for(int i  = 0;i < elem ;i++){
        temp->data[i] = (char *)malloc(sizeof(char)*50);
    }
    temp->elem_num  = 0;
    temp->free_node = LISTLEN;
    temp->use_node  = 0;
    temp->flag      = 0;
    temp->type      = 0;
    return 0;

}


