#include <math.h>
#include <stdio.h>

int divisor(int x, int y);

int main(void)
{
    int x;
    int y;
    int numbers = scanf("%d %d", &x, &y);
    if (numbers != 2)
    {
        return 0;
    }
    if (x == 0 || y == 0)
    {
        printf("0");
        return 0;
    }
    int m = divisor(x, y);
    printf("%d", m);
}

int divisor(int x, int y)
{
    if (x < y)
    {
        int mid = x;
        x = y;
        y = mid;
    }
    while (x % y != 0)
    {
        int mid = x;
        x = y;
        y = mid % y;
    }
    return y;
}
