#include <stdio.h>
#include <stdlib.h>

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
static int balance_factor(AVLNode *n)
{
    return n ? h(n->left) - h(n->right) : 0;
}

AVLNode *make_node(int value)
{
    AVLNode *node = malloc(sizeof(AVLNode));
    node->item = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

static void rotate_left(AVLNode **node)
{
    AVLNode *new_root = (*node)->right;
    (*node)->right = new_root->left;
    new_root->left = *node;

    update_height(*node);
    update_height(new_root);
    *node = new_root;
}

static void rotate_right(AVLNode **node)
{
    AVLNode *new_root = (*node)->left;
    (*node)->left = new_root->right;
    new_root->right = *node;

    update_height(*node);
    update_height(new_root);
    *node = new_root;
}

static void reblance(AVLNode **node)
{
    update_height(*node);
    int bf = balance_factor(*node);

    // l 서브트리 편향
    if (bf >= 2)
    {
        if (balance_factor((*node)->left) >= 0)
        {
            // LL
            rotate_right(node);
        }
        else
        {
            // LR
            rotate_left(&(*node)->left);
            rotate_right(node);
        }
    }
    // r 서브트리 편향
    else if (bf <= -2)
    {
        if (balance_factor((*node)->right) >= 0)
        {
            // RR
            rotate_left(node);
        }
        else
        {
            // RL
            rotate_right(&(*node)->right);
            rotate_left(node);
        }
    }
}

void insert_node(AVLNode **root, int value)
{
    if (*root == NULL)
    {
        *root = make_node(value);
        return;
    }
    if (value == (*root)->item)
    {
        return;
    }

    if (value < (*root)->item)
    {
        insert_node(&((*root)->left), value);
    }
    else
    {
        insert_node(&((*root)->right), value);
    }

    reblance(root);
}

void delete_node(AVLNode **root, int value)
{
    if (*root == NULL)
    {
        return;
    }
}

int main()
{
    AVLNode *root = make_node(10);
    insert_node(&root, 20);
    insert_node(&root, 30);
    return 0;
}