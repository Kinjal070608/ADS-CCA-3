#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_OPS 1000000
char *stack[MAX_OPS];
int top = -1;
int main() {
      int Q;
    scanf("%d", &Q);
    char S[1000001] = "";
    while (Q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            char W[1000001];
            scanf("%s", W);
            stack[++top] = strdup(S);
            strcat(S, W);
        }
        else if (type == 2) {
            int k;
            scanf("%d", &k);
            stack[++top] = strdup(S);

            int len = strlen(S);
            S[len - k] = '\0';
        }
        else if (type == 3) {
            int k;
            scanf("%d", &k);

            printf("%c\n", S[k - 1]);
        }
        else if (type == 4) {
            // undo
            if (top >= 0) {
                strcpy(S, stack[top]);
                free(stack[top]);
                top--;
            }
        }
    }
    return 0;
}
