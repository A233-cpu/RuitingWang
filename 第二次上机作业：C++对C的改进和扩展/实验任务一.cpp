#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// 定义学生结构体
struct Student {
	string name;     // 姓名
	float chinese;   // 语文成绩
	float math;      // 数学成绩
	float english;   // 英语成绩
	float average;   // 平均分
};

int main0() {
	int studentCount;
	cout << "请输入学生人数：";
	cin >> studentCount;

	// 用vector存储学生信息（避免变量长度数组问题）
	vector<Student> students(studentCount);

	// 输入每个学生的信息
	for (int i = 0; i < studentCount; ++i) {
		cout << "请输入第" << (i + 1) << "个学生的信息(姓名 语文 数学 英语）：" << endl;

		cin >> students[i].name
			>> students[i].chinese
			>> students[i].math
			>> students[i].english;


		// 计算平均分
		students[i].average = (students[i].math + students[i].english + students[i].chinese) / 3.0f;
	}

	// 输出结果（格式化保留2位小数）
	cout << endl << "学生信息及成绩统计：" << endl;
	cout << fixed << setprecision(2); // 设置浮点数输出精度
	for (const auto& stu : students) {

		cout << stu.name << " "
			<< stu.chinese << " "
			<< stu.math << " "
			<< stu.english << " "

			<< stu.average;

		// 平均分≥90时输出Excellent
		if (stu.average >= 90.0f) {
			cout << " Excellent";
		}
		cout << endl;
	}

	return 0;
}