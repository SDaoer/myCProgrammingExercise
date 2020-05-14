# include <stdio.h>
# include <stdlib.h>

typedef int ElemType;
typedef struct _binTreeNode{
    ElemType data;
    struct _binTreeNode* left;
    struct _binTreeNode* right;
} BinTreeNode;
typedef BinTreeNode* BinTree;


/* �½�һ����(���ظ��ڵ�ָ��) */
BinTree newBinTree(ElemType e);
/* ����һ����(��Ҫ���õ����ı���) */
void destroyBinTree(BinTree BT);
/* �����м���Ԫ�� */
void attchOnBinTree(BinTree BT, ElemType e);
/* ǰ��������(�ݹ�ʵ��) */
void preOrderTraversal_Recursive(BinTree BT);
/* ����������(�ݹ�ʵ��) */
void postOrderTraversal_Recursive(BinTree BT);

/* ǰ��������(�ǵݹ�ʵ��) */
void preOrderTraversal_Nonrecursive(BinTree BT);
/* ����������(�ǵݹ�ʵ��) */
void postOrderTraversal_Nonrecursive(BinTree BT);

int main()
{
    int a[] = {1, 5, 3, 4, 9, 8, 0, 7, 6, 2};

    // ���ڵ�Ԫ��Ϊ 5������� < 5 Ԫ�أ��ұ��� > 5 Ԫ��
    BinTree tree = newBinTree(5);

    for (int i = 0; i < 10; i++) {
        attchOnBinTree(tree, a[i]);
    }

    puts("���������");
    preOrderTraversal(tree);
    puts("\n=====================");
    puts("���������");
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
        } else { // ������ͬԪ�ز�������
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