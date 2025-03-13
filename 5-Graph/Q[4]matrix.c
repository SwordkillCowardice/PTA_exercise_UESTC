// 测试邻接矩阵表示的图基本操作
#include <stdio.h>
#include <stdlib.h>

// 函数原型
void print_matrix(int** matrix, int row);
void check_existence(int** matrix, int start, int end, int value);
void check_neighbor(int** matrix, int size, int point, int value);
void delete_edge(int** matrix, int start, int end, int value);
void delete_point(int** matrix, char nodes[], int size, int point, int last, int value);
int calculate_edges(int** matrix, int size, int value);

// 主函数
int main(void)
{
    // 定义最大顶点数和无边默认值,读入数据
    int max_count;
    int no_edge_value;
    scanf("%d", &max_count);
    scanf("%d", &no_edge_value);

    // 定义实际顶点数和边数,并读入数据
    int points;
    int edges;
    scanf("%d", &points);
    scanf("%d", &edges);

    // 定义数组info,读取顶点信息
    char* info = (char*)malloc(points * sizeof(char));
    if (info == NULL)
        return 0;

    // 读取时尤其注意：读取字符时要处理换行符和空格
    for (int i = 0; i < points; i++)
    {
        scanf(" %c", &info[i]);
    }

    // 动态分配二维数组,作为邻接矩阵
    int** matrix = (int**)malloc(points * sizeof(int*));
    if (matrix == NULL)
    {
        free(info);
        return 0;
    }

    for (int i = 0; i < points; i++)
    {
        matrix[i] = (int*)malloc(points * sizeof(int));
        if (matrix[i] == NULL)
        {
            free(info);
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
            matrix[i][j] = no_edge_value;
        }
    }

    // 读取边的信息
    for (int i = 0; i < edges; i++)
    {
        // 定义边的两顶点x,y,边权重weight
        int x;
        int y;
        int weight;

        // 读入边并赋值
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &weight);
        matrix[x][y] = weight;
    }

    // 初次打印邻接矩阵,打印顶点数
    print_matrix(matrix, points);
    printf("顶点数 = %d\n", points);

    // 检查边的存在性
    for (int i = 0; i < 2; i++)
    {
        // 定义待检查边的编号并输入
        int point1;
        int point2;
        scanf("%d", &point1);
        scanf("%d", &point2);

        // 检查
        check_existence(matrix, point1, point2, no_edge_value);
    }

    // 输出邻接点
    int point;
    scanf("%d", &point);
    check_neighbor(matrix, points, point, no_edge_value);

    // 删除边并再次检查
    int start;
    int end;
    scanf("%d", &start);
    scanf("%d", &end);
    delete_edge(matrix, start, end, no_edge_value);
    check_existence(matrix, start, end, no_edge_value);

    // 读取待删除顶点,打印待删除顶点信息
    int index;
    scanf("%d", &index);
    printf("待删除的顶点信息为 %c\n", info[index]);

    // 删除顶点
    delete_point(matrix, info, points, index, points - 1, no_edge_value);

    // 打印信息
    printf("当前顶点数 = %d\n", points - 1);
    printf("当前边数 = %d\n", calculate_edges(matrix, points - 1, no_edge_value));
    for (int i = 0; i < points - 1; i++)
    {
        printf("%c", info[i]);
    }
    printf("\n");

    // 打印矩阵
    print_matrix(matrix, points - 1);

    // 释放内存
    free(info);
    for (int i = 0; i < points; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// 按要求打印邻接矩阵
void print_matrix(int** matrix, int row)
{
    printf("邻接矩阵为：\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 检查边的存在性
void check_existence(int** matrix, int start, int end, int value)
{
    if (matrix[start][end] != value)
        printf("<%d, %d> 的存在性 = 1\n", start, end);
    else
        printf("<%d, %d> 的存在性 = 0\n", start, end);
}

// 检查邻接点
void check_neighbor(int** matrix, int size, int point, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (matrix[point][i] != value)
        {
            printf("顶点%d的第一个邻接点 = %d\n", point, i);
            return;
        }
    }
}

// 删除边
void delete_edge(int** matrix, int start, int end, int value)
{
    matrix[start][end] = value;
}

// 删除顶点
void delete_point(int** matrix, char nodes[], int size, int point, int last, int value)
{
    // 修改顶点数组
    nodes[point] = nodes[last];

    // 修改邻接矩阵(先交换行,再交换列)
    for (int i = 0; i < size; i++)
    {
        matrix[point][i] = matrix[last][i];
        matrix[last][i] = value;
    }

    for (int i = 0; i < size; i++)
    {
        matrix[i][point] = matrix[i][last];
        matrix[i][last] = value;
    }
}

// 统计边数
int calculate_edges(int** matrix, int size, int value)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] != value)
                count++;
        }
    }
    return count;
}
