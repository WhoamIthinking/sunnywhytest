#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double PI;
double func(double R,double h){
    return acos((R-h)/R)*R*R-sqrt(R*R-(R-h)*(R-h))*(R-h);
}
double find_solu(double left,double right,double i,double r){
    double s=PI*r*r/2.0;
    while(left<right){
        double mid=(left+right)/2.0;
        if(func(r,mid)/s==i){
            return mid;
        }
        if(fabs((func(r,mid)-s*i))<0.00001){
            return mid;
        }
        if(func(r,mid)/s<i){
            left=mid;
        }
        else{
            right=mid;
        }
    }
    return -1;
}
int main(){
    double r,i;
    PI = acos(-1.0);
    scanf("%lf %lf",&r,&i);
    double t=find_solu(0,r,i,r);
    printf("%.2lf",t);
    return 0;
}