#include<stdio.h>
#include<stdlib.h>
int main(){
    int n;
    scanf("%d",&n);
    int *a=(int*)malloc(sizeof(int)*n);
    int *max_left=(int*)malloc(sizeof(int )*n);
    int *min_right=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        max_left[i]=0;
        min_right[i]=999999;
    }
    for(int i=0;i<n;i++){
        if(i==0){
            max_left[i]=0;
        }
        else{
            if(a[i-1]>max_left[i-1]){
                max_left[i]=a[i-1];
            }
            else{
                max_left[i]=max_left[i-1];
            }
        }
    }
    for(int i=n-1;i>=0;i--){
        if(i==n-1){
            min_right[i]=999999;
        }
        else{
            if(a[i+1]<min_right[i+1]){
                min_right[i]=a[i+1];
            }
            else{
                min_right[i]=min_right[i+1];
            }
        }
    }
    int p=0;
    for(int i=0;i<n;i++){
        if(a[i]<min_right[i]&&a[i]>max_left[i]){
            p++;
        }
    }
    printf("%d",p);
    free(a);
    free(min_right);
    free(max_left);
    return 0;
}