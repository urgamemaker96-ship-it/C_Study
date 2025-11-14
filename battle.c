#include "show.h"
#include "util.h"
#include "battle.h"
#include "Struct.h"
#include <stdio.h>
#include< string.h >

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
				int skillDamage = 0; // 스킬함수에서 호출된 스킬 데미지 값을 받아주는 변수

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
	damaskill* skill = &type->skill_isanghaessi;

	if (type->mana < skill->mana_cost) {
		printf("마나가 부족해서 스킬을 사용할 수 없습니다! (현재 %d, 필요 %d)\n",
			type->mana, skill->mana_cost);
		return 0; // return 0 해주는 이유 마나 없으면 바로 함수종료함 , 만약 0처리 안해주면 계속 마나 깎임
	}

	type->mana -= skill->mana_cost; // 기본 설정값은 마나에서 구조체 스킬에서 불러온 마나 코스트를 깎는것이다.

	// 스킬 레벨에 따른 데미지 계산 (레벨당 20% 증가) + 특성(공격력,최대체력,마나)에 맞게 또 1.2 증가
	float level_bonus = 1.0f + ((skill->level - 1) * 0.2f);
	int damage = (int)((type->specialattack * level_bonus) + // 레벨업시 공격력 1.2배 증가 + 특성에 맞게 1.2 배증가
		(type->Maxhealth * skill->bonus_ratio));//bounus_ratio 변수는 float 형이라서 int 형으로 강제변환

	printf("%s의 %s! %d 데미지! (스킬Lv.%d), 마나 %d를 사용했습니다!\n", // 구조체에서 불러온 다마고치가 스킬 구조체에서 불러온 스킬명을 가지고 데미지 출력 및 마나코스트 출력
		type->damaname, skill->name, damage, skill->level, skill->mana_cost);
	return damage;
}

int Skill_paili(damagochi* type)
{
	damaskill* skill = &type->skill_paili;

	if (type->mana < skill->mana_cost) {
		printf("마나가 부족해서 스킬을 사용할 수 없습니다! (현재 %d, 필요 %d)\n",
			type->mana, skill->mana_cost);
		return 0;// return 0 해주는 이유 마나 없으면 바로 함수종료함 , 만약 0처리 안해주면 계속 마나 깎임
	}

	type->mana -= skill->mana_cost;// 기본 설정값은 마나에서 구조체 스킬에서 불러온 마나 코스트를 깎는것이다.
	
	// 스킬 레벨에 따른 데미지 계산 (레벨당 20% 증가) + 특성(공격력,최대체력,마나)에 맞게 또 1.2 증가
	float level_bonus = 1.0f + ((skill->level - 1) * 0.2f);
	int damage = (int)((type->specialattack * level_bonus) +// 레벨업시 공격력 1.2배 증가 + 특성에 맞게 1.2 배증가
		(type->gochiattack * skill->bonus_ratio)); //bounus_ratio 변수는 float 형이라서 int 형으로 강제변환

	printf("%s의 %s! %d 데미지! (스킬Lv.%d), 마나 %d를 사용했습니다!\n",// 구조체에서 불러온 다마고치가 스킬 구조체에서 불러온 스킬명을 가지고 데미지 출력 및 마나코스트 출력
		type->damaname, skill->name, damage, skill->level, skill->mana_cost);

	return damage;
}

int Skill_kkobugi(damagochi* type)
{
	damaskill* skill = &type->skill_kkobugi;

	if (type->mana < skill->mana_cost) {
		printf("마나가 부족해서 스킬을 사용할 수 없습니다! (현재 %d, 필요 %d)\n",
			type->mana, skill->mana_cost);
		return 0;// return 0 해주는 이유 마나 없으면 바로 함수종료함 , 만약 0처리 안해주면 계속 마나 깎임
	}

	type->mana -= skill->mana_cost;// 기본 설정값은 마나에서 구조체 스킬에서 불러온 마나 코스트를 깎는것이다.
	
	// 스킬 레벨에 따른 데미지 계산 (레벨당 20% 증가) + 특성(공격력,최대체력,마나)에 맞게 또 1.2 증가
	float level_bonus = 1.0f + ((skill->level - 1) * 0.2f);
	int damage = (int)((type->specialattack * level_bonus) +// 레벨업시 공격력 1.2배 증가 + 특성에 맞게 1.2 배증가
		(type->mana * skill->bonus_ratio));//bounus_ratio 변수는 float 형이라서 int 형으로 강제변환

	printf("%s의 %s! %d 데미지! (스킬Lv.%d), 마나 %d를 사용했습니다!\n",// 구조체에서 불러온 다마고치가 스킬 구조체에서 불러온 스킬명을 가지고 데미지 출력 및 마나코스트 출력
		type->damaname, skill->name, damage, skill->level, skill->mana_cost);

	return damage;
}