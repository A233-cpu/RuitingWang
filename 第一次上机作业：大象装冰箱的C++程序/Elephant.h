#pragma once
#ifndef ELEPHANT_H  // ͷ�ļ���������ֹ�ظ�����
#define ELEPHANT_H

#include <string>  // ����string����
using namespace std;  // ��string��ʹ��

class Elephant {
private:
	string name;    // ��������
	double weight;  // �������أ���λ��kg��
public:
	// ���캯������ʼ�����ƺ�����
	Elephant(string n, double w);
	// ��Ա�������������������Ϊ
	void enterRefrigerator();
};

#endif  // ����ͷ�ļ�����