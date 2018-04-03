/*************************************************************************
	> File Name: server_init.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月03日 星期二 21时32分17秒
 ************************************************************************/

#include"./server_init.h"



char **info;         /*暂时存储配置信息*/
int  node_info_num;  /*标记有多少个IP节点*/
netmap NetMap;       /*客户端路由表存储结构*/
int  this_server_port;  /*本机的端口*/


int test_net(){

    netinfo * temp;
    temp = NetMap.networkmap;
    int i  = 0;
    for(i = 0;i < NetMap.node_num;i++){
        printf("ip :%s\n",temp->ip_char);
        printf("port :%s\n",temp->port_char);
        printf("port :%d\n",temp->port_int);
        printf("start :%d\n",temp->hash_start);
        printf("end :%d\n",temp->hash_end);
        temp = temp->next;
    }


}




int explex(char ** infoex,int temp){
    
    char buf_exp[BUFFEXP];
    int index,i,j,flag;
    memset(buf_exp,0,BUFFEXP);
    for(index = 0;index < temp;index++){
        i = 0;
        flag = 0;
        for(j = 0;j < 50;j++){

            

            if(flag == 0){
                buf_exp[i] = info[index][j];
                i++;
            }

        }
        //printf("%s\n",buf_exp);
        add_nodeinmap(buf_exp,1);
        memset(buf_exp,0,50);   
    }
    
}



int read_server(int temp1,char *temp2){

    FILE *fp;
    char buf[10];
    init_info(NULL,0);
    fp = fopen("profile","at+");
    fgets(buf,50,fp);
    for(int i = 0;i < node_info_num;i++){
        fgets(info[i],50,fp);
    }
    fclose(fp);
    explex(NULL,node_info_num);

}




int write_server(int temp1,char *temp2){}


int init_info(char * temp1,int temp){
    
    
    FILE *fp;
    char start[50];
    char num[10];
    int i,j;

    NetMap.node_num   = 0;      /*初始化网络路由表*/
    NetMap.networkmap = NULL;
    NetMap.tail       = NULL;

    memset(num,0,10);
    memset(start,0,50);

    fp = fopen("profile","at+");
    fgets(start,50,fp);
    fclose(fp);
    j = 0;
    for(i = 0;i < 50;i++){
        if(start[i] == '['){
            i++;
        }
        if(start[i] == ']'){
            break;
        }
        num[j] = start[i];
        j++;
    }
    node_info_num  = atoi(num);
    
    _init_info();


    return 0;


}

int _init_info(){
    

    int i,j;

    info = (char**)malloc(sizeof(char *)*node_info_num);

    for(i = 0; i < node_info_num;i++){
        
        char *tmp = (char *)malloc(sizeof(char)*50);
        info[i] = tmp;

    }
    return 0;


}



int add_nodeinmap(char *buffer,int temp1){

    printf("%s",buffer);
    if(NetMap.node_num    == 0){
        netinfo * temp    = (netinfo*)malloc(sizeof(netinfo));
        temp->next        = NULL;
        NetMap.node_num   = 1;
        NetMap.networkmap = temp;
        NetMap.tail       = temp;
        _add_nodeinmap(buffer,temp);

    }else{
        netinfo * temp    = (netinfo*)malloc(sizeof(netinfo));
        NetMap.node_num   += 1;
        NetMap.tail->next = temp;
        NetMap.tail       = temp;
        temp->next = NULL;
        _add_nodeinmap(buffer,temp);
    }

}



int _add_nodeinmap(char * buf,netinfo * tem){
    char  ip[17];
    char  port[5];
    char  start[8];
    char  end[8];
    char  buff[30];
    memset(buff,0,30);
    int len = 0,i = 0;
    len = strlen(buf);
    int j,flag = 0;
    tem->ip_char = (char *)malloc(sizeof(char)*IPLEN);
    tem->port_char = (char *)malloc(sizeof(char)*PORTLEN);

    for(j = 0;j < len;j++){
        
        if(buf[j] == '['){
            j += 1;
        }
            
        if(buf[j] == ']'){
            
            j += 2;
            switch(flag){
                case  0:{
                    memset(buff,0,30);
                    break;
                }
                case 1:{
                    memcpy(tem->ip_char,buff,IPLEN);
                    //printf("ip: %s\n",tem->ip_char);
                    break;
                }
                case 2:{
                    memcpy(tem->port_char,buff,PORTLEN);
                    //printf("port:%s\n",tem->port_char);
                    break;
                }
                case 3:{
                    tem->hash_start = atoi(buff);
                    //printf("start:%d\n",tem->hash_start);
                    break;
                }
                case 4:{
                    tem->hash_end   = atoi(buff);
                    //printf("end:%d\n",tem->hash_end);
                    break;
                }
                
            }
            flag++;
            memset(buff,0,30);
            i = 0;
        }
        buff[i] = buf[j];
        i++;

    }
    tem->port_int = atoi(tem->port_char);

}


int proc_profile(){
    
    printf("profile :\n");
    printf("firstline: [node_info_num]\n");
    printf("otherline:[sever][ip][port][start][end]\n");

    
}

int server_init(int server_port){
    
    this_server_port = server_port; 
    read_server(0,NULL);


}

