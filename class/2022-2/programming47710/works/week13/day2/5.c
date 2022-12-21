#include <stdio.h>

int main()
{
    FILE *f = fopen("sonething", "w+");

    fseek(f, 0L, SEEK_SET);
    // --> 0

    fseek(f, 4 * sizeof(double), SEEK_SET);
    // --> 32

    fseek(f, 300L, SEEK_CUR);
    // --> 400

    fseek(f, 0L, SEEK_END);
    // --> End of File.

    rewind(f);
    // --> 0
}