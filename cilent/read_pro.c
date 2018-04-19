/*************************************************************************
	> File Name: read_pro.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 10时33分30秒
 ************************************************************************/

#include"./read_pro.h"



char **info;         /*暂时存储配置信息*/
int  node_info_num;  /*标记有多少个IP节点,读取配置文件时加载*/
netmap NetMap;       /*客户端路由表存储结构*/



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


int appendnode(Message mess,int flag){
    
    if(NetMap.node_num    == 0){
        netinfo * temp    = (netinfo*)malloc(sizeof(netinfo));
        temp->next        = NULL;
        NetMap.node_num   = 1;
        NetMap.networkmap = temp;
        NetMap.tail       = temp;
        _app_nodeinmap(mess,temp);

    }else{
        netinfo * temp    = (netinfo*)malloc(sizeof(netinfo));
        NetMap.node_num   += 1;
        NetMap.tail->next = temp;
        NetMap.tail       = temp;
        temp->next = NULL;
        _app_nodeinmap(mess,temp);
    }

}



/*示例化netinfo 网络转发节点*/

int _app_nodeinmap(Message mess,netinfo * temp){
    
    char buff[3][20];

    int llen = strlen(mess.buff_val);                //获取端口和范围
    int len = strlen(mess.buff_key);                 //获取IP 

    temp->ip_char = (char *)malloc(sizeof(char) * len);  //直接拷贝IP 内容
    memcpy(temp->ip_char,mess.buff_key,len);             

    
    int j ,k = 0;
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

    temp->port_int   =  atoi(buff[0]); 
    temp->hash_start =  atoi(buff[1]);
    temp->hash_end   =  atoi(buff[2]);
    temp->status     =  1;
    NetMap.node_num++;        /*计数加一*/

    return 0;    
    
}




int delnode(Message mess,int flag){
 
    /*if(NetMap.node_num    == 0){
        netinfo * temp    = (netinfo*)malloc(sizeof(netinfo));
        temp->next        = NULL;
        NetMap.node_num   = 1;
        NetMap.networkmap = temp;
        NetMap.tail       = temp;
        _app_nodeinmap(mess,temp);

    }*/
    int Flag = find_servernode(mess,flag);
    if(Flag > 0){
    
        delserver(Flag);    
    
    }else{
        
        printf("DEL SERVER IS NOT EXIST\n");    

    }

    
}


/*查找服务器节点在链表中的位置，然后返回是第几个节点*/
int find_servernode(Message mess,int flag){
    
    char buff[3][20];
    netinfo * temp  = NetMap.networkmap;
    int llen = strlen(mess.buff_val);
    int j ,k = 0;
    int number = 0;
    for(int i = 0;i < llen ; i++){
        if(mess.buff_val[i] == ':'){
            j++;
            k = 0;
        }else{
            
            buff[j][k] = mess.buff_val[i];
            k++;
        }
    }  

    
    while(temp != NULL){
        
        //printf("temp->ip_char : %s mess.buff_key: %s\n",temp->ip_char,mess.buff_key);
        //printf("temp->port_char: %s buff[0]: %s\n",temp->port_char,buff[0]);
        int iplen = strlen(temp->ip_char);
        int portlen = strlen(temp->port_char);
        int mplen   = strlen(mess.buff_key);
        int mpplen  = strlen(buff[0]);
        //printf("len : %d %d\n len:%d %d\n",iplen,mplen,portlen,mpplen);
        number++;
        if((strncmp(temp->ip_char,mess.buff_key,iplen) == 0) && (strncmp(temp->port_char,buff[0],portlen) == 0)){
                printf("I find this server : %d\n",number);
                return number;    
        }else{
                //printf("Can not find this server\n");
        }
        temp = temp->next;
        
    }

    return number;        /*0 为没找到， >0 即为存在*/

}



int delserver(int flag){
    
    int index = flag;
    netinfo * temp = NetMap.networkmap;

    if(flag == 1){
        NetMap.networkmap = temp->next;
        free(temp->ip_char);
        free(temp->port_char);
        free(temp);
        NetMap.node_num--;

    }else{
        flag -= 1;
        for(int i = 1;i < flag;i++){
            temp = temp->next;    
        }
        netinfo * node = temp->next;
        temp->next = temp->next->next;
        free(node->ip_char);
        free(node->port_char);
        NetMap.node_num--;
    }
    
    return 0;


}



