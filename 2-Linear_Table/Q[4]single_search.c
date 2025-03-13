// 这个程序的目的是往链表中插入元素，并进行查找
#include <stdio.h>
#include <stdlib.h>

// 定义常量
#define LOW 0
#define HIGH 20

// 定义节点
typedef struct node
{
    int value;
    struct node *next;
} node;

// 函数原型
void insert(node **p, int x);
void search(node *p, int x);
void destroy(node *p);

// 主函数
int main(void)
{
    // 声明头结点
    node *head = NULL;

    // 读取需要插入的元素个数 并检查合法性
    int number;
    scanf("%d", &number);

    if (!(number >= LOW && number <= HIGH))
        return 0;

    // 临时变量tmp存储待插入元素
    int tmp;

    // 读取元素 并插入
    for (int i = 0; i < number; i++)
    {
        if (i < number - 1)
            scanf("%d ", &tmp);
        else
            scanf("%d", &tmp);

        insert(&head, tmp);
    }

    // 查找指定元素
    int goal;
    scanf("%d", &goal);

    search(head, goal);

    // 销毁链表
    destroy(head);
}

// 插入函数
void insert(node **p, int x)
{
    // 分配新节点 检查并初始化
    node *new = malloc(sizeof(node));
    if (new == NULL)
        return;

    new->value = x;
    new->next = NULL;

    // 判断头结点是否为空
    if (*p == NULL)
    {
        *p = new;
        return;
    }

    // 一般情况
    new->next = *p;
    *p = new;
}

// 搜索函数
void search(node *p, int x)
{
    // 遍历链表进行查找
    while (p != NULL)
    {
        if (p->value == x)
        {
            printf("%d", x);
            return;
        }

        // 迭代
        p = p->next;
    }

    // 链表遍历完成仍未找到
    printf("%d 未找到。", x);
}

// 销毁函数
void destroy(node *p)
{
    // 基本情况
    if (p == NULL)
        return;

    // 递归
    destroy(p->next);
    free(p);
}
