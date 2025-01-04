#include<stdio.h>
#include<stdlib.h>
// 阶乘函数
long long factorial(int num) {
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}
// 组合数函数
long long combination(int n, int m) {
    if (m > n) return 0; // 当 m > n 时，组合数为 0
    return factorial(n) / (factorial(m) * factorial(n - m));
}
int result[200][12];
int k;
void printf_combination(int n);
void generate_combination(int *arr,int n,int m,int index){
    if(index==m){
        printf_combination(n);
    }
    else{
        
    }
}