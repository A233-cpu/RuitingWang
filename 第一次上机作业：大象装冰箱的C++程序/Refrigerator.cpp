#include "Refrigerator.h"
#include <iostream>

// ʵ�ֹ��캯��
Refrigerator::Refrigerator(string b, double v) : brand(b), volume(v), isOpen(false) {}

// ʵ��openDoor����
void Refrigerator::openDoor() {
	isOpen = true;
	cout << brand << "���䣨�ݻ�" << volume << "L�����Ѵ򿪣�" << endl;
}

// ʵ��closeDoor����
void Refrigerator::closeDoor() {
	isOpen = false;
	cout << brand << "�������ѹرգ�" << endl;
}