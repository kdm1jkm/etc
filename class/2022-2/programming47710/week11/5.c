// Question-5 10개 정도의 속담을 문자열의 형태로 함수 set_proverb() 내부에 저장하고 있습니다.
// 사용자가 set_proverb()을 호출하면, 이 함수 set_proverb()는 그 인수로 받은 이중 포인터를
// 이용하여 외부에 있는 char형 포인터 s를 설정합니다. 이 set_proverb()을 작성하고 테스트하시오.
// About 10 proverbs are stored in the function set_proverb() in the form of strings. When the user calls
// set_proverb(), this function set_proverb() sets the external char pointer s using the double pointer received
// as its argument. Write and test this set_proverb().
// Input/Output example:
// Which proverb will you choose? 2
// selected proverb = A bad workman quarrels with his tools.
// Hint
// set_proverb(char **q, int n) 함수는 외부의 포인터 값을 변경하여야 하므로, 이중 포인터 변수를
// 가진다. 또, 내부에 정적 포인터 배열로 10개의 속담을 저장하고 있다. The set_proverb(char **q, int n) function
// has a double pointer variable because it must change the external pointer. It also stores 10 proverbs as an array of static
// pointers inside.

#include <stdio.h>

void set_proverb(char **q, int n)
{
    static char *array[10] = {"A bad shearer never had a good sickle.",
                              "A bad workman (always) blames his tools. ",
                              "A bad workman quarrels with his tools.",
                              "A bad thing never dies.",
                              "A bad workman finds fault with his tools.",
                              "A bad workman always blames his tools.",
                              "A bargain is a bargain.",
                              "A barking dog never bites.",
                              "A barking dog was never a good hunter."};

    *q = array[n];
}

int main()
{
    char *s;

    int n;
    printf("Which proverb will you choose? ");
    scanf("%d", &n);

    set_proverb(&s, n);

    printf("Selected proverb = %s\n", s);
}