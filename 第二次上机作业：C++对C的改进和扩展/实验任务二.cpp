#include <iostream>
#include <cstring> // ���ڴ����ַ�������ѡ��������ָ�����Ҳ���Բ��ã�
using namespace std;

// ͳ��Ԫ����ĸ�����ĺ���
int countVowels(const char* p) {
	int count = 0;
	// �����ַ�����ֱ������������'\0'
	while (*p != '\0') {
		// �жϵ�ǰ�ַ��Ƿ���Ԫ����ĸ
		if (*p == 'a' || *p == 'e' || *p == 'i' || *p == 'o' || *p == 'u') {
			count++;
		}
		p++; // ָ���ƶ�����һ���ַ�
	}
	return count;
}

int main1() {
	char str[100]; // �����ַ�����洢������ַ���
	cout << "�������ַ�����";
	cin.getline(str, 100); // ����һ���ַ�����֧�ֺ��ո�������

	// ���ú�����������
	int result = countVowels(str);
	cout << "Number of vowels: " << result << endl;

	return 0;
}