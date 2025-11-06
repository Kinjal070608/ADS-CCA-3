#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;
Node* newNode(int v) {
    if (v == -1) return NULL;
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}
void inorder(Node* root, int* out, int* idx) {
    if (!root) return;
    inorder(root->left, out, idx);
    out[(*idx)++] = root->data;
    inorder(root->right, out, idx);
}
void swapDepth(Node* root, int depth, int k) {
    if (!root) return;
    if (depth % k == 0) {
        Node* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    }
    swapDepth(root->left, depth + 1, k);
    swapDepth(root->right, depth + 1, k);
}

/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */

/*
 * To return the 2d integer array from the function, you should:
 *     - Store the number of rows of the array to be returned in the result_rows variable
 *     - Store the number of columns of the array to be returned in the result_columns variable
 *     - Allocate the array dynamically
 *
 * For example,
 * int** return_2d_integer_array(int* result_rows, int* result_columns) {
 *     *result_rows = 2;
 *     *result_columns = 3;
 *
 *     int** a = malloc(2 * sizeof(int*));
 *
 *     for (int i = 0; i < 2; i++) {
 *         *(a + i) = malloc(3 * sizeof(int));
 *
 *         for (int j = 0; j < 3; j++) {
 *             *(*(a + i) + j) = 3 * i + j + 1;
 *         }
 *     }
 *
 *     return a;
 * }
 *
 */
int** swapNodes(int indexes_rows, int indexes_columns, int** indexes, int queries_count, int* queries, int* result_rows, int* result_columns) {
    int n = indexes_rows;
    Node** nodes = malloc((n + 1) * sizeof(Node*));
    for (int i = 1; i <= n; i++) {
        nodes[i] = newNode(i);
    }
    for (int i = 1; i <= n; i++) {
        int left = indexes[i - 1][0];
        int right = indexes[i - 1][1];
        nodes[i]->left = (left == -1) ? NULL : nodes[left];
        nodes[i]->right = (right == -1) ? NULL : nodes[right];
    }
    Node* root = nodes[1];
    *result_rows = queries_count;
    *result_columns = n;
    int** ans = malloc(queries_count * sizeof(int*));
    for (int qi = 0; qi < queries_count; qi++) {
        int k = queries[qi];
        swapDepth(root, 1, k);
        ans[qi] = malloc(n * sizeof(int));
        int idx = 0;
        inorder(root, ans[qi], &idx);
    }
    free(nodes);
    return ans;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int** indexes = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(indexes + i) = malloc(2 * (sizeof(int)));

        char** indexes_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int indexes_item = parse_int(*(indexes_item_temp + j));

            *(*(indexes + i) + j) = indexes_item;
        }
    }

    int queries_count = parse_int(ltrim(rtrim(readline())));

    int* queries = malloc(queries_count * sizeof(int));

    for (int i = 0; i < queries_count; i++) {
        int queries_item = parse_int(ltrim(rtrim(readline())));

        *(queries + i) = queries_item;
    }

    int result_rows;
    int result_columns;
    int** result = swapNodes(n, 2, indexes, queries_count, queries, &result_rows, &result_columns);

    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_columns; j++) {
            fprintf(fptr, "%d", *(*(result + i) + j));

            if (j != result_columns - 1) {
                fprintf(fptr, " ");
            }
        }

        if (i != result_rows - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
