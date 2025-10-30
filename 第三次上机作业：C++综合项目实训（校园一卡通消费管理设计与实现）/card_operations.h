#ifndef CARD_OPERATIONS_H
#define CARD_OPERATIONS_H

#include <iostream>
#include <iomanip>
#include <string>

// ϵͳ����
const double FEE_RATE = 0.02;          // ��ֵ��������
const double WARNING_BALANCE = 10.0;   // ������ֵ

// ѧ��һ��ͨ�˻��ṹ��
struct Card
{
	int    id;            // ѧ��
	std::string name;          // ����
	double balance;       // ��ǰ���
	int    transactions;  // ���״���
};

//�����ռ䣺�������
namespace card
{
	void printLine(char c = '-', int len = 60);
	void title(const std::string& s);
}


//��̬�ڴ����
Card* createCards(int n);
void destroyCards(Card* p);

//�˻�����
void inputCards(Card* arr, int n);
void deposit(Card& c, double amount, double fee = FEE_RATE);
bool spend(Card& c, double cost);
bool spend(Card& c, double cost, const std::string& item);
void showBalance(const Card& c);
void viewStudentID(const Card* p);

//���ߺ���
int toCent(double amount);
void printReport(const Card* arr, int n);

#endif