// (Constraint 1) 표준 입력으로 부터 두 명의 이름 (알파벳 10 글자 이내로 가정한다) 과 점수 (0~100)를
// 각각 입력 받아, 그 점수의 합계를 출력한다. It receives the names of two people (assuming within 10
// letters of the alphabet) and scores (0-100) from the standard input, and outputs the total sum of the
// scores.
// (Constraint 2) 다음 형식으로 출력한다. 출력때 공백의 개수에는 제한이 없다. The output format is as
// follow. There is no constraint to the number of spaces in the output.
// Enter name1 and score1 : Hong 93
// Enter name2 and score2 : Lee 97
// ---------------------
//     Name    | score
// ---------------------
//        Hong |  93
//         Lee |  97
//       TOTAL | 190
// ---------------------

#include <stdio.h>

#define MAX 2

int main()
{
    char names[MAX][11];
    int scores[MAX];

    for (int i = 0; i < MAX; i++)
    {
        printf("Enter name%d and score%d : ", i + 1, i + 1);
        scanf("%s %d", names[i], &scores[i]);
    }

    int scoreSum = 0;

    puts("---------------------");
    puts("    Name    | score  ");
    puts("---------------------");
    for (int i = 0; i < MAX; i++)
    {
        printf(" %10s | %3d\n", names[i], scores[i]);
        scoreSum += scores[i];
    }
    printf(" %10s | %3d\n", "TOTAL", scoreSum);
    puts("---------------------");
}