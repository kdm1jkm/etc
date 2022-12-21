#include <stdio.h>

int get_sum(int array[], int size);

int main()
{
    int m[][6] = {
        {10, 10, 10, 10, 10, 10},
        {10, 10, 10, 10, 10, 10},
        {10, 10, 10, 10, 10, 10}};

    int total = 0;

    int count = sizeof(m) / sizeof(m[0]);
    int size = sizeof(m[0]) / sizeof(m[0][0]);
    for (int i = 0; i < count; i++)
        total += get_sum(m[i], size);

    printf("Sum of integers = %d\n", total);

    return 0;
}

int get_sum(int array[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += array[i];

    return sum;
}