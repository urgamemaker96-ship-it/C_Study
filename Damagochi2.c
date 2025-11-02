#include <stdio.h>
#include <stdlib.h> // rand()�Լ� ���� ���̺귯��
#include <time.h> // time()�Լ� ���� ���̺귯��


//�Լ� ����� main �Լ� ������ �Լ� ���� ��������� ������ �Լ����� ���� �� �ʿ����.
#pragma region  Select
void SelectSleep(int*,int*,int*,int*);
void SelectPoop(int*);
void SelectEat(int*, int*);
void SelectWalk(int*, int*, int*, int*, int*, int*);
void SelectTug(int*, int*, int*, int*, int*, int*);
void SelectShop(int*, int*, int*, int*);
void SelectGuide();
#pragma endregion

#pragma region Show
void ShowStatus(int*, int*, int*, int*, int*, int*, int*);
void ShowShop();
void ShowChoice();
void ShowBattle(int, int*, int*);
void ShowDamage(int, int);
#pragma endregion

#pragma region Util
int UserInput();
int Percent(int);
#pragma endregion

#pragma region GameStatus
void Init();
int IsGameOver(int*, int*, int*, int*);
void Action(int, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*);
void LevelUpRule(int*, int*, int*);
#pragma endregion

#pragma region Battle
int TakeDamage(int, int);

#pragma endregion



int main(void)
{	
	//1.��� ���� ���������� �����ؼ� ������ �̿��ذ����� �� �۵��ϴ��� �׽�Ʈ �غ���!
	//2.��� ������ ���������� �����ϴ� ���� �Լ����� ������ ����
	//3.�ش� ������ �Լ� Ȯ���ϴ� ���� ������ ��� �Ͼ, �ش� �Լ� �Ķ���Ͱ��� ���Ӱ� ���� 
	//4.�Լ� �Ķ���� ���� ���������� �����ϰ� �� ������ Ÿ���� ������ Ÿ������ �������ص� ���� �ȳ��� ��������
	
	//���������� �ʱⰪ ����
	int mana = 100; // ����, ��ų �Լ������ �ٸ���ġ���� �ʿ�
	int Maxhealth = 100; // �������� �� �ʿ��ؼ� ���� ������ �ƴ϶� ���ο� ����������
	int health = 100;  // �ʱⰪ ����
	int hungry = 50;  // �ʱⰪ ����
	int gochiattack = 40; //�� ��ī���� �ý��� ����� ���� �ʿ��� ������ �ʱ�ȭ����
	int poo = 50; // �躯Ȱ������
	int stress = 40; // ��Ʈ���� ����, ������� ���� ���� ����
	int exp = 0; // ������ �ý��� ����� ���� �ʿ��� ������ �ʱ�ȭ ����
	int currentlevel = 1; // ������ �ý��� ����� ���� �ʿ��� ������ �ʱ�ȭ ����
	int rewardgold = 8000; // ���� �ý��� ����� ���ؼ� ������ ����

	int mainInput;

	// ���� �ʱ�ȭ
	Init();

	while (!IsGameOver(&poo, &stress, &currentlevel, &health)) // �ݺ��� ����
	{
		//������ ���� üũ
		LevelUpRule(&exp, &currentlevel, &gochiattack);
		
		// ���� ���� ���
		ShowStatus(&health, &mana, &hungry, &poo, &stress, &exp, &rewardgold);

		// ���� �Է� �޴� ���
		ShowChoice();

		// ���� �Է� ���
		mainInput = UserInput();

		// ���� �Է¿� ���� �׼�		
		Action(mainInput,&health, &Maxhealth, &stress, &mana, &poo, &hungry, &gochiattack, &exp, &rewardgold, &currentlevel);
	}
}

void SelectSleep(int* health, int* Maxhealth , int* stress, int* mana)
{
	if (*health >= *Maxhealth)
	{
		printf("���̻� �� �ʿ䰡 �����ϴ�.\n");
		*stress += 10;
	}
	else
	{
		*health += 10;
		printf("�ٸ���ġ�� ü���� %d �����߽��ϴ�\n", 10);

	}

	if (*mana >= 100)
	{
		printf("���̻� ������ ȸ���� �� �����ϴ�.\n");
		*stress += 10;
	}
	else
	{
		*mana += 10;
		printf("�ٸ���ġ�� ������ %d �����߽��ϴ�\n", 10);
	}
}

void SelectPoop(int* poo)
{
	*poo = 0;
	printf("�ٸ���ġ�� �躯Ȱ�������� %d �Ǿ����ϴ�\n", *poo);
}

void SelectEat(int* hungry,int* poo)
{
	if (*hungry >= 200)
	{
		printf("���̻� ���� �ʿ䰡 �����ϴ�.\n");
	}
	else
	{
		*hungry += 20;
		*poo += 20;
		printf("�ٸ���ġ�� �������� %d �����߽��ϴ�\n", 20);
	}
}

void SelectWalk(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold,int* stress)
{
	int userInput;
	if (Percent(50)) //0~49�ϱ� 50�ۼ�Ʈ��
	{
		printf("===================================================\n");
		printf("��å �� ���� ��Ÿ�����ϴ�!!.\n");

		// ���� ���� �ʱ�ȭ
		int turnon = 1; // while �� ���� ���� ��������
		int battle_enemyhealth = 100;  // �� ü�º��� ����
		int battle_enemyattack = 20; // �� ���ݷ� ��������

		//while �� �ȿ� while �� ���� �����ҷ��� ������ �ʿ��ߴ�
		while (turnon)
		{
			//1. battle_enemyhealth�� ���� ������ ������ �ȹ޾��൵��, �̹� ���� ��Ͽ� �����
			//2. ShowBattle(����,&����,&����) �÷� �޾ƾ� �Ǵµ� �׷� ��� health, mana �� �޸� ��ġ(�ּ�) ���̳���
			//3-1 �̹� SelectWalk �Լ� ���� ü�°� ������ ������ ������ �������༭ 
			//3-2 ���� ���� ShowBattle �Լ��� �� ü�°� ���� ������ &������ ������� ���������ʹ� �׷��� �׳� �������� mana, health ���ִ°Ŵ�
			ShowBattle(battle_enemyhealth, health, mana); //&health, &mana �Ƚ��ִµ��� ������ �ִ�.
			scanf_s("%d", &userInput);

			switch (userInput) // �б⹮ �ȿ� �б⹮ ���� �� �־���!!!
			{
			case 1: // ����
				battle_enemyhealth = TakeDamage(*gochiattack, battle_enemyhealth); //���������� ���� ���ܼ� TakeDamage �Լ��� ShowDamage �Լ��� ������ Ÿ������ �������
				printf("������ %d ��ŭ ���ظ� ����ϴ�!\n", *gochiattack);

				if (battle_enemyhealth <= 0) // �� �������
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // ���� while ���� Ż��
					*exp += 50;   // ����ġ ȹ��
					printf("����ġ�� %d ������ϴ�!\n", 50);
					*rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					*stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}
				break;

			case 2: // �� ��� ������ ��ų���� ���� ����� �� ü�� -�Ǹ� ��� ������
				printf("�ٸ���ġ�� ��ų�� ����߽��ϴ�!.\n");
				if (*mana < 50) //0���� �ϴ� Ÿ�̹� �ȸ¾Ƽ� 50���� ����
				{
					printf("������ ���� ��ų�� ������� ���մϴ�.!.\n");

				}
				else
				{
					*mana -= 50;

					int totalDamage = *health + *gochiattack; // ShowDamage �Լ� �ڷ����� �´� �Ķ���� ��� ���ؼ� ���ο� ���� ������
					battle_enemyhealth = TakeDamage(totalDamage, battle_enemyhealth);
					ShowDamage(1, totalDamage);
					//�ݵ�� ���� �ʱ�ȭ ����� �� ü���� �������

				}
				if (battle_enemyhealth <= 0)
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // ���� while ���� Ż��
					*exp += 50;   // ����ġ ȹ��
					printf("����ġ�� %d ������ϴ�!\n", 50);
					*rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					*stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}

				break;

			case 3: // ����
				printf("�����ƽ��ϴ�!\n");
				*stress += 10;
				turnon = 0;  // ���� while ���� Ż��
				break;


			}

			//�� ü�� �����ϸ� ������
			if (battle_enemyhealth > 0)
			{
				*health -= battle_enemyattack;
				printf("���� ����� �����߽��ϴ�! ü���� %d �����߽��ϴ�.\n", battle_enemyattack);


				if (Percent(30)) // ����ų�� 30�ۼ�Ʈ�� ��ų ����
				{	//TakeDamage �Լ��� �׳� �ܼ� ����� 
					//-> �Ķ���� Ÿ�Կ� �����ʴ�*���� ����ص� *���� ���� �ش� ������ �ּҿ� �ִ� ���̶�� ���̴�.
					int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
					*health = TakeDamage(totalEnemyDagame, *health);
					ShowDamage(2, totalEnemyDagame);
				}
				if (*health <= 0)
				{
					printf("�ٸ���ġ�� ���������ϴ�!\n");
					turnon = 0;
				}
			}
		}
	}
	else
	{
		if (*stress <= 0)
		{
			*stress = 0;
			printf("���̻� ��Ʈ���� ������ ���� �� �����ϴ�.\n");
		}
		else
		{
			*stress -= 20;
			printf("��Ʈ������ ��å���� ���� %d �پ����ϴ�.\n", 20);
		}
	}
}

void SelectTug(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress)
{
	int userInput;
	if (Percent(60))
	{
		printf("===================================================\n");
		printf("�ͱ׳��� �� ���� ��Ÿ�����ϴ�!!.\n");

		// while �� �ȿ� �� while �� ������ ���� ���� â ���� �� ����
		int turnon = 1; // while �� �ȿ� while �� �������� �������� �� �ʱ�ȭ
		int battle_enemyhealth = 80;  // ��å�� ���ؼ� ü�� ����
		int battle_enemyattack = 30;   // 

		while (turnon)
		{
			ShowBattle(battle_enemyhealth, health, mana);
			scanf_s("%d", &userInput);

			switch (userInput)
			{
			case 1: // ����
				battle_enemyhealth = TakeDamage(*gochiattack, battle_enemyhealth);
				printf("������ %d ��ŭ ���ظ� ����ϴ�!\n", *gochiattack);

				if (battle_enemyhealth <= 0)
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // while �� �� while �� Ż���ϰ� �Ϲ� while������ ��
					*exp += 50;
					printf("����ġ�� %d ������ϴ�!\n", 50);
					*rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					*stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}
				break;

			case 2: // ��ų
				printf("�ٸ���ġ�� ��ų�� ����߽��ϴ�!.\n");
				if (*mana < 50)
				{
					printf("������ ���� ��ų�� ������� ���մϴ�.!.\n");
				}
				else
				{

					int totalDamage = *health + *gochiattack;
					battle_enemyhealth = TakeDamage(totalDamage, battle_enemyhealth);
					ShowDamage(1, totalDamage);
					//�� �ʱ�ȭ ������� �� ü�� ���δ�, �̰� ���� �߿���!!

				}
				if (battle_enemyhealth <= 0)
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // ���� while ���� Ż��
					*exp += 50;   // ����ġ ȹ��
					printf("����ġ�� %d ������ϴ�!\n", 50);
					*rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					*stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}



				break;

			case 3: // ����
				printf("�����ƽ��ϴ�!\n");
				*stress += 10;
				turnon = 0;  // while �� Ż���Ѵ�. ���� 0���� �� �ʱ�ȭ �����ָ� ���� ���ϰ� ��� �����
				break;


			}

			// �� ü���� �����ϸ� ������
			if (battle_enemyhealth > 0)
			{
				*health -= battle_enemyattack;
				printf("���� ����� �����߽��ϴ�! ü���� %d �����߽��ϴ�.\n", battle_enemyattack);

				if (Percent(30)) // ����ų�� 30�ۼ�Ʈ�� ��ų ����
				{
					int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
					*health = TakeDamage(totalEnemyDagame, *health);
					ShowDamage(2, totalEnemyDagame);
				}
				if (*health <= 0)
				{
					printf("�ٸ���ġ�� ���������ϴ�!\n");
					turnon = 0;
				}
			}
		}
	}
	else
	{
		if (*stress <= 0)
		{
			*stress = 0;
			printf("���̻� ��Ʈ���� ������ ���� �� �����ϴ�.\n");
		}
		else
		{
			*stress -= 30;
			printf("��Ʈ������ �ͱ�Ȱ������ ���� %d �پ����ϴ�.\n", 30);
		}
	}
}

void SelectShop(int* rewardgold,int* Maxhealth, int* gochiattack, int* currentlevel)
{
	int userInput;

	if (*rewardgold < 200)
	{
		printf("���� ���� �̿��� �� �����ϴ�!!\n");

	}
	else
	{
		ShowShop();
		//�б⹮ �ȿ� �б⹮ ���� �� �ִ�, �Է� ���� ���� num2�� ������� ������ �׷� �ʿ� ���� num1�� ��, �Է¹޴°� �ǹ̰� ���� �ϳ��� ����ϴ�.
		scanf_s("%d", &userInput);
		switch (userInput)
		{
		case 1:
			*rewardgold -= 200;
			*Maxhealth += 100;

			printf("�ִ�ü���� %d �����Ͽ� %d�� �Ǿ����ϴ�.", 100, *Maxhealth);
			break;

		case 2:
			*rewardgold -= 300;
			*gochiattack += 50;
			printf("���ݷ��� %d �����Ͽ� %d�� �Ǿ����ϴ�.", 50, *gochiattack);
			break;


		case 3:
			*rewardgold -= 400;
			*currentlevel += 1;
			printf("������ %d �����Ͽ� %d�� �Ǿ����ϴ�.", 1, *currentlevel);
			break;
		}
	}


}

void SelectGuide()
{
	printf("�ٸ���ġ�� ��Ʈ������ 100�� ��ų� �躯������ 100�� ��� ��� �׸��� ���� �� ü���� �������� ����մϴ�.\n");
	printf("�ٸ���ġ�� ������ 10�̵Ǹ� ���������ϸ� ������ Ŭ���� �˴ϴ�..\n");
	printf("�ٸ���ġ�� �Ұ����� ������ �Ҷ� ,����ĥ�� ��Ʈ������ 10�� �޽��ϴ�.\n");
	printf("�ٸ���ġ�� ���� �ڰų�, ���� �����߸� ��� ��Ʈ������ ȸ���մϴ� .\n");
}

//�Լ� ���ǵ� > �Լ� ���� �κа� �Լ� �̸��� �� ������ߵ� , �׸��� ���ϰ��� �ݵ�� 1����


int TakeDamage(int damage, int health)//�̹� ���� �������� health ����Ǿ� �־ ���� ������ �ڷ��������� �ȸ���
{
	return health - damage;
}
int Percent(int num1) // Ȯ�������� ������ִ� �Լ�
{
	return (rand() % 100) < num1; // 0����99���� �����ϰ� �����µ� < 70�� 0~69���� ��ȯ�� -> ���� ��ü�� ��ȯ�ȴ�.
	//0�� 1�� �Ǵ� -> ������ ���̸� ����Ǵ°Ŵ�!
}
void ShowStatus(int* health, int* mana, int* hungry, int* poo, int* stress, int* exp, int* rewardgold)
{
	printf("===================================================\n");
	printf("����â\n");
	printf("ü��: %d\n", *health);
	printf("����: %d\n", *mana);
	printf("������: %d\n", *hungry);
	printf("ȭ���: %d\n", *poo);
	printf("��Ʈ����: %d\n", *stress);
	printf("����ġ: %d\n", *exp);
	printf("������: %d\n", *rewardgold);
	printf("===================================================\n");
}
void ShowChoice()
{
	printf("\n=======================================================================================\n");
	printf("1.���ڱ� 2.�����ϱ� 3.���ֱ� 4.��å�ϱ� 5.�ͱ׳��� 6.���� 7.�ٸ���ġ ���̵����\n");
	printf("=======================================================================================\n");
}
void ShowBattle(int num1, int* num2, int* num3)// �� ü���� �� ��Ͽ� ���������� �̹� �� ������ ������ ü��, ���� �������� �׷��� ���� ������ Ÿ������ �������
{
	printf("\n----- ���� -----\n");
	printf("�� ü��: %d\n", num1);
	printf("�� ü��: %d\n", *num2);
	printf("�� ����: %d\n", *num3);
	printf("���ϴ� ���ڸ� ���� ���� �Ͻʼ�\n");
	printf("1.���� 2.��ų 3.����\n");
	printf("�Է�: ");
}
void ShowShop()
{
	printf("���ϴ� ��ǰ�� �����Ͽ� �ֽʼ�!!\n");
	// �Է��ش޶�� �ȳ� �޽����� ���
	printf("=========================================================================\n");
	printf("1.�ִ�ü����������:200��� 2.���ݷ���������:300��� 3.����������:400���\n");
	printf("=========================================================================\n");
	printf("�Է�: ");

}


void LevelUpRule(int* exp, int* currentlevel, int* gochiattack)
{
	if (*exp >= 100 * *currentlevel * 1.2)
	{
		(*currentlevel)++; //*(currentlevel)++ �̷����ؼ� �����Ͱ� ����Ű�� ���� �������Ѿ� �Ǵµ� ������ �� ��ü�� ������Ŵ -> ��������
		*exp = 0; //�����ͷ� ������ �����ǰ��� 0���� �ʱ�ȭ����
		*gochiattack += 10; //�����ͷ� ������ �����ǰ��� 10�� ��������
		printf("\n ���� ��! ���� ����: %d\n", *currentlevel);
		printf("���ݷ��� %d�� �����߽��ϴ�!\n", *gochiattack);
	}

}

void Init()
{
	// rand() �ʱ�ȭ�� �� ����!
	srand((unsigned int)time(NULL)); // ������ ���� �ʿ����, ���α׷� ����� �ѹ��� �ʱ�ȭ ���൵��
}

int IsGameOver(int* poo, int* stress, int* currentlevel, int*health)
{
	//�躯������ 100�� �޼� �� ���ӿ��� ���� -> break�� �Լ� ������ ó������ ���Ұ� ���� ���ܵ�
	if (*poo >= 100 || *stress >= 100)
	{
		printf("�ٸ���ġ�� ���� �ɷȽ��ϴ�.\n");
		printf("������ ����Ǿ����ϴ�.\n");
		return 1; // ���� ����
	}
	//�¸� ���Ǵ޾��ֱ� -> break�� �Լ� ������ ó������ ���Ұ� ���� ���ܵ�
	if (*currentlevel == 10)
	{
		printf("�ٸ���ġ�� ������ �����߽��ϴ�!!\n");
		printf("������ ����Ǿ����ϴ�.\n");
		return 1;  // ���� ����
	}
	// �ٸ���ġ ���
	if (*health <= 0)
	{
		printf("������ ����Ǿ����ϴ�.\n");
		return 1; // ���� ����
	}

	return 0;
}

int UserInput()
{
	int inputNum;

	printf("�Է�: ");
	scanf_s("%d", &inputNum);
	return inputNum;
}

void Action(int num1,int* health, int* Maxhealth, int* stress, int* mana, int* poo, int* hungry, int* gochiattack,int* exp, int* rewardgold, int* currentlevel)
{	//���� ���������� ���� ������ �Ķ���ͺ��� �տ� &�ȴ޾��ذŴ�.
	switch (num1)
	{
	case 1:
		SelectSleep(health, Maxhealth, stress, mana);
		break;
	case 2:
		SelectPoop(poo);
		break;
	case 3:
		SelectEat(hungry, poo);
		break;
	case 4:
		SelectWalk(health, mana, gochiattack, exp, rewardgold, stress);
		break;
	case 5:
		SelectTug(health, mana, gochiattack, exp, rewardgold, stress);
		break;
	case 6:
		SelectShop(rewardgold, Maxhealth, gochiattack, currentlevel);
		break;
	case 7:
		SelectGuide();
		break;
	}
}

void ShowDamage(int target, int damage)
{
	
	switch (target)
	{
	case 1: // �ٸ���ġ -> ��
		printf("�ٸ���ġ�� ü�°� ���ݷ��� ��ģ ��ų(�Ѱ��ݷ�:%d)�� ����߽��ϴ�!\n", damage);
		printf("������ %d�� ���ظ� �������ϴ�!\n", damage);
		break;

	case 2: // �� -> �ٸ���ġ
		printf("���� ü�°� ���ݷ��� ��ģ ��ų(�Ѱ��ݷ�:%d)�� ����߽��ϴ�!\n", damage);
		printf("�ٸ���ġ���� %d�� ���ظ� �������ϴ�!\n", damage);
		break;
	}
}