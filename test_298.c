#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_N 10  // 定义最大输入数值

// 栈结构体定义
typedef struct {
    float data[MAX_N];  // 存储栈元素的数组
    int top;          // 栈顶指针
} Stack;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;  // 栈顶指针初始化为-1，表示空栈
}

// 入栈操作
void push(Stack* s, float value) {
    s->data[++(s->top)] = value;  // 先增加栈顶指针，再存入数据
}

// 出栈操作
float pop(Stack* s) {
    return s->data[(s->top)--];  // 返回栈顶元素并减少栈顶指针
}

// 判断栈是否为空
int isEmpty(Stack* s) {
    return s->top == -1;  // 栈顶指针为-1表示空栈
}

int get_priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


int main(){
    char num[200];
     // 使用 fgets 读取包含空格的字符串
    if (fgets(num, sizeof(num), stdin) != NULL) {
        // 移除末尾的换行符
        size_t len = strlen(num);
        if (len > 0 && num[len - 1] == '\n') {
            num[len - 1] = '\0';
        }
    }
    Stack s;
    initStack(&s);
    float result=0;
    int i=0;
    while(num[i]!='\0'){
        if(num[i]==' '){
            i++;
        }
        if(get_priority(num[i])==0){
            push(&s,(float)num[i]);
            i++;
        }
        else{
            float b=pop(&s)-'0';
            float a=pop(&s)-'0';
            float c;
            if(get_priority(num[i])==1){
                if(num[i]=='+'){
                    c=a+b;
                }
                else{
                    c=a-b;
                }
            }
            else{
                if(num[i]=='*'){
                    c=a*b;
                }
                else{
                    c=a/b;
                }
            }
            push(&s,(float)c+'0');
            i++;
        }
    }
    result=pop(&s);
    printf("%.2f",result-'0');
    return 0;
}