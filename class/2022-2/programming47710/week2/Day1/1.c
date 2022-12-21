// Question-1. 다음 프로그램의 소스코드 또는 주석들에 있는 각 빈칸들 (A) ~ (K)을 적절히 채우십시오.
// Fill in the blanks (A) to (K) appropriately in the source code or comments of the following programs.

#include <stdio.h>

#include <stdio.h>
int main(void)
{
    int x = 3, y = 4, z = 5;
    double f = 7.0;
    printf("%d\n", 9 / 7);   // What is the output? (A)
    printf("%d\n", 9 % 7);   // What is the output? (B)
    y *= x;                  // What is the uncompressed form? (C)
    x++;                     // What is the uncompressed form? (D)
    printf("%f\n", 2 / 0.5); // What is the output? (E)
    x = 36.5;                // What is stored to x? (F)
    // f = (G)x;                              // Fill the blank with the most proper datatype conversion.
    f = (double)x;                         // Fill the blank with the most proper datatype conversion.
    printf("%d\n", 9.2 > 7);               // What is the output? (H)
    printf("%d\n", (9.2 > 7) && (7 > 33)); // What is the output? (I)
    printf("%d\n", (9.2 > 7) || (7 > 33)); // What is the output? (J)
    x = y = z = 7;                         // Add all parentheses to show the order of operations.(J) --> (K)
    return 0;

    // (A) 1
    // (B) 2
    // (C) y = y * x;
    // (D) x = x + 1;
    // (E) 4.000000
    // (F) 36
    // (G) double
    // (H) 1
    // (I) 0
    // (J) 1
    // (K) x = (y = (z = 7));
}