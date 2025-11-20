#ifndef MYARRAY_H
#define MYARRAY_H

class MyArray {
private:
	int* p;       // 动态数组指针
	int N;        // 数组元素个数

public:
	MyArray();                          // 默认构造
	explicit MyArray(int n);            // 带参数构造
	MyArray(const MyArray& other);      // 拷贝构造（深拷贝）

	~MyArray();

	int getSize() const;                // 获取数组长度
	int* getData() const;               // 获取数组指针
	void setData(int index, int value); // 设置指定位置元素值

	MyArray merge(const MyArray& other) const; 

	MyArray add(const MyArray& other) const;     
	MyArray subtract(const MyArray& other) const;
	MyArray multiply(const MyArray& other) const;
	MyArray divide(const MyArray& other) const;  
};

#endif 