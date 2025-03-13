// 辨别排序类型并输出下一轮排序的结果
// 这道题出题不严谨：因为无论是归并排序还是插入排序,都可能出现某轮排序结果和下一轮排序结果完全相同的情况
// 即A->……->B->B->C->…… 此时如果题目给的中间序列是B,你无法确定下一轮输出B还是C
// PTA和牛客要求插入排序输出下下次的排序结果(PTA测试点2考察,即输出C)
// PTA要求归并排序输出下一次排序的结果(虽然其实排序的结果是一样的,测试点5 6考察,即输出B)
#include <stdio.h>
#include <stdlib.h>

// 非递归归并排序函数原型(这里是修改版的,为了迎合题目需求)
void merge_sort(int array[], int mid[], int n);
void merge(int array[], int tmp[], int begin1, int end1, int begin2, int end2);

// 主函数
int main(void)
{
    // 定义数据元素个数n,读取n
    int n;
    scanf("%d", &n);

    // 动态分配内存,array存储原数据,mid存储中间结果
    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL)
        return 0;

    int* mid = (int*)malloc(n * sizeof(int));
    if (mid == NULL)
    {
        free(array);
        return 0;
    }

    // 分别读取元素和中间结果
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &mid[i]);
    }

    // 判断是否为插入排序(特点：除有序区外，其他元素和原数据保持一致)
    // 定义有序区末元素索引count,标志变量sign
    int count = 0;
    int sign = 0;

    // 求出有序区末元素位置(count不可能等于n-1,否则已经排好不符合题意)
    while (mid[count] <= mid[count + 1])
        count++;

    // 比较无序区元素和原数据,并更新sign,sign为1表示序列为归并排序结果
    for (int i = count + 1; i < n; i++)
    {
        if (array[i] != mid[i])
        {
            sign = 1;
            break;
        }
    }

    // 符合插入排序特点时
    if (!sign)
    {
        // 输出判断结果
        printf("Insertion Sort\n");

        // 再做一轮插入排序
        // key为待插入元素, j为有序区最后一个数据的下标
        int key = mid[count + 1];
        int j = count;

        // 找到插入位置(移动有序区元素)
        while (mid[j] > key && j >= 0)
        {
            mid[j + 1] = mid[j];
            j--;
        }
        // 插入
        mid[j + 1] = key;
    }

    // 确定为归并排序(题目给的归并排序为非递归实现)
    else
    {
        // 输出判断结果
        printf("Merge Sort\n");

        // 调用修改的归并排序得出下一轮结果
        merge_sort(array, mid, n);

        // 把结果拷贝回mid
        for (int i = 0; i < n; i++)
        {
            mid[i] = array[i];
        }
    }

    // 输出下一轮的排序情况(即答案)
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", mid[i]);
    }
    printf("%d", mid[n - 1]);

    // 释放内存
    free(array);
    free(mid);
}

// 实现归并
void merge_sort(int array[], int mid[], int n)
{
    // 开辟临时数组tmp,暂存每轮归并结果
    int* tmp =(int*)malloc(n * sizeof(int));
    if (tmp == NULL)
        return;

    // 循环进行归并
    // 定义初始步长gap,辅助标记变量change
    int gap = 1;
    int change = 0;

    // 每轮以gap为长归并元素
    while (gap < n)
    {
        // 定义same判断该轮排序结果与题给序列相同
        int same = 1;

        // 归并
        for (int i = 0; i < n; i += 2 * gap)
        {
            // 求出两子序列的起始位置(begin2为后一个子序列起始位置,若大于n,说明只剩一组,不需要归并)
            int begin1 = i;
            int begin2 = i + gap;
            if (begin2 >= n)
                break;

            // 求出两子序列的终止位置(end2>n没关系,只要还有下一组,无论有几个元素都要归并(即从start2到n-1的元素))
            int end1 = begin2 - 1;
            int end2 = begin2 + gap - 1;
            if (end2 >= n)
                end2 = n - 1;

            // 子序列两两归并
            merge(array, tmp, begin1, end1, begin2, end2);
        }

        // 归并完检查是否需要退出
        if (change == 1)
            break;

        // 比对本轮结果与题给序列
        for (int i = 0; i < n; i++)
        {
            if (array[i] != mid[i])
            {
                same = 0;
                break;
            }
        }

        // 如果本轮相同,则更新change,以在下一轮做完后退出
        if (same == 1)
            change = 1;

        // 更新gap
        gap *= 2;
    }

    // 释放内存
    free(tmp);
}

// 实现合并操作
void merge(int array[], int tmp[], int begin1, int end1, int begin2, int end2)
{
    // 定义pos,pos为本轮归并起始位置
    int pos = begin1;

    // 定义start和end分别保存本轮归并的起始位置和终点位置,为后面拷贝做准备
    int start = begin1;
    int end = end2;

    // 循环比较两组元素,按序插入tmp数组(循环退出时至少还有一组没插完)
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (array[begin1] <= array[begin2])
            tmp[pos++] = array[begin1++];
        else
            tmp[pos++] = array[begin2++];
    }

    // 处理可能没插完的组别
    while (begin1 <= end1)
        tmp[pos++] = array[begin1++];
    while (begin2 <= end2)
        tmp[pos++] = array[begin2++];

    // 将数据拷回array
    while (start <= end)
    {
        array[start] = tmp[start];
        start++;
    }
}
