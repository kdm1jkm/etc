/*
 * �޸� ���� �Լ� (realloc)
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * ���� ������� ���� ������ ������ 5���� �Ѿ��
 * �޸𸮸� �ٽ� �Ҵ��ϸ� ���� ������?
 */
int main(void) {
    int i, cnt = 0;
    int capacity = 5; // ���� �Ҵ���� �޸��� ũ��(Ȥ�� �迭�� ����� �� ������ ����)�� ������ ������ �ʿ��ϴ�.
    int *malloc_p = (int *)malloc(capacity * sizeof(int));
    char buf[256]; // ���Ͽ��� ���� ���� ������ ����
    FILE *fp;

    // inputs������ input01.txt ������ �б� ���� ����
    if ((fp = fopen("inputs/input01.txt", "r")) == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    printf("Success to open file\n");

    while (fgets(buf, sizeof(buf), fp) != NULL) {   // ���Ͽ��� �� �پ� �о buf�� ����
        if (cnt >= capacity) { // ������� ���� �����Ͱ� capacity(�뷮)�� ä���
            printf("realloc at %dth index\n", cnt);
            capacity++; // �뷮(capacity)�� �ø� ��
            malloc_p = (int *)realloc(malloc_p, capacity * sizeof(int)); // �޸𸮸� �ٽ� �Ҵ�
        }
        malloc_p[cnt] = (int)strtol(buf, NULL, 10); // ���ڿ��� ������ ��ȯ�Ͽ� malloc_p�� ����
        cnt++;
    }
    printf("Read %d integers\n", cnt);

    // �������� fclose!!
    if (fclose(fp) == EOF) {
        printf("Failed to close file\n");
        return 1;
    }
    printf("Success to close file\n");
    
    // ���Ͽ��� ���� ���� ���
    for (i = 0; i < cnt; i++)
        printf("malloc_p[%d]: %d\n", i, malloc_p[i]);

    // �������� free!!
    free(malloc_p);

    return 0;
}
