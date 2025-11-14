#include "card_operations.h"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

//命名空间函数实现
namespace card
{
	// 打印分隔线
	void printLine(char c, int len)
	{
		for (int i = 0; i < len; ++i)
		{
			cout << c;
		}
		cout << endl;
	}

	// 打印标题
	void title(const string& s)
	{
		cout << "\n==== " << s << " ====\n";
	}
}

//创建账户数组
Card* createCards(int n)
{
	return new Card[n];
}

//释放账户数组
void destroyCards(Card* p)
{
	delete[] p;
}


//输入账户信息
void inputCards(Card* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << "请输入学号、姓名和初始余额：";
		try
		{
			cin >> arr[i].id >> arr[i].name >> arr[i].balance;

			if (cin.fail())                    // 非法输入检测
			{
				cin.clear();
				cin.ignore(1000, '\n');
				throw runtime_error("输入格式错误，请输入正确的数据类型。");
			}

			if (arr[i].balance < 0)            // 余额校验
			{
				throw invalid_argument("初始余额不能为负数！");
			}

			arr[i].transactions = 0;
		}
		catch (const exception& e)
		{
			cout << "输入异常：" << e.what() << endl;
			i--;  // 重新输入当前账户信息
		}
	}
}

// 充值函数（带默认参数）
void deposit(Card& c, double amount, double fee)
{
	c.balance += amount * (1.0 - fee);
	c.transactions++;
}

// 消费函数（函数重载）
bool spend(Card& c, double cost)
{
	if (c.balance >= cost)
	{
		c.balance -= cost;
		c.transactions++;
		return true;
	}
	return false;
}

bool spend(Card& c, double cost, const string& item)
{
	cout << "消费项目：" << item << endl;

	try
	{
		if (cost < 0)
		{
			throw invalid_argument("消费金额不能为负数！");
		}

		if (c.balance < cost)
		{
			throw runtime_error("余额不足，消费失败！");
		}

		c.balance -= cost;
		c.transactions++;
		return true;
	}
	catch (const exception& e)
	{
		cout << "异常提示：" << e.what() << endl;
		return false;
	}
}

// 显示余额 常引用：用于防止数据被修改
void showBalance(const Card& c)
{
	cout << c.name << " 当前余额为：" << c.balance << endl;
}

// 查看学号 指向常量的指针：可访问但不能修改指向值
void viewStudentID(const Card* p)
{
	cout << "账户ID为：" << p->id << endl;
}

//打印报表
void printReport(const Card* arr, int n)
{
	using card::printLine;
	printLine('=');
	cout << left << setw(8) << "ID"
		<< setw(12) << "Name"
		<< right << setw(14) << "Balance"
		<< setw(14) << "Transactions" << endl;
	printLine('-');

	cout.setf(ios::fixed);
	cout << setprecision(2);

	for (int i = 0; i < n; ++i)
	{
		cout << left << setw(8) << arr[i].id
			<< setw(12) << arr[i].name
			<< right << setw(14) << arr[i].balance
			<< setw(14) << arr[i].transactions << endl;
	}
	printLine('=');
}

// 金额转分
int toCent(double amount)
{
	return static_cast<int>(amount * 100);
}