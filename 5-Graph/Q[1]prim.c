// 求最小生成树的Prim算法
#include <stdio.h>
#include <stdlib.h>

// 定义一个大数MAX,表示顶点之间无边
#define MAX 99999

// 主函数
int main(void)
{
    // 定义顶点数count,边数edges
    int count;
    int edges;
    scanf("%d", &count);
    scanf("%d", &edges);

    // 动态分配邻接矩阵
    int** matrix = (int**)malloc(count * sizeof(int*));
    if (matrix == NULL)
        return 0;

    for (int i = 0; i < count; i++)
    {
        matrix[i] = (int*)malloc(count * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return 0;
        }
    }

    // 初始化邻接矩阵
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = MAX;
        }
    }

    // 读取边,修改邻接矩阵
    for (int i = 0; i < edges; i++)
    {
        int start;
        int end;
        int weight;
        scanf("%d", &start);
        scanf("%d", &end);
        scanf("%d", &weight);
        matrix[start][end] = weight;
        matrix[end][start] = weight;
    }

    // 定义父节点数组
    int* parents = (int*)malloc(count * sizeof(int));
    if (parents == NULL)
    {
        for (int i = 0; i < count; i++)
            free(matrix[i]);
        free(matrix);
        return 0;
    }

    // 初始化父节点数组
    parents[0] = -1;
    for (int i = 1; i < count; i++)
        parents[i] = 0;

    // 定义points数组,存储被选中的点
    int* points = (int*)malloc(count * sizeof(int));
    if (points == NULL)
    {
        for (int i = 0; i < count; i++)
            free(matrix[i]);
        free(matrix);
        free(parents);
        return 0;
    }

    // 定义number变量,存储points数组中已有点个数
    int number = 0;
    points[number++] = 0;

    // 定义sign数组,表示顶点已经被加入
    int* sign = (int*)malloc(count * sizeof(int));
    if (sign == NULL)
    {
        for (int i = 0; i < count; i++)
            free(matrix[i]);
        free(matrix);
        free(parents);
        free(points);
        return 0;
    }

    // 初始化sign数组
    sign[0] = 1;
    for (int i = 1; i < count; i++)
        sign[i] = 0;

    // 定义总权重
    int total_weight = 0;

    // 定义轮数round
    int round = count - 1;

    // 每一轮找出最小边,将顶点加入
    for (int i = 0; i < round; i++)
    {
        // 定义当前最小边,及边的起始点和终点
        int smallest_edge = MAX;
        int index1 = 0;
        int index2 = -1;

        // 遍历每一个已选顶点
        for (int j = 0; j < number; j++)
        {
            // 遍历每一个未选择顶点
            for (int k = 0; k < count; k++)
            {
                if (sign[k])
                    continue;
                else
                {
                    // 更新最小边
                    if (matrix[points[j]][k] < smallest_edge)
                    {
                        smallest_edge = matrix[points[j]][k];
                        index1 = points[j];
                        index2 = k;
                    }
                    // 当多个待收录顶点到当前点集的距离等长时，按编号升序进行收录
                    else if (matrix[points[j]][k] == smallest_edge)
                    {
                        if (k < index2)
                        {
                            index1 = points[j];
                            index2 = k;
                        }
                    }
                }
            }
        }
        // index2未更新,说明不连通,无法找到最小生成树
        if (index2 == -1)
        {
            total_weight = -1;
            break;
        }
        // 更新顶点数组,标记数组,父节点数组权重
        else
        {
            points[number++] = index2;
            sign[index2] = 1;
            parents[index2] = index1;
            total_weight += matrix[index1][index2];
        }
    }

    // 打印结果
    printf("total weight = %d\n", total_weight);
    for (int i = 0; i < count; i++)
        printf("%d ", parents[i]);

    // 释放内存
    for (int i = 0; i < count; i++)
        free(matrix[i]);
    free(matrix);
    free(parents);
    free(points);
    free(sign);
}
