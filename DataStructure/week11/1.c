# include <stdio.h>
# include <stdlib.h>

typedef int ElemType;
typedef struct _binTreeNode{
    ElemType data;
    struct _binTreeNode* left;
    struct _binTreeNode* right;
} BinTreeNode;
typedef BinTreeNode* BinTree;


/* 新建一棵树(返回根节点指针) */
BinTree newBinTree(ElemType e);
/* 销毁一棵树(需要利用到树的遍历) */
void destroyBinTree(BinTree BT);
/* 在树中加入元素 */
void attchOnBinTree(BinTree BT, ElemType e);
/* 前序遍历输出(递归实现) */
void preOrderTraversal_Recursive(BinTree BT);
/* 后序遍历输出(递归实现) */
void postOrderTraversal_Recursive(BinTree BT);

/* 前序遍历输出(非递归实现) */
void preOrderTraversal_Nonrecursive(BinTree BT);
/* 后序遍历输出(非递归实现) */
void postOrderTraversal_Nonrecursive(BinTree BT);

int main()
{
    int a[] = {1, 5, 3, 4, 9, 8, 0, 7, 6, 2};

    // 根节点元素为 5，左边是 < 5 元素，右边是 > 5 元素
    BinTree tree = newBinTree(5);

    for (int i = 0; i < 10; i++) {
        attchOnBinTree(tree, a[i]);
    }

    puts("先序遍历：");
    preOrderTraversal(tree);
    puts("\n=====================");
    puts("后序遍历：");
    postOrderTraversal(tree);
    puts("\n=====================");

    destroyBinTree(tree);

    system("pause");
    return 0;
}

BinTree newBinTree(ElemType e)
{
    BinTree root = (BinTree)malloc(sizeof(BinTreeNode));
    root->data = e;
    root->left = NULL;
    root->right = NULL;

    return root;
}

void attchOnBinTree(BinTree BT, ElemType e)
{
    BinTreeNode* p = BT;
    while (1) {
        if (e < p->data) {
            if (p->left) {
                p = p->left;
            } else {
                p->left = (BinTreeNode*)malloc(sizeof(BinTreeNode));
                p->left->data = e;
                p->left->left = p->left->right = NULL;
                break;
            }
        } else if (e > p->data) {
            if (p->right) {
                p = p->right;
            } else {
                p->right = (BinTreeNode*)malloc(sizeof(BinTreeNode));
                p->right->data = e;
                p->right->left = p->right->right = NULL;
                break;
            }
        } else { // 对于相同元素不做处理
            break;
        }
    }
}


void preOrderTraversal(BinTree BT)
{
    if (BT) {
        printf("%d ", BT->data);
        preOrderTraversal(BT->left);
        preOrderTraversal(BT->right);
    }
}

void postOrderTraversal(BinTree BT)
{
    if (BT) {
        preOrderTraversal(BT->left);
        preOrderTraversal(BT->right);
        printf("%d ", BT->data);
    }
}

void destroyBinTree(BinTree BT)
{
    if (BT) {
        destroyBinTree(BT->left);
        destroyBinTree(BT->right);
        free(BT);
        BT = NULL;
    }
}