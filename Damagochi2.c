#include <stdio.h>
#include <stdlib.h> // rand()�Լ� ���� ���̺귯��
#include <time.h> // time()�Լ� ���� ���̺귯��


//�Լ� ����� main �Լ� ������ �Լ� ���� ��������� ������ �Լ����� ���� �� �ʿ����.
int AttackAddHealth1(int, int,int);
int AttackAddHealth2(int, int,int);
void ShowStatus(int,int,int,int,int,int,int);
void ShowGuide(); // �ٱ����ο��ٰ� �Լ� ��������� �ش� �Լ� �����ִ�. -> �Լ��ȿ� �Լ� ����Ҷ�
void ShowShop();
void ShowBattle(int,int,int);
int Percent(int);

int mana = 100; // ����, ��ų �Լ������ �ٸ���ġ���� �ʿ�
int Maxhealth = 100; // �������� �� �ʿ��ؼ� ���� ������ �ƴ϶� ���ο� ����������
int health = 100;  // �ʱⰪ ����
int hungry = 50;  // �ʱⰪ ����
int gochiattack = 40; //�� ��ī���� �ý��� ����� ���� �ʿ��� ������ �ʱ�ȭ����
int poo = 50; // �躯Ȱ������
int num1; // �Է¹ޱ����� ��������
int stress = 40; // ��Ʈ���� ����, ������� ���� ���� ����
// �� ��ī���� �ý��� ����ٺ��� �ʿ��� ������ �ʱ�ȭ ����
// �� ��ī���� �ý��� ����ٺ��� �ʿ��� ������ �ʱ�ȭ ����
int exp = 0; // ������ �ý��� ����� ���� �ʿ��� ������ �ʱ�ȭ ����
int currentlevel = 1; // ������ �ý��� ����� ���� �ʿ��� ������ �ʱ�ȭ ����
int gameon = 1; //while �� �ȿ� �� �ٸ� while �� ����� ���� ���� while �� ������ �ʿ��ؼ� ���� ������ ������
int rewardgold = 8000; // ���� �ý��� ����� ���ؼ� ������ ����




void SwitchSelect1to3(int num1)
{
	switch (num1)
	{
	case 1: //1���� ������ ���ڱ⸦ �õ��Ѵ�.
		if (health >= Maxhealth)
		{
			printf("���̻� �� �ʿ䰡 �����ϴ�.\n");
			stress += 10;
		}
		else
		{
			health += 10;
			printf("�ٸ���ġ�� ü���� %d �����߽��ϴ�\n", 10);

		}

		if (mana >= 100)
		{
			printf("���̻� ������ ȸ���� �� �����ϴ�.\n");
			stress += 10;
		}
		else
		{
			mana += 10;
			printf("�ٸ���ġ�� ������ %d �����߽��ϴ�\n", 10);
		}
		break;

	case 2: //2���� ������ �躯Ȱ���� 0�̵ǰ�
		poo = 0;
		printf("�ٸ���ġ�� �躯Ȱ�������� %d �Ǿ����ϴ�\n", poo);
		break;

	case 3: //3���� ������ �������� ä������ �躯������ ä������.
		if (hungry >= 200)
		{
			printf("���̻� ���� �ʿ䰡 �����ϴ�.\n");
		}
		else
		{
			hungry += 20;
			poo += 20;
			printf("�ٸ���ġ�� �������� %d �����߽��ϴ�\n", 20);
		}
		break;

	}
}

void SwitchSelect4(int num1) 
{
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
			ShowBattle(battle_enemyhealth, health, mana);
			scanf_s("%d", &num1);

			switch (num1) // �б⹮ �ȿ� �б⹮ ���� �� �־���!!!
			{
			case 1: // ����
				battle_enemyhealth -= gochiattack;
				printf("������ %d ��ŭ ���ظ� ����ϴ�!\n", gochiattack);

				if (battle_enemyhealth <= 0) // �� �������
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // ���� while ���� Ż��
					exp += 50;   // ����ġ ȹ��
					printf("����ġ�� %d ������ϴ�!\n", 30);
					rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}
				break;

			case 2: // �� ��� ������ ��ų���� ���� ����� �� ü�� -�Ǹ� ��� ������
				printf("�ٸ���ġ�� ��ų�� ����߽��ϴ�!.\n");
				if (mana < 50) //0���� �ϴ� Ÿ�̹� �ȸ¾Ƽ� 50���� ����
				{
					printf("������ ���� ��ų�� ������� ���մϴ�.!.\n");

				}
				else
				{
					mana -= 50;

					battle_enemyhealth = AttackAddHealth1(health, gochiattack, battle_enemyhealth);
					//�ݵ�� ���� �ʱ�ȭ ����� �� ü���� �������

				}
				if (battle_enemyhealth <= 0)
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // ���� while ���� Ż��
					exp += 50;   // ����ġ ȹ��
					printf("����ġ�� %d ������ϴ�!\n", 30);
					rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}

				break;

			case 3: // ����
				printf("�����ƽ��ϴ�!\n");
				stress += 10;
				turnon = 0;  // ���� while ���� Ż��
				break;


			}

			//�� ü�� �����ϸ� ������
			if (battle_enemyhealth > 0)
			{
				health -= battle_enemyattack;
				printf("���� ����� �����߽��ϴ�! ü���� %d �����߽��ϴ�.\n", battle_enemyattack);


				if (Percent(30)) // ����ų�� 30�ۼ�Ʈ�� ��ų ����
				{
					health = AttackAddHealth2(battle_enemyhealth, battle_enemyattack, health);
				}
				if (health <= 0)
				{
					printf("�ٸ���ġ�� ���������ϴ�!\n");
					turnon = 0;
					gameon = 0;  // ���� ����
				}
			}
		}
	}
	else
	{
		if (stress <= 0)
		{
			stress = 0;
			printf("���̻� ��Ʈ���� ������ ���� �� �����ϴ�.\n");
		}
		else
		{
			stress -= 20;
			printf("��Ʈ������ ��å���� ���� %d �پ����ϴ�.\n", 20);
		}
	}
}

void SwitchSelect5(int num1) 
{
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
			scanf_s("%d", &num1);

			switch (num1)
			{
			case 1: // ����
				battle_enemyhealth -= gochiattack;
				printf("������ %d ��ŭ ���ظ� ����ϴ�!\n", gochiattack);

				if (battle_enemyhealth <= 0)
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // while �� �� while �� Ż���ϰ� �Ϲ� while������ ��
					exp += 50;
					printf("����ġ�� %d ������ϴ�!\n", 20);
					rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}
				break;

			case 2: // ��ų
				printf("�ٸ���ġ�� ��ų�� ����߽��ϴ�!.\n");
				if (mana < 50)
				{
					printf("������ ���� ��ų�� ������� ���մϴ�.!.\n");
				}
				else
				{

					battle_enemyhealth = AttackAddHealth1(health, gochiattack, battle_enemyhealth);
					//�� �ʱ�ȭ ������� �� ü�� ���δ�, �̰� ���� �߿���!!

				}
				if (battle_enemyhealth <= 0)
				{
					printf("���� ����߽��ϴ�!!.\n");
					turnon = 0;  // ���� while ���� Ż��
					exp += 50;   // ����ġ ȹ��
					printf("����ġ�� %d ������ϴ�!\n", 30);
					rewardgold += 200;
					printf("��带 %d ������ϴ�!\n", 200);
					stress -= 10;
					printf("��Ʈ�������� %d ��ŭ ���������ϴ�\n", 10);
				}



				break;

			case 3: // ����
				printf("�����ƽ��ϴ�!\n");
				stress += 10;
				turnon = 0;  // while �� Ż���Ѵ�. ���� 0���� �� �ʱ�ȭ �����ָ� ���� ���ϰ� ��� �����
				break;


			}

			// �� ü���� �����ϸ� ������
			if (battle_enemyhealth > 0)
			{
				health -= battle_enemyattack;
				printf("���� ����� �����߽��ϴ�! ü���� %d �����߽��ϴ�.\n", battle_enemyattack);

				if (Percent(30)) // ����ų�� 30�ۼ�Ʈ�� ��ų ����
				{
					health = AttackAddHealth2(battle_enemyhealth, battle_enemyattack, health);
				}
				if (health <= 0)
				{
					printf("�ٸ���ġ�� ���������ϴ�!\n");
					turnon = 0;
					gameon = 0;  // ���� ����
				}
				if (health <= 0)
				{
					printf("�ٸ���ġ�� ���������ϴ�!\n");
					turnon = 0;
					gameon = 0;  // ���� ����
				}
			}
		}
	}
	else
	{
		if (stress <= 0)
		{
			stress = 0;
			printf("���̻� ��Ʈ���� ������ ���� �� �����ϴ�.\n");
		}
		else
		{
			stress -= 30;
			printf("��Ʈ������ �ͱ�Ȱ������ ���� %d �پ����ϴ�.\n", 30);
		}
	}
}





void SwitchSelect6(int num1) 
{
	switch (num1)
	{
	case 6: // ���� �ý���
		if (rewardgold < 200)
		{
			printf("���� ���� �̿��� �� �����ϴ�!!\n");
			break;
		}
		else
		{
			ShowShop();
			//�б⹮ �ȿ� �б⹮ ���� �� �ִ�, �Է� ���� ���� num2�� ������� ������ �׷� �ʿ� ���� num1�� ��, �Է¹޴°� �ǹ̰� ���� �ϳ��� ����ϴ�.
			scanf_s("%d", &num1);
			switch (num1)
			{
			case 1:
				rewardgold -= 200;
				Maxhealth += 100;

				printf("�ִ�ü���� %d �����Ͽ� %d�� �Ǿ����ϴ�.", 100, Maxhealth);
				break;

			case 2:
				rewardgold -= 300;
				gochiattack += 50;
				printf("���ݷ��� %d �����Ͽ� %d�� �Ǿ����ϴ�.", 50, gochiattack);
				break;


			case 3:
				rewardgold -= 400;
				currentlevel += 1;
				printf("������ %d �����Ͽ� %d�� �Ǿ����ϴ�.", 1, currentlevel);
				break;
			}
		}
		break;
	}
}
void SwitchSelect7(int num1) 
{
	switch(num1)
	{
		case 7:
			ShowGuide();
			break;
	}
}




//�Լ� ���ǵ� > �Լ� ���� �κа� �Լ� �̸��� �� ������ߵ� , �׸��� ���ϰ��� �ݵ�� 1����
int AttackAddHealth2(int num1, int num2, int num3)
{
	int totalDamage = num1 + num2;
	printf("���� ü�°� ���ݷ��� ��ģ ��ų(�Ѱ��ݷ�:%d)�� ����߽��ϴ�!\n", totalDamage);
	printf("�ٸ���ġ���� %d�� ���ظ� �������ϴ�!\n", totalDamage);
	return num3 - totalDamage;
}

int AttackAddHealth1(int num1, int num2, int num3)
{
	int totalDamage = num1 + num2;
	printf("�ٸ���ġ�� ü�°� ���ݷ��� ��ģ ��ų(�Ѱ��ݷ�:%d)�� ����߽��ϴ�!\n", totalDamage);
	printf("������ %d�� ���ظ� �������ϴ�!\n", totalDamage);
	return num3 - totalDamage;

}
int Percent(int num1) // Ȯ�������� ������ִ� �Լ�
{	
	return (rand() % 100) < num1; // 0����99���� �����ϰ� �����µ� < 70�� 0~69���� ��ȯ�� -> ���� ��ü�� ��ȯ�ȴ�.
								//0�� 1�� �Ǵ� -> ������ ���̸� ����Ǵ°Ŵ�!
}
void ShowStatus(int num1, int num2, int num3, int num4, int num5, int num6, int num7) 
{	
	printf("===================================================\n");
	printf("����â\n");
	printf("ü��: %d\n", num1);
	printf("����: %d\n", num2);
	printf("������: %d\n", num3);
	printf("ȭ���: %d\n", num4);
	printf("��Ʈ����: %d\n", num5);
	printf("����ġ: %d\n", num6);
	printf("������: %d\n", num7);
	printf("===================================================\n");
}
void ShowChoice()
{
	printf("\n=======================================================================================\n");
	printf("1.���ڱ� 2.�����ϱ� 3.���ֱ� 4.��å�ϱ� 5.�ͱ׳��� 6.���� 7.�ٸ���ġ ���̵����\n");
	printf("=======================================================================================\n");
	printf("�Է�: ");

}
void ShowBattle(int num1, int num2, int num3) 
{
	printf("\n----- ���� -----\n");
	printf("�� ü��: %d\n", num1);
	printf("�� ü��: %d\n", num2);
	printf("�� ����: %d\n", num3);
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
void ShowGuide() 
{
	printf("�ٸ���ġ�� ��Ʈ������ 100�� ��ų� �躯������ 100�� ��� ��� �׸��� ���� �� ü���� �������� ����մϴ�.\n");
	printf("�ٸ���ġ�� ������ 10�̵Ǹ� ���������ϸ� ������ Ŭ���� �˴ϴ�..\n");
	printf("�ٸ���ġ�� �Ұ����� ������ �Ҷ� ,����ĥ�� ��Ʈ������ 10�� �޽��ϴ�.\n");
	printf("�ٸ���ġ�� ���� �ڰų�, ���� �����߸� ��� ��Ʈ������ ȸ���մϴ� .\n");
}


int main(void)
{

	// rand() �ʱ�ȭ�� �� ����!
	srand((unsigned int)time(NULL)); // ������ ���� �ʿ����, ���α׷� ����� �ѹ��� �ʱ�ȭ ���൵��
	while (gameon) // �ݺ��� ����
	{
		//������ ����
		if (exp >= 100 * currentlevel * 1.2)
		{
			currentlevel++;
			exp = 0;
			gochiattack += 10;
			printf("\n ���� ��! ���� ����: %d\n", currentlevel);
			printf("���ݷ��� %d�� �����߽��ϴ�!\n", gochiattack);
		}
		//�躯������ 100�� �޼� �� ���ӿ��� ����
		if (poo >= 100 || stress >= 100)
		{
			printf("�ٸ���ġ�� ���� �ɷȽ��ϴ�.\n");
			printf("������ ����Ǿ����ϴ�.\n");
			break;
		}
		//�¸� ���Ǵ޾��ֱ�
		if (currentlevel == 10)
		{
			printf("�ٸ���ġ�� ������ �����߽��ϴ�!!\n");
			printf("������ ����Ǿ����ϴ�.\n");
			break;
		}
		// �ٸ���ġ�� ü��,������,�躯Ȱ������ �� ���ߵȴ�
		ShowStatus(health, mana, hungry, poo, stress, exp, rewardgold);
		ShowChoice();
		// �Է��ش޶�� �ȳ� �޽����� ���

		//1~6�� ���ڸ� �Է��� �� �ְ� �Է��� �޴´�
		scanf_s("%d", &num1);
		SwitchSelect1to3(num1); // 1~3�� �����ϴϱ� switch �б⹮���� �Լ��� ����� ���.
		switch (num1)
		{
		case 4: // ��å�ϱ�
			SwitchSelect4(num1);
			break;
		case 5: // �ͱ׳���
			SwitchSelect5(num1);
			break;
		case 6:
			SwitchSelect6(num1); // �׳� ���ָ� �Է¸� ������ ������ ��ɾȸ��� -> case 6 �� break�� ��������ߵ�
			break;
		case 7:
			SwitchSelect7(num1); // �׳� ���ָ� �Է¸� ������ ������ ��ɾȸ��� -> case 6 �� break�� ��������ߵ�
			break;
		}
	}

}
		


	
