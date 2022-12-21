// Question-4. 점수를 학점으로 변환하는 함수 score2grade()를 작성하십시오. 이 함수 score2grade()
// 를 사용하여, "프로그래밍" 과목의 점수를 실수형으로 입력 받아, 다음과 같이 학점을 출력하는 C
// 프로그램을 작성하십시오. (포인터나 배열을 사용하지 않아도 됩니다.) Write a function score2grade() that
// converts scores to grades. By using this function score2grade(), write a C program that receives the score of the
// subject “Programming” as a real number and outputs the credit as follows. (You don't need to use a pointer nor an array.)
// 점수 (Score) 학점 (Grade)
// 90 or more A
// less than 90 ~ 80 or more B
// less than 80 ~ 70 or more C
// less than 70 ~ 60 or more D
// less than 60 F
// Examples of execution results:
// Enter your score: 96.7
// Your score is A.
// Enter your score: 83
// Your score is B.

#include <stdio.h>

char score2grade(double score)
{
    if (score >= 90)
        return 'A';
    else if (score >= 80)
        return 'B';
    else if (score >= 70)
        return 'C';
    else if (score >= 60)
        return 'D';
    else
        return 'F';
}

int main()
{
    printf("Enter your score: ");
    double score;
    scanf("%lf", &score);

    printf("Your score is %c.\n", score2grade(score));

    return 0;
}