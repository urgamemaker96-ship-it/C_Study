#include "show.h"
#include "util.h"
#include "battle.h"
#include "Struct.h"
#include <stdio.h>


void Battle(damagochi* selected, int* rewardgold, char* enemyname)
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
			selected->health <= 0 ||
			userInput == 3)
			return;

		ShowBattle(battle_enemyhealth, selected);
		scanf_s("%d", &userInput);

		switch (userInput)
		{
		case 1: // 공격
			TakeDamage(selected->gochiattack, &battle_enemyhealth);
			printf("%s에게 %d 만큼 피해를 줬습니다!\n", enemyname, selected->gochiattack);

			if (battle_enemyhealth <= 0)
			{
				printf("%s이 사망했습니다!!.\n", enemyname);
				selected->exp += 50;
				printf("경험치를 %d 얻었습니다!\n", 50);
				*rewardgold += 200;
				printf("골드를 %d 얻었습니다!\n", 200);
				selected->stress = GetSubstractResultOrZero(selected->stress, 10);
				printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
			}
			break;

		case 2: // 스킬
			printf("%s가 스킬을 사용했습니다!.\n", selected->damaname);
			if (selected->mana < 50)
			{
				printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");
			}
			else
			{
				int skillDamage = 0;

				// 다마고치 이름에 따라 스킬 함수 호출 -> strcmp 이라고 문자열 비교해주는 함수 있어서 그걸로 처리함
				if (strcmp(selected->damaname, "이상해씨") == 0)
				{
					skillDamage = Skill_Isanghaessi(selected);
				}
				else if (strcmp(selected->damaname, "파이리") == 0)
				{
					skillDamage = Skill_paili(selected);
				}
				else if (strcmp(selected->damaname, "꼬북이") == 0)
				{
					skillDamage = Skill_kkobugi(selected);
				}
			
				TakeDamage(skillDamage, &battle_enemyhealth);
				ShowDamage(selected->damaname, enemyname, skillDamage);
				//값 초기화 해줘야지 적 체력 깎인다, 이거 제일 중요함!!

			}
			if (battle_enemyhealth <= 0)
			{
				printf("%s이 사망했습니다!!.\n", enemyname);
				selected->exp += 50;   // 경험치 획득
				printf("경험치를 %d 얻었습니다!\n", 50);
				*rewardgold += 200;
				printf("골드를 %d 얻었습니다!\n", 200);
				selected->stress = GetSubstractResultOrZero(selected->stress, 10);
				printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
			}
			break;

		case 3: // 도망
			printf("도망쳤습니다!\n");
			selected->stress += 10;
			break;
		}

		// 적 체력이 존재하면 공격함
		if (battle_enemyhealth > 0)
		{
			selected->health = GetSubstractResultOrZero(selected->health, battle_enemyattack);
			printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", enemyname, battle_enemyattack);

			if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
			{
				int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
				TakeDamage(totalEnemyDagame, &selected->health);
				ShowDamage(enemyname, selected->damaname, totalEnemyDagame);
			}
			
			if (selected->health <= 0)
			{
				printf("%s가 쓰러졌습니다!\n", selected->damaname);
			}
		}
	}
}
int Skill_Isanghaessi(damagochi* type)
{	
	if (type->mana < 50) {
		printf("마나가 부족해서 스킬을 사용할 수 없습니다! (현재 %d)\n", type->mana);
		return 0; // 리턴 꼭 해줘야된다, 안해주면 마나 -단위됨, 이 조건 맞으면 출력만하고 해당함수 바로종료
	}
	type->mana -= 50;
	int damage = (type->specialattack * 2) + (type->Maxhealth* 0.2); // 스킬데미지 최대체력 비례공력추가
	printf("이상해씨의 덩굴채찍! %d 데미지! ,마나 %d를 사용했습니다!\n", damage, type->mana);
	return damage;
}

int Skill_paili(damagochi* type)
{
	if (type->mana < 50) {
		printf("마나가 부족해서 스킬을 사용할 수 없습니다! (현재 %d)\n", type->mana);
		return 0; // 리턴 꼭 해줘야된다, 안해주면 마나 -단위됨, 이 조건 맞으면 출력만하고 해당함수 바로종료
	}
	type->mana -= 50;
	int damage = (type->specialattack * 2) + (type->gochiattack * 0.2); //스킬데미지 공격력 비례공력추가
	printf("파이리의 화염방사! %d 데미지! ,마나 %d를 사용했습니다!\n", damage, type->mana);
	
	return damage;
}

int Skill_kkobugi(damagochi* type)
{
	if (type->mana < 50) {
		printf("마나가 부족해서 스킬을 사용할 수 없습니다!(현재 %d)\n", type->mana);
		return 0; // 리턴 꼭 해줘야된다, 안해주면 마나 -단위됨, 이 조건 맞으면 출력만하고 해당함수 바로종료
	}
	type->mana -= 50;
	int damage = (type->specialattack * 2) +((type->mana * 0.2));//스킬데미지 마나 비례공력추가
	printf("꼬북이의 물대포! %d 데미지! ,마나 %d를 사용했습니다!\n", damage, type->mana);

	return damage;

}