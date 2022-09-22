#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

typedef struct _pos
{
    char a, b;
} pos;

bool isValid(pos a, pos b)
{
    int deltaX = a.a - b.a;
    int deltaY = a.b - b.b;
    return (deltaX * deltaX + deltaY * deltaY) == 5;
}

bool *getMoved(bool *moved, pos p)
{
    return &moved[(p.a - 'A') + 6 * (p.b - '1')];
}

int main()
{
    pos prevPos, startPos;
    scanf("%c%c", &prevPos.a, &prevPos.b);
    startPos = prevPos;

    bool moved[36];
    memset(moved, false, sizeof(bool) * 36);
    *getMoved(moved, prevPos) = true;

    for (int i = 0; i < 35; i++)
    {
        pos currentPos;
        scanf(" %c%c", &currentPos.a, &currentPos.b);
        if (!isValid(prevPos, currentPos) || *getMoved(moved, currentPos))
        {
            printf("Invalid\n");
            return 0;
        }

        *getMoved(moved, currentPos) = true;
        prevPos = currentPos;
    }
    if (!isValid(startPos, prevPos))
    {
        printf("Invalid\n");
        return 0;
    }

    printf("Valid\n");
    return 0;
}