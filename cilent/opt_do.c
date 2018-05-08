/*************************************************************************
	> File Name: opt_do.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 14时46分27秒
 ************************************************************************/

#include"./opt_do.h"
#include"./order.h"
#include"./message.h"
#include"./cilent_sock.h"
#include"./read_pro.h"

#include<unistd.h>

extern netmap NetMap;
extern int    server_id;
order orders;


char buf_in[BUFFLEN];     /*指令缓冲*/
char buf_oder[ODER];      /*命令缓冲*/
char buf_key[KEYLEN];     /*KEY 缓冲*/
char buf_val[VALLEN];     /*VAL缓冲*/

int  server_id = 0 ;      /*数据库默认ID 为0号*/


int init_cilent(){

    orders.orders[0] = "DEL";
    orders.orders[1] = "GET";
    orders.orders[2] = "SET";
    orders.orders[3] = "del";
    orders.orders[4] = "get";
    orders.orders[5] = "set";
    orders.orders[6] = "EXIST";
    orders.orders[7] = "exist";
    orders.orders[8] = "ADDNODE";
    orders.orders[9] = "addnode";
    orders.orders[10]= "DELNODE";
    orders.orders[11]= "delnode";
    
    orders.orders[12] = "CLIST";
    orders.orders[13] = "rlist";
    orders.orders[14] = "LSET";
    orders.orders[15] = "lset";
    orders.orders[16] = "RDEL";
    orders.orders[17] = "rdel";
    orders.orders[18] = "LPUSH";
    orders.orders[19] = "lpush";
    orders.orders[20] = "LPOP";
    orders.orders[21] = "lpop";
    orders.orders[22] = "SCHUNK";
    orders.orders[23] = "schunk";

    orders.orders[24] = "AOF";
    orders.orders[25] = "aof";
    orders.orders[26] = "RDB";
    orders.orders[27] = "rdb";
    orders.orders[28] = "SHOW";
    orders.orders[29] = "show";
    orders.orders[30] = "BRDB";
    orders.orders[31] = "brdb";
    orders.orders[32] = "shutdown";
    orders.orders[33] = "SHUTDOWN";

    orders.num = 34;

}

int opt(char * temp1,char *temp2,int argc){    /*客户端数据处理流程*/

    int start = 1;
    int flag  = 1;
    int loop  = 1;



    while(loop){
        memset(buf_in,0,BUFFLEN);
        fflush(stdin);
        printf(">>");
        fgets(buf_in,BUFFLEN,stdin);
        buf_in[BUFFLEN-1] = '\0';
    
        flag = chunk(buf_in);
        if(flag == 0){
            printf("erro styn\n");
            exit(0);
        }
        loop = do_send(argc);
        if(loop == 0){
            break;
        }
    }

}

int chunk(char * temp1){          /*检查命令是否合理*/
    
   
    memset(buf_oder,0,ODER);
    memset(buf_key,0,KEYLEN);
    memset(buf_val,0,VALLEN);
    int i = 0,j = 0;
    int flag = 0;
    for(i = 0;i < BUFFLEN ;i++){
        if(buf_in[i] != ' '){
            if(flag == 0){
                buf_oder[j] = buf_in[i];
                j++;
            }


            if(flag == 1){
                buf_key[j] = buf_in[i];
                j++;
            }

            if(flag == 2){
                buf_val[j] = buf_in[i];
                j++;
            }

        }else{
            j = 0;
            if(buf_in[i+1] != ' '){
                flag++;
            }
            continue;
        }
        
    }

    //printf("%s\n%s\n%s\n",buf_oder,buf_key,buf_val);    //test order
    int len = strlen(buf_oder);   
    int table;
    //for(table = 0;table < 3;table++){                   //test order
      //  printf("%s\n",orders.orders[table]); 
    //}
    //printf("all : %d\n",orders.num);
    int index,back_val = 0;
    for(index = 0;index < orders.num;index++){
        if(strcmp(buf_oder,orders.orders[index]) == 0){
            //printf("LLLLLLLL\n");
            back_val = 1;
        }
        //printf("%s\n%s\n",buf_oder,orders.orders[i]);
    }
    return back_val;

}



int do_send(int fd){        /*根据哈希值发送数据*/

    Message message;
    Message bcmess;
    int hash = 0;
    int len  = strlen(buf_key);
    int vlen = strlen(buf_val);
    int sfd;
    int server_num = 0;
    int distribute = 0;
    int r1 = 0;
    int r2 = 0;
    //hash = get_hash(buf_key,len);
    memcpy(message.buff_mo,buf_oder,ODER);
    memcpy(message.buff_key,buf_key,KEYLEN);
    memcpy(message.buff_val,buf_val,VALLEN);
    if(vlen == 0){
        message.buff_val[vlen]   = '\0';   
        message.buff_key[len-1] = '\0';
    }else{  
        message.buff_val[vlen-1] = '\0';
        
    }
    //printf("val %s len %d\n",message.buff_val,vlen);
    int klen = strlen(message.buff_key);
    hash = get_hash(message.buff_key,klen);
    //hash = get_hash(buf_key,len);
    printf("%d\n",hash);
    //get_time();
    server_num = get_server(hash);
    message.hash = hash;
    message.flag = ALIVE;
    message.Type = get_ordernum(buf_oder);        /*获取命令类型*/
    message.server_hash = server_id;              /*默认在0号数据库*/
    
    distribute = do_local(message.Type,message);  /*与服务器操作相关的预处理操作*/  
    if(distribute > 0){                           /*分布式转发需要广播到所有的服务器*/
        write_all(message,distribute);
        return 1;
    }
    if(distribute < 0){                           /*检查网络转发表是否一致*/
        chunk_network(message,distribute);
        //close(sfd);
        return 1;
    }
     
    r1 = rdb_aof_send(message,distribute);
    if(r1 == 1){
        return 1;
    }
    
    r2 = show_shut_send(message,distribute);
    if(r2 == 1){
        return 1;
    }

    sfd = get_socket(server_num,hash);
    write(sfd,(char *)&message,sizeof(message));
    recv(sfd,(void *)&bcmess,sizeof(bcmess),0);         /*接受返回数据*/
    print_bc(bcmess);
    //printf("server : %d\n",server_num);
    //sleep(1);
    close(sfd);
    //printf("OK,%s %s %s\n",message.buff_mo,message.buff_key,message.buff_val);
    return 1;

}

int _send_to(int fd,Message mess){
    




}

/*Murrem2 哈希算法*/

int get_hash(char *data,int len){

    int  h, k;
 
    h = 0 ^ len;
 
    while (len >= 4) {
        k = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;
 
        k *= 0x5bd1e995;
        k ^= k >> 24;
        k *= 0x5bd1e995;
 
        h *= 0x5bd1e995;
        h ^= k;
 
        data += 4;
        len -= 4;
    }
 
    switch (len) {
            case 3:
                h ^= data[2] << 16;
            case 2:
                h ^= data[1] << 8;
            case 1:
                h ^= data[0];
                h *= 0x5bd1e995;
    }
 
    h ^= h >> 13;
    h *= 0x5bd1e995;
    h ^= h >> 15;
 
    return h;


}

int get_server(int hash){
    

    return (hash % NetMap.node_num);

}


int get_ordernum(char * order){
    
    if((strcmp(order,"SET") == 0) || (strcmp(order,"set") == 0)){

        return STRING;

    }else if((strcmp(order,"EXIST") == 0) || (strcmp(order,"exist") == 0)){

        return COMMON;

    }else if((strcmp(order,"DEL") == 0) || (strcmp(order,"del") == 0)){
    
        return STRING;

    }else if((strcmp(order,"GET") == 0) || (strcmp(order,"get") == 0)){
        
        return STRING;

    }else if((strcmp(order,"ADDNODE") == 0) || (strcmp(order,"addnode") == 0)){
    
        return SERVER;

    }else if((strcmp(order,"DELNODE") == 0) || (strcmp(order,"delnode") == 0)){
    
        return SERVER;

    }else if((strcmp(order,"SCHUNK") == 0) || (strcmp(order,"schunk") == 0)){
    
        return SERVER;

    }else if((strcmp(order,"CLIST") == 0) || (strcmp(order,"clist") == 0)){

        return LIST;

    }else if((strcmp(order,"LSET") == 0) || (strcmp(order,"lset") == 0)){
    
        return LIST;

    }else if((strcmp(order,"RDEL") == 0) || (strcmp(order,"rdel") == 0)){
        
        return LIST;

    }else if((strcmp(order,"LPUSH") == 0) || (strcmp(order,"lpush") == 0)){
    
        return LIST;

    }else if((strcmp(order,"LPOP") == 0) || (strcmp(order,"lpop") == 0)){
    
        return LIST;
        
    }else if((strcmp(order,"RDB") == 0) || (strcmp(order,"rdb") == 0)){
        
        return SERVER;
    
    }else if((strcmp(order,"AOF") == 0) || (strcmp(order,"aof") == 0)){
        
        return SERVER;

    }else if((strcmp(order,"SHOW") == 0) || (strcmp(order,"show") == 0)){
        
        return SERVER;
    }else if((strcmp(order,"BRDB") == 0) || (strcmp(order,"brdb") == 0)){
        
        return SERVER;
    }else{
        //pass ;
    }
    

}


/*本地网络转发预处理*/
int do_local(int Type,Message message){
    
    if(Type == SERVER){
        if(strcmp(message.buff_mo,"ADDNODE") == 0 || strcmp(message.buff_mo,"addnode") == 0){

            ADDNODE(message,0);
            REWRITEFILE();
            return NetMap.node_num;

        }else if(strcmp(message.buff_mo,"DELNODE") == 0 || strcmp(message.buff_mo,"delnode") == 0){
            
            DELNODE(message,0);
            REWRITEFILE();
            return NetMap.node_num;

        }else if(strcmp(message.buff_mo,"SCHUNK") == 0 || strcmp(message.buff_mo,"schunk") == 0){
            
            return -1;
            
        }else if(strcmp(message.buff_mo,"RDB") == 0 || strcmp(message.buff_mo,"rdb") == 0){
            
            return 0;

        }else if(strcmp(message.buff_mo,"AOF") == 0 || strcmp(message.buff_mo,"aof") == 0){
            
            return 0;

        }else{
            //pass
        }    
        
    }else{
        //pass
    }
    return 0;
        
}


int ADDNODE(Message mess,int flag){
    printf("---------------------------------------------\n");
    //printf("ADDNODE : %s : %s\n",mess.buff_key,mess.buff_val);
    appendnode(mess,flag);
    printf("---------------------------------------------\n");
}


int DELNODE(Message mess,int flag){
    
    test_net();
    printf("DELNODE : %s: %s\n",mess.buff_key,mess.buff_val);
    delnode(mess,flag);
    test_net();

}

int REWRITEFILE(){
    
    int number;
    number = rewritefile();

    return number;
}


int print_bc(Message mess){
    
    if(strcmp(mess.buff_mo,"GET") == 0 || strcmp(mess.buff_mo,"get") == 0){
        
        printf("GET,%s\n",mess.buff_val);

    }else{     
        printf("Key:%s:%s\n",mess.buff_key,mess.oob);

    }

}



/*发送AOF 和 RDB 相关指令给制定的服务器*/
/*指令为： RDB/AOF IP port*/
int rdb_aof_send(Message mess,int flag){
    

    if(strcmp(mess.buff_mo,"AOF") == 0 || strcmp(mess.buff_mo,"aof") == 0 
              || strcmp(mess.buff_mo,"RDB")  == 0 || strcmp(mess.buff_mo,"rdb")  == 0
              || strcmp(mess.buff_mo,"BRDB") == 0 || strcmp(mess.buff_mo,"brdb") == 0){   

        int sockfd;
        struct sockaddr_in servaddr;
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(atoi(mess.buff_val));
        inet_pton(AF_INET,mess.buff_key,&servaddr.sin_addr);
        connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
        write(sockfd,(char *)&mess,sizeof(Message));
        close(sockfd);
        return 1;

    }else{
        
        return 0;
    }
    



}


int show_shut_send(Message mess,int flag){
    

    if(strcmp(mess.buff_mo,"SHOW") == 0 || strcmp(mess.buff_mo,"show") == 0 
            || strcmp(mess.buff_mo,"SHUTDOWN") == 0 || strcmp(mess.buff_mo,"shutdown") == 0){   

        int sockfd;
        struct sockaddr_in servaddr;
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(atoi(mess.buff_val));
        inet_pton(AF_INET,mess.buff_key,&servaddr.sin_addr);
        connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
        write(sockfd,(char *)&mess,sizeof(Message));
        close(sockfd);
        return 1;

    }else{
        
        return 0;
    }
    



}

