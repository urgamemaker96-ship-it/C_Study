#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable:4996) 

//����������

enum { HungrtyState, StressState ,HealthState};
int look; // �������ͽ� Ȯ�ο�

//�ٸ���ġ �ʱ���·� �� �ʱ�ȭ
int hungry = 10; //������
int poo= 10; // �躯Ȱ��
int health= 10; // ü��
int stress= 10; // ������
int exp= 0 ; // ����ġ
int currentlevel = 1; //���� ����


// �Լ��� ����
void Feed(int, int, int);
void  Poo();
void OutPlay(int, int, int);
void ThugPlay(int, int, int);


//������ 1.���� �߻� �ý����� ��� ������ �Ǵ��� ���� �������� -> while���� ����غ��� �õ��� �غ���...
//       2.�¸� ���Ǹ� ������ Ŭ���� �ǵ� ���ٵ� �¸� ������ �����߻��� �������� ������ �ɰͰ���...

//���� �ذ� �� �͵� : �Լ��� ���� �ش� ��ɵ��� ������ ���� �ٲ��ִ� ���� ��������
// -> �� ��ɵ��� ��� �����ؼ� �ٸ���ġ ������ �������ϴ°�?

int main(void)
{ // ��å�̳� �ͱ� ���� �ϴٰ� �߰��� ���� �߻� -> 1�� ����, 2�� ���� ��ġ��, ���� ü�� �������� ���� ü�� ��������
  //  �� ���� ����� ������ �̿��Ͽ� ������ ��...	

		
		

		
		 // �Ű������� ���� ������� ������ ������ �ʰ� �������� ������ ���´�. -> �������� �����Ͻ� 0���� �ʱ�ȭ
						  // �̷��� ������ ����? �Լ����� ���� ������ �ʴ� ������ Ȯ��... ��� ó�� �ؾ��ϴ°�? 
						// �ذ�� -> ���������� �Ű������� �����ϰ� �������� -> �Ű������� num1 ,num2,num3 ���� ó���ϴϱ� �����۵���
		printf("0�� ���� ���� ����� ���ϰ��� ���´¸� Ȯ���Ͻÿ�....\n");
		scanf("%d", &look);
	
		printf("1�� ���� ���� ����� ���ϰ߿��� ���̸� �ּ���.\n");
		scanf("%d", &look+1);


		printf("2�� ���� ���� ����� ���ϰ߿��� ȭ����� ����� �ּ���.\n");
		scanf("%d", &look + 2);

		printf("3�� ���� ���� ����� ���ϰ߿��� ��å�� ����� �ּ���.\n");
		scanf("%d", &look + 3);
		
		printf("4�� ���� ���� ����� ���ϰ߿��� �ͱװ����� ���� �ּ���.\n");
		scanf("%d", &look + 3);


		Feed(100,100,100);
		

		// ���� ���� ����
		switch (look) // look�� �����Ǥ� �������� ������ �� 0���� �ʱ�ȭ �Ǽ� 0���̴�.
		{
		case HungrtyState: //0�̰� , enum ���������� ������� ����

			printf("������� %d �Դϴ�\n", hungry);
			break;

		case StressState: //1�̴�

			printf("��Ʈ���������� %d �̰� �躯Ȱ���� %d �Դϴ�\n", stress,poo);
			break;
		case HealthState://2�̴�

			printf("ü�»��´� %d �Դϴ�\n", health);
			break;
		}
	




		// ������� ���ǹ�
		if (health <= 0 || poo >= 100 || hungry <= 0 || stress >= 100)
		{
			printf("����� �ֿϰ��� ����߽��ϴ�.\n");
		}


		// ������ ���ǹ�
		if (exp >= 100*currentlevel*1.2) 
		{	
			exp = 0; // ������ �� ����ġ �ʱ�ȭ
			currentlevel += 1; // ����ġ�����ؼ� 1 ����
			printf("����� �ֿϰ��� ������ %d�������߽��ϴ�.\n",currentlevel);

		}



}

//���ִ��Լ� -> ü������, ������ ����, �躯Ȱ�� ����
void Feed(int num1, int num2, int num3) 
{
	

	health += num1;
	hungry += num2;
	poo += num3;
	
	return health, hungry, poo;
}

//�躯�Լ� -> �躯 Ȱ�� 0���� ����ȭ
void Poo()
{	
	return poo = 0;

}

//��å �Լ� -> ü�°���, ������ ����, ����ġ ����
void OutPlay(int num1, int num2, int num3)
{
	health -= num1;
	hungry -= num2;
	exp += num3;
	return health, hungry, exp;
}

//�ͱ׳��� -> ����� ����, ������ ����, ����ġ ����
void ThugPlay(int num1, int num2, int num3)
{
	hungry -= num1;
	stress -= num2;
	exp += num3;

	return hungry, stress, exp;
}




