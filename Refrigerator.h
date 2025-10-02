#pragma once
#ifndef REFRIGERATOR_H  // ͷ�ļ�����
#define REFRIGERATOR_H

#include <string>
using namespace std;

class Refrigerator {
private:
	string brand;   // ����Ʒ��
	double volume;  // �����ݻ�����λ��L��
	bool isOpen;    // ������״̬��trueΪ����falseΪ��
public:
	// ���캯������ʼ��Ʒ�ƺ��ݻ�
	Refrigerator(string b, double v);
	// ��Ա�������򿪱�����
	void openDoor();
	// ��Ա�������رձ�����
	void closeDoor();
};

#endif