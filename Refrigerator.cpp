#include "Refrigerator.h"
#include <iostream>

// 实现构造函数
Refrigerator::Refrigerator(string b, double v) : brand(b), volume(v), isOpen(false) {}

// 实现openDoor方法
void Refrigerator::openDoor() {
	isOpen = true;
	cout << brand << "冰箱（容积" << volume << "L）门已打开！" << endl;
}

// 实现closeDoor方法
void Refrigerator::closeDoor() {
	isOpen = false;
	cout << brand << "冰箱门已关闭！" << endl;
}