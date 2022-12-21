// Question-5. 다음 C프로그램은 어떤 배열을 초기화하고 반복문을 사용하여 배열의 모든 원소의 합을
// 출력하는 프로그램이다. 초기화된 배열을 매개변수로 입력받아 모든 원소의 합을 반환하는 함수
// sum_array()를 작성하십시오. 이 C프로그램을 이 함수를 사용함으로써 refactoring하십시오.
// The following C program initializes an array and prints the sum of all the elements of the array using a loop statement.
// Write a function sum_array() that takes an initialized array as a parameter and returns the sum of all elements. Using
// this function, rewrite this C program.

double sum_array(double *arr, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

#include <stdio.h>
int main(void)
{
    double degree[] = {-5.34, 3.67, 19.76, 28.76, 35.63};
    int size = sizeof(degree) / sizeof(degree[0]);
    printf("Print total sum of the array elements\n");
    printf("sum = %.2f\n", sum_array(degree, size));
    return 0;
}