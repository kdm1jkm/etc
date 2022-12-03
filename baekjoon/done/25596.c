// N 원래 박스 갯수
// M 서브 박스 최대 갯수
// K 추가 박스 최대 갯수

// 입력
// N M K
// 설계도 갯수/서브박스

// 출력
// 0 | 1 (가능 여부)
// 추가한 박스(S)
// 설계도 갯수/서브박스

#include <stdio.h>
#include <stdlib.h>

int getChildCount(int *parents, int len, int parent)
{
    int result = 0;
    for (int i = 0; i < len; i++)
        if (parents[i] == parent)
            result++;
    return result;
}

int findMainbox(int *parents, int len)
{
    for (int i = 0; i < len; i++)
        if (parents[i] == -1)
            return i;

    return -1;
}

void setParent(int *parents, int len, int num, int prevParent, int newParent)
{
    int changed = 0;
    for (int i = 0; i < len; i++)
    {
        if (parents[i] == prevParent)
        {
            changed++;
            parents[i] = newParent;
        }
        if (changed >= num)
            return;
    }
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int *parents = (int *)malloc(sizeof(int) * (n + k));
    for (int i = 0; i < n + k; i++)
        parents[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int count;
        scanf("%d", &count);
        for (int j = 0; j < count; j++)
        {
            int num;
            scanf("%d", &num);
            parents[num - 1] = i;
        }
    }

    int addedBoxes = 0;

    for (int currentBox = 0; currentBox < n; currentBox++)
    {
        int childCount = getChildCount(parents, n + addedBoxes, currentBox);
        if (childCount <= m)
            continue;

        int newBoxCount = childCount / m;

        // 실패
        if (addedBoxes + newBoxCount > k)
        {
            puts("0");
            return 0;
        }

        for (int i = 0; i < newBoxCount; i++)
        {
            int newBox = n + addedBoxes;
            parents[newBox] = currentBox;

            setParent(parents, n + addedBoxes, m, currentBox, newBox);

            addedBoxes++;
        }

        currentBox--;
    }

    puts("1");
    printf("%d\n", addedBoxes);
    for (int i = 0; i < n + addedBoxes; i++)
    {
        int childCount = getChildCount(parents, n + addedBoxes, i);
        printf("%d ", childCount);
        for (int j = 0; j < n + addedBoxes; j++)
        {
            if (parents[j] == i)
                printf("%d ", j + 1);
        }
        putchar('\n');
    }

    free(parents);

    return 0;
}