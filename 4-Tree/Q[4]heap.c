// 根据给定序列建立小顶堆,并打印指定路径
#include <stdio.h>
#include <stdlib.h>

// 建立堆,打印路径
void build_heap(int array[], int n);
void print_trace(int array[], int loc);

// 主函数
int main(void)
{
    // 定义堆中元素个数n,定义路径总数
    int n;
    int paths;

    // 读取元素
    scanf("%d", &n);
    scanf("%d", &paths);

    // 定义heap数组存储堆元素,定义start数组存储路径起点
    int* heap = (int*)malloc(n * sizeof(int));
    if (heap == NULL)
        return 0;

    int* start = (int*)malloc(paths * sizeof(int));
    if (start == NULL)
    {
        free(heap);
        return 0;
    }

    // 读取元素
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &heap[i]);
    }

    for (int i = 0; i < paths; i++)
    {
        scanf("%d", &start[i]);
    }

    // 建立堆
    build_heap(heap, n);

    // 输出路径
    for (int i = 0; i < paths; i++)
    {
        print_trace(heap, start[i]);
    }

    // 释放内存
    free(heap);
    free(start);
}

// 利用小顶堆元素之间的关系,动态调整数组元素位置
void build_heap(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // 首节点元素,没有双亲,无法移动
        if (i == 0)
            continue;

        // 双亲存在,则定义当前节点序号pos(从1开始),其双亲节点序号parent_pos,双亲索引parent_index
        int pos = i + 1;
        int parent_pos = pos / 2;
        int parent_index = parent_pos - 1;

        // 判断当前节点与其双亲节点大小关系
        if (array[i] >= array[parent_index])
            continue;
        else
        {
            // 当前节点比双亲节点小时,持续交换直至该节点到达正确位置
            int tmp = i;
            while (array[tmp] < array[parent_index] && parent_pos)
            {
                int mid = array[tmp];
                array[tmp] = array[parent_index];
                array[parent_index] = mid;

                // 实时更新当前节点索引,当前节点双亲位置及其索引
                tmp = parent_index;
                parent_pos /= 2;
                parent_index = parent_pos - 1;
            }
        }
    }
}

// 打印路径
void print_trace(int array[], int loc)
{
    while (loc)
    {
        // 当前节点对应数组索引index
        int index = loc - 1;
        if (index)
            printf("%d ", array[index]);
        else
            printf("%d\n", array[index]);

        // 更新节点为当前节点双亲节点
        loc /= 2;
    }
}
