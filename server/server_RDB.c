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
        return index;

    }else if(type == RDB){
        
        KeyVal * kv = (KeyVal *)temp;
        strcpy(index->buff_mo,"RDB");
        strcpy(index->buff_key,kv->Key.dystr_data);
        strcpy(index->buff_val,((char *)kv->Val));
        index->hash = kv->hash;
        index->Type = kv->Type;
        return index;

    }else{
        //pass
    }

    

}


/*初始化AOF 和 RDB*/
int init_log(int Type){
    
    LOGAOF.sum = 0;
    LOGAOF.free = BUFFSIZE;
    for(int i = 0;i < BUFFSIZE;i++){

        memset(((char *)&(LOGAOF.buff[i])),0,sizeof(LOG));

    }
    
    LOGRDB.sum = 0;
    LOGRDB.free = BUFFSIZE;
    for(int j = 0;j < BUFFSIZE;j++){
        
        memset(((char *)&(LOGAOF.buff[j])),0,sizeof(LOG));

    }


}


int w_aof(void * temp,int flag,int Type){
    
    int sum = LOGAOF.sum;
    if(sum < BUFFSIZE){  
        LOG * obj = log_create(temp,flag,Type);
        memcpy((void *)&(LOGAOF.buff[sum]),obj,sizeof(LOG));
        LOGAOF.sum++;
        LOGAOF.free--;
    }else{
        //writetofile;
        LOG * obj = log_create(temp,flag,Type);
        memcpy((void *)&(LOGAOF.buff[sum]),obj,sizeof(LOG));
        LOGAOF.sum++;
        LOGAOF.free--;
    }

}


int all_rdb(){
    
    int i = 0;
    int j = 0;
    for(i = 0;i < index1;i++){
        for(j = 0;j < index2;j++){
            
            //writetofile();
        }
    }


}




int writetofile(int Type){
    
    FILE *fp;

    if(Type == RDB){
        fp = fopen("RDB","w+");
        for(int i = 0;i < LOGRDB.sum;i++){
            //写入文件；
        }


    }else if(Type == AOF){



    }


}

int readfromfile(int Type){



}
