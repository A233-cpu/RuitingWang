#include<iostream>
using namespace std;

class Date {
private:
	int year;
	int month;
	int day;
	const int daysInMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };//存储平年1-12月份的天数
	bool isLeapYear()const {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}//判断当前月份是否为闰年
	long long dateToTotalDays()const {
		long long total = 0;
		for (int y = 1; y < year; y++)
			total += 365 + ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
		for (int m = 1; m < month; m++)
			total += daysInMonth[m] + (m == 2 && isLeapYear() ? 1 : 0);
		return total + day;
	}//计算从公元1年1月1日到当前日期的总天数

public:
	void SetDate(int ,int ,int );
	void Display();
	int GetYear();
	int GetMonth();
	int GetDay();
	string GetWeekDay();//获取星期几
	long long GetDayDiff(const Date&other);//计算天数差
};

void Date::SetDate(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

int Date::GetYear() {
	return year;
}

int Date::GetMonth() {
	return month;
}

int Date::GetDay() {
	return day;
}

void Date::Display() {
	cout << year << "-" << month << "-" << day << endl;
}

//获取星期几
string Date::GetWeekDay(){
const string week[] = { "星期日","星期一","星期二","星期三","星期四","星期五","星期六" };
return week[(dateToTotalDays()) % 7];
 }

 // 计算天数差（当前 - 传入日期）
 long long Date::GetDayDiff(const Date& other) {
	 return dateToTotalDays() - other.dateToTotalDays();
 }

int main() {
	Date today, yesterday,* t,festival;
	today.SetDate(2025, 11, 13);
	cout << "Today is:";
	today.Display();
	cout << "Today's week:" << today.GetWeekDay() << endl;
	t = &yesterday;
	(*t).SetDate(2025, 11, 12);
	cout << "Yesterday is:";
	(*t).Display();
	cout << "Yesterday's week:" << yesterday.GetWeekDay() << endl;
	// 测试天数差
	festival.SetDate(2025, 1, 1);
	cout << "Days between today and 2025-01-01: " << today.GetDayDiff(festival) << endl;
	cout << "Days between today and yesterday: " << today.GetDayDiff(yesterday) << endl;
	return 0;
}