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
order orders;


char buf_in[BUFFLEN];     /*指令缓冲*/
char buf_oder[ODER];      /*命令缓冲*/
char buf_key[KEYLEN];     /*KEY 缓冲*/
char buf_val[VALLEN];     /*VAL缓冲*/



int init_cilent(){

    orders.orders[0] = "DEL";
    orders.orders[1] = "GET";
    orders.orders[2] = "SET";
    orders.orders[3] = "del";
    orders.orders[4] = "get";
    orders.orders[5] = "set";
    orders.num = 6;

}

int opt(char * temp1,char *temp2,int argc){

    int start = 1;
    int flag  = 1;
    int loop  = 1;



    while(loop){
        memset(buf_in,0,BUFFLEN);
        fflush(stdin);
        printf(">>");
        fgets(buf_in,BUFFLEN,stdin);
        buf_in[BUFFLEN-1] = '\0';
        //printf("yaun: %s\n",buf_in);
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

int chunk(char * temp1){
    
   
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
    int hash = 0;
    int len  = strlen(buf_key);
    int vlen = strlen(buf_val);
    int sfd;
    int server_num = 0;
    memcpy(message.buff_mo,buf_oder,ODER);
    memcpy(message.buff_key,buf_key,KEYLEN);
    memcpy(message.buff_val,buf_val,VALLEN);
    message.buff_val[vlen-1] = '\0';
    //printf("val %s",message.buff_val);
    //printf("lalalalal\n");
    hash = get_hash(buf_key,len);
    //printf("%d\n",hash);
    //get_time();
    server_num = get_server(hash);
    message.hash = hash;
    message.flag = ALIVE;
    message.Type = get_ordernum(buf_oder);    /*获取命令类型*/
    //printf("%d\n",server_num);
    sfd = get_socket(server_num,hash);
    write(sfd,(char *)&message,sizeof(message));
    printf("server : %d\n",server_num);
        /*给服务器一个时间*/
    //sleep(1);
    close(sfd);
    //printf("OK,%s %s %s\n",message.buff_mo,message.buff_key,message.buff_val);
    return 1;

}

int _send_to(int fd,Message mess){
    




}

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

    }else{

        return -1;
    }
    

}


