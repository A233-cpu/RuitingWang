#include "MyArray.h"
#include <iostream>
using namespace std;

// 辅助函数：打印数组信息
void printArray(const string& name, const MyArray& arr) {
	cout << name << "（长度：" << arr.getSize() << "）：";
	int size = arr.getSize();
	if (size == 0) {
		cout << "空数组" << endl;
		return;
	}
	int* data = arr.getData();
	for (int i = 0; i < size; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
}

int main() {
	// ==============================================
	// 测试1：构造函数（默认构造、带参数构造、拷贝构造）
	// ==============================================
	cout << "===== 测试构造函数 =====" << endl;
	MyArray arr1;                  
	MyArray arr2(3);            
	MyArray arr3(-2);              
	MyArray arr4(arr2);            

	arr2.setData(0, 1);
	arr2.setData(1, 2);
	arr2.setData(2, 3);
	arr2.setData(3, 4); // 测试越界赋值

	printArray("arr1（默认构造）", arr1);
	printArray("arr2（带参数构造+赋值）", arr2);
	printArray("arr3（非法长度）", arr3);
	printArray("arr4（拷贝arr2）", arr4);

	// ==============================================
	// 测试2：数组合并
	// ==============================================
	cout << "\n===== 测试数组合并 =====" << endl;
	MyArray arr5(2);
	arr5.setData(0, 4);
	arr5.setData(1, 5);
	printArray("arr2", arr2);
	printArray("arr5", arr5);
	MyArray merged = arr2.merge(arr5);
	printArray("合并结果", merged);

	// ==============================================
	// 测试3：四则运算（长度一致和不一致）
	// ==============================================
	cout << "\n===== 测试四则运算 =====" << endl;
	MyArray arr6(3); 
	arr6.setData(0, 6);
	arr6.setData(1, 7);
	arr6.setData(2, 8);
	MyArray arr7(2);  
	arr7.setData(0, 2);
	arr7.setData(1, 4);

	printArray("arr2（[1,2,3]）", arr2);
	printArray("arr6（[6,7,8]）", arr6);
	printArray("arr7（[2,4]）", arr7);

	MyArray add1 = arr2.add(arr6);
	MyArray add2 = arr2.add(arr7);
	printArray("arr2 + arr6", add1);
	printArray("arr2 + arr7", add2);

	MyArray sub1 = arr6.subtract(arr2);
	MyArray sub2 = arr7.subtract(arr2);
	printArray("arr6 - arr2", sub1);
	printArray("arr7 - arr2", sub2);

	MyArray mul1 = arr2.multiply(arr6);
	MyArray mul2 = arr2.multiply(arr7);
	printArray("arr2 * arr6", mul1);
	printArray("arr2 * arr7", mul2);

	MyArray div1 = arr6.divide(arr2);
	MyArray div2 = arr2.divide(arr7);
	printArray("arr6 / arr2", div1);
	printArray("arr2 / arr7", div2);

	// ==============================================
	// 测试4：深拷贝验证（修改拷贝对象不影响原对象）
	// ==============================================
	cout << "\n===== 测试深拷贝 =====" << endl;
	MyArray arr8 = arr2; 
	arr8.setData(0, 99); 
	printArray("原对象arr2", arr2);  
	printArray("拷贝对象arr8", arr8); 

	return 0;
}