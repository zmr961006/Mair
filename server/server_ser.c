/*************************************************************************
	> File Name: server_ser.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 13时52分08秒
 ************************************************************************/

#include"./server_ser.h"
//#include"./server_mess.h"
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
    printf("in ADDNODE \n");
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
    
    /*temp 设置为当前的netinfo 节点*/

    netinfo * node = NetMap.networkmap;
    while(node != NULL){

        if((strcmp(node->ip_char,temp->ip_char) == 0) && (node->port_int ==  temp->port_int)){
            temp = node;         /*temp 设置为指向链表中的节点，就可以修改链表中的数据了*/
            break;
            
        }
        node = node->next;
    }

    /*FLAG = 0 则为增加节点与范围操作，当FLAG = 1 则为删除节点与合并范围操作*/
    /*增加节点就为遍历整个链表，寻找增加的范围在原节点的哪一个区间，修改相应的范围*/
    /*增加总共分为三种情况：
     * 第一种：在节点区间内部
     * 第二种：在节点区间中间，跨节点服务范围增加服务节点
     * 第三种：在节点区间外部扩展，在最大的服务范围内进行扩展
     */
        
    /*增加节点本质上我们只设置一中情况的节点增加情况，即是在一个节点的从开始位置增加节点，例如在
     * 0～500 节点上增加0～300 节点，则在这种情况下，我们只需要找到0～500 节点，然后修改0～500节点 
     * 的开始服务范围为 301～500 就可以了
     */
    

    /*temp 为新增加的节点,index 为需要找到的被修改节点*/
    if(FLAG == 0){                
        netinfo * index = NetMap.networkmap;
        while(index != NULL){
            if(temp->hash_start == index->hash_start){
                /*则找到一个在区间内增加的服务节点，属于第一中情况*/
                /*则需要修改当前找到的服务节点的服务器范围*/
                /*只能从开始位置进行节点增加操作*/
                
                index->hash_start = temp->hash_end + 1;
                
                printf("add node change\n");
                return 0;
                //data_trans(mess,start,end);
                
            }else if((temp->hash_start < index->hash_end) && (temp->hash_end > index->hash_end)){
                /*则找到为一个跨区增加服务器的节点，属于第二种情况*/
                /*跨范围增加节点需要修改两个节点的服务范围，分别是前一个的终止和后一个开始*/
            
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
            
        /*删除节点的情况比较简单，直接选择删除节点就行，但是在节点修改时，需要进行较为复杂的操作*/
        /*被删除的节点主要有两种情况，需要考虑前驱和后继节点，所以在算法的设计上，我们只需要遍历
         *链表将这个节点的前驱和后继找到，然后统一处理就行了。
         *当只有一个节点的时候，反馈不能删除节点就OK，当有前驱节点的时候，将被删除节点的上限直接
         *修改为前驱节点的上限，当有后继节点的时候，则需要将自己的服务开始范围更新给后继节点。
         *如果修改的节点范围超过整个服务范围则拒绝删除这个节点
         */

        /*index ：指向节点； rear : 前驱节点；next : 后继节点*/
        /*temp 当前节点*/

        netinfo * index = NetMap.networkmap;
        netinfo * rear;
        netinfo * next;
        int ssum = 1;
        int flag_have_rear = 0;    /*标志有无前驱节点*/
        int flag_have_next = 0;    /*标志有无后继节点*/
        while(index != NULL){
            
            if(NetMap.node_num == 1){
                printf("can not del node in this system\n");
            }else if((index->hash_end + 1) == temp->hash_start){
                /*则表示此节点是temp节点的前驱节点*/
                /*如果没有后继节点则直接合并到前驱节点*/
                /*Q：如何确定此节点一定没有后继节点*/
                flag_have_rear = 1;
                rear = index ;          /*保存当前节点的前驱节点*/
            }else if((index->hash_start-1) == temp->hash_end){
                /*则表示此节点是temp节点的后继节点*/
                /*如果存在后继节点则直接进行合并操作*/
                /*这种情况下找到节点是可以直接处理的，无需其他操作*/
                //merge_hash_next();
                //return 0;
                flag_have_next = 1;
                next = index;
                
            }else{
                
                //pass
                
            }
            
            ssum++;
            index = index->next;
        }
        if((flag_have_rear == 1) && (flag_have_next == 0)){
            /*只有前驱节点，没有后继节点*/
            rear->hash_end = temp->hash_end;
        }
        


        if((flag_have_rear == 1) && (flag_have_next == 1)){
            /*既有前驱节点，又有后继节点*/
            next->hash_start = temp->hash_start;
            
        }

        if((flag_have_rear == 0) && (flag_have_next == 1)){
            /*只有后继节点，没有前驱节点*/
            next->hash_start = temp->hash_start;
        }


    }
    
    return 0;

}


