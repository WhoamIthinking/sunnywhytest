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
    int i=mycmp(a,b);
    if(i>0){
        printf("a > b");
    }
    else if(i<0){
        printf("a < b");
    }
    else{
        printf("a = b");
    }
    return 0;
}