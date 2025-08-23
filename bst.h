typedef struct _bstnode
{
    int item;
    struct _bstnode *left;
    struct _bstnode *right;
} BSTNode;

BSTNode *make_node(int init_value);

void insert_bstnode(BSTNode **node, int value);
