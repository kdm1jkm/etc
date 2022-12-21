// Question-6 다음 내용을 참고로 구조체 person을 정의하고, 사람 3명을 선언하여 적당한 값을 입력하고
// 출력하는 프로그램을 작성하십시오. Define the structure person with reference to the following contents,
// declare 3 people, and write a program that inputs and outputs appropriate values.
// • 구조체 date 멤버 구성: 이름, 전화번호, 생일. Structure date member configuration: name, phone
// number, birthday
// • 생일의 자료형은 구조체 date 를 사용하며. The data type of birthday uses the structure date
// • 구조체 date 멤버 구성: 년, 월. Structure date members: year, month, day
// • 출력 예. Example of output
// Name Phone Birthday
// -------------------------------------------------
// James 010-1111-1111 1998. 1. 7.
// Tony 010-2222-2222 2000. 5. 15.
// Harry 010-3333-3333 1999. 11. 17.
#include <stdio.h>
#include <string.h>
//날짜를 위한 구조체
struct date
{
    int year, month, day;
};
struct person
{
    char name[100];
    char phoneNumber[100];
    struct date birthday;
};
typedef struct person person;
int main()
{
    int i;
    person p[3] = {{"James", "010 - 1111 - 1111", {1998, 1, 7}},
                   {"Tony", "010 - 2222 - 2222", {2000, 5, 15}},
                   {"Harry", "010 - 3333 - 3333", {1999, 11, 17}}};
    printf("%16s%15s%20s\n", " name ", " Phone ", " Birthday ");
    for (i = 0; i <= 2; i++)
        printf("%16s%20s%6d.%2d.%2d.\n", p[i].name, p[i].phoneNumber, p[i].birthday.year, p[i].birthday.month, p[i].birthday.day);
    return 0;
}