// The purpose of this program is to find the particular sum
#include <stdio.h>

// Function prototype
int sum(int x);

// Main function
int main(void)
{
    int number;
    int p = scanf("%d", &number);
    if (p != 1)
        return 0;
    int result = sum(number);
    printf("%d", result);
}

// Get the sum
int sum(int x)
{
    int total = 0;
    for (int i = 1; i < x + 1; i++)
    {
        total += i;
    }

    for (int i = 1; i < x * x + 1; i++)
    {
        total += i;
    }
    return total;
}
