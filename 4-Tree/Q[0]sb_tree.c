// 创建一棵二叉树,并进行中序遍历
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点
typedef struct node
{
    int value;
    struct node* left_child;
    struct node* right_child;
} node;

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

        // 读入各节点的值
        scanf("%d", &left->value);
        scanf("%d", &right->value);
        scanf("%d", &root->value);

        // 建立二叉树结构
        root->left_child = left;
        root->right_child = right;

        // 输出结果
        printf("%d\n", root->left_child->value);
        printf("%d\n", root->value);
        printf("%d\n", root->right_child->value);

        // 释放内存
        free(root->left_child);
        free(root->right_child);
        free(root);
    }
}
