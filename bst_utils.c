#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bst.h"

BSTNode *make_node(int init_value)
{
    BSTNode *node = malloc(sizeof(BSTNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->item = init_value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// BSTNode의 이중 포인터 - node 포인터 값을 변경시키기 위해 주소 값을 보냄
void insert_bstnode(BSTNode **node, int value)
{
    if (*node == NULL)
    {
        BSTNode *new_node = make_node(value);
        *node = new_node;
        return;
    }

    if (value < (*node)->item)
    {
        insert_bstnode(&((*node)->left), value);
    }
    else if (value > (*node)->item)
    {
        insert_bstnode(&((*node)->right), value);
    }
    else
    {
        return;
    }
}

BSTNode *search_bstnode(BSTNode *node, int value)
{
    if (node == NULL || value == node->item)
    {
        return node;
    }

    return value < node->item
               ? search_bstnode(node->left, value)
               : search_bstnode(node->right, value);
}

void inorder_travasal(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder_travasal(root->left);
    printf("%d ", root->item);
    inorder_travasal(root->right);
}

BSTNode *max_node(BSTNode *root)
{
    if (root == NULL || root->right == NULL)
    {
        return root;
    }
    return max_node(root->right);
}

BSTNode *min_node(BSTNode *root)
{
    if (root == NULL || root->left == NULL)
    {
        return root;
    }
    return min_node(root->left);
}

#define HAS(v) ((v) == NULL ? 0 : 1)

void delete_bstnode(BSTNode **node, int value)
{
    if (*node == NULL)
    {
        return;
    }

    BSTNode *cur = *node;
    int node_item = cur->item;

    if (node_item == value)
    {
        BSTNode *lmax = max_node(cur->left);
        BSTNode *rmin = min_node(cur->right);
        BSTNode *replace_node = (lmax ? lmax : (rmin ? rmin : NULL));

        if (replace_node == NULL)
        {
            free(cur);
            *node = NULL;
            return;
        }
        int replace_value = replace_node->item;
        cur->item = replace_value;

        if (lmax)
        {
            delete_bstnode(&(cur->left), replace_value);
        }
        else
        {
            delete_bstnode(&(cur->right), replace_value);
        }
    }
    else if (value < node_item)
    {
        delete_bstnode(&(cur->left), value);
    }
    else
    {
        delete_bstnode(&(cur->right), value);
    }
}
