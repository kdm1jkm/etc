// 문제6. 다음 배열에 있는 모든 원소들의 값을 각각 10씩 증가시켜 출력하는, 다음 조건들을 만족하는
// 프로그램을 작성하십시오.
// (조건 1) 배열 int data[] = {3, 21, 35, 57, 24, 82, 8}; 을 선언하고 초기화한다.
// (조건 2) 각 원소들의 값을 10 씩 증가시키기 위해서 *(data + i)와 반복문을 사용한다.
// Question-6. Write a program that satisfies the following conditions, printing out the increased values of all
// elements in the following array.
// (Condition 1) Declare and initialize the array, int data[] = {3, 21, 35, 57, 24, 82, 8};
// (Condition 2) Use *(data + i) and a loop in order to increase the value of each element of the array by 10.
// Example of the output:
// List of the array elements
// 13 31 45 67 34 92 18

#include <stdio.h>

int main()
{
    int data[] = {3, 21, 35, 57, 24, 82, 8};

    for (int i = 0; i < 7; i++)
    {
        *(data + i) += 10;
    }

    puts("List of the array elements");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", data[i]);
    }

    return 0;
}