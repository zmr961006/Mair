/*************************************************************************
	> File Name: read_pro.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月26日 星期一 10时33分30秒
 ************************************************************************/

#include"./read_pro.h"

char info[3][50];



int explex(char ** infoex,int temp){
    
    char buf_exp[BUFFEXP];
    int index,i,j,flag;
    


    for(index = 0;index < temp;index++){
        i = 0;
        flag = 0;
        for(j = 0;j < 50;j++){

            if(info[index][j] == '['){
                flag = 1;
                j++;
            }
            
            if(info[index][j] == ']'){
                flag = 0;
                
            }

            if(flag == 1){
                buf_exp[i] = info[index][j];
                i++;
            }

        }
        printf("%s\n",buf_exp);
        memset(buf_exp,0,50);   
    }
    
}



int read_server(int temp1,char *temp2){

    FILE *fp;
    
    fp = fopen("../cilent/profile","at+");
    int i;
    for(int i = 0;i < 3;i++){
        fgets(info[i],50,fp);
    }
    
    for(int j = 0;j < 3;j++){
        printf("%s\n",info[j]);
    }

    explex(NULL,3);

    fclose(fp);

}




int write_server(int temp1,char *temp2){
    




}
int init_info(char * temp1,int temp){
    
    FILE *fp;
    char start[50];
    char num[10];
    int i,j,nums = 0;
    memset(num,0,10);
    memset(start,0,50);
    fp = fopen("../cilent/profile","at+");
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
    nums = atoi(num);
    printf("%s | %s \n%d\n",start,num,nums);
    



}


int main(){
    //int fd;
    //char * temp;
    //read_server(fd,temp);
    init_info(NULL,0);
}
