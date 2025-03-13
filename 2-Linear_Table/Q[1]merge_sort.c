// 归并排序
#include <stdio.h>
#include <stdlib.h>

// 函数原型
void merge_sort(int array[], int n);
void m_sort(int array[], int tmp[], int low, int high);
void merge(int array[], int tmp[], int low, int mid, int high);

// 主函数
int main(void)
{
    // 读取元素个数
    int n;
    scanf("%d", &n);

    // 动态分配内存,存储元素
    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL)
        return 0;

    // 逐个读取元素
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    // 调用归并排序
    merge_sort(array, n);

    // 打印结果
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    // 释放内存
    free(array);
}

// 函数接口
void merge_sort(int array[], int n)
{
    // 动态分配内存
    int* tmp = (int*)malloc(n * sizeof(int));
    if (tmp == NULL)
        return;

    else
    {
        m_sort(array, tmp, 0, n - 1);
        free(tmp);
    }
}

// 实现归并排序
void m_sort(int array[], int tmp[], int low, int high)
{
    // 基本情况
    if (low >= high)
        return;

    // 递归情况
    else
    {
        // 求出中间位置,递归处理左右半区,再合并
        int mid = (low + high) / 2;
        m_sort(array, tmp, low, mid);
        m_sort(array, tmp, mid + 1, high);
        merge(array, tmp, low, mid, high);
    }
}

// 实现合并操作
void merge(int array[], int tmp[],int low, int mid, int high)
{
    // 定义左半区和右半区仍未排序的第一个元素
    int l_pos = low;
    int r_pos = mid + 1;

    // 定义插入位置
    int pos = low;

    // 将元素按序插入tmp
    while (l_pos <= mid && r_pos <= high)
    {
        if (array[l_pos] <= array[r_pos])
            tmp[pos++] = array[l_pos++];
        else
            tmp[pos++] = array[r_pos++];
    }

    // 处理可能未插入的半区
    while (l_pos <= mid)
        tmp[pos++] = array[l_pos++];

    while (r_pos <= high)
        tmp[pos++] = array[r_pos++];

    // 将元素插回array
    while (low <= high)
    {
        array[low] = tmp[low];
        low++;
    }
}
