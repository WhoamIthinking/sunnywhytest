#include<stdio.h>
long int values[20];
long int weights[20];
int n;
long int volume;
long int max;
void bag(int index,long int now,long int value){
    if((now>=volume)||(index>=n)){
        if(value>max){
            max=value;
        }
        return;
    }
    else{
        if(volume-now<weights[index]){
            bag(index+1,now,value);
        }
        else{
            bag(index+1,now,value);
            bag(index+1,now+weights[index],value+values[index]);
        }
    }
}
int main(){
    scanf("%d %d",&n,&volume);
    for(int i=0;i<n;i++){
        scanf("%ld",&weights[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%ld",&values[i]);
    }
    bag(0,0,0);
    printf("%ld",max);
    return 0;
}