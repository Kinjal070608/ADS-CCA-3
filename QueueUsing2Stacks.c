#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000
int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;
void push1(int x) {
    stack1[++top1] = x;
}
void push2(int x) {
    stack2[++top2] = x;
}
int pop1() {
    return stack1[top1--];
}
int pop2() {
    return stack2[top2--];
}

int main() {
    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {  
            int x;
            scanf("%d", &x);
            push1(x);
        }
        else if (type == 2) {  
            if (top2 == -1) {
                while (top1 != -1) {
                    push2(pop1());
                }
            }
            pop2();
        }
        else if (type == 3) {  
            if (top2 == -1) {
                while (top1 != -1) {
                    push2(pop1());
                }
            }
            printf("%d\n", stack2[top2]);
        }
    }    
    return 0;
}
