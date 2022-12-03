#include <stdio.h>
#include <stdbool.h>

int main()
{
    int runCount;
    scanf("%d", &runCount);

    for (int run = 0; run < runCount; run++)
    {
        char operations[100001];
        int len;
        int arr[100000];
        scanf(" %s %d", operations, &len);

        if (len > 0)
        {
            scanf(" [%d", arr);
            for (int i = 1; i < len - 1; i++)
            {
                scanf(",%d", arr + i);
            }
            getchar();
        }

        bool reversed = false;
        char operation;
        int index;
        int frontDelete = 0, backDelete = 0;
        while ((operation = operations[index++]) != '\0')
        {
            switch (operation)
            {
            case 'R':
                reversed = !reversed;
                break;

            case 'D':
                if (reversed)
                    frontDelete++;
                else
                    backDelete++;
                break;
            }
        }

        if (frontDelete + backDelete > len)
        {
            puts("error");
            continue;
        }

        putchar('[');
        if (len > 0)
        {
            if (reversed)
            {
                printf("%d", arr[len - backDelete - 1]);
                for (int i = len - backDelete - 2; i >= frontDelete; i--)
                    printf(",%d", arr[i]);
            }
            else
            {

                printf("%d", arr[frontDelete]);
                for (int i = frontDelete + 1; i < len - backDelete; i++)
                    printf(",%d", arr[i]);
            }
        }
        putchar(']');
        putchar('\n');
    }
}