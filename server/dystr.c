/*************************************************************************
	> File Name: dystr.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月14日 星期六 12时38分44秒
 ************************************************************************/

#include"./dystr.h"


dystr * dystr_create(char * data,int len){  /*预先分配字符两倍的存储量*/
    
    len = strlen(data);
    dystr * temp = (dystr *)malloc(sizeof(dystr));
    temp->dystr_data = (char *)malloc(sizeof(char) * len * 2);
    strncpy(temp->dystr_data,data,len);
    temp->len = len;
    temp->plen = len * 2;

    return temp;
}



int dystr_free(dystr *temp){
    
    free(temp->dystr_data);
    free(temp);

    return 0;
    
}



int dystr_mod(dystr * temp,char * data,int len){
    
    len = strlen(data);
    if(temp->len < len){
        memset(temp->dystr_data,0,temp->plen);
        memcpy(temp->dystr_data,data,len);
        temp->len = len;
    }else{
        free(temp->dystr_data);
        temp->dystr_data = (char * )malloc(sizeof(char)* len *2);
        temp->len = len;
        temp->plen = len * 2;
    }

    return 0;

}

int dystr_create2(dystr temp,char *data,int len){
    
    len = strlen(data);
    temp.dystr_data = (char *)malloc(sizeof(char) * len * 2);
    strcmp(temp.dystr_data,data);
    temp.len = len;
    temp.plen = 2 * len;
    
}

int dystr_create3(dystr * temp,char * data,int len){
    
    len = strlen(data);
    temp->dystr_data = (char *)malloc(sizeof(char) * len * 2);
    strcmp(temp->dystr_data,data);
    temp.len = len;
    temp.plen = 2 * len;

}

