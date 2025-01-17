#include<stdio.h>
#include<string.h>
int main(){
    char a[200];
    char b[200];
    scanf("%s %s",a,b);
    int al,bl;
    al=strlen(a)-1;
    bl=strlen(b)-1;
    int n=strlen(a);
    if(strlen(b)>strlen(a)){
        n=strlen(b);
    }
    int p=n;
    int c=0;
    char result[200];
    while(al>=0&&bl>=0){
        result[n]=(a[al]-'0'+b[bl]-'0'+c)%10+'0';
        c=(a[al]-'0'+b[bl]-'0'+c)/10;
        al--;bl--;n--;
    }
    while(al>=0){
        result[n]=(a[al]-'0'+c)%10+'0';
        c=(a[al]-'0'+c)/10;
        al--;n--;
    }
    while(bl>=0){
        result[n]=(b[bl]-'0'+c)%10+'0';
        c=(b[bl]-'0'+c)/10;
        bl--;n--;
    }
    result[0]='0';
    if(c==1){
        result[0]=1+'0';
    }
    for(int i=0;i<p+1;i++){
        if(i==0&&result[0]=='0'){
            continue;
        }
        printf("%c",result[i]);
    }
    return 0;
}