#include "Elephant.h"  // ������Ӧ��ͷ�ļ�
#include <iostream>    // ����cout���

// ʵ�ֹ��캯��
Elephant::Elephant(string n, double w) : name(n), weight(w) {}

// ʵ��enterRefrigerator����
void Elephant::enterRefrigerator() {
	cout << name << "������" << weight << "kg��׼��������䣡" << endl;
}