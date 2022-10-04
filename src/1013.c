// (100+1+ | 01)+
//
// Regular Expression
// Sigma = {0, 1}
// (1000* 11* + 01)(1000* 11* + 01)*

//   0 1 2 3 4 5 6 7 8 9
// 0 1 9 4 1 5 5 1 8 5 9
// 1 2 3 9 2 9 6 7 7 3 9

#include <stdio.h>
#include <stdbool.h>

bool checkGoalState(int state)
{
    return state == 3 || state == 6 || state == 7;
}

int main()
{
    const int transitions[2][10] = {
        {1, 9, 4, 1, 5, 5, 1, 8, 5, 9},
        {2, 3, 9, 2, 9, 6, 7, 7, 3, 9}};

    int count;
    scanf("%d", &count);

    char str[200];
    for (int loop = 0; loop < count; loop++)
    {
        scanf(" %s", str);
        int i = 0;
        int state = 0;
        while (str[i] != '\0')
        {
            int currentAlphabet = str[i] - '0';
            state = transitions[currentAlphabet][state];
            i++;
        }
        if (checkGoalState(state))
            printf("YES\n");
        else
            printf("NO\n");
    }
}