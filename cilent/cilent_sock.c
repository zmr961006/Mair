/*************************************************************************
	> File Name: cilent_sock.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 14时38分23秒
 ************************************************************************/

#include"./cilent_sock.h"
#include"./read_pro.h"

extern netmap NetMap;

int get_socket(int fd,int temp){

    int sockfd;
    int i = 0;
    struct sockaddr_in servaddr;

    netinfo * tem;
    netinfo * cn;
    cn = NetMap.networkmap;
    tem = cn;
    
   tem = find_send_node(fd,temp);              /*寻找合适的转发节点fd:服务器个数总数，temp:哈希值*/
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


int write_all(Message mess,int flag){
    
    netinfo * temp = NetMap.networkmap;

    while(temp != NULL){
        if(temp->virtual_server == 0){   
            int sockfd;    
            sockfd = get_socket2(temp);   
            write(sockfd,(char *)&mess,sizeof(Message));
            temp = temp->next;
        }
    }

    return 0;
}


int get_socket2(netinfo * temp){
    

    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(temp->port_int);
    inet_pton(AF_INET,temp->ip_char,&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    return sockfd;




    
}
