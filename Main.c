/*
* 1. ����¹�
 
#include <stdio.h> // �����ϴ� <�������>

int main(void) // ���� �Լ� ���α׷��� ������
{
	printf("Hello, World!\n"); // ��� �Լ� ("���ڿ� ���Ĺ���");
	return 0; // 0�� ��ȯ�ϰ� ����
}


printf�� �Լ���.
main�� �Լ���.

return 0;�� �ϴ� ����?
�ü����� ���� ���� ���� ���� ����
���α׷��� ������ ����� �Ը���� �Ű������� ���� ������ �� �ִ� �ɼ��� �־�����
���� ����Ǿ��� ���� 0�ڵ带 ��ȯ�ϴ� �Ϲ��� ���� �־���.



#define _CRT_SECURE_NO_WARNINGS << �̰� �� ���°�? �Ⱦ��� ���� �Ǵ°�?

#include <stdio.h>

int main(void)
{
	int inputNum = 0;
	printf("�Է�: ");
	scanf("%d", &inputNum); // ���ۻ��� ������ �� ���°�?
	printf("�Է��� ��: %d", inputNum);
}
*/

/*
* 2. ������ ���� ������ �޸�� ��ü
*/

/*
* 3. ���ǹ��� 4.�б⹮
* [���ǹ�]
* if, else if, else
* ���ǽ� �˻簡 �����ϴ� (��)
* ������ ������
* 
* [�б⹮]
* switch~case
* ���ǰ˻簡 �Ұ����ϴ�
* ������ ������
* �������� ����

#include <stdio.h>
enum {Attack, Run};
int main(void)
{
	int a = 0;

	if (a < 10)
	{
		printf("10���� �۴�");
	}
	else if (a > 10)
	{
		printf("10����ũ��");
	}
	else
	{
		printf("10�̴�");
	}

	switch (a)
	{
	case Attack:
		printf("����");
		break;
	case Run:
		printf("����");
		break;
	case 11:
		printf("10����ũ��");
		break;
	}
}
*/

/*5. �ݺ���
* 
* for, while, do~while

for(i = 0; i < 5; i++)
{
	printf("test");
}

while(true)
{
	printf("test");
	// �� �ݺ��� �ȿ��� Ư�� ������ �Ϸ� �Ǿ��� �� Ż��
}

���ǹ� �б⹮�� ��Ȯ�� �ٸ�������
�ݺ����� ������ �����̴�.


*/

/*
* 6. �Լ�
* 
*/

#include <stdio.h>

int dataA = 100;
int dataB = 200;
// �Լ��� ����
void Add(int, int);
void PrintNum(int);

// ���� �Լ�
int main(void)
{
	int a = 10;
	int b = 20;
	// �Լ��� ȣ��
	Add(a, b);
}

// �Լ��� ����
void Add(int num1, int num2) // int num1 = a, int num2 = b
{
	PrintNum(num1 + num2);
}

void PrintNum(int result)
{
	printf("%d \n", result);
}