#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "free_parcking_spot.csv"

// 주차장 정보를 담을 구조체 구현
typedef struct _parking_t
{
    char name[100];
    char agency[100];
    char city[100];
    char district[100];
    double longitude;
    double latitude;
} parking_t;

// 배열리스트 구조체 구현
typedef struct _parking_list_t
{
    int len;
    parking_t *parkings;
} parking_list_t;

// utils_t 구조체 구현
typedef struct _utils_t
{
    void (*sort)(parking_list_t *);
    void (*print)(parking_list_t *);
    void (*filter)(parking_list_t *);
} utils_t;

/* Array List */
int array_list_create(parking_list_t **list);
int array_list_destroy(parking_list_t **list);
int array_list_insert_last(parking_list_t *list, parking_t e);

/* Sort */
void selection_sort(parking_list_t *list);
void insertion_sort(parking_list_t *list);

void my_print(parking_list_t *list);
void my_sort(parking_list_t *list);
void my_filter(parking_list_t *list);
int main(int argc, char **argv)
{
    FILE *fp;
    int op;
    char strTemp[440];

    fp = fopen(filename, "r");

    parking_list_t *list = NULL;
    array_list_create(&list);

    if (fp != NULL)
    {
        while (!feof(fp))
        {
            parking_t parkingArr;

            char *pline = fgets(strTemp, sizeof(strTemp), fp);
            if (feof(fp))
                break;
            char *ptoken = strtok(pline, ",");

            ptoken = strcpy(parkingArr.name, ptoken);
            ptoken = strtok(NULL, ",");
            ptoken = strcpy(parkingArr.agency, ptoken);
            ptoken = strtok(NULL, ",");
            ptoken = strcpy(parkingArr.city, ptoken);
            ptoken = strtok(NULL, ",");
            ptoken = strcpy(parkingArr.district, ptoken);
            ptoken = strtok(NULL, ",");
            parkingArr.longitude = strtod(ptoken, NULL);
            ptoken = strtok(NULL, ",");
            parkingArr.latitude = strtod(ptoken, NULL);

            array_list_insert_last(list, parkingArr);
        }
        fclose(fp);
    }

    else
    {
        printf("Cannot open the free_parcking_spot.csv\n");
        return -1;
    }

    printf("Stored all elements\n");
    printf("=====Choose function=====\n");
    printf("1) sort\n");
    printf("2) print\n");
    printf("3) filter\n");
    printf("4) exit\n");
    printf("Input option: ");
    scanf("%d", &op);
    printf("\n");

    utils_t funcPtr;
    funcPtr.sort = my_sort;
    funcPtr.print = my_print;
    funcPtr.filter = my_filter;

    if (op == 1)
        funcPtr.sort(list);
    else if (op == 2)
        funcPtr.print(list);
    else if (op == 3)
        funcPtr.filter(list);
    else if (op == 4)
        printf("Exit the program\n");
    else
        printf("Invalid option");

    array_list_destroy(&list);

    return 0;
}

void my_print(parking_list_t *list)
{
    int i;
    parking_t key;
    printf("====== Print all elements (len:%d)======\n", list->len);
    for (i = 0; i < list->len; i++)
    {
        key = list->parkings[i];
        printf("%s(%s) [%s %s (%.5lf, %.5lf)]\n", key.name, key.agency, key.city, key.district, key.longitude, key.latitude);
    }
}

void my_sort(parking_list_t *list)
{
    int op;

    // 옵션 입력
    printf("====== Choose a sorting algorithm ======\n");
    printf("(1) selection sort\n");
    printf("(2) insertion sort\n");
    printf("Input option 1:");
    scanf("%d", &op);

    if (op == 1)
    {
        // selection sort
        selection_sort(list);
    }
    else if (op == 2)
    {
        // insertion sort
        insertion_sort(list);
    }
    else
        printf("Invalid option\n");
}

/* Array List */
int array_list_create(parking_list_t **list)
{
    if (*list != NULL)
        return 0;

    *list = (parking_list_t *)malloc(sizeof(parking_list_t));

    (*list)->len = 0;
    (*list)->parkings = NULL;

    return 1; // return Success
}
int array_list_destroy(parking_list_t **list)
{
    if (*list == NULL)
        return 0;

    if ((*list)->parkings != NULL)
        free((*list)->parkings);
    free(*list);

    return 1; // return Success
}
int array_list_insert_last(parking_list_t *list, parking_t e)
{
    if (list == NULL)
        return 0;

    if (list->parkings == NULL)
        list->parkings = (parking_t *)malloc(sizeof(parking_t));
    else
        list->parkings = (parking_t *)realloc(list->parkings, sizeof(parking_t) * (list->len + 1));

    list->parkings[list->len] = e;
    list->len++;

    return 1;
}

void swap(parking_t *a, parking_t *b)
{
    parking_t tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Sort */
void selection_sort(parking_list_t *list)
{
    int op;
    int i, j, min;
    int cmpcity, cmpdist;
    utils_t funcPtr;

    printf("====== Selection Sort ======\n");
    printf("(1) by city-district\n");
    printf("(2) by longitude-latitude\n");
    printf("Input option2:");
    scanf("%d", &op);

    if (op == 1)
    {

        for (i = 0; i < list->len; i++)
        {
            min = i;
            for (j = 0; j < list->len; j++)
            {
                cmpcity = strcmp(list->parkings[j].city, list->parkings[min].city);
                if (cmpcity != 0)
                {
                    if (cmpcity < 0)
                        min = j;
                }
                else
                {
                    cmpdist = strcmp(list->parkings[j].district, list->parkings[min].district);
                    if (cmpdist < 0)
                        min = j;
                }
                swap(&list->parkings[i], &list->parkings[min]);
            }
        }
        funcPtr.print = my_print;
        funcPtr.print(list);
    }

    else if (op == 2)
    {
        for (i = 0; i < list->len; i++)
        {
            min = i;
            for (j = 0; j < list->len; j++)
            {

                if (list->parkings[j].longitude < list->parkings[min].longitude)
                    min = j;
                else if (list->parkings[j].longitude == list->parkings[min].longitude)
                {

                    if (list->parkings[j].latitude < list->parkings[min].latitude)
                        min = j;
                }
            }
            swap(&list->parkings[i], &list->parkings[min]);
        }
        funcPtr.print = my_print;
        funcPtr.print(list);
    }

    else
        printf("Invalid option\n");
}
void insertion_sort(parking_list_t *list)
{
    int op;
    int i, j;
    int cmpcity, cmpdist;
    parking_t key;
    utils_t funcPtr;

    printf("====== Insertion Sort ======\n");
    printf("(1) by city-district\n");
    printf("(2) by longitude-latitude\n");
    printf("Input option2: ");
    scanf("%d", &op);

    if (op == 1)
    {
        for (i = 1; i < list->len; i++)
        {
            key = list->parkings[i];
            for (j = i; j > 0; j--)
            {
                cmpcity = strcmp(list->parkings[j - 1].city, key.city);
                if (cmpcity != 0)
                {
                    if (cmpcity < 0)
                        swap(&list->parkings[j], &list->parkings[j - 1]);
                    else
                        cmpdist = strcmp(list->parkings[j - 1].district, key.district);
                    if (cmpdist < 0)
                        swap(&list->parkings[j], &list->parkings[j - 1]);
                }
                list->parkings[j] = key;
            }

            funcPtr.print = my_print;
            funcPtr.print(list);
        }
    }
    else if (op == 2)
    {
        for (i = 1; i < list->len; i++)
        {
            key = list->parkings[i];
            for (j = i; j > 0; j--)
            {
                if (list->parkings[j - 1].longitude < key.longitude)
                    swap(&list->parkings[j], &list->parkings[j - 1]);
                else if (list->parkings[j - 1].latitude == key.latitude)
                    if (list->parkings[j - 1].district < key.district)
                        swap(&list->parkings[j], &list->parkings[j - 1]);
                    else
                        break;
            }
            list->parkings[j] = key;
        }

        funcPtr.print = my_print;
        funcPtr.print(list);
    }
    else
        printf("Invalid option\n");
}

/* Filter */
void my_filter(parking_list_t *list)
{
    int i, op;
    parking_t key, new_key;
    char city[100];
    char district[100];
    double min_long, max_long, min_lat, max_lat;
    utils_t funcPtr;

    parking_list_t *new_list = NULL;
    array_list_create(&new_list);

    printf("====== Filter ======\n");
    printf("(1) by city-district\n");
    printf("(2) by longitude-latitude\n");
    printf("Input option: ");
    scanf("%d", &op);

    if (op == 1)
    {
        printf("Input city: ");
        scanf("%s", city);
        printf("Input district: ");
        scanf("%s", district);
        for (i = 0; i < list->len; i++)
        {
            key = list->parkings[i];
            if (strcmp(key.city, city) == 0 && strcmp(key.district, district) == 0)
                new_key = new_list->parkings[i];
        }

        array_list_destroy(&list);

        funcPtr.print = my_print;
        funcPtr.print(new_list);
    }

    else if (op == 2)
    {
        printf("Input min_long: \n");
        scanf("%lf\n", &min_long);
        printf("Input max_long: \n");
        scanf("%lf\n", &max_long);
        printf("Input min_lat: \n");
        scanf("%lf\n", &min_lat);
        printf("Input max_lat: \n");
        scanf("%lf\n", &max_lat);

        for (i = 0; i < list->len; i++)
        {
            key = list->parkings[i];
            if (key.longitude > min_long && key.longitude < max_long)
            {
                if (key.latitude > min_lat && key.latitude < max_long)
                    new_key = new_list->parkings[i];
            }
        }

        array_list_destroy(&list);

        funcPtr.print = my_print;
        funcPtr.print(new_list);
    }
    else
        printf("Invalid option\n");
}