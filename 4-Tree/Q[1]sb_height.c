// 创建一棵二叉树,并计算其高度
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点
typedef struct node
{
    int value;
    struct node* left_child;
    struct node* right_child;
} node;

// 计算高度函数
int get_height(node* root);

// 主函数
int main(void)
{
    // 建立根节点
    node* root = (node*)malloc(sizeof(node));
    if (root == NULL)
        return 0;

    else
    {
        // 建立左子树节点
        node* left = (node*)malloc(sizeof(node));
        if (left == NULL)
        {
            free(root);
            return 0;
        }

        // 建立右子树节点
        node* right = (node*)malloc(sizeof(node));
        if (right == NULL)
        {
            free(root);
            free(left);
        }

        // 建立二叉树结构
        root->left_child = left;
        root->right_child = right;
        left->left_child = NULL;
        left->right_child = NULL;
        right->left_child = NULL;
        right->right_child = NULL;

        // 读入各节点的值
        scanf("%d", &left->value);
        scanf("%d", &right->value);
        scanf("%d", &root->value);

        // 计算高度
        int result = get_height(root);
        printf("%d", result);

        // 释放内存
        free(root->left_child);
        free(root->right_child);
        free(root);
    }
}

// 实现计算高度函数
int get_height(node* root)
{
    // 基本情况
    if (root == NULL)
        return 0;
    else if (root->left_child == NULL && root->right_child == NULL)
        return 1;

    // 递归情况
    else
    {
        int tmp1 = get_height(root->left_child);
        int tmp2 = get_height(root->right_child);
        return tmp1 > tmp2? tmp1 + 1:tmp2 + 1;
    }
}
