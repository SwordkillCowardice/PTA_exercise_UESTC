// 判断栈操作的合法性
#include <stdio.h>
#include <stdlib.h>

// 定义序列最大长度（含零终止符）
#define LENGTH 101

// 主函数
int main(void)
{
    // 定义待测序列个数和堆栈最大容量
    int n;
    int m;

    // 读入数据
    scanf("%d", &n);
    scanf("%d", &m);

    // 动态分配二维数组
    char** array = (char**)malloc(n * sizeof(char*));
    if (array == NULL)
        return 0;

    for (int i = 0; i < n; i++)
    {
        array[i] = (char*)malloc(LENGTH * sizeof(char));
        if (array[i] == NULL)
            return 0;
    }

    // 读取序列
    for (int i = 0; i < n; i++)
    {
        scanf("%100s", array[i]);
    }

    // 定义堆栈容量，标志变量
    int rest;
    int sign;

    // 对每个序列分别判断
    for (int i = 0; i < n; i++)
    {
        // 变量更新
        sign = 1;
        rest = 0;

        // 逐个字符判断
        for (int j = 0; array[i][j] != '\0'; j++)
        {
            // 入栈时需要栈未满
            if (array[i][j] == 'S')
            {
                // 栈满仍然入栈，则不合法，否则更新rest
                if (rest == m)
                {
                    printf("NO\n");
                    sign = 0;
                    break;
                }

                else
                   rest++;
            }

            // 进行出栈时
            else
            {
                // 栈空仍然出栈，则不合法
                if (rest == 0)
                {
                   printf("NO\n");
                   sign = 0;
                   break;
                }

                else
                   rest--;
            }
        }

        // 退出循环时，判断是否合法
        if (sign == 1)
        {
            if (rest == 0)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }

    // 释放内存
    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}
