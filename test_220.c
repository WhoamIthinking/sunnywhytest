#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void multiply(char* num1, char* num2, char* result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int* res = (int*)calloc(len1 + len2, sizeof(int));
    
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + res[p2];
            
            res[p1] += sum / 10;
            res[p2] = sum % 10;
        }
    }
    
    int i = 0, k = 0;
    while (i < len1 + len2 && res[i] == 0) i++;
    if (i == len1 + len2) {
        result[k++] = '0';
    } else {
        while (i < len1 + len2) {
            result[k++] = res[i++] + '0';
        }
    }
    result[k] = '\0';
    free(res);
}

int main() {
    char num1[1001], num2[1001];
    scanf("%s %s", num1, num2);
    
    char result[2002];
    multiply(num1, num2, result);
    
    printf("%s\n", result);
    
    return 0;
}