/*************************************************************************
	> File Name: opt_do.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 14时46分27秒
 ************************************************************************/

#include"./opt_do.h"
#include"./order.h"
#include"./message.h"


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
        printf(">>");
        fgets(buf_in,BUFFLEN,stdin);
        buf_in[BUFFLEN-1] = '\0';
        //printf("yaun: %s\n",buf_in);
        flag = chunk(buf_in);
        if(flag == 0){
            printf("erro styn\n");
        }
        loop = do_send(argc);
        if(loop == 0){
            break;
        }
    }

}

int chunk(char * temp1){
    
   

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

    //printf("%s\n%s\n%s\n",buf_oder,buf_key,buf_val);    test order
    int len = strlen(buf_oder);   
    /*int table;
    for(table = 0;table < 3;table++){                   test order
        printf("%s\n",orders.orders[table]); 
    }*/
    int index,back_val = 0;
    for(index = 0;index < orders.num;index++){
        if(strcmp(buf_oder,orders.orders[index]) == 0){
            back_val = 1;
        }
    }
    return back_val;

}



int do_send(int fd){

    message message;
    memcpy(message.buff_mo,buf_oder,ODER);
    memcpy(message.buff_key,buf_key,KEYLEN);
    memcpy(message.buff_val,buf_val,VALLEN);
    

    printf("OK,%s %s %s\n",message.buff_mo,message.buff_key,message.buff_val);
    return 1;

}
