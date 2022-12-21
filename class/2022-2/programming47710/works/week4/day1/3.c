// 문제3. Refer to the slide p.43 of W04 Lecture. Write the codes according to the following instructions. Explain what
// happened after each step.

#include <stdio.h>
int main(void)
{
    char text[] = "FRIENDS";
    char *p = &text[3];
    char ch;
    // Refer to the slide p.43 of W04 Lecture
    // Write the codes according to the following instructions:
    // (1) Print out p and *p
    printf("p: %p, *p: %c\n", p, *p);

    // (2) Run ch = *p++ and then print out ch, p, and *p. Explain what happened.
    ch = *p++;
    printf("ch: %c\n", ch);
    // 포인터 p가 가리키는 주소값이 1byte(char 크기) 늘어나고, 그 전에 해당 값을 참조해 ch에 넣음.
    // 'E'

    // (3) Let p = &text[3]. Run ch = *(p++) and then print out ch, p, and *p. Explain what happened.
    p = &text[3];
    ch = *(p++);
    printf("ch: %c, p: %p, *p: %c\n", ch, p, *p);
    // 2번과 동일
    // 'E'

    // (4) Let p = &text[3]. Run ch = *++p and then print out ch, p, and *p. Explain what happened.
    p = &text[3];
    ch = *++p;
    printf("ch: %c, p: %p, *p: %c\n", ch, p, *p);
    // 포인터 p가 가리키는 주소값이 1byte 늘어나고, 해당 주소를 참조.
    // 'N'

    // (5) Let p = &text[3]. Run ch = (*p)++ and then print out ch, p, and *p. Explain what happened.
    p = &text[3];
    ch = (*p)++;
    printf("ch: %c, p: %p, *p: %c\n", ch, p, *p);
    // p가 참조하는 값을 1 증가, 'E'가 'F'가 됨.

    // (6) Let p = &text[3]. Run ch = ++*p and then print out ch, p, and *p. Explain what happened.
    p = &text[3];
    ch = ++*p;
    printf("ch: %c, p: %p, *p: %c\n", ch, p, *p);
    // G가 됨

    return 0;
}