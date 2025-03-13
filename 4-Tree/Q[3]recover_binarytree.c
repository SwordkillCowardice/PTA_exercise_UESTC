// 根据前序序列和中序序列还原二叉树,并计算其高度
#include <stdio.h>
#include <stdlib.h>

// 定义树节点
typedef struct treenode
{
    char letter;
    struct treenode* left_child;
    struct treenode* right_child;
} treenode;

// 建造二叉树函数接口, 建造二叉树, 获取二叉树高度, 销毁二叉树
treenode* build_tree(char priorder[], char midorder[], int n);
treenode* build(char priorder[], char midorder[], int sign[], int start, int end);
int get_height(treenode* root);
void destroy(treenode* root);

// 主函数
int main(void)
{
    // 定义节点数n,读取n
    int n;
    scanf("%d", &n);

    // 动态分配先序数组,中序数组
    char* pri = (char*)malloc(n * sizeof(char));
    if (pri == NULL)
        return 0;

    char* mid = (char*)malloc(n * sizeof(char));
    if(mid == NULL)
    {
        free(pri);
        return 0;
    }

    // 分别读取先序和中序序列
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &pri[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &mid[i]);
    }

    // 定义根节点，建立二叉树
    treenode* root = build_tree(pri, mid, n);

    // 获得树的高度并输出结果
    int height = get_height(root);
    printf("%d", height);

    // 释放内存
    free(pri);
    free(mid);
    destroy(root);
}

// 建立二叉树的函数接口,为了简洁
treenode* build_tree(char priorder[], char midorder[], int n)
{
    // 分配标志数组
    int* sign = (int*)malloc(n * sizeof(int));
    if (sign == NULL)
        return NULL;

    // 初始化sign数组
    for (int i = 0; i < n; i++)
        sign[i] = 0;

    // 返回结果
    treenode* result = build(priorder, midorder, sign, 0, n - 1);
    free(sign);
    return result;
}

// 递归地建立二叉树(start和end分别是构造以某个节点为根的二叉树的起始位置和终点位置)
treenode* build(char priorder[], char midorder[], int sign[], int start, int end)
{
    // 基本情况
    if (start > end)
        return NULL;

    // 递归情况
    // 分配一个新的树节点并初始化
    treenode* new = (treenode*)malloc(sizeof(treenode));
    if (new == NULL)
        return NULL;
    new->letter = priorder[start];
    new->left_child = NULL;
    new->right_child = NULL;

    // 该节点为叶子节点时
    if (start == end)
        return new;

    // 找到当前节点在中序序列中的位置,并标记当前节点(标记的目的是避免后续节点确定左子树时出错)
    int index = 0;
    while (midorder[index] != priorder[start])
        index++;
    sign[index] = 1;

    // 确定该节点左子树上元素个数
    // 根据中序序列中该节点左边的节点是否已被标记(最后一个被标记的节点和该节点之间的元素属于该左子树)
    int tmp = -1;
    for (int i = index - 1; i >= 0; i--)
    {
        if (sign[i] == 1)
        {
            tmp = i;
            break;
        }
    }

    // 递归建立左右子树
    // 确定左右子树在先序序列中的起始和结束建立位置,是本题的最大难点
    new->left_child = build(priorder, midorder, sign, start + 1, start + index - tmp - 1);
    new->right_child = build(priorder, midorder,sign, start + index - tmp, end);
    return new;
}

// 递归地计算二叉树高度
int get_height(treenode* root)
{
    // 基本情况
    if (root == NULL)
        return 0;

    // 递归情况
    int height1 = get_height(root->left_child) + 1;
    int height2 = get_height(root->right_child) + 1;
    return height1 > height2? height1:height2;
}

// 递归地销毁二叉树
void destroy(treenode* root)
{
    // 基本情况
    if (root == NULL)
        return;

    // 递归情况
    destroy(root->left_child);
    destroy(root->right_child);
    free(root);
}
