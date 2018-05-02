/*************************************************************************
	> File Name: distribute.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月21日 星期六 23时00分05秒
 ************************************************************************/

#include"./distribute.h"

netmap VnetMap;          /*虚拟节点*/

extern netmap NetMap;

int virtual_off = 0;    /*默认关闭虚拟节点1:on ; 0:off*/

int add_virtual_node(){}

int del_virtual_node(){}

int init_virtual(){}


/*如果开启了虚拟节点则先找虚拟节点，否则直接在真实节点中查找*/

netinfo * find_send_node(int servernumber,int hash){

    netinfo * temp = NULL;
    int re_hash = hash % LIMIT;        /*LIMIT表示哈希散列区间最大值，由此挑选出应当发送的服务器*/
    if(virtual_off == 0){
        temp = find_real_node(re_hash);
        return temp;
    }else if(virtual_off == 1){
        temp = find_virtual_node(re_hash);
        if(temp == NULL){
            temp = find_real_node(re_hash);
        }
        return temp;
    }else{
        //pass
    }


}

netinfo * find_real_node(int hash){

    netinfo * index = NetMap.networkmap;
    while(index != NULL){
    
        if(hash >= index->hash_start && hash <= index->hash_end){
            
            return index;
        }    
        index = index->next;
    }
    return index;
}

netinfo * find_virtual_node(int hash){
    
    netinfo * index = NetMap.networkmap;
    while(index != NULL){
        
        if(hash >= index->hash_start && hash <= index->hash_end){
            
            return index;
        }
        index = index->next;
    }
    return index;


}

/*检查网络并且更新网络转发表*/

int chunk_network(Message mess,int flag){
    
    int sockfd;
    Message messbc;
    netinfo *temp;
    temp = NetMap.networkmap;

    sockfd = get_socket2(temp);                     /*首先发送访问信息，获取版本与转发表条数*/
    send(sockfd,(char *)&mess,sizeof(Message),0);
    recv(sockfd,(void *)&messbc,sizeof(Message),0);
    
    int now_version =  NetMap.version;
    
    //printf("version:%d:index:%d\n",atoi(messbc.buff_val),messbc.hash);/*test*/
    //return 0;

    if(now_version ==  atoi(messbc.buff_val)){    
        printf("NetWork map OK!\n");
        return 0;
    
    }else{ /*重新发送数据*/
        close(sockfd);
        sockfd = get_socket2(temp);
        memset(mess.buff_mo,0,30);                 /*发送请求更新数据*/
        memcpy(mess.buff_mo,"UPDATE",6);
        send(sockfd,(char *)&mess,sizeof(Message),0);

        int index = messbc.hash;
        free_network(NetMap.version);                         /*删除原来客户端的网络转发表*/
        
        Message messbct[index];
        printf("index = %d\n",index);
        for(int i = 0;i < index;i++){
            printf("in for:%d\n",i);
            memset((char *)&messbct[i],0,sizeof(Message));       
            recv(sockfd,(void *)&messbct[i],sizeof(Message),0);
            ADDNODE(messbct[i],0);
            //recv(sockfd,(void *)&messbct[1],sizeof(Message),0);
            //ADDNODE(messbct[1],0);
            //recv(sockfd,(void *)&messbct[2],sizeof(Message),0);
            //ADDNODE(messbct[2],0);

            //printf("recv %s:%s\n",messbct[i].buff_key,messbct[i].buff_val);
            //ADDNODE(messbct[i],0);
        
        }
        printf("before rewrite");
        REWRITEFILE();
        close(sockfd);
    }


}


int free_network(int version){
    
    NetMap.networkmap = NULL;
    NetMap.version    = 0;
    NetMap.node_num   = 0;

}

