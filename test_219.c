#include<stdio.h>
#include<string.h>
int mycmp(char *a,char* b){
    int al,bl;
    al=strlen(a);
    bl=strlen(b);
    if(al>bl){
        return 1;
    }
    else if(al<bl){
        return -1;
    }
    else{
        for(int i=0;i<al;i++){
            if(a[i]>b[i]){
                return 1;
            }
            if(a[i]<b[i]){
                return -1;
            }
        }
        return 0;
    }
}
int main(){
    char a[200];
    char b[200];
    scanf("%s %s",a,b);
    int signal=mycmp(a,b);
    if(signal==0){
        printf("0");
        return 0;
    }
    if(signal==-1){
        char temp[200];
        strcpy(temp,a);
        strcpy(a,b);
        strcpy(b,temp);
    }
    int al,bl;
    al=strlen(a)-1;
    bl=strlen(b)-1;
    int n=strlen(a);
    int p=n;
    int c=0;
    char result[200];
    while(al>=0&&bl>=0){
        if(a[al]+c>=b[bl]){
            result[n]=a[al]+c-b[bl]+'0';
            c=0;
        }
        else{
            result[n]=a[al]+c+10-b[bl]+'0';
            c=-1;
        }
        al--;bl--;n--;
    }
    while(al>=0){
        result[n]=a[al]+c;
        c=0;
        al--;n--;
    }
    if(signal==-1){
        result[0]='-';
    }
    else{
        result[0]='0';
    }
    int q=0;
    if(result[0]=='-'){
        printf("-");
    }
    for(int i=1;i<p+1;i++){
        if(result[i]!='0'){
            q=1;
        }
        if(q==1){
            printf("%c",result[i]);
        }
    }
    return 0;
}