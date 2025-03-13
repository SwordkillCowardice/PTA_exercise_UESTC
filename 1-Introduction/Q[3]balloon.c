// The purpose of the program is to puncture more balloons
#include <stdio.h>
#include <stdlib.h>

// Constants for errors
#define LOW 0
#define HIGHO 1000
#define HIGHT 100000
#define AMOUNT 2
#define ValueError 360
#define VALID 361
#define MALLOCFAILURE 453

// Function prototypes
int check_inputs(int x, int y);
int get_coordinate(int height, int a[], int length);

// A global variable
int max_amount = 0;

// Main function
int main(void)
{
    // Define and get the number of balloons and height
    int number;
    int h;
    int numbers = scanf("%d %d", &number, &h);

    // Error check
    if (numbers != AMOUNT || !check_inputs(number, h))
        return ValueError;

    // Dynamically allocate memory to create an array of balloon locations
    int *balloons = malloc(number * sizeof(int));
    if (balloons == NULL)
        return MALLOCFAILURE;

    // Get Balloon Location
    for (int i = 0; i < number; i++)
    {
        scanf("%d", &balloons[i]);
    }

    // Call the function and print the result
    int result = get_coordinate(h, balloons, number);
    printf("%d %d", result, max_amount);

    // Free
    free(balloons);
}

// Check the inputs
int check_inputs(int x, int y)
{
    if (x < LOW || y < LOW || x > HIGHT || y > HIGHO)
        return ValueError;
    else
        return VALID;
}

// Find the position of the balloon that will cover the most balloons first,
// then pan according to height
int get_coordinate(int height, int a[], int length)
{
    // Define the number of balloons punctured, beginning and end
    int numbers = 0;
    int start = 0;
    int end = 0;

    // Dealing with extremes (height is larger than total length of balloons)
    if (a[length - 1] - a[start] <= height)
    {
        max_amount = length;
        return a[start] - (height - (a[length - 1] - a[start]));
    }

    // For each balloon location find the maximum number of balloons it can cover
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (a[j] <= a[i] + height)
                numbers++;
            else
                break;
        }

        // Update the max number of ballons and the start
        if (numbers > max_amount)
        {
            max_amount = numbers;
            start = i;
        }

        // Update numbers and determine if the judgment can be stopped
        numbers = 0;
        int rest_balloons = length - i;
        if (max_amount >= rest_balloons)
            break;
    }

    // Find the minimum position
    for (int i = start; i < length; i++)
    {
        // Determine whether the end falls on the balloon or not
        if (a[i] == a[start] + height)
        {
            end = i;
            break;
        }

        else if (a[i] > a[start] + height)
        {
            end = i - 1;
            break;
        }
    }
    return a[start] - (height - (a[end] - a[start]));
}
