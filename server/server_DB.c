/*************************************************************************
    > File Name: server_DB.c
    > Author: 
    > Mail: 
    > Created Time: 2018年04月14日 星期六 12时16分42秒
 ************************************************************************/
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#include"./server_DB.h"
#include"./server_str.h"
#include"./server_RDB.h"



Mair_DB server_DB;    /*全局数据存储系统*/

extern netmap NetMap;
extern int this_server_port;  /*本机端口*/

//int virtual_off = 0;

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


int database_choice(Message mess,char * order,int hash,int fd){
    
    int Flag = mess.Type;
    if((Flag == STRING)||(Flag == COMMON)){
        if((strcmp(mess.buff_mo,"SET") == 0) || (strcmp(mess.buff_mo,"set") == 0)){
            SET(mess,0,fd);
            return STRING;
        }else if((strcmp(mess.buff_mo,"EXIST") == 0) || (strcmp(mess.buff_mo,"exist") == 0)){
            EXIST(mess,0,fd);
            return STRING;
        }else if((strcmp(mess.buff_mo,"GET") == 0) || (strcmp(mess.buff_mo,"get") == 0)){
            GET(mess,0,fd);
	        return STRING;
        }else if((strcmp(mess.buff_mo,"DEL") == 0) || (strcmp(mess.buff_mo,"del") == 0)){
            DEL(mess,0,fd);
	        return STRING;
        }else if((strcmp(mess.buff_mo,"TRANS") == 0) || (strcmp(mess.buff_mo,"trans") == 0)){
            //printf("已经接受分布式转发"\n);
            ADD(mess,0,fd);   
            return STRING;
        }else{
            //pass
        }
    }else if(Flag == INT){
            //pass
    }else if((Flag == LIST)||(Flag == COMMON)){

	    if((strcmp(mess.buff_mo,"CLIST") == 0) || (strcmp(mess.buff_mo,"clist") == 0)){
            CLIST(mess,0,fd);
            return LIST;
        }else if((strcmp(mess.buff_mo,"LSET") == 0) || (strcmp(mess.buff_mo,"lset") == 0)){
            LSET(mess,0,fd);
            return LIST;
        }else if((strcmp(mess.buff_mo,"RDEL") == 0) || (strcmp(mess.buff_mo,"RDEL") == 0)){
            RDEL(mess,0,fd);
            print_list(NULL);
	        return LIST;
        }else if((strcmp(mess.buff_mo,"LPUSH") == 0) || (strcmp(mess.buff_mo,"LPUSH") == 0)){
            LPUSH(mess,0,fd);
            print_list(NULL);
	        return LIST;
        }else if((strcmp(mess.buff_mo,"LPOP") == 0) ||(strcmp(mess.buff_mo,"lpop") == 0)){
            LPOP(mess,0,fd);
            return LIST;
        }else if((strcmp(mess.buff_mo,"EXIST") == 0) || (strcmp(mess.buff_mo,"exist") == 0)){
            EXIST(mess,0,fd);
            return LIST;
        }else{
            //pass
        }

    }else if(Flag == ZLIST){

    }else if(Flag == SERVER){
        
	    if((strcmp(mess.buff_mo,"ADDNODE") == 0) || (strcmp(mess.buff_mo,"addnode") == 0)){
                int port = atoi(mess.buff_val);
                if(port == this_server_port){
                    return SERVER;
                }
                ADDNODE(mess,0,fd);
                REWRITEFILE();
                DATA_TRANS(this_server_port);
                //printf("已经执行分布式转发\n");
                //test_net();
                return SERVER;
        }else if((strcmp(mess.buff_mo,"DELNODE") == 0) || (strcmp(mess.buff_mo,"delnode") == 0)){
                DELNODE(mess,0,fd);
                REWRITEFILE();
                int port = atoi(mess.buff_val);
                if(port == this_server_port){
                    printf("I will down\n");
                    DATA_TRANS(this_server_port);
                }
                //printf("已经执行分布式转发\n");
                test_net();
                return SERVER;
        }else if((strcmp(mess.buff_mo,"SCHUNK") == 0) || (strcmp(mess.buff_mo,"schunk") == 0)){
                SCHUNK(mess,0,fd);
                return SERVER;
        }else if((strcmp(mess.buff_mo,"UPDATE") == 0) || (strcmp(mess.buff_mo,"update") == 0)){
                UPDATE(mess,0,fd);
                return SERVER;
        }else if((strcmp(mess.buff_mo,"RDB") == 0) || (strcmp(mess.buff_mo,"rdb") == 0)){
                all_rdb();                    /*遍历一遍内存数据库，将数据存储到文件中*/
                writetofilenow(RDB);          /*将内存中的剩余的没有写入文件的数据，写入文件*/
                return SERVER;
        }else if((strcmp(mess.buff_mo,"AOF") == 0) || (strcmp(mess.buff_mo,"aof") == 0)){
               readfromfile(AOF);
               return SERVER;
        }else if((strcmp(mess.buff_mo,"SHOW") == 0) || (strcmp(mess.buff_mo,"show") == 0)){
                FINDALL();
                return SERVER;
        }else if((strcmp(mess.buff_mo,"BRDB") == 0) || (strcmp(mess.buff_mo,"brdb") == 0)){
                readfromfile(RDB);            /*从文件中恢复数据*/
                return SERVER;
        }else if((strcmp(mess.buff_mo,"SHUTDOWN") == 0) || (strcmp(mess.buff_mo,"shutdown") == 0)){
                readfromfile(AOF);           /*服务器结束服务时，保存内存中的数据*/
                exit(0);
                return SERVER;
        }else if((strcmp(mess.buff_mo,"TRANS") == 0) || (strcmp(mess.buff_mo,"trans") == 0)){
                
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

int echo_bc(int fd){
    
    char * buf = "OK,setval";
    send(fd,buf,20,0);



}

/*数据迁移服务开始*/
/*1.修改路由表，包括其中的范围,在上一级操作中已经修改完成*/
/*2.根据范围的修改遍历，将相应的数据进行转发*/


int DATA_TRANS(int temp){
    

    int i = 0;
    int j = 0;
    int sum = 0;
    for(int i  = 0;i < 10;i++){
        for(int j = 0;j < 100;j++){
            if(server_DB.ServerDB[i].sum_index[j] != 0){
                KeyVal * temp = server_DB.ServerDB[i].DB[j];
                //printf("ServerDB[%d].DB[%d] have %d KVs\n",i,j,server_DB.ServerDB[i].sum_index[j]);
                for(int k = 0;k < server_DB.ServerDB[i].sum_index[j];k++){
                    temp = temp->next;
                    if(temp != NULL && temp->status != DEAD){

                        /*将内存数据转换成Message 消息*/
                        Message * mess = kv_to_mess(temp,NULL,0);
                        /*将数据转发到相应的服务器中*/
                        send_to_server(mess,NULL,0);
                        
                        sum++;
                    }
                
                }
            }
        }    
    
    }

    

    return 0;


}


/*仅仅是接口有变化，使用Message 指针接口*/

/*
int database_choice2(Message *mess,char * order,int hash,int fd){
    


    int Flag = mess->Type;
    if((Flag == STRING)||(Flag == COMMON)){
        if((strcmp(mess->buff_mo,"SET") == 0) || (strcmp(mess->buff_mo,"set") == 0)){
            SET(mess,0,fd);
            return STRING;
        }else if((strcmp(mess->buff_mo,"EXIST") == 0) || (strcmp(mess->buff_mo,"exist") == 0)){
            EXIST(mess,0,fd);
            return STRING;
        }else if((strcmp(mess->buff_mo,"GET") == 0) || (strcmp(mess->buff_mo,"get") == 0)){
            GET(mess,0,fd);
	    return STRING;
        }else if((strcmp(mess->buff_mo,"DEL") == 0) || (strcmp(mess->buff_mo,"del") == 0)){
            DEL(mess,0,fd);
	    return STRING;
        }else{
            //pass;
        }
    }else if(Flag == INT){
            //pass
    }else if((Flag == LIST)||(Flag == COMMON)){

	    if((strcmp(mess->buff_mo,"CLIST") == 0) || (strcmp(mess->buff_mo,"clist") == 0)){
            CLIST(mess,0,fd);
            return LIST;
        }else if((strcmp(mess->buff_mo,"LSET") == 0) || (strcmp(mess->buff_mo,"lset") == 0)){
            LSET(mess,0,fd);
            return LIST;
        }else if((strcmp(mess->buff_mo,"RDEL") == 0) || (strcmp(mess->buff_mo,"RDEL") == 0)){
            RDEL(mess,0,fd);
            print_list(NULL);
	    return LIST;
        }else if((strcmp(mess->buff_mo,"LPUSH") == 0) || (strcmp(mess->buff_mo,"LPUSH") == 0)){
            LPUSH(mess,0,fd);
            print_list(NULL);
	    return LIST;
        }else if((strcmp(mess->buff_mo,"LPOP") == 0) ||(strcmp(mess->buff_mo,"lpop") == 0)){
            LPOP(mess,0,fd);
            return LIST;
        }else if((strcmp(mess->buff_mo,"EXIST") == 0) || (strcmp(mess->buff_mo,"exist") == 0)){
            EXIST(mess,0,fd);
            return LIST;
        }else{
            //pass
        }

    }else if(Flag == ZLIST){

    }else if(Flag == SERVER){
        
	    if((strcmp(mess->buff_mo,"ADDNODE") == 0) || (strcmp(mess->buff_mo,"addnode") == 0)){
                ADDNODE(mess,0,fd);
                REWRITEFILE();
                DATA_TRANS();
                return SERVER;
        }else if((strcmp(mess->buff_mo,"DELNODE") == 0) || (strcmp(mess->buff_mo,"delnode") == 0)){
                DELNODE(mess,0,fd);
                REWRITEFILE();
                return SERVER;
        }else if((strcmp(mess->buff_mo,"SCHUNK") == 0) || (strcmp(mess->buff_mo,"schunk") == 0)){
                SCHUNK(mess,0,fd);
                return SERVER;
        }else if((strcmp(mess->buff_mo,"UPDATE") == 0) || (strcmp(mess->buff_mo,"update") == 0)){
                UPDATE(mess,0,fd);
                return SERVER;
        }else if((strcmp(mess->buff_mo,"RDB") == 0) || (strcmp(mess->buff_mo,"rdb") == 0)){
                //RDB()
                return SERVER;
        }else if((strcmp(mess->buff_mo,"AOF") == 0) || (strcmp(mess->buff_mo,"aof") == 0)){
               readfromfile(AOF);
               return SERVER;
        }else if((strcmp(mess->buff_mo,"SHOW") == 0) || (strcmp(mess->buff_mo,"show") == 0)){
               FINDALL();
               return SERVER;

        }else{

        }

    }else if(Flag == WATCH){
        
    }else{
        //pass
    }
    
    return 0;

}
*/


Message * kv_to_mess(KeyVal * temp,char *temp2,int temp3){
    
    Message * mess = (Message *)malloc(sizeof(Message));
    memset((char *)mess,0,sizeof(Message));
    strcpy(mess->buff_mo,"TRANS");
    strcpy(mess->buff_key,temp->Key.dystr_data);
    strcpy(mess->buff_val,temp->Val);

    mess->hash = temp->hash;
    mess->Type = temp->Type;
    mess->server_hash = temp->server_hash;
    
    strcpy(mess->oob,"TRANS");

    return mess;
}


int send_to_server(Message * mess,char * temp2,int temp3){
    
    int hash = mess->hash;
    int sfd;
    sfd = get_socket(hash);
    write(sfd,(char *)mess,sizeof(Message));
    close(sfd);
    return 0;

}


int get_socket(int hash){

    int sockfd;
    int i = 0;
    struct sockaddr_in servaddr;

    netinfo * tem;
    netinfo * cn;
    cn = NetMap.networkmap;
    tem = cn;
    
   tem = find_sends_node(hash);              /*寻找合适的转发节点fd:服务器个数总数，temp:哈希值*/
   if(tem == NULL){
        printf("can not find node %d\n",__LINE__);
        printf("tem = head\n");
        tem = cn;
    }
    printf("this kv is send to %s:%d\n",tem->ip_char,tem->port_int);
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(tem->port_int);
    inet_pton(AF_INET,tem->ip_char,&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    return sockfd;
    
    
}


netinfo * find_sends_node(int hash){

    netinfo * temp = NULL;
    int re_hash = hash % LIMIT;        /*LIMIT表示哈希散列区间最大值，由此挑选出应当发送的服务器*/
    //if(virtual_off == 0){
        temp = find_real_node(re_hash);
        return temp;
    /*}else if(virtual_off == 1){
        temp = find_virtual_node(re_hash);
        if(temp == NULL){
            temp = find_real_node(re_hash);
        }
        return temp;
    }else{
        //pass
    }*/


}

netinfo * find_reals_node(int hash){

    netinfo * index = NetMap.networkmap;
    while(index != NULL){
    
        if(hash >= index->hash_start && hash <= index->hash_end){
            
            return index;
        }    
        index = index->next;
    }
    return index;
}

netinfo * find_virtuals_node(int hash){
    
    netinfo * index = NetMap.networkmap;
    while(index != NULL){
        
        if(hash >= index->hash_start && hash <= index->hash_end){
            
            return index;
        }
        index = index->next;
    }
    return index;


}

