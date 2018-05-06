/*************************************************************************
	> File Name: server_watch.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月15日 星期日 12时06分10秒
 ************************************************************************/

#include"./server_watch.h"

/*检测模块*/

extern Mair_DB server_DB;

/*打印MESS*/

int print_mess(Message mess){
    
    printf("P_MS\n");
    printf("|order|Key|Vale|Type|Hash|\n");
    printf("|%s|%s|%s|%d|%d|\n",mess.buff_mo,mess.buff_key,mess.buff_val,mess.Type,mess.hash);
    return 0;

}

int print_mess2(Message * mess){  

    printf("*******************************\n");
    printf("|order|Key|Vale|Type|Hash|\n");
    printf("|%s|%s|%s|%d|%d|\n",mess->buff_mo,mess->buff_key,mess->buff_val,mess->Type,mess->hash);
    printf("*******************************\n");
    return 0;
}


/*打印KV*/

int print_kv(KeyVal * temp){
    
    printf("P_KV\n");
    printf("|key|val|hash|db_index|tab_index|online|TYPE|\n");
    printf("|%s|%s|%d|%d|%d|%d|%d|\n",temp->Key.dystr_data,temp->Val,temp->hash,temp->db_id,temp->table_id,temp->status,temp->Type);
    return 0;

}



/*打印数据库存储情况,并且统计总数*/

int print_dbnum(){
    
    int sum = 0;

    for(int i = 0;i < 10;i++){
        for(int j = 0;j < 100;j++){
            if(server_DB.ServerDB[i].sum_index[j] != 0){
                printf("%d database; %d tablelist ;exist %d KVs\n",i,j,server_DB.ServerDB[i].sum_index[j]);
                sum += server_DB.ServerDB[i].sum_index[j];
            }
            
        }
    }    

    printf("all Database have %d KVs\n",sum);
    return sum;
}


int print_list(){
    int sum = 0;
    for(int i = 0;i < 10;i++){
        for(int j = 0;j < 100;j++){
            if(server_DB.ServerDB[i].sum_index[j] != 0){
                int index = server_DB.ServerDB[i].sum_index[j];
                KeyVal * temp = server_DB.ServerDB[i].DB[j];
                 for(int k = 0;k < server_DB.ServerDB[i].sum_index[j];k++){
                    temp = temp->next;
                    print_kv(temp);
                    
                    if((temp != NULL) && (temp->Type == LIST)){
                        printf("i want do somthing\n");
				        int unode = ((RLIST *)(temp->Val))->use_node;
                        for(int k = 0; k < LISTLEN;k++){
                            if(((RLIST*)(temp->Val))->bitmap[k] != 0){  
                                printf("Lval:%s\n",((RLIST*)(temp->Val))->data[k]);
                            }
                        }
                        //print_kv(temp);
                        sum++;
                    }
                
                }
                            
            }
        }   
            
    }
        

    //printf("all Database have %d KVs\n",sum);
    return sum;



}

int print_klist(RLIST  * temp){
    
    


}
