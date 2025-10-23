#include <iostream>
using namespace std;

// 1. ���ð汾��swap��������������������
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}

// 2. ����swap��������ͨ����ͬ��������ʵ�֣��˴���int����Ԫ�ؽ���Ϊ����
void swap(int arr[], int idx1, int idx2) {
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

int main() {
	// �������ð汾��swap
	int a, b;
	cout << "������������: ";
	cin >> a >> b;
	cout << "Before swap: x=" << a << ", y=" << b << endl;
	swap(a, b);
	cout << "After swap: x=" << a << ", y=" << b << endl;

	// �������ذ汾��swap������Ԫ�ؽ�����
	int arr[] = { 10, 20 };
	cout << "\n���齻��ǰ: arr[0]=" << arr[0] << ", arr[1]=" << arr[1] << endl;
	swap(arr, 0, 1);
	cout << "���齻����: arr[0]=" << arr[0] << ", arr[1]=" << arr[1] << endl;

	return 0;
}
