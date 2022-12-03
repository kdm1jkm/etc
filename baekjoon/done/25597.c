#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int speeds[] = {8, 4, 1};
#define SPEED_COUNT 3

int buttonPressCount(int *periods)
{
    int result = 0;
    for (int i = 0; i < SPEED_COUNT; i++)
        if (periods[i] != 0)
            result++;
    return result;
}

int sum(int *periods)
{
    int result = 0;
    for (int i = 0; i < SPEED_COUNT; i++)
        result += periods[i];
    return result;
}

bool run(int *periods, int t)
{
    if (sum(periods) > t)
        return false;

    int count = buttonPressCount(periods);
    printf("%d\n", count);

    int passed = t - sum(periods);

    for (int i = 0; i < SPEED_COUNT; i++)
    {
        if (periods[i] == 0)
            continue;
        printf("%d %d\n", passed, speeds[i]);
        passed += periods[i];
    }

    return true;
}

void movePeriod(int *periods, int from, int to)
{
    periods[to] += periods[from] * speeds[from] / speeds[to];
    periods[from] = 0;
}

int main()
{
    int x, t;
    scanf("%d %d", &x, &t);

    int minPeriods[SPEED_COUNT];
    int periods[SPEED_COUNT];
    for (int i = 0; i < SPEED_COUNT; i++)
    {
        minPeriods[i] = x / speeds[i];
        x %= speeds[i];
    }

    int periodSum = sum(minPeriods);

    if (periodSum > t)
    {
        printf("-1\n");
        return 0;
    }

    int pressCount = buttonPressCount(minPeriods);

    // 1번 누르는 경우
    if (pressCount == 1)
    {
        run(minPeriods, t);
        return 0;
    }

    // 2번 누르는 경우
    else if (pressCount == 2)
    {
        memcpy(periods, minPeriods, sizeof(int) * 3);

        // 속도 4로 모으는 경우
        if (periods[2] == 0)
        {
            movePeriod(periods, 0, 1);
            if (run(periods, t))
                return 0;
        }

        // 속도 1로 모으는 경우
        else
        {
            movePeriod(periods, 0, 2);
            movePeriod(periods, 1, 2);
            if (run(periods, t))
                return 0;
        }

        // 모을 수 없는 경우
        memcpy(periods, minPeriods, sizeof(int) * 3);
        if (run(periods, t))
            return 0;
        else
        {
            printf("CANNOT REACH HERE!\n");
            return -1;
        }
    }

    // 3번 나오는 경우
    else
    {
        // 1로 합치는 경우
        memcpy(periods, minPeriods, sizeof(int) * 3);
        movePeriod(periods, 0, 2);
        movePeriod(periods, 1, 2);
        if (run(periods, t))
            return 0;

        // 8을 4로 합치는 경우
        memcpy(periods, minPeriods, sizeof(int) * 3);
        movePeriod(periods, 0, 1);
        if (run(periods, t))
            return 0;

        // 4를 1로 합치는 경우
        memcpy(periods, minPeriods, sizeof(int) * 3);
        movePeriod(periods, 1, 2);
        if (run(periods, t))
            return 0;

        // 8을 1로 합치는 경우
        memcpy(periods, minPeriods, sizeof(int) * 3);
        movePeriod(periods, 0, 2);
        if (run(periods, t))
            return 0;

        // 합칠 수 없는 경우
        memcpy(periods, minPeriods, sizeof(int) * 3);
        if (run(periods, t))
            return 0;
        else
        {
            printf("CANNOT REACH HERE!\n");
            return -1;
        }
    }
}