#include "select.h"
#include "show.h"
#include "util.h"
#include "battle.h"
#include <stdio.h>
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

void SelectSleep(damagochi* selected)
{
	int gap = 0;
	// 잠을 자면 체력 또는 마나가 증가한다.
	// 근데 체력과 마나가 둘 다 최대면 
	// 스트레스만 준다.
	if (selected->health >= selected->Maxhealth && selected->mana >= 100)
	{
		printf("더이상 잘 필요가 없습니다.\n");
		selected->stress += 10;
		return;
	}

	if (selected->health < selected->Maxhealth)
	{
		gap = GetAddResultOrZero(selected->Maxhealth, -(selected->health), 10);

		selected->health = GetAddResultOrZero(selected->health, 10, selected->Maxhealth);
		printf("%s의 체력이 %d 증가했습니다\n", selected->damaname, gap);
	}

	if (selected->mana < 100)
	{
		gap = GetAddResultOrZero(100, -(selected->mana), 10);
		selected->mana = GetAddResultOrZero(selected->mana, 10, 100);
		printf("%s의 마나가 %d 증가했습니다\n", selected->damaname, gap);
	}
}

void SelectPoop(damagochi* selected)
{
	selected->poo = 0;
	printf("%s의 배변활동지수가 %d 되었습니다\n", selected->damaname, selected->poo);
}

void SelectEat(damagochi* selected)
{
	if (selected->hungry >= 200)
	{
		printf("더이상 먹을 필요가 없습니다.\n");
	}
	else
	{
		selected->hungry += 20;
		selected->poo += 20;
		printf("%s의 포만감이 %d 증가했습니다\n", selected->damaname, 20);
	}
}

void SelectWalk(damagochi* selected, char* enemyname)
{
	if (Percent(50))
	{
		Battle(selected, &selected->rewardgold, enemyname);
	}
	else
	{
		if (selected->stress <= 0)
		{
			selected->stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			selected->stress = GetSubstractResultOrZero(selected->stress, 30);
			printf("스트레스가 산책활동으로 인해 %d 줄었습니다.\n", 30);
		}
	}
}

void SelectTug(damagochi* selected, char* enemyname)
{
	if (Percent(60))
	{
		Battle(selected, &selected->rewardgold, enemyname);
	}
	else
	{
		if (selected->stress <= 0)
		{
			selected->stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			selected->stress = GetSubstractResultOrZero(selected->stress, 30);
			printf("스트레스가 터그활동으로 인해 %d 줄었습니다.\n", 30);
		}
	}
}

void SelectShop(damagochi* selected)
{
	int userInput;

	if (selected->rewardgold < 200)
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
			selected->rewardgold -= 200;
			selected->Maxhealth += 100;

			printf("최대체력이 %d 증가하여 %d이 되었습니다.", 100, selected->Maxhealth);
			break;

		case 2:
			selected->rewardgold -= 300;
			selected->gochiattack += 50;
			printf("공격력이 %d 증가하여 %d이 되었습니다.", 50, selected->gochiattack);
			break;


		case 3:
			if (selected->rewardgold >= 400) // 다마고치가 가지고 있는 돈이 크면
			{
				selected->rewardgold -= 400; // 400골드 소모

				//레벨업 처리
				LevelUpRule(selected,true);// 어떤 다마고치 타입의 레벨업인지 설정해줌 -> 다마고치 레벨 조건대로 레벨스텟 조정됨	
				
				printf("레벨 업 아이템을 사용했습니다!\n");
			}
			else
			{
				printf("골드가 부족합니다!\n");
			}
			break;
		}
	}


}

void SelectGuide(damagochi* selected)
{
	printf("%s는 스트레스가 100을 찍거나 배변지수가 100일 경우 사망 그리고 전투 시 체력이 떨어지면 사망합니다.\n", selected->damaname);
	printf("%s는 레벨이 10이되면 최종성장하며 게임이 클리어 됩니다..\n", selected->damaname);
	printf("%s는 불가능한 선택을 할때 ,도망칠때 스트레스를 10씩 받습니다.\n", selected->damaname);
	printf("%s는 잠을 자거나, 적을 쓰러뜨릴 경우 스트레스를 회복합니다 .\n", selected->damaname);
}