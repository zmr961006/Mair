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
    int re_hash = hash % LIMIT;
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


