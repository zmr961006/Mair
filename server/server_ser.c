/*************************************************************************
	> File Name: server_ser.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 13时52分08秒
 ************************************************************************/

#include"./server_ser.h"
#include<unistd.h>
extern netmap NetMap;


int ADDNODE(Message mess,int flag,int fd){
    int bc = 0;
    printf("---------------------------------------------\n");
    test_net();
    printf("ADDNODE : %s : %s\n",mess.buff_key,mess.buff_val);
    appendnode(mess,flag);
    bc = 10;
    server_bc(mess,NULL,bc,fd);
    test_net();
    printf("---------------------------------------------\n");

}


int DELNODE(Message mess,int flag,int fd){
    int bc = 0; 
    test_net();
    printf("DELNODE : %s: %s\n",mess.buff_key,mess.buff_val);
    delnode(mess,flag);
    bc = 11;
    server_bc(mess,NULL,bc,fd);
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

