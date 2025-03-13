// 实现求单源最短路的Dijkstra算法
#include <stdio.h>
#include <stdlib.h>

// 定义一个大数,用于表示顶点之间不可直达
#define MAX 99999

// 获取最短路径函数
void getShortestPath(int** graph, int dist[], int path[], int sign[], int points);

// 主函数
int main(void)
{
    // 定义顶点总数points,边总数edges，读入数据
    int points;
    int edges;
    scanf("%d", &points);
    scanf("%d", &edges);

    // 动态分配邻接矩阵
    int** matrix = (int**)malloc(points * sizeof(int*));
    if (matrix == NULL)
        return 0;

    for (int i = 0; i < points; i++)
    {
        matrix[i] = (int*)malloc(points * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return 0;
        }
    }

    // 初始化邻接矩阵
    for (int i = 0; i < points; i++)
    {
        for (int j = 0; j < points; j++)
        {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = MAX;
        }
    }

    // 读入边,修改邻接矩阵
    for (int i = 0; i < edges; i++)
    {
        // 定义起点,终点,权重
        int start;
        int end;
        int weight;
        scanf("%d", &start);
        scanf("%d", &end);
        scanf("%d", &weight);
        matrix[start][end] = weight;
    }

    // 定义dist数组,存储最短路径长度
    int* dist = (int*)malloc(points* sizeof(int));
    if (dist == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        return 0;
    }

    // 初始化dist
    for (int i = 0; i < points; i++)
    {
        dist[i] = matrix[0][i];
    }

    // 定义路径数组path
    int* path = (int*)malloc(points * sizeof(int));
    if (path == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(dist);
        return 0;
    }

    // 初始化path数组
    path[0] = -1;
    for (int i = 1; i < points; i++)
    {
        if (matrix[0][i] != MAX)
            path[i] = 0;
        else
            path[i] = -1;
    }

    // 定义标志数组sign,表示顶点已经求过最短路径
    int* sign = (int*)malloc(points * sizeof(int));
    if (sign == NULL)
    {
        for (int i = 0; i < points; i++)
            free(matrix[i]);
        free(matrix);
        free(dist);
        free(path);
        return 0;
    }

    // 初始化sign(sign[0]用不上)
    for (int i = 1; i < points; i++)
        sign[i] = 0;

    // 求最短路径
    getShortestPath(matrix, dist, path, sign, points);

    // 释放内存
    for (int i = 0; i < points; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(dist);
    free(path);
    free(sign);
}

// 定义求最短路径函数
void getShortestPath(int** matrix, int* dist, int* path, int* sign, int points)
{
    // 定义循环总轮次
    int round = points - 1;

    for (int i = 0; i < round; i++)
    {
        // 定义当前最短路径small及对应索引index
        int small = MAX;
        int index = 0;

        // 遍历dist数组,在尚未被标记的节点中找出路径最短的,并标记该节点
        // 注意：当多个待收录顶点路径等长时，按编号升序进行收录。
        for (int j = 1; j < points; j++)
        {
            // 一定是小于号而不是小于等于
            if (!sign[j] && dist[j] < small)
            {
                small = dist[j];
                index = j;
            }
        }
        sign[index] = 1;

        // 更新元素最短路径及前驱(每轮已经更新了下一轮要选出的路径的前驱)
        for (int j = 1; j < points; j++)
        {
            if (!sign[j] && j != index)
            {
                int new_value = dist[index] + matrix[index][j];
                if (dist[j] > new_value)
                {
                    dist[j] = new_value;
                    path[j] = index;
                }
            }
        }
    }

    // 打印结果
    for (int i = 0; i < points; i++)
    {
        printf("v[%d]: dist=%d, path=%d\n", i, dist[i], path[i]);
    }
}
