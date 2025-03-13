// The purpose of this program is to find the greatest common divisor of two numbers
#include <stdio.h>

// Define error codes and boundaries
#define INVALID_INPUT 410
#define VALID 1
#define AMOUNT 2
#define LOW 0
#define HIGH 1000000

// Function prototypes
int check_numbers(int m, int n);
int divisor(int x, int y);

// Main function
int main(void)
{
    // Define and get input numbers from the user
    int first_number;
    int second_number;

    printf("Please enter the numbers: ");
    int numbers = scanf("%d %d", &first_number, &second_number);

    // Check inputs for legality
    if (numbers != AMOUNT || !check_numbers(first_number, second_number))
        return INVALID_INPUT;

    // Call the function to get the result
    int result = divisor(first_number, second_number);
    printf("%d\n", result);
}

// Check for the inputs
int check_numbers(int m, int n)
{
    if (m < LOW || n < LOW || m > HIGH || n > HIGH || (m == 0 && n == 0))
        return 0;
    else
        return VALID;
}

// Divide by tossing and turning
int divisor(int x, int y)
{
    // Deposit larger values into x
    if (x < y)
    {
        int mid = x;
        x = y;
        y = mid;
    }

    // Handle the case where there is exactly one input of 0
    if (y == 0)
        return x;

    // A loop for the result
    while (x % y != 0)
    {
        int mid = x;
        x = y;
        y = mid % y;
    }
    return y;
}
