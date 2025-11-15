#include "util.h"
#include <string.h> //strcpy_s 사용위해서
#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

//사용자 입력처리
int UserInput()
{
	int inputNum;

	printf("입력: ");
	scanf_s("%d", &inputNum);
	return inputNum;
}
// 단순출력
void JustPrint(char* str) 
{
	printf("%s 이름을 입력 : ", str);
}


//*다마고치 구조체 정보입력 및 선택 함수들
// 다마고치 주인이름 동적할당으로 받아 값 초기화해줌
char* InputName_Malloc()
{
	char temp[64];  // 임시 버퍼 (64바이트 = 한글 약 21글자까지 처리 가능)

	// %63s: 최대 63글자만 읽음 (null 문자 공간 남기기 위해)
	// (unsigned)sizeof(temp): 버퍼 크기 전달 (버퍼 오버플로우 방지)
	scanf_s("%63s", temp, (unsigned)sizeof(temp));

	// 동적 메모리 할당: 문자열 길이 + 1(null 문자)
	// strlen(temp): 실제 입력된 문자열 길이 계산
	// +1: 문자열 끝을 나타내는 null 문자('\0') 공간
	char* name = (char*)malloc(strlen(temp) + 1);

	// 안전한 문자열 복사 함수
	// strcpy_s(대상포인터, 대상버퍼크기, 원본문자열)
	// strlen(temp) + 1: null 문자 포함한 전체 크기
	strcpy_s(name, strlen(temp) + 1, temp);

	// 입력 확인 메시지 출력
	printf("입력하신 이름은 %s 입니다\n\n", name);

	return name;  // 동적 할당된 메모리 주소 반환 (호출한 곳에서 free() 해야함) -> 수동으로 메모리 제거해줘야됨
}
// 다마고치 선택출력함수
int SelectDamagochiType() {
	int choice; //입력받을 수 변수 선언

	printf("\n=== 다마고치 선택 ===\n");
	printf("1. 기본 다마고치\n");
	printf("2. 이상해씨 - 높은 체력\n");
	printf("3. 파이리 - 높은 공격력\n");
	printf("4. 꼬북이 - 높은 마나\n");

	scanf_s("%d", &choice); //scanf_s 써야 오류안뜸
	

	return choice;
}
// 스킬 초기화 함수
void InitializeSkills(damagochi* type, int inputnum)
{
	switch (inputnum)
	{ // 일부러 2, 3, 4 순으로 맞춰준거임 메인에서 1번은 기본 다마고치라서
	case 2: // 이상해씨
		strcpy_s(type->skill_isanghaessi.name, sizeof(type->skill_isanghaessi.name), "덩굴채찍");
		type->skill_isanghaessi.level = 1; // 구조체에서 기본스킬레벨 1로 초기화
		type->skill_isanghaessi.bonus_ratio = 0.2f; // 구조체에서 레벨업시 스킬공격력 증가 배수
		type->skill_isanghaessi.mana_cost = 50; // 구조체에서 마나코스트 가져옴 -> 이걸로 구조체 다마고치가 가진 마나를 빼줄거임
		break;
	case 3: // 파이리
		strcpy_s(type->skill_paili.name, sizeof(type->skill_isanghaessi.name), "화염방사");
		type->skill_paili.level = 1;// 구조체에서 기본스킬레벨 1로 초기화
		type->skill_paili.bonus_ratio = 0.2f;// 구조체에서 레벨업시 스킬공격력 증가 배수
		type->skill_paili.mana_cost = 50;// 구조체에서 마나코스트 가져옴 -> 이걸로 구조체 다마고치가 가진 마나를 빼줄거임
		break;
	case 4: // 꼬부기
		strcpy_s(type->skill_kkobugi.name, sizeof(type->skill_isanghaessi.name), "물대포");
		type->skill_kkobugi.level = 1;// 구조체에서 기본스킬레벨 1로 초기화
		type->skill_kkobugi.bonus_ratio = 0.2f;// 구조체에서 레벨업시 스킬공격력 증가 배수
		type->skill_kkobugi.mana_cost = 50;	 // 구조체에서 마나코스트 가져옴 -> 이걸로 구조체 다마고치가 가진 마나를 빼줄거임
		break;
	}
}
// 스킬 데미지 계산 함수 (실제 마나는 소모하지 않음) -> 스킬함수 로직 그대로 가져와서 계산만함
int CountSkillDamage(damagochi* type, int skill_type, bool Isnextlevel)
{
	switch (skill_type)
	{
	case 1: // 이상해씨 스킬
	{
		damaskill* skill = &type->skill_isanghaessi;
		// Isnextlevel에 따라 level_bonus 계산 방식 변경
		float level_bonus = 1.0f + ((skill->level - (Isnextlevel ? 0 : 1)) * 0.2f); // Isnextlevel 참이면 0 아니면 1
		return (int)((type->specialattack * level_bonus) +
			(type->Maxhealth * skill->bonus_ratio));
	}
	case 2: // 파이리 스킬
	{
		damaskill* skill = &type->skill_paili;
		float level_bonus = 1.0f + ((skill->level - (Isnextlevel ? 0 : 1)) * 0.2f); //Isnextlevel 참이면 0 아니면 1
		return (int)((type->specialattack * level_bonus) +
			(type->gochiattack * skill->bonus_ratio));
	}
	case 3: // 꼬부기 스킬
	{
		damaskill* skill = &type->skill_kkobugi;
		float level_bonus = 1.0f + ((skill->level - (Isnextlevel ? 0 : 1)) * 0.2f);//Isnextlevel 참이면 0 아니면 1
		return (int)((type->specialattack * level_bonus) +
			(type->mana * skill->bonus_ratio));
	}
	}
}
//다시 할당 해주는 거니깐 이번엔 메모리 할당크기를 좀 늘려봄 -> realloc 씀
void RenameCharacter(damagochi* selected, bool IsDamagochi)
{
	
	// 현재 이름과 새로운 이름 입력 메시지를 조건에 따라 다르게 출력
	char* currentName = IsDamagochi ? selected->damaname : selected->mastername; //IsDamagochi 다마고치 참이면 다마고치이름 거짓이면 주인이름
	char* nameType = IsDamagochi ? "다마고치" : "주인"; //IsDamagochi 다마고치 참이면 다마고치이름 거짓이면 주인이름

	printf("현재 %s 이름: %s\n", nameType, currentName);
	printf("새로운 %s 이름을 입력하세요: ", nameType);

	char temp[128];
	scanf_s("%127", temp, (unsigned)sizeof(temp));

	// realloc으로 메모리 재할당
	size_t new_size = strlen(temp) + 1; // strln() 함수 반환값이 size_t -> 이건 언사인드 int 다, 음수가없는 int
	//더블포인터인 이유는 이미 접근해서 할당처리한 구조체의 값을 바꾸기 위해서 -> selected->damaname 자체는 char* 타입 이걸 변경하기 위해서는 &selected->damaname 해줘야됨.
	char** targetName = IsDamagochi ? &selected->damaname : &selected->mastername; //targetName 은 다마고치가 참이면 다마고치 이름 아니면 주인이름

	char* new_name = (char*)realloc(*targetName, new_size); // malloc 과 다르게 1번째인자는 기존주소 2번째 인자에는 크기넣음

	*targetName = new_name;
	strcpy_s(*targetName, new_size, temp);
	printf("%s 이름이 %s로 변경되었습니다.\n", nameType, *targetName);
}
// 메모리 할당 및 복사 함수 -> 선택한 다마고치 이름 받아서 처리간편화 하기 위해 만듬
char* AllocateAndCopyName(char* source)
{
	size_t len = strlen(source) + 1; // 다마고치보다 무조건 1칸큼 -> 동적할당 할때 쓰는 자료형이 size_t
	char* new_name = (char*)malloc(len); // 길이만큼 동적할당해줌
	if (new_name != NULL) {
		strcpy_s(new_name, len, source); //받은 이름을 그대로 복사 붙어넣기로 값 초기화 해줌
	}
	return new_name;
}
// 모든 이름 메모리 해제
void FreeDamagochiNames(damagochi* selected)
{
	if (selected != NULL)
	{
		if (selected->damaname != NULL)
		{
			free(selected->damaname);
			selected->damaname = NULL;
		}
		if (selected->mastername != NULL)
		{
			free(selected->mastername);
			selected->mastername = NULL;
		}
	}
}


//*배틀관련 함수들
//대미지 주는 함수
void TakeDamage(int damage, int* health)
{
	*health -= damage;
}
//확률조건을 출력해주는 함수->조건식이 반환 값으로 나와서 조건문에 바로 이어 쓸수있음
int Percent(int num1)
{
	return (rand() % 100) < num1; // 0에서99까지 랜덤하게 나오는데 < 70면 0~69까지 반환됨 -> 조건 자체가 반환된다.
	//0과 1로 판단 -> 조건이 참이면 실행되는거다!
}


//*최대치 및 최하치 고정 함수
//0보다 크면 result 그게 아니면 result = 0 -> 삼항연산식으로처리
int GetSubstractResultOrZero(int num1, int num2)
{
	int result = num1 - num2;

	return result >= 0 ?
		result : 0;
}
// 최대치보다 크면 max로 고정, 아니면 result -> 삼항연산식으로처리
int GetAddResultOrZero(int num1, int num2, int max)
{
	int result = num1 + num2;

	return result >= max ?
		max : result;
}


//*포획관련 함수정의
//컬렉션 관리 통합 함수 - 포획된 다마고치를 저장하고 확장하고 해제를 처리함 -> 최대수용량 재할당
void ManageCaptureCollection(capture* collection, int operation, int capacity)
{
	switch (operation)
	{
	case 0: // 초기화
		collection->count = 0; // 현재 포획수 0
		collection->capacity = capacity; // 최대 수용 가능 수 설정

		// 다마고치 포인터 배열 동적 할당
	   // sizeof(damagochi*) * capacity: 다마고치 포인터 capacity개 만큼의 메모리
		collection->capturedList = (damagochi**)malloc(sizeof(damagochi*) * capacity); // 더블포인터인 이유가 list[0],list[1] 순번으로 다마고치 데이터 넣어줄려고
		for (int i = 0; i < capacity; i++)
		{
			collection->capturedList[i] = NULL; // 순차적으로 인덱스 순으로 접근해서 할당크기 초기화해줌
		}
		printf("포획 컬렉션 초기화 완료 (용량: %d)\n", capacity);
		break;

	case 1: // 확장
		if (collection->count >= collection->capacity)
		{ // 현재 포획한 수가 최대수용공간을 넘어버리면
			int newCapacity = collection->capacity * 2; // 공간 2배로 만들어버린다.
			//capturedList 주소에다가 재할당 해준다 원래크기 capcity*2만큼
			damagochi** newList = (damagochi**)realloc( collection->capturedList,sizeof(damagochi*) * newCapacity);
			if (newList != NULL)
			{
				collection->capturedList = newList;
				collection->capacity = newCapacity;
				for (int i = collection->count; i < newCapacity; i++)
				{
					collection->capturedList[i] = NULL;
				}
				printf("포획 컬렉션 확장 완료! (새 용량: %d)\n", newCapacity);
			}
		}
		break;

	case 2: // 해제 -> 게임종료될때 파라메터값 2로 써줘서 해제처리해줌
		if (collection->capturedList != NULL) {
			for (int i = 0; i < collection->count; i++)
			{
				if (collection->capturedList[i] != NULL)
				{
					FreeDamagochiNames(collection->capturedList[i]);
					free(collection->capturedList[i]);
				}
			}
			free(collection->capturedList);
			collection->capturedList = NULL;
		}
		collection->count = 0;
		collection->capacity = 0;
		printf("포획 컬렉션 메모리 해제 완료\n");
		break;
	}
}

// 포획 시도 및 포획확률계산 함수
int ProcessCapture(damagochi* enemy, damagochi* selected, bool attemptCapture)
{
	if (!attemptCapture) // 포획시도가 아니라면 계산하는 상태
	{
		// 확률만 계산 (정보 제공용)
		int baseChance = 30; //기본확률30퍼센트
		float healthRatio = (float)enemy->health / enemy->Maxhealth; //적최대 체력 퍼센트로 나눠줌
		int healthBonus = (int)((1.0f - healthRatio) * 40); //체력 비율 떨어지면 확률 오르게 해주는 변수
		int levelBonus = selected->currentlevel * 2; // 현재 레벨에다 확률 오르게 해주는 변수
		int totalChance = baseChance + healthBonus + levelBonus; // 조건 충족시 토탈확률확보
		return totalChance > 90 ? 90 : totalChance; // 토탈확률이 90퍼센트 이상이다? 그럼 90으로 최대치 고정
	}
	else {
		// 실제 포획 시도
		int captureChance = ProcessCapture(enemy, selected, false); // 토탈 확률을 captureChane에다 초기화
		printf("포획 시도 중... (확률: %d%%)\n", captureChance);

		if (Percent(captureChance)) //1부터 90안에 든다 -> 90퍼확률이다.
		{
			printf("포획 성공!\n");
			return 1;
		}
		else {
			printf("포획 실패! 적이 저항했습니다.\n");
			return 0;
		}
	}
}
// 캡처 메뉴 및 전환 통합 함수
void HandleCaptureMenu(damagochi** current, capture* collection, bool showOnly)
{
	printf("\n=== 포획된 다마고치 (%d/%d) ===\n", collection->count, collection->capacity);

	if (collection->count == 0) {
		printf("포획한 다마고치가 없습니다.\n");
		return;
	}

	// 현재 다마고치 정보 표시
	printf("현재 사용 중: %s (Lv.%d)\n", (*current)->damaname, (*current)->currentlevel);
	printf("------------------------\n");

	// 포획된 다마고치 목록 표시
	for (int i = 0; i < collection->count; i++)
	{
		damagochi* a = collection->capturedList[i];
		printf("%d. %s (Lv.%d) - 체력:%d/%d 공격력:%d 마나:%d\n", // 1번부터 순차적으로 간단한 포획 다마고치 정보표시
			i + 1, a->damaname, a->currentlevel,
			a->health, a->Maxhealth, a->gochiattack, a->mana);
	}

	if (!showOnly)
	{
		printf("0. 돌아가기\n");
		printf("교체할 다마고치 선택: ");

		int choice;
		scanf_s("%d", &choice);

		if (choice > 0 && choice <= collection->count) {
			// 현재 다마고치와 선택한 다마고치 교체
			damagochi* temp = *current; // 현제 다마고치를 임시저장
			*current = collection->capturedList[choice - 1]; // 현재 다마고치를 잡은 다마고치 주소로 보내버림
			collection->capturedList[choice - 1] = temp; // 이전 주소에 있던 잡았던 다마고치가 현재 다마고치로 변경됨

			printf("\n다마고치 교체 완료!\n");
			printf("이전: %s → 현재: %s\n", temp->damaname, (*current)->damaname); // 교체되었으니 다마고치 이름변경해줌

			// 교체 후 현재 다마고치 상태 표시
			printf("\n현재 다마고치 상태:\n");
			printf("체력: %d/%d, 마나: %d, 공격력: %d\n",
				(*current)->health, (*current)->Maxhealth,
				(*current)->mana, (*current)->gochiattack);
		}
	}
}

// 포획 컬렉션에 다마고치 추가 -> 배틀 포획성공할때 마다 판정
void AddToCaptureCollection(capture* collection, damagochi* captured) {
	// 용량이 부족하면 확장
	if (collection->count >= collection->capacity) {
		ManageCaptureCollection(collection, 1, 0); // operation 1 = 확장
	}

	// 확장 후에도 여전히 용량이 부족하면 포획 실패
	if (collection->count >= collection->capacity) {
		printf("포획 한계에 도달했습니다! 더 이상 포획할 수 없습니다.\n");
		FreeDamagochiNames(captured);
		free(captured);
		return;
	}

	// 컬렉션에 다마고치 추가
	collection->capturedList[collection->count] = captured;
	collection->count++;

	printf("포획 성공! 컬렉션에 추가되었습니다. (현재 %d/%d마리)\n",
		collection->count, collection->capacity);
}

// 포획된 다마고치 생성 -> 배틀중 생성
damagochi* CreateCapturedDamagochi(damagochi* original, char* newName) {
	// 메모리 할당
	damagochi* captured = (damagochi*)malloc(sizeof(damagochi));

	//원본 데이터 복사
	*captured = *original;
	// 새로운 이름 설정
	captured->damaname = AllocateAndCopyName(newName);
	if (captured->damaname == NULL) {
		free(captured);
		return NULL;
	}


	captured->health = captured->Maxhealth; // 현재 체력만 회복시켜줌

	// 레벨과 경험치 초기화 (새로운 시작)
	captured->currentlevel = 1;
	captured->exp = 0;
	captured->skillpoint = 0;
	captured->rewardgold = 0;

	// 스킬 레벨 초기화 (하지만 스킬 정보는 유지)
	captured->skill_isanghaessi.level = 1;
	captured->skill_paili.level = 1;
	captured->skill_kkobugi.level = 1;

	// 스킬 마나 코스트도 초기화
	captured->skill_isanghaessi.mana_cost = 50;
	captured->skill_paili.mana_cost = 50;
	captured->skill_kkobugi.mana_cost = 50;

	printf("새로운 다마고치 생성: %s\n", captured->damaname);
	return captured;
}

//포획된 다마고치정보 출력
void ShowDetailedCaptureInfo(capture* collection)
{
	printf("\n=== 포획된 다마고치 상세 정보 (%d/%d) ===\n",
		collection->count, collection->capacity);

	if (collection->count == 0) {
		printf("포획한 다마고치가 없습니다.\n");
		return;
	}
	// 순차적으로 인덱스 로 접근하여 출력해줌
	for (int i = 0; i < collection->count; i++)
	{
		damagochi* a = collection->capturedList[i];
		printf("\n[%d] %s\n", i + 1, a->damaname);
		printf("   레벨: %d\n", a->currentlevel);
		printf("   체력: %d/%d\n", a->health, a->Maxhealth);
		printf("   마나: %d\n", a->mana);
		printf("   공격력: %d\n", a->gochiattack);
		printf("   특수공격력: %d\n", a->specialattack);
		printf("   포만감: %d\n", a->hungry);
		printf("   배변: %d\n", a->poo);
		printf("   스트레스: %d\n", a->stress);
		printf("   경험치: %d\n", a->exp);
		printf("   골드: %d\n", a->rewardgold);
		printf("   스킬포인트: %d\n", a->skillpoint);

		// 스킬 정보 표시
		if (strstr(a->damaname, "이상해씨") != NULL)
		{
			printf("   스킬: %s (Lv.%d)\n",
				a->skill_isanghaessi.name, a->skill_isanghaessi.level);
		}
		else if (strstr(a->damaname, "파이리") != NULL)
		{
			printf("   스킬: %s (Lv.%d)\n",
				a->skill_paili.name, a->skill_paili.level);
		}
		else if (strstr(a->damaname, "꼬부기") != NULL)
		{
			printf("   스킬: %s (Lv.%d)\n",
				a->skill_kkobugi.name, a->skill_kkobugi.level);
		}
	}
}