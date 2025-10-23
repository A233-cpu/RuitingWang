#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// ����ѧ���ṹ��
struct Student {
	string name;     // ����
	float chinese;   // ���ĳɼ�
	float math;      // ��ѧ�ɼ�
	float english;   // Ӣ��ɼ�
	float average;   // ƽ����
};

int main0() {
	int studentCount;
	cout << "������ѧ��������";
	cin >> studentCount;

	// ��vector�洢ѧ����Ϣ��������������������⣩
	vector<Student> students(studentCount);

	// ����ÿ��ѧ������Ϣ
	for (int i = 0; i < studentCount; ++i) {
		cout << "�������" << (i + 1) << "��ѧ������Ϣ(���� ���� ��ѧ Ӣ���" << endl;

		cin >> students[i].name
			>> students[i].chinese
			>> students[i].math
			>> students[i].english;


		// ����ƽ����
		students[i].average = (students[i].math + students[i].english + students[i].chinese) / 3.0f;
	}

	// ����������ʽ������2λС����
	cout << endl << "ѧ����Ϣ���ɼ�ͳ�ƣ�" << endl;
	cout << fixed << setprecision(2); // ���ø������������
	for (const auto& stu : students) {

		cout << stu.name << " "
			<< stu.chinese << " "
			<< stu.math << " "
			<< stu.english << " "

			<< stu.average;

		// ƽ���֡�90ʱ���Excellent
		if (stu.average >= 90.0f) {
			cout << " Excellent";
		}
		cout << endl;
	}

	return 0;
}