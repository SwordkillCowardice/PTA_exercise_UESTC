// The purpose of this program is to find the particular sum
#include <stdio.h>

// Constants
#define INVALIDINPUTS 333
#define HIGH 100
#define LOW 0
#define INVALID 0
#define SUCCESS 1

// Function prototype
int value(int m, int n);
int check_numbers(int x, int y);

// Main funtion
int main(void)
{
    // Define and get numbers
    int first_number;
    int second_number;

    // Check their validity
    int numbers = scanf("%d %d", &first_number, &second_number);
    if (numbers != 2 || !check_numbers(first_number, second_number))
        return INVALIDINPUTS;

    // Call the function to get the result
    int result = value(first_number, second_number);
    printf("%d", result);
}

// Check for their value
int check_numbers(int x, int y)
{
    if (x > HIGH || y > HIGH || x <= LOW || y <= LOW)
        return INVALID;
    return SUCCESS;
}

// Get the sum
int value(int m, int n)
{
    int total = 0;
    int mid = 0;

    for (int i = 0; i < m + 1; i++)
    {
        mid += i;
    }

    for (int i = 1; i < n + 1; i++)
    {
        total += mid * i;
    }
    return total;
}
