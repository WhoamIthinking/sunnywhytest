#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10  // 定义最大输入数值

// 栈结构体定义
typedef struct {
    int data[MAX_N];  // 存储栈元素的数组
    int top;          // 栈顶指针
} Stack;

// 存储所有可能的出栈序列
int all_sequences[10000][MAX_N];  // 二维数组存储所有序列
int sequence_count = 0;           // 序列计数器

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

// 核心递归函数
void generateSequences(Stack* stack, int push_num, int n, 
                      int current_sequence[], int current_len) {
    // 找到一个完整序列
    if (current_len == n) {
        // 将当前序列保存到全局结果数组中
        for (int i = 0; i < n; i++) {
            all_sequences[sequence_count][i] = current_sequence[i];
        }
        sequence_count++;
        return;
    }

    // 保存当前栈的状态，用于回溯
    Stack temp_stack = *stack;

    // 选择1：入栈操作
    if (push_num <= n) {  // 还有数字可以入栈
        push(stack, push_num);  // 将push_num入栈
        // 递归处理下一个状态
        generateSequences(stack, push_num + 1, n, 
                        current_sequence, current_len);
        *stack = temp_stack;  // 恢复栈的状态（回溯）
    }

    // 选择2：出栈操作
    if (!isEmpty(stack)) {  // 栈不为空时可以出栈
        int top_value = pop(stack);  // 出栈
        current_sequence[current_len] = top_value;  // 将出栈元素加入序列
        // 递归处理下一个状态
        generateSequences(stack, push_num, n, 
                        current_sequence, current_len + 1);
        *stack = temp_stack;  // 恢复栈的状态（回溯）
    }
}

// 比较函数，用于qsort
int compare(const void* a, const void* b) {
    int* seq1 = (int*)a;
    int* seq2 = (int*)b;
    
    for (int i = 0; i < MAX_N; i++) {
        if (seq1[i] != seq2[i]) {
            return seq1[i] - seq2[i];
        }
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);  // 输入n

    Stack stack;
    initStack(&stack);  // 初始化栈
    int current_sequence[MAX_N] = {0};  // 当前正在生成的序列

    // 生成所有可能的序列
    generateSequences(&stack, 1, n, current_sequence, 0);

    // 对序列进行字典序排序
    qsort(all_sequences, sequence_count, 
          sizeof(all_sequences[0]), compare);

    // 按要求格式输出所有序列
    for (int i = 0; i < sequence_count; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", all_sequences[i][j]);
            if (j < n-1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
