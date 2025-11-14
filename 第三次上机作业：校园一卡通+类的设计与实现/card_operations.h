#ifndef CARD_OPERATIONS_H
#define CARD_OPERATIONS_H

#include <iostream>
#include <iomanip>
#include <string>

// 系统常量
const double FEE_RATE = 0.02;          // 充值手续费率
const double WARNING_BALANCE = 10.0;   // 低余额警戒值

// 学生一卡通账户结构体
struct Card
{
	int    id;            // 学号
	std::string name;          // 姓名
	double balance;       // 当前余额
	int    transactions;  // 交易次数
};

//命名空间：输出工具
namespace card
{
	void printLine(char c = '-', int len = 60);
	void title(const std::string& s);
}


//动态内存管理
Card* createCards(int n);
void destroyCards(Card* p);

//账户操作
void inputCards(Card* arr, int n);
void deposit(Card& c, double amount, double fee = FEE_RATE);
bool spend(Card& c, double cost);
bool spend(Card& c, double cost, const std::string& item);
void showBalance(const Card& c);
void viewStudentID(const Card* p);

//工具函数
int toCent(double amount);
void printReport(const Card* arr, int n);

#endif