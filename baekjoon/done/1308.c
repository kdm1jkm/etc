#include <stdio.h>
#include <stdbool.h>

bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

int getDays(int year, int month)
{
    switch (month)
    {
    case 2:
        if (isLeapYear(year))
            return 29;
        return 28;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;

    default:
        return 31;
        break;
    }
}

typedef struct _date
{
    int year, month, day;
} date;

int main()
{
    date date1, date2;
    scanf("%d %d %d", &date1.year, &date1.month, &date1.day);
    scanf("%d %d %d", &date2.year, &date2.month, &date2.day);

    if (date2.year - date1.year > 1000 || date2.year - date1.year == 1000 && (date2.month > date1.month || date2.month == date1.month && date2.day >= date1.day))
    {
        printf("gg\n");
        return 0;
    }

    unsigned long int result = 0;

    for (int i = date1.year + 1; i < date2.year; i++)
    {
        if (isLeapYear(i))
            result += 366;
        else
            result += 365;
    }

    if (date1.year == date2.year)
    {
        for (int i = date1.month + 1; i < date2.month; i++)
            result += getDays(date1.year, i);
    }
    else
    {
        for (int i = date1.month + 1; i <= 12; i++)
            result += getDays(date1.year, i);
        for (int i = 1; i < date2.month; i++)
            result += getDays(date2.year, i);
    }

    if (date1.year == date2.year && date1.month == date2.month)
    {
        result += date2.day - date1.day;
    }
    else
    {
        result += getDays(date1.year, date1.month) - date1.day;
        result += date2.day;
    }

    printf("D-%ld\n", result);
}