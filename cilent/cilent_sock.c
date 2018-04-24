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
    //for(i = 0;i < fd;i++){                   // 选择一个合适的服务器转发,暂时关闭分布转发
    //    tem = NetMap.networkmap->next;
    //}
   // tem = find_send_node(fd,temp);              /*寻找合适的转发节点fd:服务器个数总数，temp:哈希值*/
    /*if(tem == NULL){
        printf("can not find node %d\n",__LINE__);
        printf("tem = head\n");
        tem = cn;
    }*/

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(tem->port_int);
    inet_pton(AF_INET,tem->ip_char,&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    return sockfd;
    
    
}
