// 实现二叉查找树的插入、删除、查找操作
#include <stdio.h>
#include <stdlib.h>

// 定义节点
typedef struct treenode
{
    int value;
    struct treenode* left_child;
    struct treenode* right_child;
} treenode;

// 构造二叉树函数,查找函数,删除函数,销毁二叉树函数
void build_tree(treenode** root, int array[], int n);
treenode* search(treenode* root, int number);
void delete_specialnode(treenode* node);
void delete(treenode** root, int number);
void destroy(treenode* root);

// 主函数
int main(void)
{
    // 定义树中元素个数,并读取
    int n;
    scanf("%d", &n);

    // 动态分配数组array,存储数据
    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL)
    {
        printf("Allocated Failure\n");
        return 0;
    }

    // 读取数据
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    // 建立二叉树
    treenode* root = NULL;
    build_tree(&root, array, n);

    // 定义查找目标goal,输入goal
    int goal;
    scanf("%d", &goal);

    // 进行删除,第一次查找包含在删除中
    delete(&root, goal);

    // 再查找
    search(root, goal);

    // 释放内存
    free(array);
    destroy(root);
}

// 构造二叉树(要传二级指针，否则无法正确建树)
void build_tree(treenode** root, int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // 建立新节点并初始化
        treenode* new = (treenode*)malloc(sizeof(treenode));
        if (new == NULL)
            return;
        new->value = array[i];
        new->left_child = NULL;
        new->right_child = NULL;

        // 判断根是否空
        if (*root == NULL)
        {
            *root = new;
            continue;
        }

        // 不为空时
        else
        {
            // 定义tmp用于找到最终位置,final存储tmp的双亲
            treenode* tmp = *root;
            treenode* final = *root;

            // 找到插入位置并插入
            while (tmp != NULL)
            {
                final = tmp;
                if (new->value < tmp->value)
                    tmp = tmp->left_child;
                else
                    tmp = tmp->right_child;
            }

            // 判断插入位置是final的右孩子还是左孩子
            if (new->value > final->value)
                final->right_child = new;
            else
                final->left_child = new;
        }
    }
}

// 查找函数
treenode* search(treenode* root, int number)
{
    // 从根节点开始查找
    treenode* tmp = root;

    // 循环
    while (tmp != NULL)
    {
        // 查找成功
        if (number == tmp->value)
        {
            printf("Found key = %d\n", number);
            return tmp;
        }
        else if (number < tmp->value)
            tmp = tmp->left_child;
        else
            tmp = tmp->right_child;
    }

    // 循环正常结束表示查找失败
    printf("NotFound.\n");
    return NULL;
}

// 删除有左右子树节点的函数
void delete_specialnode(treenode* node)
{
    // 找到前驱节点
    treenode* front = node->left_child;
    treenode* parent = node;

    while (front->right_child)
    {
        parent = front;
        front = front->right_child;
    }

    // 用前驱节点代替该节点
    node->value = front->value;

    // 删除前驱节点（需判断前驱节点是否就是待删节点的左子树节点）
    if (parent == node)
        parent->left_child = front->left_child;
    else
        parent->right_child = front->left_child;
}

// 删除具有指定值的节点
void delete(treenode** root, int number)
{
    // 搜索指定值,判断是否在树中
    treenode* result = search(*root, number);
    if (result == NULL)
    {
        printf("错误：%d不在树中。\n", number);
        return;
    }

    // 指定值在树中
    else
    {
        // 目标节点是根节点时
        if (result == *root)
        {
            // 根节点的左孩子为空
            if ((*root)->left_child == NULL)
                *root = (*root)->right_child;

            // 根节点的右孩子为空
            else if ((*root)->right_child == NULL)
                *root = (*root)->left_child;

            // 根节点左右孩子均不空
            else
                delete_specialnode(*root);
            free(*root);
            return;
        }

        // 目标节点不是根节点
        // 找到目标节点的双亲节点,tmp用于查找,ptr用于存储双亲
        treenode* tmp = *root;
        treenode* ptr = *root;

        // 循环退出时,ptr存储的便是result节点的双亲节点
        while (tmp != result)
        {
            ptr = tmp;
            if (tmp->value < result->value)
                tmp = tmp->right_child;
            else
                tmp = tmp->left_child;
        }

        // 删除节点
        // 目标节点的左子树为空,将目标节点的右子树接给其双亲节点的对应子树
        if (result->left_child == NULL)
        {
            if (ptr->left_child == result)
                ptr->left_child = result->right_child;
            else
                ptr->right_child = result->right_child;
        }

        // 目标节点的右子树为空时
        else if (result->right_child == NULL)
        {
            if (ptr->left_child == result)
                ptr->left_child = result->left_child;
            else
                ptr->right_child = result->left_child;
        }

        // 目标节点具有左右子树时
        else
            delete_specialnode(result);
        free(result);
    }
}

// 递归销毁排序树
void destroy(treenode* root)
{
    // 基本情况
    if (root == NULL)
        return;

    // 递归情况:先释放左右子树,再释放本身
    else
    {
        destroy(root->left_child);
        destroy(root->right_child);
        free(root);
    }
}
