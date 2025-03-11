/*
 * �޸� ���� �Լ� (sizeof(malloc))
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 int main(void) {
     // �迭������! int Ÿ�� �޸𸮸� ����Ű�� �ִ� �ִ� ������
     int *malloc_p = (int *)malloc(5 * sizeof(int)); // 4����Ʈ ���� �����͸� 5�� ������ �� �ִ� ���� �޸𸮸� �Ҵ�
 
     // malloc_p�� ��·�� "�����ͺ���"�̴�.
     // ���� sizeof(malloc_p)�� �������� �Ҵ���� �޸��� ũ�Ⱑ �ƴ� ������ ������ ũ�⸦ ��ȯ�Ѵ�.
     printf("sizeof(malloc_p): %lu\n", sizeof(malloc_p));
 
     // �������� free!!
     free(malloc_p);
 
     return 0;
 }