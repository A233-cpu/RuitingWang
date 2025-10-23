#include <iostream>
#include <iomanip>
using namespace std;

// 1. �����������������ֵ�ƽ��
inline double square(double x) {
	return x * x;
}

// 2. Ĭ�ϲ��������������ݣ�Ĭ��ָ��Ϊ2��
double power(double base, int exponent = 2) {
	double result = 1.0;
	for (int i = 0; i < exponent; ++i) {
		result *= base;
	}
	return result;
}

// 3. �������أ�ʵ��˫���ȸ���������������
double calc(double a, double b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		if (b == 0) {
			cout << "Error: divide by zero" << endl;
			return 0;
		}
		return a / b;
	default:
		cout << "Invalid operator" << endl;
		return 0;
	}
}

// �������أ�ʵ����������������
double calc(int a, int b, char op) {
	// ����˫���Ȱ汾��calc������������
	return calc(static_cast<double>(a), static_cast<double>(b), op);
}

int main2() {
	double num;
	int a_int, b_int;
	double a_double, b_double;
	char op;

	// ������������square
	cout << "Enter a number to calculate its square: ";
	cin >> num;
	cout << "Square: " << fixed << setprecision(2) << square(num) << endl;

	// ����Ĭ�ϲ�������power
	cout << "\nEnter base number (exponent defaults to 2): ";
	cin >> num;
	cout << "Power result: " << fixed << setprecision(2) << power(num) << endl;
	cout << "Enter base number and exponent: ";
	cin >> num >> a_int;
	cout << "Power result: " << fixed << setprecision(2) << power(num, a_int) << endl;

	// ���Ժ�������calc�������棩
	cout << "\nEnter two integers and operator (+-*/): ";
	cin >> a_int >> b_int >> op;
	cout << "Integer calculation result: " << fixed << setprecision(2) << calc(a_int, b_int, op) << endl;

	// ���Ժ�������calc��˫���Ȱ棩
	cout << "\nEnter two doubles and operator (+-*/): ";
	cin >> a_double >> b_double >> op;
	cout << "Double calculation result: " << fixed << setprecision(2) << calc(a_double, b_double, op) << endl;

	return 0;
}