// 这个程序的目的是将元素按序插入链表,并输出插入结果
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

// 声明头指针和表长
node *head = NULL;
int length = 0;

// 声明插入函数,打印函数,销毁函数
void insert(int x, int pos);
void print_list(node *p);
void destroy(node *p);

// 主函数
int main(void)
{
    // 读取需要插入的元素个数 并检查合法性
    int number;
    scanf("%d", &number);

    if (!(number > LOW && number <= HIGH))
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

        insert(tmp, i + 1);
    }

    // 输出结果
    print_list(head);

    // 错误插入示例
    insert(tmp, 0);
    insert(tmp, length + 2);

    // 销毁链表
    destroy(head);
}

// 定义插入函数
void insert(int x, int pos)
{
    // 处理不合法位置
    if (pos <= LOW || pos > length + 1)
    {
        printf("错误：插入位置不合法。\n");
        return;
    }

    // 创建一个新节点，检查并初始化
    node *new = malloc(sizeof(node));
    if (new == NULL)
        return;

    new->value = x;
    new->next = NULL;

    // 处理头节点为空的情况
    if (head == NULL)
    {
        head = new;
        length++;
        return;
    }

    // 遍历节点 找到尾节点 并插入
    for (node *ptr = head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->next == NULL)
        {
            ptr->next = new;
            length++;
            return;
        }
    }
}

// 定义打印函数
void print_list(node *p)
{
    // 先打印长度
    printf("%d: ", length);

    // 逐个打印元素
    for (node *ptr = head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->next != NULL)
            printf("%d ", ptr->value);
        else
            printf("%d", ptr->value);
    }

    // 打印换行符
    printf("\n");
}

// 定义销毁函数
void destroy(node *p)
{
    // 基本情况
    if (p == NULL)
        return;

    // 递归
    destroy(p->next);
    free(p);
}
