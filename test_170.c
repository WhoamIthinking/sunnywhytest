#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double func(double x,double a){
    return x*x*x+x*x+x-a;
}
double find_solution(double a,double left,double right){
    while (left<right)
    {  
        double middle=(left+right)/2.0;
        if(func(middle,a)==0){
            return middle;
        }
        if(fabs(func(middle,a))<0.01){
            return middle;
        }
        if(func(left,a)*func(middle,a)<0){
            right=middle;
        }
        else{
            left=middle;
        }
        /* code */
    }
    return left;
}
int main(){
    double a;
    scanf("%lf",&a);
    double t=find_solution(a,-100,+100);
    printf("%.2lf",t);
    return 0;
}