#include <iostream>
#include <cmath>
using namespace std;

class Point2D {
private:
	double x, y; 
public:
	Point2D(double x = 0.0, double y = 0.0) : x(x), y(y) {
		cout << "Point2D构造函数调用" << endl;
	}

	~Point2D() {
		cout << "Point2D析构函数调用" << endl;
	}

	Point2D& move(double dx, double dy) {
		x += dx;
		y += dy;
		return *this;
	}

	void show() const {
		cout << "二维坐标：(" << x << ", " << y << ")" << endl;
	}

	friend double distance(const Point2D& p1, const Point2D& p2);

	double getX() const { return x; }
	double getY() const { return y; }
};

double distance(const Point2D& p1, const Point2D& p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return sqrt(dx * dx + dy * dy);
}

class Point3D : public Point2D {
private:
	double z;
public:
	Point3D(double x = 0.0, double y = 0.0, double z = 0.0) : Point2D(x, y), z(z) {
		cout << "Point3D构造函数调用" << endl;
	}

	~Point3D() {
		cout << "Point3D析构函数调用" << endl;
	}

	Point3D& move(double dx, double dy, double dz) {
		Point2D::move(dx, dy);
		z += dz;
		return *this;
	}

	void show() const {
		cout << "三维坐标：(" << getX() << ", " << getY() << ", " << z << ")" << endl;
	}

	friend double distance(const Point3D& p1, const Point3D& p2);

	double getZ() const { return z; }
};

double distance(const Point3D& p1, const Point3D& p2) {
	double dx = p2.getX() - p1.getX();
	double dy = p2.getY() - p1.getY();
	double dz = p2.z - p1.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

int main() {
	Point2D p2d1(1, 2), p2d2(4, 6);
	cout << "=====二维点测试=====" << endl;
	p2d1.show();
	p2d2.show();
	cout << "两点距离：" << distance(p2d1, p2d2) << endl;
	p2d1.move(2, 3).show(); 

	Point3D p3d1(1, 2, 3), p3d2(4, 6, 8);
	cout << "\n=====三维点测试=====" << endl;
	p3d1.show();
	p3d2.show();
	cout << "两点距离：" << distance(p3d1, p3d2) << endl;
	p3d1.move(2, 3, 4).show(); 
	return 0;
}