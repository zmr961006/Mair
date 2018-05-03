/*************************************************************************
	> File Name: server_ser.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 13时52分08秒
 ************************************************************************/

#include"./server_ser.h"
#include<unistd.h>
extern netmap NetMap;

#define MAXLISMIT  100000


int ADDNODE(Message mess,int flag,int fd){
    int bc = 0;
    int FLAG = 0;   /*0为设置hash的增加操作*/
    printf("---------------------------------------------\n");
    test_net();
    printf("ADDNODE : %s : %s\n",mess.buff_key,mess.buff_val);
    appendnode(mess,flag);
    bc = 10;
    server_bc(mess,NULL,bc,fd);
    set_hash(mess,FLAG);             /*设置更改过后的hash服务范围*/
    test_net();
    printf("---------------------------------------------\n");

}


int DELNODE(Message mess,int flag,int fd){
    int bc = 0; 
    int FLAG = 1;  /*1为设置hash的合并删除操作*/
    test_net();
    printf("DELNODE : %s: %s\n",mess.buff_key,mess.buff_val);
    delnode(mess,flag);
    bc = 11;
    server_bc(mess,NULL,bc,fd);
    set_hash(mess,FLAG);             /*设置更改过后的hash服务范围*/
    test_net();

}

int REWRITEFILE(){
    
    int number;
    number = rewritefile();

    return number;
}


/*效验版本信息*/

int SCHUNK(Message mess,int flag,int fd){   
    
    Message messbc;
    sprintf(messbc.buff_val,"%d",-1);
    messbc.hash = NetMap.node_num;
    send(fd,(char *)&messbc,sizeof(Message),0); 
    return 0;

}


int UPDATE(Message mess,int flag,int fd){
    netinfo * temp;
    temp = NetMap.networkmap;
    for(int i  =0;i < NetMap.node_num;i++){
        Message messbc;
        char hstart[10];
        char hend[10];
        char stus[10];
        char vser[10];
        
        memset((char *)&messbc,0,sizeof(Message));
        memcpy(messbc.buff_mo,"ADDNODE",7);

        sprintf(hstart,"%d",temp->hash_start);
        sprintf(hend,"%d",temp->hash_end);
        sprintf(stus,"%d",temp->status);
        sprintf(vser,"%d",temp->virtual_server);

        strcpy(messbc.buff_key,temp->ip_char);
        
        strcpy(messbc.buff_val,temp->port_char);
        strcat(messbc.buff_val,":");
        strcat(messbc.buff_val,hstart);
        strcat(messbc.buff_val,":");
        strcat(messbc.buff_val,hend);
        strcat(messbc.buff_val,":");
        strcat(messbc.buff_val,stus);
        strcat(messbc.buff_val,":");
        strcat(messbc.buff_val,vser);
        
        int len = strlen(messbc.buff_val);
        for(int j = 0;j < len;j++){
            printf("%c",messbc.buff_val[j]);
        }
        printf("\n");
        //printf("send:%s  %s | %s\n",messbc.buff_mo,messbc.buff_key,messbc.buff_val);
    
        temp = temp->next;
        sleep(1);
        send(fd,(char *)&messbc,sizeof(Message),0);
    }
    return 0;
}


int set_hash(Message mess,int FLAG){
    
    netinfo * temp = (netinfo *)malloc(sizeof(netinfo));

    char buff[5][30];

    int llen = strlen(mess.buff_val);                //获取端口和范围
    int len = strlen(mess.buff_key);                 //获取IP 

    temp->ip_char = (char *)malloc(sizeof(char) * len);  //直接拷贝IP 内容
    memcpy(temp->ip_char,mess.buff_key,len);             

    
    int j = 0; 
    int k = 0;
    for(int i = 0;i < llen ; i++){
        if(mess.buff_val[i] == ':'){
            j++;
            k = 0;
        }else{
            
            buff[j][k] = mess.buff_val[i];
            k++;
        }
    }

    int plen = strlen(buff[0]);
    temp->port_char = (char *)malloc(sizeof(char) * plen);
    memcpy(temp->port_char,buff[0],plen);

    temp->port_int       =  atoi(buff[0]); 
    temp->hash_start     =  atoi(buff[1]);
    temp->hash_end       =  atoi(buff[2]);
    temp->status         =  atoi(buff[3]);
    temp->virtual_server =  atoi(buff[4]);
    
    /*FLAG = 0 则为增加节点与范围操作，当FLAG = 1 则为删除节点与合并范围操作*/
    /*增加节点就为遍历整个链表，寻找增加的范围在原节点的哪一个区间，修改相应的范围*/
    /*增加总共分为三种情况：
     * 第一种：在节点区间内部
     * 第二种：在节点区间中间，跨节点服务范围增加服务节点
     * 第三种：在节点区间外部扩展，在最大的服务范围内进行扩展
     */

    if(FLAG == 0){                
        netinfo * index = NetMap.networkmap;
        while(index != NULL){
            if((temp->hash_start >= index->hash_start) && (temp->hash_end <= index->hash_end )){
                /*则找到一个在区间内增加的服务节点，属于第一中情况*/
                
                
                
            }else if((temp->hash_start <= index->hash_end) && (temp->hash_end >= index->hash_end)){
                /*则找到为一个跨区增加服务器的节点，属于第二种情况*/
            
            
            }else if((temp->hash_start >= index->hash_end) && (temp->hash_end >= MAXLISMIT)){
                /*则找到超过服务器最大服务器的服务范围，则属于第三种情况*/
            
            
            }else{
                //pass
            }
            
            index = index->next;
        }
        
    }else if(FLAG == 1){
        /*删除的节点仅仅只影响一个存在的服务器节点，所以只要找到修改就可以了，其中也分为三种情况
         * 第一种：只有一个节点，则不能进行删除转发操作。
         * 第二种：有前驱节点，有后继节点。
         * 第三种：有前驱节点，无后继节点。
         */

        netinfo * index = NetMap.networkmap;
        netinfo * next;
        int ssum = 1;
        while(index != NULL){
            next = index->next;
            if(NetMap.node_num == 1){
                printf("can not del node in this system\n");
            }else if(){
                
                
                
            }else if(){



            }else{
                


            }
            
            ssum++;
            index = index->next;
        }
        
    
    
    
    }
    
    return 0;

}
