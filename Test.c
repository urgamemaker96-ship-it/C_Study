
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//
//int main() {
//    int arr[5] = { 10, 20, 30, 40, 50 };
//
//    // �迭�� �̸��� ù ��° ����� �ּҸ� ����Ŵ
//    int* ptr = arr;  // arr[0]�� ����Ŵ
//
//    // ������ �������� 3��° ��� ����
//    int* third_element = ptr + 2;  // 0��°���� 2��ŭ �̵� �� 2�� �ε��� (3��° ���)
//
//    printf("�迭 ��ü: ");
//    for (int i = 0; i < 5; i++) {
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
//
//    printf("3��° ��� (arr[2]): %d\n", arr[2]);
//    printf("������ �������� ã�� ��: %d\n", *third_element);
//    printf("0��° ����� �ּ� �迭��: %p\n", arr);
//    printf("0��° ����� �ּ�: %p\n", &arr[0]);
//    printf("0��° ����� �ּ� �迭��: %p\n", arr + 1);
//    printf("0��° ����� �ּ�: %p\n", &arr[1]);
//    printf("3��° ����� �ּ� �迭��: %p\n", &arr[2]);
//    printf("3��° ����� �ּ�: %p\n", third_element);
//
//    return 0;
//}

int main(void)
{
	char name[20];
	int input[10];
	printf("�̸��� �Է�: ");
	scanf("%s", name);
	printf("�̸�: %s", name);


	printf("���ڸ� �Է�: ");
	scanf("%d", input);
	printf("����: %d", input[0]);
}