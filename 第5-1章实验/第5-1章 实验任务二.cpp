#include <iostream>
using namespace std;

class base {
public:
	int a;          
protected:
	int b;        
private:
	int c;          
	static int count; 
public:
	base(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {
		count++;
		cout << "base构造函数调用，当前对象数：" << count << endl;
	}

	~base() {
		count--;
		cout << "base析构函数调用，当前对象数：" << count << endl;
	}

	void print() {
		cout << "base: a=" << a << ", b=" << b << ", c=" << c << endl;
	}

	static int Manage() {
		return count;
	}

	int getC() const { return c; }
};

int base::count = 0;

class derived1 : public base {
public:
	derived1(int a, int b, int c) : base(a, b, c) {
		cout << "derived1（公有继承）构造函数调用" << endl;
	}

	~derived1() {
		cout << "derived1（公有继承）析构函数调用" << endl;
	}

	void testAccess() {
		cout << "derived1（公有继承）访问：" << endl;
		cout << "a=" << a;                
		cout << ", b=" << b;           
		// cout << ", c=" << c;       
		cout << ", c=" << getC() << endl; 
	}
};

class derived2 : protected base {
public:
	derived2(int a, int b, int c) : base(a, b, c) {
		cout << "derived2（保护继承）构造函数调用" << endl;
	}

	~derived2() {
		cout << "derived2（保护继承）析构函数调用" << endl;
	}

	void testAccess() {
		cout << "derived2（保护继承）访问：" << endl;
		cout << "a=" << a;               
		cout << ", b=" << b;            
		cout << ", c=" << getC() << endl; 
	}
};

class derived3 : private base {
public:
	derived3(int a, int b, int c) : base(a, b, c) {
		cout << "derived3（私有继承）构造函数调用" << endl;
	}

	~derived3() {
		cout << "derived3（私有继承）析构函数调用" << endl;
	}

	void testAccess() {
		cout << "derived3（私有继承）访问：" << endl;
		cout << "a=" << a;              
		cout << ", b=" << b;           
		cout << ", c=" << getC() << endl; 
	}
};

int main0() {
	cout << "===== 1. 公有继承测试 =====" << endl;
	derived1 d1(1, 2, 3);
	d1.testAccess();
	cout << "类外访问derived1的a：" << d1.a << endl; 

	cout << "\n===== 2. 保护继承测试 =====" << endl;
	derived2 d2(4, 5, 6);
	d2.testAccess();

	cout << "\n===== 3. 私有继承测试 =====" << endl;
	derived3 d3(7, 8, 9);
	d3.testAccess();

	cout << "\n===== 4. 构造/析构顺序验证 =====" << endl;
	{
		derived1 temp(10, 20, 30);
	} 

	cout << "\n最终base对象总数：" << base::Manage() << endl;
	return 0;
}