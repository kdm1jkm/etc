// 문제4. 다음의 배열을 초기화하고 반복문을 사용하여 배열의 모든 원소를 출력하는, 다음 조건을
// 만족하는, 프로그램을 작성하십시오.
// (조건 1) 배열 double degree[] = {-5.34, 3.67, 19.76, 28.76, 35.63}; 을 선언하고 초기화한다.
// (조건 2) 배열의 크기를 계산하여 변수 size 에 저장해 반복문에서 사용한다.
// Question-4. Write a program that satisfies the following conditions, which initializes the following array and
// prints out all the elements of the array using a loop.
// (Condition 1) Declare and initialize the array, double degree[] = {-5.34, 3.67, 19.76, 28.76, 35.63};
// (Condition 2) Calculate the size of the array, store it in the variable "size", and use it in a loop.
// Example of the output:
// List of array elements
// -5.34 3.67 19.76 28.76 35.63

#include <stdio.h>

int main()
{
    double degree[] = {-5.34, 3.67, 19.76, 28.76, 35.63};
    int size = sizeof(degree) / sizeof(double);

    puts("List of array elements");
    for (int i = 0; i < size; i++)
        printf("%.2f ", degree[i]);
    putchar('\n');

    return 0;
}