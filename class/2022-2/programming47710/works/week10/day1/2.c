// Question-2 다음 내용을 참고로 프로그램의 빈 네모상자 부분에 들어갈 소스를 작성하시오. Write the
// source to be put in the empty square box of the program referring to the following contents.
//  함수 arraycopy(int *from, int *to, int size)는 배열 from의 처음 원소부터 size 개수까지 원소 값을
// 배열 to의 동일한 순서의 원소에 복사하는 함수. The function arraycopy(int *from, int *to, int size) is
// a function that copies the element values from the first element of the array from to the number of
// size to the elements in the same order of the array to.
//  함수 arrayprint(int *p, int size)는 배열 p의 처음 원소부터 size 개수까지 원소 값을 출력하는 함수.
// The function arrayprint(int *p, int size) is a function that prints the element values from the first
// element in the array p to the number of sizes.

#include <stdio.h>
void arraycopy(int *from, int *to, int size);
void arrayprint(int *p, int size);
int main(void)
{
    int to[] = {13, 34, 28, 56, 73, 45};
    int from[] = {3, 5, 1, 6, 7};
    arraycopy(from, to, 5);
    arrayprint(from, 5);
    arrayprint(to, 6);
    return 0;
}
void arraycopy(int *from, int *to, int size)
{
    for (int i = 0; i < size; i++)
        to[i] = from[i];
}
void arrayprint(int *p, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", p[i]);
    putchar('\n');
}