/*
 * �޸� ���� �Լ� (malloc + free -> malloc)
 */

#include <stdio.h>
#include <stdlib.h>

/* ������ ������ ����ؼ� �߰��ϰ� ������...
 * ������ ������ ����� ������ ���� ���Ѵ�...
 */
int main(void) {
    int i, cnt = 0; // �ε��� 0���� �ʱ�ȭ
    int *malloc_p = (int *)malloc(5 * sizeof(int)); // 4����Ʈ ���� �����͸� 5�� ������ �� �ִ� ���� �޸𸮸� �Ҵ�
    char buf[256]; // ���Ͽ��� ���� ���� ������ ����
    FILE *fp;

    // inputs������ input01.txt ������ �б� ���� ����
    if ((fp = fopen("inputs/input01.txt", "r")) == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    printf("Success to open file\n");

    while (fgets(buf, sizeof(buf), fp) != NULL) { // ���Ͽ��� �� �پ� �о buf�� ����
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
