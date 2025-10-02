#pragma once
#ifndef ELEPHANT_H  // 头文件保护：防止重复包含
#define ELEPHANT_H

#include <string>  // 用于string类型
using namespace std;  // 简化string的使用

class Elephant {
private:
	string name;    // 大象名称
	double weight;  // 大象体重（单位：kg）
public:
	// 构造函数：初始化名称和体重
	Elephant(string n, double w);
	// 成员方法：大象进入冰箱的行为
	void enterRefrigerator();
};

#endif  // 结束头文件保护