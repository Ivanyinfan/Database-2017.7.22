#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int randN(int n);

int main()
{
	ofstream fout;
	int size;
	int length;
	char value[20];
	int op;
	srand(time(NULL));
	int randNum;
	while (true)
	{
		cout << "0.quit" << endl;
		cout << "1.correctnessTestFile" << endl;
		cout << "2.randomCorrectnessTestFile" << endl;
		cout << "Please select:";
		cin >> op;
		if (op == 0)
			break;
		switch (op)
		{
		case 1:
			fout.open("../../../database/SimpleTestFile.txt");
			size = 35;
			for (int i = 1; i < size * 2 + 1; i += 2)
			{
				length = rand() % 19 + 1;
				for (int j = 0; j < length; ++j)
					value[j] = rand() % 26 + 97;
				value[length] = '\0';
				fout << "1 " << i << " " << value << endl;
			}
			fout << 4 << endl;
			fout << 1 << " " << -1 << " -1" << endl;//�߽����
			fout << 4 << endl;
			fout << 2 << " " << -1 << endl;//�߽�ɾ��
			fout << 4 << endl;
			fout << 0 << " " << -1 << endl;//�����ڲ���
			fout << 0 << " " << 1 << endl;//���ڲ���
			fout << 1 << " " << 22 << " 22" << endl;
			fout << 4 << endl;
			fout << 1 << " " << 24 << " 24" << endl;
			fout << 4 << endl;
			fout << 1 << " " << 20 << " 20" << endl;//�������һ��
			fout << 4 << endl;
			fout << 1 << " " << 66 << " 66" << endl;//��Ӳ���������
			fout << 4 << endl;
			fout << 1 << " " << 64 << " 64" << endl;
			fout << 2 << " " << 69 << endl;//�����ֵܽ�
			fout << 4 << endl;
			fout << 2 << " " << 66 << endl;//�����ֵܺϲ����Ҹ��ڵ��������ֵܺϲ�
			fout << 4 << endl;
			fout << 1 << " " << 10 << " 10" << endl;
			fout << 2 << " " << 1 << endl;//�����ֵܽ�
			fout << 4 << endl;
			fout << 2 << " " << 10 << endl;//�����ֵܺϲ����Ҹ��ڵ������ֵܽ�
			fout << 4 << endl;
			for (int i = 3; i <= 7; i += 2)
			{
				fout << 2 << " " << i << endl;//���ڵ������ֵܺϲ���ɾ�����ڵ�һ������
				fout << 4 << endl;
			}
			fout << 4 << endl;
			fout << 2 << " " << 64 << endl;
			fout << 4 << endl;
			for (int i = 67; i >= 53; i -= 2)
			{
				fout << 2 << " " << i << endl;//���ڵ������
				fout << 4 << endl;
			}
			fout << 4 << endl;
			for (int i = 51; i >= 19; i -= 2)//����һ��
			{
				fout << 2 << " " << i << endl;
				fout << 4 << endl;
			}
			fout << 2 << " " << 24 << endl;
			fout << 4 << endl;
			fout << 2 << " " << 22 << endl;
			fout << 4 << endl;
			fout << 2 << " " << 20 << endl;
			fout << 4 << endl;
			for (int i = 1; i < 19; i += 2)//���
			{
				fout << 2 << " " << i << endl;
				fout << 4 << endl;
			}
			for (int i = 1; i < size * 2 + 1; i += 2)
			{
				length = rand() % 19 + 1;
				for (int j = 0; j < length; ++j)
					value[j] = rand() % 26 + 97;
				value[length] = '\0';
				fout << "1 " << i << " " << value << endl;
				fout << 4 << endl;
			}//�ٴβ���
			fout << 4 << endl;
			for (int i = 1; i < size * 2 + 1; i += 2)
			{
				length = rand() % 19 + 1;
				for (int j = 0; j < length; ++j)
					value[j] = rand() % 26 + 97;
				value[length] = '\0';
				fout << "3 " << i << " " << value << endl;
				fout << 4 << endl;
			}//����
			fout.close();
			break;
		case 2:
			fout.open("../../../database/randomTestFile.txt");
			for (int i = 0; i < 1000; ++i)
			{
				randNum = randN(4);
				length = rand() % 19 + 1;
				for (int j = 0; j < length; ++j)
					value[j] = rand() % 26 + 97;
				value[length] = '\0';
				fout << "1 " << randNum << " " << value << endl;
			}
			fout << 4 << endl;
			for (int i = 0; i < 100; ++i)
			{
				randNum = randN(4);
				fout << "0 " << randNum << endl;
			}
			for (int i = 0; i < 100; ++i)
			{
				randNum = randN(4);
				fout << "2 " << randNum << endl;
			}
			fout << 4 << endl;
			for (int i = 0; i < 100; ++i)
			{
				randNum = randN(4);
				length = rand() % 19 + 1;
				for (int j = 0; j < length; ++j)
					value[j] = rand() % 26 + 97;
				value[length] = '\0';
				fout << "3 " << randNum << " " << value << endl;
			}
			fout << 4 << endl;
			fout.close();
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	}
	return 0;
}

int randN(int n)
{
	int result = 0;
	for (int i = 0; i < n; ++i)
		result = result * 10 + rand() % 10;
	return result;
}