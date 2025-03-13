// 实现拓扑排序
#include <stdio.h>
#include <stdlib.h>

// 顶点信息长度
#define LENGTH 4

// 主函数
int main(void)
{
    // 定义顶点数points,边数edges
    int points;
    int edges;
    scanf("%d", &points);
    scanf("%d", &edges);

    // 动态分配info数组,存储顶点信息
    char** info = (char**)malloc(points * sizeof(char*));
    if (info == NULL)
        return 0;

    for (int i = 0; i < points; i++)
    {
        info[i] = (char*)malloc(LENGTH * sizeof(char));
        if (info[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(info[j]);
            free(info);
            return 0;
        }
    }

    // 读取顶点信息
    for (int i = 0; i < points; i++)
    {
        scanf("%s", info[i]);
    }

    // 定义邻接矩阵
    int** matrix = (int**)malloc(points * sizeof(int*));
    if (matrix == NULL)
    {
        for (int i = 0; i < points; i++)
            free(info[i]);
        free(info);
        return 0;
    }

    for (int i = 0; i < points; i++)
    {
        matrix[i] = (int*)malloc(points * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            for (int k = 0; k < points; k++)
                free(info[k]);
            free(info);
            return 0;
        }
    }

    // 初始化邻接矩阵
    for (int i = 0; i < points; i++)
    {
        for (int j = 0; j < points; j++)
            matrix[i][j] = 0;
    }

    // 读取边,并修改邻接矩阵
    for (int i = 0; i < edges; i++)
    {
        int start;
        int end;
        scanf("%d", &start);
        scanf("%d", &end);
        matrix[start][end] = 1;
    }

    // 定义entranceDegree数组,存储入度
    int* entranceDegree = (int*)malloc(points * sizeof(int));
    if (entranceDegree == NULL)
    {
        for (int i = 0; i < points; i++)
            free(info[i]);
        free(info);
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        return 0;
    }

    // 初始化入度数组
    for (int i = 0; i < points; i++)
        entranceDegree[i] = 0;

    // 更新入度数组
    for (int i = 0; i < points; i++)
    {
        for (int j = 0; j < points; j++)
        {
            if (matrix[j][i] == 1)
                entranceDegree[i]++;
        }
    }

    // 定义order数组,存储排序结果
    int* order = (int*)malloc(points * sizeof(int));
    if (order == NULL)
    {
        for (int i = 0; i < points; i++)
            free(info[i]);
        free(info);
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(entranceDegree);
        return 0;
    }

    // 定义number变量,存储已排序顶点个数
    int number = 0;

    // 遍历度数数组,找出入度为0的节点,并删除以其为弧尾的弧
    int count = points;
    while (count)
    {
        int amount = 0;
        for (int i = 0; i < points; i++)
        {
            if (entranceDegree[i] == 0)
            {
                entranceDegree[i] = -1;
                order[number++] = i;
                for (int j = 0; j < points; j++)
                {
                    if (matrix[i][j] == 1)
                        entranceDegree[j]--;
                }
                amount++;
            }
        }
        if (amount == 0)
            break;
        count -= amount;
    }

    // 判断结果并输出
    if (number != points)
    {
        printf("该图拓扑序存在性为 0\n");
        printf("找不到工作咋办\n");
    }
    else
    {
        printf("该图拓扑序存在性为 1\n");
        for (int i = 0; i < points; i++)
            printf("%s ", info[order[i]]);
    }

    // 释放内存
    for (int i = 0; i < points; i++)
        free(info[i]);
    free(info);
    for (int i = 0; i < points; i++)
        free(matrix[i]);
    free(matrix);
    free(entranceDegree);
    free(order);
}