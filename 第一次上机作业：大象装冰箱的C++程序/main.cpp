#include "Elephant.h"   // �����������ͷ�ļ�
#include "Refrigerator.h"  // �����������ͷ�ļ�

int main() {
	// ʵ��������������ơ������󡱣�����5000kg
	Elephant bigElephant("������", 5000);
	// ʵ�����������Ʒ�ơ����������ݻ�500L
	Refrigerator myFridge("����", 500);

	// ִ�С���������䡱������
	myFridge.openDoor();    // ���俪��
	bigElephant.enterRefrigerator();  // ����������
	myFridge.closeDoor();   // �������

	return 0;  // ������������
}