#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_N 10  // 定义最大输入数值

// 栈结构体定义
typedef struct {
    int data[MAX_N];  // 存储栈元素的数组
    int top;          // 栈顶指针
} Stack;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;  // 栈顶指针初始化为-1，表示空栈
}

// 入栈操作
void push(Stack* s, int value) {
    s->data[++(s->top)] = value;  // 先增加栈顶指针，再存入数据
}

// 出栈操作
int pop(Stack* s) {
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

int main() {
    char begin[200];
    char result[200];
     // 使用 fgets 读取包含空格的字符串
    if (fgets(begin, sizeof(begin), stdin) != NULL) {
        // 移除末尾的换行符
        size_t len = strlen(begin);
        if (len > 0 && begin[len - 1] == '\n') {
            begin[len - 1] = '\0';
        }
    }
    Stack stack;
    initStack(&stack);  // 初始化栈
    int i=0;int t=0;
    while(begin[i]!='\0'){
        if(begin[i]==' '){
            i++;
        }
        else{
            if(get_priority(begin[i])==0){
                result[t]=begin[i];
                t++;i++;
            }
            else{
                if(isEmpty(&stack)==1){
                    push(&stack,begin[i]);
                    i++;
                }
                else{
                    while(get_priority(stack.data[stack.top])>=get_priority(begin[i])){
                        result[t++]=pop(&stack);
                    }
                    push(&stack,begin[i]);
                    i++;
                }
            }
        }
    }
    while(isEmpty(&stack)==0){
        result[t++]=pop(&stack);
    }
    result[t]='\0';
    for(int i=0;i<t;i++){
        if(i!=0){
            printf(" ");
        }
        printf("%c",result[i]);
    }
    return 0;
}
