// 这个程序的目的是将输入元素插入单链表,并删除指定位置元素
#include <stdio.h>
#include <stdlib.h>

// 定义常量
#define LOW 0
#define HIGH 10000

// 定义表长
int length = 0;

// 定义节点
typedef struct node
{
    int value;
    struct node *next;
} node;

// 声明插入函数,删除函数,打印函数,销毁函数
void insert(node **p, int x);
void delete(node **p, int pos);
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

    // 设置头指针
    node *head = NULL;

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

    // 删除指定元素
    int position;
    scanf("%d", &position);

    delete(&head, position);

    // 打印链表
    print_list(head);

    // 销毁链表
    destroy(head);
}

// 插入函数原型
void insert(node **p, int x)
{
    // 创建一个新节点，检查并初始化
    node *new = malloc(sizeof(node));
    if (new == NULL)
        return;

    new->value = x;
    new->next = NULL;

    // 处理头节点为空的情况
    if (*p == NULL)
    {
        *p = new;
        length++;
        return;
    }

    // 顺次插入
    new->next = *p;
    *p = new;
    length++;
}

// 删除指定元素
void delete(node **p, int pos)
{
    // 判断特殊位置
    if (pos <= 0 || pos > length)
    {
        printf("错误：删除位置不合法。\n");
        return;
    }

    // 删除首元素单独处理,注意不要忽视表长为1的情况
    if (pos == 1)
    {
        if (length == 1)
        {
            free(*p);
            *p = NULL;
            length--;
            return;
        }
        else
        {
            node *ptr = *p;
            *p = (*p)->next;
            free(ptr);
            length--;
            return;
        }
    }

    // 计数 并删除指定位置
    int count = 1;
    node *tmp = *p;

    // 循环
    while (count != pos)
    {
        if (count == pos - 1)
        {
            // 尾结点特殊处理
            if (pos == length)
            {
                free(tmp->next);
                tmp->next = NULL;
                length--;
                return;
            }

            // 非尾部节点
            else
            {
                node *f = tmp->next;
                tmp->next = f->next;
                free(f);
                length--;
                return;
            }
        }

        // 迭代
        tmp = tmp->next;
        count++;
    }
}

// 打印链表
void print_list(node *p)
{
    // 先打印长度
    if (length != 0)
        printf("%d: ", length);
    else
        printf("%d:", length);

    // 逐个打印元素
    for (node *ptr = p; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->next != NULL)
            printf("%d ", ptr->value);
        else
            printf("%d", ptr->value);
    }

    // 打印换行符
    printf("\n");
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
