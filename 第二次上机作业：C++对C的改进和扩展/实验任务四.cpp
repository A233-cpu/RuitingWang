#include <iostream>
using namespace std;

// 1. 引用版本的swap函数（交换两个整数）
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}

// 2. 重载swap函数（可通过不同参数类型实现，此处以int数组元素交换为例）
void swap(int arr[], int idx1, int idx2) {
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

int main() {
	// 测试引用版本的swap
	int a, b;
	cout << "输入两个整数: ";
	cin >> a >> b;
	cout << "Before swap: x=" << a << ", y=" << b << endl;
	swap(a, b);
	cout << "After swap: x=" << a << ", y=" << b << endl;

	// 测试重载版本的swap（数组元素交换）
	int arr[] = { 10, 20 };
	cout << "\n数组交换前: arr[0]=" << arr[0] << ", arr[1]=" << arr[1] << endl;
	swap(arr, 0, 1);
	cout << "数组交换后: arr[0]=" << arr[0] << ", arr[1]=" << arr[1] << endl;

	return 0;
}
