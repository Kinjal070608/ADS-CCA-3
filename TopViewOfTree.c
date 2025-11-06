#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

struct node* insert( struct node* root, int data ) {
		
	if(root == NULL) {
	
        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;
	  
	} else {
      
		struct node* cur;
		
		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}
	
		return root;
	}
}

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/
void topView( struct node *root) {
     if (root == NULL)
        return;
    struct node* qnode[2000];
    int qhd[2000];
    int front = 0, rear = 0;
    int offset = 1000;
    int seen[2001];
    int value[2001];
    for (int i = 0; i < 2001; i++)
        seen[i] = 0;
    qnode[rear] = root;
    qhd[rear] = 0;
    rear++;
    int minHD = 0, maxHD = 0;
    while (front < rear) {
        struct node* curr = qnode[front];
        int hd = qhd[front];
        front++;
        int idx = hd + offset;
        if (!seen[idx]) {
            seen[idx] = 1;
            value[idx] = curr->data;
        }
        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;
        if (curr->left != NULL) {
            qnode[rear] = curr->left;
            qhd[rear] = hd - 1;
            rear++;
        }
        if (curr->right != NULL) {
            qnode[rear] = curr->right;
            qhd[rear] = hd + 1;
            rear++;
        }
    }
    for (int hd = minHD; hd <= maxHD; hd++) {
        printf("%d ", value[hd + offset]);
    }
}


int main() {
  
    struct node* root = NULL;
    
    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }
  
	topView(root);
    return 0;
}
