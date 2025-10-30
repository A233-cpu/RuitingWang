#include "Elephant.h"  // 包含对应的头文件
#include <iostream>    // 用于cout输出

// 实现构造函数
Elephant::Elephant(string n, double w) : name(n), weight(w) {}

// 实现enterRefrigerator方法
void Elephant::enterRefrigerator() {
	cout << name << "（体重" << weight << "kg）准备进入冰箱！" << endl;
}