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

/*打印KV*/

int print_kv(KeyVal * temp){
    
    printf("P_KV\n");
    printf("|key|val|hash|db_index|tab_index|online|\n");
    printf("|%s|%s|%d|%d|%d|%d|\n",temp->Key.dystr_data,temp->Val,temp->hash,temp->db_id,temp->table_id,temp->status);
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




