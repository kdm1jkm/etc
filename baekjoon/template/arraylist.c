//********************************* List ***************************************

#include <stdlib.h>

typedef int LIST_TYPE;

typedef struct _arrayList
{
    LIST_TYPE *data;
    size_t capacity;
    size_t size;
} ArrayList;

ArrayList *newArrayList(size_t capacity)
{
    ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));

    arrayList->capacity = capacity;
    arrayList->data = malloc(sizeof(LIST_TYPE) * capacity);
    arrayList->size = 0;

    return arrayList;
}

void freeArrayList(ArrayList *arrayList)
{
    free(arrayList->data);
    free(arrayList);
}

void sortList(ArrayList *arrayList, int compare(const void *, const void *))
{
    qsort(arrayList->data, arrayList->size, sizeof(LIST_TYPE), compare);
}

LIST_TYPE *getListElement(ArrayList *arrayList, size_t index)
{
    return &arrayList->data[index];
}

bool resetListCapacity(ArrayList *arrayList, size_t capacity)
{
    void *prev = arrayList->data;
    arrayList->data = realloc(arrayList->data, sizeof(LIST_TYPE) * capacity);
    if (arrayList->data == NULL)
    {
        arrayList->data = prev;
        return false;
    }
    arrayList->capacity = capacity;
    return true;
}

bool listAppend(ArrayList *arrayList, LIST_TYPE element)
{
    if (arrayList->size == arrayList->capacity)
        if (!resetListCapacity(arrayList, arrayList->capacity * 2))
            return false;

    *getListElement(arrayList, arrayList->size++) = element;

    return true;
}

void *findElement(ArrayList *arrayList, void *element, int compare(const void *, const void *))
{
    return bsearch(element, arrayList->data, arrayList->size, sizeof(LIST_TYPE), compare);
}
