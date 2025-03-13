// 辨别排序类型并输出下一轮排序的结果
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    // 定义有序区元素索引count,标志变量sign
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

        // 进行下一轮排序
        // 首先确定当前排序情况(题目已知至少进行了一轮排序)
        // 定义number变量,存储最小有序组的长度;定义group变量,存储当前总组数
        int number = 2;
        int group = round(n / 2);

        // 定义变量judge辅助判断
        int judge = 1;

        // 循环判断组间关系
        while (judge)
        {
            // 定义步长gap;剩余组数rest
            int gap = 2 * number;
            int rest = group;

            // 判断两组元素交界位置是否满足大小关系
            for (int i = number - 1; rest >= 2; i += gap)
            {
                // 若交界处不满足大小关系,则说明number为当前最大有序组组长
                if (mid[i] > mid[i + 1])
                {
                    judge = 0;
                    break;
                }

                // 更新剩余组数
                rest -= 2;
            }

            // 判断为组间有序,则说明有序组长度可翻倍
            if (judge)
                number *= 2;
        }

        // 根据所得number进行下一轮排序
        // 开一个临时数组,存储归并暂时结果
        int* tmp = (int*)malloc(n * sizeof(int));
        if (tmp == NULL)
            return 0;

        // 定义gap存储归并时移动步长
        int gap = 2 * number;

        // 以两倍组长移动归并初始位置
        for (int i = 0; i < n; i += gap)
        {
            // 分别求出待归并的两组元素的begin
            int begin1 = i;
            int begin2 = i + number;

            // 没有下一组时,直接将当前组拷入mid
            if (begin2 >= n)
            {
                for (int j = begin1; j < n; j++)
                {
                    tmp[j] = mid[j];
                }
                break;
            }

            // 分别求出两组元素的end
            int end1 = begin2 - 1;
            int end2 = begin2 + number - 1;
            if (end2 >= n)
                end2 = n - 1;

            // 定义初始位置pos
            int pos = begin1;

            // 循环比较元素
            while (begin1 <= end1 && begin2 <= end2)
            {
                if (mid[begin1] <= mid[begin2])
                    tmp[pos++] = mid[begin1++];
                else
                    tmp[pos++] = mid[begin2++];
            }

            // 处理可能未比较完的半区
            while (begin1 <= end1)
                tmp[pos++] = mid[begin1++];
            while (begin2 <= end2)
                tmp[pos++] = mid[begin2++];
        }

        // 将tmp中元素拷入mid中
        for (int i = 0; i < n; i++)
        {
            mid[i] = tmp[i];
        }

        // 释放tmp
        free(tmp);
    }

    // 输出下一轮的排序情况
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", mid[i]);
    }
    printf("%d", mid[n - 1]);

    // 释放内存
    free(array);
    free(mid);
}
