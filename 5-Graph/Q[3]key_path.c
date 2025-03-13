// 求图中关键活动
#include <stdio.h>
#include <stdlib.h>

// 主函数
int main(void)
{
    // 定义顶点数points,边数edges
    int points;
    int edges;
    scanf("%d", &points);
    scanf("%d", &edges);

    // 定义邻接矩阵matrix
    int** matrix = (int**)malloc(points * sizeof(int*));
    if (matrix == NULL)
        return 0;

    for (int i = 0; i < points; i++)
    {
        matrix[i] = (int*)malloc(points * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return 0;
        }
    }

    // 初始化邻接矩阵
    for (int i = 0; i < points; i++)
    {
        for (int j = 0; j < points; j++)
            matrix[i][j] = 0;
    }

    // 读取边,更新邻接矩阵
    for (int i = 0; i < edges; i++)
    {
        int start;
        int end;
        int weight;
        scanf("%d", &start);
        scanf("%d", &end);
        scanf("%d", &weight);
        matrix[start][end] = weight;
    }

    // 定义ev数组,存储各顶点最早开始时间
    int* ev = (int*)malloc(points * sizeof(int));
    if (ev == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        return 0;
    }

    // 初始化ev数组
    for (int i = 0; i < points; i++)
        ev[i] = 0;

    // 定义入度数组,用于拓扑排序
    int* entrancedegree = (int*)malloc(points * sizeof(int));
    if (entrancedegree == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(ev);
        return 0;
    }

    // 初始化入度数组
    for (int i = 0; i < points; i++)
    {
        entrancedegree[i] = 0;
        for (int j = 0; j < points; j++)
        {
            if (matrix[j][i] != 0)
                entrancedegree[i]++;
        }
    }

    // 利用拓扑排序更新ev数组
    int ctr = 1;
    int count = 0;
    while (ctr)
    {
        ctr = 0;
        for (int i = 0; i < points; i++)
        {
            if (entrancedegree[i] == 0)
            {
                count++;
                ctr++;
                entrancedegree[i] = -1;
                for (int j = 0; j < points; j++)
                {
                    // 如果当前最早开始时间小于所需时间,最早开始时间更新为所需时间
                    if (matrix[i][j] != 0)
                    {
                        entrancedegree[j]--;
                        if (matrix[i][j] + ev[i] > ev[j])
                            ev[j] = matrix[i][j] + ev[i];
                    }
                }
            }
        }
    }

    // 拓扑排序不能完成,说明有环,则无关键路径
    if (count != points)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(ev);
        free(entrancedegree);
        printf("关键路径分析结果为 0");
        return 0;
    }

    // 定义lv数组,存储各顶点最迟开始时间
    int* lv = (int*)malloc(points * sizeof(int));
    if (lv == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(ev);
        free(entrancedegree);
        return 0;
    }

    // 初始化lv数组(找出ev最大的节点)
    int biggest = 0;
    for (int i = 0; i < points; i++)
    {
        if (ev[i] > biggest)
            biggest = ev[i];
    }
    for (int i = 0; i < points; i++)
        lv[i] = biggest;

    // 定义出度数组,用于逆拓扑排序
    int* outdegree = (int*)malloc(points * sizeof(int));
    if (outdegree == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(ev);
        free(entrancedegree);
        free(lv);
        return 0;
    }

    // 初始化出度数组
    for (int i = 0; i < points; i++)
    {
        outdegree[i] = 0;
        for (int j = 0; j < points; j++)
        {
            if (matrix[i][j] != 0)
                outdegree[i]++;
        }
    }

    // 逆拓扑排序,更新各顶点lv
    int ptr = 1;
    while (ptr)
    {
        ptr = 0;
        for (int i = 0; i < points; i++)
        {
            if (outdegree[i] == 0)
            {
                ptr++;
                outdegree[i] = -1;
                for (int j = 0; j < points; j++)
                {
                    // 如果当前最晚开始时间大于所需时间,修改值为所需时间
                    if (matrix[j][i] != 0)
                    {
                        outdegree[j]--;
                        if (lv[i] - matrix[j][i] < lv[j])
                            lv[j] = lv[i] - matrix[j][i];
                    }
                }
            }
        }
    }

    // 利用顶点的最早和最迟时间,更新关键活动边,标记为-1
    for (int i = 0; i < points; i++)
    {
        for (int j = 0; j < points; j++)
        {
            if (matrix[i][j])
            {
                if (ev[i] == lv[j] - matrix[i][j])
                {
                    matrix[i][j] = -1;
                }
            }
        }
    }

    // 输出关键活动
    for (int i = 0; i < points; i++)
    {
        for (int j = points - 1; j >= 0; j--)
        {
            if (matrix[i][j] == -1)
                printf("<%d, %d>\n", i, j);
        }
    }
    printf("关键路径分析结果为 1");

    // 释放内存
    for (int i = 0; i < points; i++)
        free(matrix[i]);
    free(matrix);
    free(ev);
    free(entrancedegree);
    free(lv);
    free(outdegree);
}
