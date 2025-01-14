#include<stdio.h>
long long int sticks[2000];
int can_cut(long long int k,long long int m,long long int n){
    long long int count=0;
    for(int i=0;i<n;i++){
        count=count+sticks[i]/m;
    }
    if(count>=k){
        return 1;
    }
    return 0;
}
int find_max_length(long long int n){
    long long int max=0;
    for(int i=0;i<n;i++){
        if(sticks[i]>max){
            max=sticks[i];
        }
    }
    return max;
}
long long int find_max_sticks(long long int left,long long int right,long long int n,long long int k,long long int p){
    long long int mid=(left+right)/2;
    if(k>p){
        return 0;
    }
    else if(k==p){
        return 1;
    }
    while(!(can_cut(k,mid,n)==1&&can_cut(k,mid+1,n)==0)){
        if(can_cut(k,mid,n)==0){
            mid=mid-1;
        }
        else{
            mid=mid+1;
        }
    }
    return mid;
}
int main(){
    long long int n,k,p;
    p=0;
    scanf("%lld %lld",&n,&k);
    for(int i=0;i<n;i++){
        scanf("%lld",&sticks[i]);
        p=p+sticks[i];
    }
    long long int m=find_max_length(n);
    long long int t=find_max_sticks(0,m,n,k,p);
    printf("%lld",t);
    return 0;
}