// 根据前序序列重构二叉树
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义数据最大长度
#define MAX 9

// 定义树节点
typedef struct treenode
{
    int value;
    struct treenode* left_child;
    struct treenode* right_child;
} treenode;

// 构造二叉树,先序遍历,销毁二叉树
treenode* build_tree(char** array, int* index, int length);
void prior_order(treenode* root);
void destroy(treenode* root);

// 主函数
int main(void)
{
    // 定义先序序列长度
    int length;
    scanf("%d", &length);

    // 二维数组array存储先序序列
    char** array = (char**)malloc(length * sizeof(char*));
    if (array == NULL)
        return 0;

    // 申请array每一维
    for (int i = 0; i < length; i++)
    {
        array[i] = (char*)malloc(MAX * sizeof(char));
        if (array[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(array[j]);
                return 0;
            }
            free(array);
            break;
        }
    }

    // 读取先序序列
    for (int i = 0; i < length; i++)
    {
        scanf("%s", array[i]);
    }

    // 构造二叉树
    int index = 0;
    treenode* root = build_tree(array, &index, length);

    // 先序遍历二叉树
    prior_order(root);

    // 释放内存
    for (int i = 0; i < length; i++)
    {
        free(array[i]);
    }
    free(array);

    // 销毁二叉树
    destroy(root);
}

// 递归构造二叉树
treenode* build_tree(char** array, int* index, int length)
{
    // 基本情况 (当前节点为空节点/已经到达序列末尾)
    if (!strcmp(array[*index], "#") || *index >= length)
    {
        (*index)++;
        return NULL;
    }

    // 递归情况
    else
    {
        // 建立新节点并赋值
        treenode* new = (treenode*)malloc(sizeof(treenode));
        if (new == NULL)
            return NULL;

        // 给当前节点赋值
        char* ptr;
        new->value = strtol(array[*index], &ptr, 10);

        // 更新index
        (*index)++;

        // 建立该节点的左子树
        new->left_child = build_tree(array, index, length);

        // 建立右子树
        new->right_child = build_tree(array, index, length);

        // 返回本轮结果
        return new;
    }
}

// 递归进行先序遍历
void prior_order(treenode* root)
{
    // 基本情况
    if (root == NULL)
        return;

    // 递归情况
    // 先访问根节点,再访问左右孩子
    else
    {
        printf("%d\n", root->value);
        prior_order(root->left_child);
        prior_order(root->right_child);
    }
}

// 销毁二叉树
void destroy(treenode* root)
{
    // 基本情况
    if (root == NULL)
        return;

    // 递归情况
    // 先释放左右孩子,再释放该节点
    else
    {
        destroy(root->left_child);
        destroy(root->right_child);
        free(root);
    }
}