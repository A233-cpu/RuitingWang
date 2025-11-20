#include "MyArray.h"
#include <cstring>   
#include <iostream>  
using namespace std;

MyArray::MyArray() : p(nullptr), N(0) {}

MyArray::MyArray(int n) : N(n) {
	if (n < 0) { // 处理非法长度
		cout << "警告：数组长度不能为负数，创建空数组" << endl;
		N = 0;
		p = nullptr;
		return;
	}
	p = new int[N];       // 动态分配内存
	memset(p, 0, N * sizeof(int)); // 初始化为0
}

MyArray::MyArray(const MyArray& other) : N(other.N) {
	if (N == 0) { // 源对象为空数组
		p = nullptr;
		return;
	}
	p = new int[N];               // 分配独立内存
	for (int i = 0; i < N; i++) { // 逐元素拷贝数据
		p[i] = other.p[i];
	}
}

MyArray::~MyArray() {
	delete[] p; // 释放数组内存
	p = nullptr; // 避免野指针
	N = 0;
}

int MyArray::getSize() const {
	return N;
}

int* MyArray::getData() const {
	return p;
}

void MyArray::setData(int index, int value) {
	if (index >= 0 && index < N) {
		p[index] = value;
	}
	else {
		cout << "错误：索引" << index << "超出数组边界（0~" << N - 1 << "）" << endl;
	}
}

MyArray MyArray::merge(const MyArray& other) const {
	int newSize = N + other.N;       
	MyArray newArr(newSize);         

	for (int i = 0; i < N; i++) {
		newArr.p[i] = p[i];
	}
	for (int i = 0; i < other.N; i++) {
		newArr.p[N + i] = other.p[i];
	}

	return newArr;
}

MyArray MyArray::add(const MyArray& other) const {
	int maxSize = max(N, other.N);   
	MyArray result(maxSize);        

	for (int i = 0; i < maxSize; i++) {
		int val1 = (i < N) ? p[i] : 0;
		int val2 = (i < other.N) ? other.p[i] : 0;
		result.p[i] = val1 + val2;
	}

	return result;
}

MyArray MyArray::subtract(const MyArray& other) const {
	int maxSize = max(N, other.N);
	MyArray result(maxSize);

	for (int i = 0; i < maxSize; i++) {
		int val1 = (i < N) ? p[i] : 0;
		int val2 = (i < other.N) ? other.p[i] : 0;
		result.p[i] = val1 - val2;
	}

	return result;
}

MyArray MyArray::multiply(const MyArray& other) const {
	int maxSize = max(N, other.N);
	MyArray result(maxSize);

	for (int i = 0; i < maxSize; i++) {
		int val1 = (i < N) ? p[i] : 0;
		int val2 = (i < other.N) ? other.p[i] : 0;
		result.p[i] = val1 * val2;
	}

	return result;
}

MyArray MyArray::divide(const MyArray& other) const {
	int maxSize = max(N, other.N);
	MyArray result(maxSize);

	for (int i = 0; i < maxSize; i++) {
		int val1 = (i < N) ? p[i] : 0;
		int val2 = (i < other.N) ? other.p[i] : 0;

		if (val2 == 0) { // 处理除数为0
			cout << "警告：第" << i << "个元素除数为0，结果设为0" << endl;
			result.p[i] = 0;
		}
		else {
			result.p[i] = val1 / val2; 
		}
	}

	return result;
}