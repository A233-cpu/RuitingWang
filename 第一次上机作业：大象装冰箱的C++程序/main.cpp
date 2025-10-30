#include "Elephant.h"   // 包含大象类的头文件
#include "Refrigerator.h"  // 包含冰箱类的头文件

int main() {
	// 实例化大象对象：名称“非洲象”，体重5000kg
	Elephant bigElephant("非洲象", 5000);
	// 实例化冰箱对象：品牌“海尔”，容积500L
	Refrigerator myFridge("海尔", 500);

	// 执行“大象进冰箱”的流程
	myFridge.openDoor();    // 冰箱开门
	bigElephant.enterRefrigerator();  // 大象进入冰箱
	myFridge.closeDoor();   // 冰箱关门

	return 0;  // 程序正常结束
}