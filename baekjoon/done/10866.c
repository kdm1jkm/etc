#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _deque
{
    int *data;
    int frontIndex;
    int backIndex;
    int size;
} Deque;

Deque *newDeque(int size)
{
    Deque *deque = (Deque *)malloc(sizeof(Deque));
    deque->data = (int *)malloc(sizeof(int) * size);
    deque->size = size;

    deque->frontIndex = 0;
    deque->backIndex = 0;

    return deque;
}

void freeDeque(Deque *deque)
{
    free(deque->data);
    free(deque);
}

int size(Deque *deque)
{
    if (deque->frontIndex <= deque->backIndex)
        return deque->backIndex - deque->frontIndex;

    return deque->size - (deque->frontIndex - deque->backIndex);
}

int front(Deque *deque)
{
    if (size(deque) == 0)
        return -1;
    return deque->data[deque->frontIndex];
}

int back(Deque *deque)
{
    if (size(deque) == 0)
        return -1;
    if (deque->backIndex == 0)
        return deque->data[deque->size - 1];
    return deque->data[deque->backIndex - 1];
}

void push_front(Deque *deque, int n)
{
    if (deque->frontIndex-- == 0)
        deque->frontIndex = deque->size - 1;

    deque->data[deque->frontIndex] = n;
}

void push_back(Deque *deque, int n)
{
    deque->data[deque->backIndex++] = n;

    if (deque->backIndex == deque->size)
        deque->backIndex = 0;
}

int pop_front(Deque *deque)
{
    if (size(deque) == 0)
        return -1;

    int result = front(deque);

    if (++deque->frontIndex == deque->size)
        deque->frontIndex = 0;

    return result;
}

int pop_back(Deque *deque)
{
    if (size(deque) == 0)
        return -1;

    int result = back(deque);

    if (deque->backIndex-- == 0)
        deque->backIndex = deque->size - 1;

    return result;
}

int empty(Deque *deque)
{
    return size(deque) == 0;
}

int main()
{
    int n;
    scanf("%d", &n);

    char command[20];
    Deque *deque = newDeque(10000);
    int x;

    for (int i = 0; i < n; i++)
    {
        scanf("%s", command);
        if (strcmp(command, "push_front") == 0)
        {
            scanf("%d", &x);
            push_front(deque, x);
        }
        else if (strcmp(command, "push_back") == 0)
        {
            scanf("%d", &x);
            push_back(deque, x);
        }
        else if (strcmp(command, "pop_front") == 0)
        {
            printf("%d\n", pop_front(deque));
        }
        else if (strcmp(command, "pop_back") == 0)
        {
            printf("%d\n", pop_back(deque));
        }
        else if (strcmp(command, "size") == 0)
        {
            printf("%d\n", size(deque));
        }
        else if (strcmp(command, "empty") == 0)
        {
            printf("%d\n", empty(deque));
        }
        else if (strcmp(command, "front") == 0)
        {
            printf("%d\n", front(deque));
        }
        else if (strcmp(command, "back") == 0)
        {
            printf("%d\n", back(deque));
        }
        else
        {
            printf("CANNOT REACH HERE!\n");
            return -1;
        }
    }

    freeDeque(deque);
}