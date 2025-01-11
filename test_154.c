#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef struct number
{
    char count[11];
}number;
number a[20000];
int cmp(const void *p1,const void *p2){
    number *a1 = (number *)p1;
    number *a2 = (number *)p2;
    char s1[22], s2[22];
    strcpy(s1, a1->count);
    strcat(s1, a2->count);
    strcpy(s2, a2->count);
    strcat(s2, a1->count);
    return strcmp(s1, s2);
}
void find_min(int n){
    int s=0;
    for(int i=0;i<n;i++){
        s=s+strlen(a[i].count);
    }
    int leading_zero = 1;
    for(int i=0;i<n;i++){
        int j=0;
        while(j<strlen(a[i].count)){
            if(leading_zero && a[i].count[j]=='0'){
                j++;
                continue;
            }
            leading_zero = 0;
            printf("%c",a[i].count[j]);
            j++;
        }
    }
    if (leading_zero) {
        printf("0");
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s",a[i].count);
    }
    qsort(a,n,sizeof(number),cmp);
    find_min(n);
    return 0;
}
