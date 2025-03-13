// 整型关键字的散列映射
#include <stdio.h>
#include <stdlib.h>

// 主函数
int main(void)
{
    // 定义关键字总数和散列表长度
    int n;
    int p;

    // 读入数据
    scanf("%d", &n);
    scanf("%d", &p);

    // 创建哈希表和结果存储数组
    int* Hashtable = (int*)malloc(p * sizeof(int));
    if (Hashtable == NULL)
        return 0;

    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL)
    {
        free(Hashtable);
        return 0;
    }

    // 初始化哈希表(表示未存放关键字时的值)
    for (int i = 0; i < p; i++)
    {
        Hashtable[i] = -5;
    }

    // 定义标志变量判断后续循环退出情况
    int sign;

    // 循环读取元素，并做处理
    for (int i = 0; i < n; i++)
    {
        // 更新sign
        sign = 1;

        // 读取元素并计算初始哈希地址
        scanf("%d", &result[i]);
        int adr = result[i] % p;

        // 线性探测处理
        // (SM题目，你下次把题目要求讲清楚会死吗?你就不能在题目
        //  要求里面把同样的关键字只输出第一个位置但不存储写清楚吗)

        // tmp变量可用作线性探测（为了简化代码逻辑直接循环）
        int tmp = adr;

        // 循环退出条件为找到空位置或者该关键字已经被存储了
        while (Hashtable[adr] != -5)
        {
            // 判断关键字是否重复，重复则不再存储，位置输出第一个
            if (Hashtable[adr] == result[i])
            {
                sign = 0;
                result[i] = adr;
                break;
            }

            adr = (++tmp) % p;
        }

        // 若是因为关键字重复退出，直接下一轮
        if (sign == 0)
            continue;

        // 正常退出时，更新哈希表和新的地址
        else
        {
            Hashtable[adr] = result[i];
            result[i] = adr;
        }
    }

    // 输出结果
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", result[i]);
    }
    printf("%d", result[n - 1]);

    // 释放内存
    free(Hashtable);
    free(result);
    return 0;
}
