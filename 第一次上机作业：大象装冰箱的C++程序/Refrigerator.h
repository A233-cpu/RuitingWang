#pragma once
#ifndef REFRIGERATOR_H  // 头文件保护
#define REFRIGERATOR_H

#include <string>
using namespace std;

class Refrigerator {
private:
	string brand;   // 冰箱品牌
	double volume;  // 冰箱容积（单位：L）
	bool isOpen;    // 冰箱门状态：true为开，false为关
public:
	// 构造函数：初始化品牌和容积
	Refrigerator(string b, double v);
	// 成员方法：打开冰箱门
	void openDoor();
	// 成员方法：关闭冰箱门
	void closeDoor();
};

#endif