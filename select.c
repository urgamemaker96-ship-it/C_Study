#include "select.h"
#include "show.h"
#include "util.h"
#include "battle.h"
#include <stdio.h>


void SelectSleep(int* health, int* Maxhealth, int* stress, int* mana, char* damaname)
{
	int gap = 0;
	// 잠을 자면 체력 또는 마나가 증가한다.
	// 근데 체력과 마나가 둘 다 최대면 
	// 스트레스만 준다.
	if (*health >= *Maxhealth && *mana >= 100)
	{
		printf("더이상 잘 필요가 없습니다.\n");
		*stress += 10;
		return;
	}

	if (*health < *Maxhealth)
	{
		gap = GetAddResultOrZero(*Maxhealth, -(*health), 10);

		*health = GetAddResultOrZero(*health, 10, *Maxhealth);
		printf("%s의 체력이 %d 증가했습니다\n", damaname, gap);
	}

	if (*mana < 100)
	{
		gap = GetAddResultOrZero(100, -(*mana), 10);
		*mana = GetAddResultOrZero(*mana, 10, 100);
		printf("%s의 마나가 %d 증가했습니다\n", damaname, gap);
	}
}

void SelectPoop(int* poo, char* damaname)
{
	*poo = 0;
	printf("%s의 배변활동지수가 %d 되었습니다\n", damaname, *poo);
}

void SelectEat(int* hungry, int* poo, char* damaname)
{
	if (*hungry >= 200)
	{
		printf("더이상 먹을 필요가 없습니다.\n");
	}
	else
	{
		*hungry += 20;
		*poo += 20;
		printf("%s의 포만감이 %d 증가했습니다\n", damaname, 20);
	}
}

void SelectWalk(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress, char* damaname, char* enemyname)
{
	if (Percent(50))
	{
		Battle(health, mana, gochiattack, exp, rewardgold, stress, damaname, enemyname);
	}
	else
	{
		if (*stress <= 0)
		{
			*stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			*stress = GetSubstractResultOrZero(*stress, 30);
			printf("스트레스가 산책활동으로 인해 %d 줄었습니다.\n", 30);
		}
	}
}

void SelectTug(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress, char* damaname, char* enemyname)
{
	if (Percent(60))
	{
		Battle(health, mana, gochiattack, exp, rewardgold, stress, damaname, enemyname);
	}
	else
	{
		if (*stress <= 0)
		{
			*stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			*stress = GetSubstractResultOrZero(*stress, 30);
			printf("스트레스가 터그활동으로 인해 %d 줄었습니다.\n", 30);
		}
	}
}

void SelectShop(int* rewardgold, int* Maxhealth, int* gochiattack, int* currentlevel)
{
	int userInput;

	if (*rewardgold < 200)
	{
		printf("돈이 없어 이용할 수 없습니다!!\n");

	}
	else
	{
		ShowShop();
		//분기문 안에 분기문 만들 수 있다, 입력 받을 변수 num2로 만드려고 했으나 그럴 필요 없어 num1만 씀, 입력받는건 의미가 없다 하나면 충분하다.
		scanf_s("%d", &userInput);
		switch (userInput)
		{
		case 1:
			*rewardgold -= 200;
			*Maxhealth += 100;

			printf("최대체력이 %d 증가하여 %d이 되었습니다.", 100, *Maxhealth);
			break;

		case 2:
			*rewardgold -= 300;
			*gochiattack += 50;
			printf("공격력이 %d 증가하여 %d이 되었습니다.", 50, *gochiattack);
			break;


		case 3:
			*rewardgold -= 400;
			*currentlevel += 1;
			printf("레벨이 %d 증가하여 %d이 되었습니다.", 1, *currentlevel);
			break;
		}
	}


}

void SelectGuide(char* damaname)
{
	printf("%s는 스트레스가 100을 찍거나 배변지수가 100일 경우 사망 그리고 전투 시 체력이 떨어지면 사망합니다.\n", damaname);
	printf("%s는 레벨이 10이되면 최종성장하며 게임이 클리어 됩니다..\n", damaname);
	printf("%s는 불가능한 선택을 할때 ,도망칠때 스트레스를 10씩 받습니다.\n", damaname);
	printf("%s는 잠을 자거나, 적을 쓰러뜨릴 경우 스트레스를 회복합니다 .\n", damaname);
}