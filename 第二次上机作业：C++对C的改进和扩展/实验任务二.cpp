#include <iostream>
#include <cstring> // 用于处理字符串（可选，这里用指针遍历也可以不用）
using namespace std;

// 统计元音字母个数的函数
int countVowels(const char* p) {
	int count = 0;
	// 遍历字符串，直到遇到结束符'\0'
	while (*p != '\0') {
		// 判断当前字符是否是元音字母
		if (*p == 'a' || *p == 'e' || *p == 'i' || *p == 'o' || *p == 'u') {
			count++;
		}
		p++; // 指针移动到下一个字符
	}
	return count;
}

int main1() {
	char str[100]; // 定义字符数组存储输入的字符串
	cout << "请输入字符串：";
	cin.getline(str, 100); // 输入一行字符串（支持含空格的情况）

	// 调用函数并输出结果
	int result = countVowels(str);
	cout << "Number of vowels: " << result << endl;

	return 0;
}