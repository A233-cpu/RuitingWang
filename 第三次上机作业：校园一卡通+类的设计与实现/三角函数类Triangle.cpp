#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
    double a, b, c; 

public:
    void Init(double sideA, double sideB, double sideC) {
        a = sideA;
        b = sideB;
        c = sideC;
    }

    bool IsTriangle() {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }//判断是否能构成三角形


    double GetSideA() { return a; }    // 读取边长a

    void SetSideA(double sideA) { a = sideA; }    // 设置边长a


    double GetSideB() { return b; }    // 读取边长b

    void SetSideB(double sideB) { b = sideB; }    // 设置边长b


    double GetSideC() { return c; }    // 读取边长c

    void SetSideC(double sideC) { c = sideC; }    // 设置边长c


    double Perimeter() {
        return IsTriangle() ? (a + b + c) : 0;
    }    // 计算周长


    double Area() {
        if (!IsTriangle()) return 0;
        double p = Perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }    // 计算面积（海伦公式）


    int TypeTriangle() {
        if (!IsTriangle()) return 0;

        // 确定最长边
        double maxSide = max(a, max(b, c));
        double other1, other2;
        if (maxSide == a) {
            other1 = b;
            other2 = c;
        } else if (maxSide == b) {
            other1 = a;
            other2 = c;
        } else {
            other1 = a;
            other2 = b;
        } 

        // 计算平方关系
        double sumSquare = other1 * other1 + other2 * other2;
        double maxSquare = maxSide * maxSide;

        if (sumSquare == maxSquare) {
            return 1; // 直角
        } else if (sumSquare > maxSquare) {
            return 2; // 锐角
        } else {
            return 3; // 钝角
        }
    }   // 判断三角形类型：1-直角，2-锐角，3-钝角，0-非三角形
};

int main() {
    Triangle t;
    t.Init(3, 4, 5);
    
    cout << "是否为三角形：" << (t.IsTriangle() ? "是" : "否") << endl;
    cout << "周长：" << t.Perimeter() << endl;
    cout << "面积：" << t.Area() << endl;
    
    int type = t.TypeTriangle();
    cout << "三角形类型：";
    switch(type) {
        case 1: cout << "直角三角形"; break;
        case 2: cout << "锐角三角形"; break;
        case 3: cout << "钝角三角形"; break;
        default: cout << "非三角形";
    }
    cout << endl;

    return 0;
}
