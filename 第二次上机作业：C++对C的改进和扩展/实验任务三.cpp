#include <iostream>
#include <iomanip>
using namespace std;

// 1. 内联函数：计算数字的平方
inline double square(double x) {
	return x * x;
}

// 2. 默认参数函数：计算幂（默认指数为2）
double power(double base, int exponent = 2) {
	double result = 1.0;
	for (int i = 0; i < exponent; ++i) {
		result *= base;
	}
	return result;
}

// 3. 函数重载：实现双精度浮点数的四则运算
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

// 函数重载：实现整数的四则运算
double calc(int a, int b, char op) {
	// 调用双精度版本的calc（类型提升）
	return calc(static_cast<double>(a), static_cast<double>(b), op);
}

int main2() {
	double num;
	int a_int, b_int;
	double a_double, b_double;
	char op;

	// 测试内联函数square
	cout << "Enter a number to calculate its square: ";
	cin >> num;
	cout << "Square: " << fixed << setprecision(2) << square(num) << endl;

	// 测试默认参数函数power
	cout << "\nEnter base number (exponent defaults to 2): ";
	cin >> num;
	cout << "Power result: " << fixed << setprecision(2) << power(num) << endl;
	cout << "Enter base number and exponent: ";
	cin >> num >> a_int;
	cout << "Power result: " << fixed << setprecision(2) << power(num, a_int) << endl;

	// 测试函数重载calc（整数版）
	cout << "\nEnter two integers and operator (+-*/): ";
	cin >> a_int >> b_int >> op;
	cout << "Integer calculation result: " << fixed << setprecision(2) << calc(a_int, b_int, op) << endl;

	// 测试函数重载calc（双精度版）
	cout << "\nEnter two doubles and operator (+-*/): ";
	cin >> a_double >> b_double >> op;
	cout << "Double calculation result: " << fixed << setprecision(2) << calc(a_double, b_double, op) << endl;

	return 0;
}