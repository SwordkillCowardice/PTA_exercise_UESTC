// 实现希尔排序
#include <stdio.h>
#include <stdlib.h>

// 函数原型
void shell_sort(int array[], int n);

// 主函数
int main(void)
{
    // 定义元素个数n，读取n
    int n;
    scanf("%d", &n);

    // 动态分配数组,存储元素
    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL)
        return 0;

    // 读取元素
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    // 调用排序
    shell_sort(array, n);

    // 打印结果
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    // 释放内存
    free(array);
}

// 实现希尔排序
void shell_sort(int array[], int n)
{
    // 定义增量inc,循环减少inc;按inc为步长,做插入排序
    for (int inc = n / 2; inc > 0; inc /= 2)
    {
        // 从inc位置开始交叉插入元素
        for (int i = inc; i < n; i++)
        {
            // 定义key存储当前待插入元素
            int key = array[i];

            // 定义该序列中有序区最后一个元素的索引j
            int j = i - inc;

            // 确定插入位置
            while (array[j] > key && j >= 0)
            {
                array[j + inc] = array[j];
                j -= inc;
            }

            // 插入
            array[j + inc] = key;
        }
    }
}
