#include "card_operations.h"
#include <iostream>

using namespace std;

int main()
{
	using card::title;
	using card::printLine;

	title("Campus Card System");

	int n;
	cout << "请输入学生数量：";
	cin >> n;

	Card* users = createCards(n);
	inputCards(users, n);

	deposit(users[0], 100.0);
	spend(users[0], 8.5, "食堂午餐");

	showBalance(users[0]);
	viewStudentID(&users[0]);

	cout << "换算为分: " << toCent(users[0].balance) << endl;

	printReport(users, n);
	destroyCards(users);

	system("pause");

	return 0;
}