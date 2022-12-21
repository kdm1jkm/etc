// 문제5. "프로그래밍" 과목의 다음 점수들을 이차원 배열에 저장하고, 각 학생 점수들의 합과 평균을
// 출력하는 프로그램을 작성하십시오.
// Question-5. Write a program that stores the following scores in the subject "Programming" in a two-dimensional
// array, and outputs the sum and average of each student's scores.
// Name Quiz Midterm Report Final
// Gildong 97 90 88 95
// James 76 89 75 83
// Harry 60 70 88 82
// Jack 83 89 92 85
// Changsoo 75 73 72 78
// Example of the output:
//     Name    Quiz Midterm  Report   Final     Sum Average
// =========================================================
//  Gildong      97      90      88      95     370   92.50
//    James      76      89      75      83     323   80.75
//    Harry      60      70      88      82     300   75.00
//     Jack      83      89      92      85     349   87.25
// Changsoo      75      73      72      78     298   74.50

#include <stdio.h>

int main()
{
    int scores[5][4] = {
        {97, 90, 88, 95},
        {76, 89, 75, 83},
        {60, 70, 88, 82},
        {83, 89, 92, 85},
        {75, 73, 72, 78}};
    char names[5][10] = {"Gildong", "James", "Harry", "Jack", "Changsoo"};

    puts("    Name    Quiz Midterm  Report   Final     Sum Average");
    puts("=========================================================");
    for (int i = 0; i < 5; i++)
    {
        printf("%8s", names[i]);
        int sum = 0;
        for (int j = 0; j < 4; j++)
        {
            sum += scores[i][j];
            printf("%8d", scores[i][j]);
        }
        printf("%8d%8.2f\n", sum, sum / 4.0);
    }

    return 0;
}