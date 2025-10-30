#include "card_operations.h"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

//�����ռ亯��ʵ��
namespace card
{
	// ��ӡ�ָ���
	void printLine(char c, int len)
	{
		for (int i = 0; i < len; ++i)
		{
			cout << c;
		}
		cout << endl;
	}

	// ��ӡ����
	void title(const string& s)
	{
		cout << "\n==== " << s << " ====\n";
	}
}

//�����˻�����
Card* createCards(int n)
{
	return new Card[n];
}

//�ͷ��˻�����
void destroyCards(Card* p)
{
	delete[] p;
}


//�����˻���Ϣ
void inputCards(Card* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << "������ѧ�š������ͳ�ʼ��";
		try
		{
			cin >> arr[i].id >> arr[i].name >> arr[i].balance;

			if (cin.fail())                    // �Ƿ�������
			{
				cin.clear();
				cin.ignore(1000, '\n');
				throw runtime_error("�����ʽ������������ȷ���������͡�");
			}

			if (arr[i].balance < 0)            // ���У��
			{
				throw invalid_argument("��ʼ����Ϊ������");
			}

			arr[i].transactions = 0;
		}
		catch (const exception& e)
		{
			cout << "�����쳣��" << e.what() << endl;
			i--;  // �������뵱ǰ�˻���Ϣ
		}
	}
}

// ��ֵ��������Ĭ�ϲ�����
void deposit(Card& c, double amount, double fee)
{
	c.balance += amount * (1.0 - fee);
	c.transactions++;
}

// ���Ѻ������������أ�
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
	cout << "������Ŀ��" << item << endl;

	try
	{
		if (cost < 0)
		{
			throw invalid_argument("���ѽ���Ϊ������");
		}

		if (c.balance < cost)
		{
			throw runtime_error("���㣬����ʧ�ܣ�");
		}

		c.balance -= cost;
		c.transactions++;
		return true;
	}
	catch (const exception& e)
	{
		cout << "�쳣��ʾ��" << e.what() << endl;
		return false;
	}
}

// ��ʾ��� �����ã����ڷ�ֹ���ݱ��޸�
void showBalance(const Card& c)
{
	cout << c.name << " ��ǰ���Ϊ��" << c.balance << endl;
}

// �鿴ѧ�� ָ������ָ�룺�ɷ��ʵ������޸�ָ��ֵ
void viewStudentID(const Card* p)
{
	cout << "�˻�IDΪ��" << p->id << endl;
}

//��ӡ����
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

// ���ת��
int toCent(double amount)
{
	return static_cast<int>(amount * 100);
}