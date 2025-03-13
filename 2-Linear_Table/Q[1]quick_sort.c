// 实现快速排序
#include <stdio.h>
#include <stdlib.h>

// 函数原型
void quick_sort(int array[], int n);
void q_sort(int array[], int low, int high);

// 主函数
int main(void)
{
    // 定义元素个数n，读取n
    int n;
    scanf("%d", &n);

    // 动态分配内存,存储数组
    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL)
        return 0;

    // 读取元素
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    // 调用快速排序
    quick_sort(array, n);

    // 输出结果
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    // 释放内存
    free(array);
}

// 接口定义
void quick_sort(int array[], int n)
{
    q_sort(array, 0, n - 1);
}

// 函数体
void q_sort(int array[], int low, int high)
{
    // 基本情况
    if (low >= high)
        return;

    // 递归情况
    else
    {
        // 定义枢纽关键字
        int key = array[low];

        // 定义高位指针和低位指针（low, high保持不变,后面递归用）
        int left = low;
        int right = high;

        // 循环比较高位元素和关键字
        while (left < right)
        {
            while (array[right] >= key && left < right)
                right--;
            if (array[right] < key)
            {
                array[left] = array[right];
                left++;
            }
            while (array[left] <= key && left < right)
                left++;
            if (array[left] > key)
            {
                array[right] = array[left];
                right--;
            }
        }

        // 插入枢纽关键字
        array[left] = key;

        // 递归地进行快排
        q_sort(array, low, left - 1);
        q_sort(array, left + 1, high);
    }
}
