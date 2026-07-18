#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    int level;
};

struct Node *nullNode;

void initializeNullNode() {
    nullNode = (struct Node*)malloc(sizeof(struct Node));
    if (nullNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    nullNode->key = 0; 
    nullNode->left = nullNode;
    nullNode->right = nullNode;
    nullNode->level = 0;
}

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->left = nullNode;
    newNode->right = nullNode;
    newNode->level = 1; 
    return newNode;
}

struct Node* skew(struct Node *T) {
    if (T == nullNode) {
        return nullNode;
    }
    
    if (T->left->level == T->level && T->left != nullNode) {
        struct Node *L = T->left;
        T->left = L->right;
        L->right = T;
        return L;
    }
    return T;
}

struct Node* split(struct Node *T) {
    if (T == nullNode) {
        return nullNode;
    }

    if (T->right->right->level == T->level && T->right != nullNode) {
        struct Node *R = T->right;
        T->right = R->left;
        R->left = T;
        
        R->level++;
        return R;
    }
    return T;
}

struct Node* insertRecursive(struct Node *T, int key) {
    if (T == nullNode) {
        return createNode(key);
    } else if (key < T->key) {
        T->left = insertRecursive(T->left, key);
    } else if (key > T->key) {
        T->right = insertRecursive(T->right, key);
    } else {
        return T;
    }

    T = skew(T);
    T = split(T);

    return T;
}

struct Node* AA_insert(struct Node *root, int key) {
    if (root == NULL) {
        initializeNullNode();
    }
    return insertRecursive(root, key);
}

struct Node* findSuccessor(struct Node *T) {
    T = T->right;
    while (T->left != nullNode) {
        T = T->left;
    }
    return T;
}

struct Node* rebalance(struct Node *T) {
    if (T == nullNode) {
        return nullNode;
    }
    
    if (T->left->level < T->level - 1 || T->right->level < T->level - 1) {
        T->level--;
        
        if (T->right->level > T->level) {
            T->right->level = T->level;
        }
    }

    T = skew(T);
    T->right = skew(T->right);
    T->right->right = skew(T->right->right);
    T = split(T);
    T->right = split(T->right);

    return T;
}

struct Node* deleteRecursive(struct Node *T, int key) {
    if (T == nullNode) {
        return nullNode;
    }

    if (key < T->key) {
        T->left = deleteRecursive(T->left, key);
    } else if (key > T->key) {
        T->right = deleteRecursive(T->right, key);
    } else {
        if (T->left == nullNode && T->right == nullNode) {
            free(T);
            return nullNode;
        } else if (T->left == nullNode || T->right == nullNode) {
            struct Node *temp = (T->left == nullNode) ? T->right : T->left;
            free(T);
            return temp;
        } else {
            struct Node *succ = findSuccessor(T);
            T->key = succ->key;
            T->right = deleteRecursive(T->right, succ->key);
        }
    }

    T = rebalance(T);
    return T;
}

struct Node* AA_delete(struct Node *root, int key) {
    if (root == NULL || root == nullNode) {
        return nullNode; // Ensure it returns nullNode if already empty
    }
    
    // Perform recursive deletion
    struct Node* newRoot = deleteRecursive(root, key);
    
    // Check if the deletion made the tree empty
    if (newRoot == NULL) {
        return nullNode;
    }

    return newRoot;
}

void inorderTraversal(struct Node *T) {
    if (T == nullNode) {
        return;
    }
    inorderTraversal(T->left);
    printf("(K:%d, L:%d) ", T->key, T->level);
    inorderTraversal(T->right);
}

void displayMenu() {
    printf("\n--- AA Tree Menu ---\n");
    printf("1. Insert Key\n");
    printf("2. Delete Key\n");
    printf("3. Display Tree (In-order)\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    initializeNullNode(); 
    struct Node *root = nullNode;
    int choice;
    int key;

    printf("AA Tree Interactive Program\n");

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer
            while (getchar() != '\n'); 
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                if (scanf("%d", &key) == 1) {
                    root = AA_insert(root, key);
                    printf("Key %d inserted.\n", key);
                } else {
                    printf("Invalid key input.\n");
                    while (getchar() != '\n');
                }
                break;
            case 2:
                printf("Enter key to delete: ");
                if (scanf("%d", &key) == 1) {
                    root = AA_delete(root, key);
                    printf("Attempted to delete key %d.\n", key);
                } else {
                    printf("Invalid key input.\n");
                    while (getchar() != '\n');
                }
                break;
            case 3:
                printf("Current Tree (In-order): ");
                if (root == nullNode) {
                    printf("Tree is empty.\n");
                } else {
                    inorderTraversal(root);
                    printf("\n");
                }
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                // Note: Full tree memory cleanup is omitted for brevity but required in production.
                free(nullNode);
                break;
            default:
                printf("Invalid choice. Please select 1, 2, 3, or 4.\n");
        }
    } while (choice != 4);

    return 0;
}