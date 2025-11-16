#include "select.h"
#include "game_status.h"
#include "show.h"
#include "util.h"
#include "battle.h"
#include <stdio.h>
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨
#include <string.h>

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

void SelectWalk(damagochi* selected, damagochi* enemy,capture* collection)
{
	if (Percent(50))
	{
		Battle(selected, enemy, &selected->rewardgold, collection);
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

void SelectTug(damagochi* selected, damagochi* enemy,capture* collection)
{
	if (Percent(60))
	{
		Battle(selected, enemy, &selected->rewardgold, collection);
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

				//강제레벨업 처리 -> 기본값은 false 이다 , 강제레벨업 함수를 또 만들어 주는것보단 bool 타입으로 처리하는게 효율적이다
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

// 스킬업그레이드 선택 함수
void UpgradeSkill(damagochi* type) 
{
	if (type->skillpoint == 0) { // 구조체에서 가져온 스킬포인트가 0이면
		printf("스킬 포인트가 부족합니다!\n");
		return; // 스킬포인트 없으면 바로 함수 종료
	}

	printf("\n=== 스킬 강화 ===\n");
	printf("보유한 스킬 포인트: %d\n", type->skillpoint);

	// 각 다마고치 타입에 따라 다른 스킬 표시
	if (strcmp(type->damaname, "이상해씨") == 0)
	{ // 이상해씨이름을 가진 구조체면
		damaskill* skill = &type->skill_isanghaessi; // 다마고치 안에 다마고치의 스킬 구조체가 있어서 그 구조체의 스킬멤버주소를 Skill 포인터 변수에 초기화시킴
		int current_damage = CountSkillDamage(type, 1,false);
		int next_damage = CountSkillDamage(type, 1, true);
		skill->mana_cost += 10; //스킬 업 할때마다 마나코스트 10씩 증가

		printf("1. %s (Lv.%d → Lv.%d)\n", skill->name, skill->level, skill->level + 1);
		printf("   현재 데미지: %d → 다음 레벨 데미지: %d (+%d)\n",
			current_damage, next_damage, next_damage - current_damage);
	}
	else if (strcmp(type->damaname, "파이리") == 0)
	{
		damaskill* skill = &type->skill_paili;
		int current_damage = CountSkillDamage(type, 2, false);
		int next_damage = CountSkillDamage(type, 2, true);
		skill->mana_cost += 10; //스킬 업 할때마다 마나코스트 10씩 증가

		printf("1. %s (Lv.%d → Lv.%d)\n", skill->name, skill->level, skill->level + 1);
		printf("   현재 데미지: %d → 다음 레벨 데미지: %d (+%d)\n",
			current_damage, next_damage, next_damage - current_damage);
	}
	else if (strcmp(type->damaname, "꼬북이") == 0)
	{
		damaskill* skill = &type->skill_kkobugi;
		int current_damage = CountSkillDamage(type, 3, false);
		int next_damage = CountSkillDamage(type, 3, true);
		skill->mana_cost += 10; //스킬 업 할때마다 마나코스트 10씩 증가

		printf("1. %s (Lv.%d → Lv.%d)\n", skill->name, skill->level, skill->level + 1);
		printf("   현재 데미지: %d → 다음 레벨 데미지: %d (+%d)\n",
			current_damage, next_damage, next_damage - current_damage);
	}

	printf("0. 취소\n");
	printf("강화할 스킬을 선택하세요: ");

	int choice;
	scanf_s("%d", &choice);

	if (choice == 0)
	{
		printf("강화를 취소했습니다.\n");
		return;
	}

	if (choice == 1)
	{
		// 해당 다마고치의 스킬 강화
		if (strcmp(type->damaname, "이상해씨") == 0)
		{
			type->skill_isanghaessi.level++;
			type->skillpoint--;
			printf("%s가 Lv.%d로 강화되었습니다! 데미지가 증가합니다.\n",
				type->skill_isanghaessi.name, type->skill_isanghaessi.level); // 스킬이름 표시해주고 레벨도 증가
		}
		else if (strcmp(type->damaname, "파이리") == 0)
		{
			type->skill_paili.level++;
			type->skillpoint--;
			printf("%s가 Lv.%d로 강화되었습니다! 데미지가 증가합니다.\n",
				type->skill_paili.name, type->skill_paili.level);// 스킬이름 표시해주고 레벨도 증가
		}
		else if (strcmp(type->damaname, "꼬북이") == 0)
		{
			type->skill_kkobugi.level++;
			type->skillpoint--;
			printf("%s가 Lv.%d로 강화되었습니다! 데미지가 증가합니다.\n",
				type->skill_kkobugi.name, type->skill_kkobugi.level);// 스킬이름 표시해주고 레벨도 증가
		}
	}

}