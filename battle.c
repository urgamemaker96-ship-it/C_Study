#include "show.h"
#include "util.h"
#include "battle.h"

#include <stdio.h>


void Battle(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress, char* damaname, char* enemyname)
{
	printf("===================================================\n");
	printf("%s이 나타났습니다!!.\n", enemyname);

	// while 문 안에 또 while 문 만들어야 전투 상태 창 만들 수 있음
	int battle_enemyhealth = 80;  // 산책과 비교해서 체력 낮다
	int battle_enemyattack = 30;   // 
	int userInput = 0;

	while (1)
	{
		if (battle_enemyhealth <= 0 ||
			*health <= 0 ||
			userInput == 3)
			return;

		ShowBattle(battle_enemyhealth, health, mana);
		scanf_s("%d", &userInput);

		switch (userInput)
		{
		case 1: // 공격
			TakeDamage(gochiattack, &battle_enemyhealth);
			printf("%s에게 %d 만큼 피해를 줬습니다!\n", enemyname, *gochiattack);

			if (battle_enemyhealth <= 0)
			{
				printf("%s이 사망했습니다!!.\n", enemyname);
				*exp += 50;
				printf("경험치를 %d 얻었습니다!\n", 50);
				*rewardgold += 200;
				printf("골드를 %d 얻었습니다!\n", 200);
				*stress = GetSubstractResultOrZero(*stress, 10);
				printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
			}
			break;

		case 2: // 스킬
			printf("%s가 스킬을 사용했습니다!.\n", damaname);
			if (*mana < 50)
			{
				printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");
			}
			else
			{

				int totalDamage = *health + *gochiattack;
				TakeDamage(&totalDamage, &battle_enemyhealth);
				ShowDamage(damaname, enemyname, totalDamage);
				//값 초기화 해줘야지 적 체력 깎인다, 이거 제일 중요함!!

			}
			if (battle_enemyhealth <= 0)
			{
				printf("%s이 사망했습니다!!.\n", enemyname);
				*exp += 50;   // 경험치 획득
				printf("경험치를 %d 얻었습니다!\n", 50);
				*rewardgold += 200;
				printf("골드를 %d 얻었습니다!\n", 200);
				*stress = GetSubstractResultOrZero(*stress, 10);
				printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
			}
			break;

		case 3: // 도망
			printf("도망쳤습니다!\n");
			*stress += 10;
			break;
		}

		// 적 체력이 존재하면 공격함
		if (battle_enemyhealth > 0)
		{
			*health = GetSubstractResultOrZero(*health, battle_enemyattack);
			printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", enemyname, battle_enemyattack);

			if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
			{
				int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
				TakeDamage(&totalEnemyDagame, health);
				ShowDamage(enemyname, damaname, totalEnemyDagame);
			}
			
			if (*health <= 0)
			{
				printf("%s가 쓰러졌습니다!\n", damaname);
			}
		}
	}
}