#include <stdio.h>

void variableUse(int num, int* numpointer)
// ������ �̿��ؼ� �ش� �Լ��� ���� �ɶ� num�̶�� ������ �ּҰ��� �����ؼ� num������ �缳����
// �ּҰ��� �������ְ� �Լ� ȣ��� ������ �������� �޸𸮷� �����Ͽ� ���� ��������༭ numpointer ������ ������� ���� ����ó����
{
	*numpointer = num;

}



int main(void) 
{
	int value = 5;
	int target = 10;

	variableUse(value, &target); //&������ �޾� �ִ°Ŵ� int* ������ �ڷ�����...
	printf("target �� ���� : %d", target);
}