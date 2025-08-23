#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

typedef struct _avlnode
{
    int item;
    struct _avlnode *left;
    struct _avlnode *right;
    int height;
} AVLNode;

static int max(int a, int b) { return a > b ? a : b; }
static int h(AVLNode *n) { return n ? n->height : 0; }

static void update_height(AVLNode *n)
{
    if (n)
    {
        n->height = 1 + max(h(n->left), h(n->right));
    }
}
static int balance_fator(AVLNode *n)
{
    return n ? h(n->left) - h(n->right) : 0;
}

static AVLNode *new_node(int value)
{
    AVLNode *n = malloc(sizeof(AVLNode));
    n->item = value;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

void left_rotate(AVLNode **node)
{
    AVLNode *next_root = (*node)->right;
    (*node)->right = next_root->left;
    next_root->left = *node;

    update_height(*node);
    update_height(next_root);
    *node = next_root;
}

void right_rotate(AVLNode **node)
{
    AVLNode *next_root = (*node)->left;
    (*node)->left = next_root->right;
    next_root->right = *node;

    update_height(*node); // 아래 노드 먼저
    update_height(next_root);
    *node = next_root;
}

void reblance(AVLNode **node)
{
    update_height(*node);
    int bf = balance_fator(*node);

    // 왼쪽 편향
    if (bf > 1)
    {
        if (balance_fator((*node)->left) >= 0)
        {
            // LL
            right_rotate(node);
        }
        else
        {
            // LR
            left_rotate(&(*node)->left);
            right_rotate(node);
        }
    }
    // 오른쪽 편향
    else if (bf < -1)
    {
        if (balance_fator((*node)->right) <= 0)
        {
            // RR
            left_rotate(node);
        }
        else
        {
            // RL
            right_rotate(&(*node)->right);
            left_rotate(node);
        }
    }
}

void insert_avl(AVLNode **node, int value)
{
    if (*node == NULL)
    {
        *node = new_node(value);
        return;
    }
    if (value == (*node)->item)
    {
        return;
    }

    if (value < (*node)->item)
    {
        insert_avl(&((*node)->left), value);
    }
    else
    {
        insert_avl(&((*node)->right), value);
    }

    reblance(node);
}

int main()
{
    AVLNode *root = new_node(10);
    insert_avl(&root, 30);
    insert_avl(&root, 40);
    return 0;
}