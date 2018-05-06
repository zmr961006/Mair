/*************************************************************************
	> File Name: server_RDB.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月04日 星期五 09时33分33秒
 ************************************************************************/

#include<stdio.h>
#include"./server_RDB.h"


extern Mair_DB server_DB;



/*日志类缓存结构*/

/*日志存储*/
LOGBUFF LOGAOF;

/*内存DUMP存储*/
LOGBUFF LOGRDB;


LOG * log_create(void * temp,int type,int flag){

    LOG * index = (LOG *)malloc(sizeof(LOG));

    if(type == AOF){
        
        Message *mess = (Message * )temp;
        strcpy(index->buff_mo,mess->buff_mo);
        strcpy(index->buff_key,mess->buff_key);
        strcpy(index->buff_val,mess->buff_val);
        strcpy(index->oob,mess->oob);
        index->hash = mess->hash;
        index->Type = mess->Type;
        index->server_hash = mess->server_hash;
        index->AOF_RDB = AOF;
        return index;

    }else if(type == RDB){
        
        KeyVal * kv = (KeyVal *)temp;
        strcpy(index->buff_mo,"RDB");
        strcpy(index->buff_key,kv->Key.dystr_data);
        strcpy(index->buff_val,((char *)(kv->Val)));
        index->hash = kv->hash;
        index->Type = kv->Type;
        index->Code = kv->Code;
        index->table_id = kv->table_id;
        index->db_id    = kv->db_id;
        index->status   = kv->status;
        index->AOF_RDB  = RDB;

        return index;
    }else{
        //pass
    }

    

}


/*初始化AOF 和 RDB*/
int init_log(int Type){
 
    if(Type == AOF){  
        LOGAOF.sum = 0;
        LOGAOF.free = BUFFSIZE;
        for(int i = 0;i < BUFFSIZE;i++){

            memset(((char *)&(LOGAOF.buff[i])),0,sizeof(LOG));

        }
        printf("init %d %d\n",LOGAOF.sum,LOGAOF.free);       
        return 0;
    }else{  
    
        LOGRDB.sum = 0;
        LOGRDB.free = BUFFSIZE;
        for(int j = 0;j < BUFFSIZE;j++){
        
            memset(((char *)&(LOGRDB.buff[j])),0,sizeof(LOG));

        }
        return 0;
    }
}


int w_aof(void * temp,int flag,int Type){
    
    int sum = LOGAOF.sum;
    if(sum == BUFFSIZE){
        
        writetofile(AOF);
        init_log(AOF);
        LOG * obj = log_create(temp,AOF,Type);
        memcpy((void *)&(LOGAOF.buff[LOGAOF.sum]),obj,sizeof(LOG));
        LOGAOF.sum++;
        LOGAOF.free--;
    
    }else{
        
        LOG * obj = log_create(temp,AOF,Type);
        memcpy((void *)&(LOGAOF.buff[LOGAOF.sum]),obj,sizeof(LOG));
        LOGAOF.sum++;
        LOGAOF.free--;
    }
    watch_log(AOF);
    //readfromfile(AOF);
    printf("in w_aof: %d %d\n",LOGAOF.sum,LOGAOF.free);

}

int w_rdb(void * temp,int flag,int Type){  
    
    int sum = LOGRDB.sum;
    if(sum == BUFFSIZE){ 

        writetofile(RDB);
        init_log(RDB);
        LOG * obj = log_create(temp,RDB,Type);
        memcpy((void *)&(LOGRDB.buff[LOGRDB.sum]),obj,sizeof(LOG));
        LOGRDB.sum++;
        LOGRDB.free--;
        
    }else{
        
        LOG * obj = log_create(temp,RDB,Type);
        memcpy((void *)&(LOGRDB.buff[LOGRDB.sum]),obj,sizeof(LOG));
        LOGRDB.sum++;
        LOGRDB.free--;
    }


}


int all_rdb(){
    
    int i = 0;
    int j = 0;
    int sum = 0;
    for(int i  = 0;i < 10;i++){
        for(int j = 0;j < 100;j++){
            if(server_DB.ServerDB[i].sum_index[j] != 0){
                KeyVal * temp = server_DB.ServerDB[i].DB[j];
                printf("ServerDB[%d].DB[%d] have %d KVs\n",i,j,server_DB.ServerDB[i].sum_index[j]);
                for(int k = 0;k < server_DB.ServerDB[i].sum_index[j];k++){
                    temp = temp->next;
                    if(temp != NULL && temp->status != DEAD){
                        w_rdb(temp,RDB,0);
                        sum++;
                    }
                
                }
            }
        }    
    
    }


}




int writetofile(int Type){
    
    FILE *fp;

    if(Type == RDB){
        fp = fopen("RDB","w");
        for(int i = 0;i < LOGRDB.sum;i++){
            fwrite((char *)&LOGRDB.buff[i],sizeof(LOG),1,fp);
        }
        fclose(fp);
        init_log(RDB);
        return 0;
    }else if(Type == AOF){
        fp = fopen("AOF","a");
        for(int j = 0;j < LOGAOF.sum;j++){
            fwrite((char *)&LOGAOF.buff[j],sizeof(LOG),1,fp);
        }
        fclose(fp);
        init_log(AOF);
        return 0;
    }

}


/*将当前剩余的内存数据全部刷入文件中加以保存*/
int writetofilenow(int Type){
    
	FILE *fp;

    if(Type == RDB){
        fp = fopen("RDB","w");
        for(int i = 0;i < LOGRDB.sum;i++){
            fwrite((char *)&LOGRDB.buff[i],sizeof(LOG),1,fp);
        }
        fclose(fp);
        init_log(RDB);
        return 0;
    }else if(Type == AOF){
        
        if(LOGAOF.sum == 0){
            return -1;
        }

        fp = fopen("AOF","a");
        for(int j = 0;j < LOGAOF.sum;j++){
            fwrite((char *)&LOGAOF.buff[j],sizeof(LOG),1,fp);
        }
        fclose(fp);
        init_log(AOF);
        return 0;
    }

    
}








/*从文件中读取出写入的信息*/
int readfromfile(int Type){


    /*读取文件之前需要将内存中的数据首先刷进文件中*/

    writetofilenow(Type);

    FILE * fp;
    int sum = 0;
    if(Type == AOF){
        fp = fopen("AOF","r");
        LOG temp;
        //printf("###############################1\n");
        while((fread(&temp,sizeof(LOG),1,fp) > 0)){
            sum++;
            //需要将文件中的数据重新恢复到数据存储系统中；
            Message *mess;
            mess = log_to_mess(&temp,0,0);
            //printf("##########################2\n");
            print_mess2(mess);  
        }
        printf("all %d LOGS\n",sum);
        fclose(fp);
        return 0;
    }else if(Type == RDB){
        fp = fopen("RDB","r");
        LOG temp;
        while((fread(&temp,sizeof(LOG),1,fp) > 0)){
            //需要将文件中的数据重新恢复到数据存储系统中；  
            sum++;

        }
        printf("all %d LOGS\n",sum);
        fclose(fp);
        return 0;
        
    }else{
        //pass
    }

}

int watch_log(int Type){
    
    if(Type == AOF){
        
        for(int i = 0;i < LOGAOF.sum;i++){  

            printf("LOGAOF:%s %s %s\n",LOGAOF.buff[i].buff_mo,LOGAOF.buff[i].buff_key,LOGAOF.buff[i].buff_val);

        }

    }else if(Type == RDB){
        
        for(int j = 0; j < LOGRDB.sum;j++){
            
            printf("LOGRDB:%s %s %d\n",LOGRDB.buff[j].buff_key,LOGRDB.buff[j].buff_val,LOGRDB.buff[j].hash);

        }

    }else{

        //pass


    }

    return 0;
}


/*log 转换为 mess*/

Message * log_to_mess(LOG * temp,int flag,int Type){
 
    Message  * index  = (Message *)malloc(sizeof(Message));
    strcpy(index->buff_mo,temp->buff_mo);
    strcpy(index->buff_key,temp->buff_key);
    strcpy(index->buff_val,temp->buff_val);
    index->hash = temp->hash;
    index->Type = temp->Type;
    index->server_hash = temp->server_hash;

    return index;

}

/*log 转换为 Kv*/
KeyVal  * log_to_kv(LOG * temp,int flag,int Type){
    
    KeyVal * index = (KeyVal *)malloc(sizeof(Message));
    //copy temp to index;
    return index;

}




