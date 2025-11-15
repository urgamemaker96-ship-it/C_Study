#include "show.h"
#include "util.h"
#include "battle.h"
#include "Struct.h"
#include <stdio.h>
#include< string.h >
#include <stdlib.h> // 랜덤함수 헤더

void Battle(damagochi* player, damagochi* enemy, int* rewardgold, capture* collection)
{
    // 전투 시작 메시지
    printf("===================================================\n");
    printf("%s이(가) 나타났습니다!!\n", enemy->damaname);

    int userInput = 0;
    int enemyUsedSkill = 0; // 적이 스킬 사용 여부

    while (1)
    {

        if (enemy->health <= 0 ||
            player->health <= 0 ||
            userInput == 3)
            break;

        ShowBattle(enemy->health, player);
        scanf_s("%d", &userInput);

        switch (userInput)
        {
        case 1: // 공격
            TakeDamage(player->gochiattack, &enemy->health);
            printf("%s에게 %d 만큼 피해를 줬습니다!\n", enemy->damaname, player->gochiattack);

            if (enemy->health <= 0)
            {
                printf("%s이 사망했습니다!!.\n", enemy->damaname);
                player->exp += 50;
                printf("경험치를 %d 얻었습니다!\n", 50);
                *rewardgold += 200;
                printf("골드를 %d 얻었습니다!\n", 200);
                player->stress = GetSubstractResultOrZero(player->stress, 10);
                printf("스트레스가 %d 만큼 떨어졌습니다\n", 10);
            }
            break;

        case 2: // 스킬
            printf("%s가 스킬을 사용했습니다!.\n", player->damaname);
            if (player->mana < 50)
            {
                printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");
            }
            else
            {
                int skillDamage = 0;

                if (strcmp(player->damaname, "이상해씨") == 0)
                {
                    skillDamage = Skill_Isanghaessi(player);
                }
                else if (strcmp(player->damaname, "파이리") == 0)
                {
                    skillDamage = Skill_paili(player);
                }
                else if (strcmp(player->damaname, "꼬부기") == 0)
                {
                    skillDamage = Skill_kkobugi(player);
                }

                TakeDamage(skillDamage, &enemy->health);
                ShowDamage(player->damaname, enemy->damaname, skillDamage);
            }
            if (enemy->health <= 0)
            {
                printf("%s이 사망했습니다!!.\n", enemy->damaname);
                player->exp += 50;
                printf("경험치를 %d 얻었습니다!\n", 50);
                *rewardgold += 200;
                printf("골드를 %d 얻었습니다!\n", 200);
                player->stress = GetSubstractResultOrZero(player->stress, 10);
                printf("스트레스가 %d 만큼 떨어짐\n", 10);
            }
            break;

        case 3: // 도망
            printf("도망쳤습니다!\n");
            player->stress += 10;
            break;

        case 4: // 포획 시도
            if (enemy->health > enemy->Maxhealth * 0.3)
            {
                printf("적의 체력이 너무 높아 포획할 수 없습니다!\n");
                printf("체력을 30%% 이하로 떨어뜨리세요. (현재: %.1f%%)\n", (float)enemy->health / enemy->Maxhealth * 100);// 소숫점 1자리까지 나타냈음,퍼센트 출력문법 보고 따라함
            }
            else
            {
                printf("포획을 시도합니다...\n");
                if (ProcessCapture(enemy, player, true))
                {
                    // 포획 성공 시 새로운 다마고치 생성 - 이름 변경 없이 원래 이름 사용
                    damagochi* captured = CreateCapturedDamagochi(enemy, enemy->damaname);
                    if (captured != NULL) {
                        AddToCaptureCollection(collection, captured);
                        printf("포획 성공! 새로운 동료가 되었습니다: %s\n", captured->damaname);
                        printf("포획 관리 메뉴(11번)에서 교체할 수 있습니다.\n");
                    }
                    return; // 전투 종료
                }
                else {
                    printf("포획에 실패했습니다! 적이 저항했습니다.\n");
                }
            }
            break;
        }
            // 적 체력이 존재하면 공격함 -> 스위치문 밖 while 문에서 판단하고 공격함
            if (enemy->health > 0)
            {
                // 적이 스킬을 사용할지 결정 (30% 확률)
                enemyUsedSkill = 0;
                if (Percent(30) && enemy->mana >= 50) //적마나 50이상일때만
                {
                    // 적이 스킬 사용
                    int enemySkillDamage = 0;

                    if (strcmp(enemy->damaname, "야생 이상해씨") == 0 )
                    {
                        enemySkillDamage = Skill_Isanghaessi(enemy);
                    }
                    else if (strcmp(enemy->damaname, "야생 파이리"))
                    {
                        enemySkillDamage = Skill_paili(enemy);
                    }
                    else if (strcmp(enemy->damaname, "야생 꼬부기"))
                    {
                        enemySkillDamage = Skill_kkobugi(enemy);
                    }

                    if (enemySkillDamage > 0) {
                        TakeDamage(enemySkillDamage, &player->health);
                        ShowDamage(enemy->damaname, player->damaname, enemySkillDamage);
                        enemyUsedSkill = 1;
                    }
                }

                // 적이 스킬을 사용하지 않았으면 일반 공격
                if (!enemyUsedSkill) {
                    player->health = GetSubstractResultOrZero(player->health, enemy->gochiattack);
                    printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", enemy->damaname, enemy->gochiattack);
                }

                if (player->health <= 0)
                {
                    printf("%s가 쓰러졌습니다!\n", player->damaname);
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

    // 이름 비교 로직 수정 -> 적 야생 이상해씨도 스킬 써야하니깐 strstr 함수 이용해서 이상해씨라는 이름만 포함하면 스킬사용하게함
    if (strstr(type->damaname, "이상해씨") != NULL) {
        printf("%s의 %s! %d 데미지! (스킬Lv.%d), 마나 %d를 사용했습니다!\n",
            type->damaname, skill->name, damage, skill->level, skill->mana_cost);
    }
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

    // 이름 비교 로직 수정 -> 적 야생 파이리도 스킬 써야하니깐 strstr 함수 이용해서 파이리라는 이름만 포함하면 스킬사용하게함
    if (strstr(type->damaname, "파이리") != NULL) {
        printf("%s의 %s! %d 데미지! (스킬Lv.%d), 마나 %d를 사용했습니다!\n",
            type->damaname, skill->name, damage, skill->level, skill->mana_cost);
    }

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

    // 이름 비교 로직 수정 -> 적 야생 꼬부기도 스킬 써야하니깐 strstr 함수 이용해서 꼬부기라는 이름만 포함하면 스킬사용하게함
    if (strstr(type->damaname, "꼬부기") != NULL) {
        printf("%s의 %s! %d 데미지! (스킬Lv.%d), 마나 %d를 사용했습니다!\n",
            type->damaname, skill->name, damage, skill->level, skill->mana_cost);
    }
	return damage;
}

