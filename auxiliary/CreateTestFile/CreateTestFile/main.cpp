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
			fout << 1 << " " << -1 << " -1" << endl;//边界插入
			fout << 4 << endl;
			fout << 2 << " " << -1 << endl;//边界删除
			fout << 4 << endl;
			fout << 0 << " " << -1 << endl;//不存在查找
			fout << 0 << " " << 1 << endl;//存在查找
			fout << 1 << " " << 22 << " 22" << endl;
			fout << 4 << endl;
			fout << 1 << " " << 24 << " 24" << endl;
			fout << 4 << endl;
			fout << 1 << " " << 20 << " 20" << endl;//添加上溢一层
			fout << 4 << endl;
			fout << 1 << " " << 66 << " 66" << endl;//添加并上溢两层
			fout << 4 << endl;
			fout << 1 << " " << 64 << " 64" << endl;
			fout << 2 << " " << 69 << endl;//向左兄弟借
			fout << 4 << endl;
			fout << 2 << " " << 66 << endl;//与左兄弟合并，且父节点亦与左兄弟合并
			fout << 4 << endl;
			fout << 1 << " " << 10 << " 10" << endl;
			fout << 2 << " " << 1 << endl;//向右兄弟借
			fout << 4 << endl;
			fout << 2 << " " << 10 << endl;//与右兄弟合并，且父节点向右兄弟借
			fout << 4 << endl;
			for (int i = 3; i <= 7; i += 2)
			{
				fout << 2 << " " << i << endl;//父节点与右兄弟合并，删除根节点一个孩子
				fout << 4 << endl;
			}
			fout << 4 << endl;
			fout << 2 << " " << 64 << endl;
			fout << 4 << endl;
			for (int i = 67; i >= 53; i -= 2)
			{
				fout << 2 << " " << i << endl;//父节点向左借
				fout << 4 << endl;
			}
			fout << 4 << endl;
			for (int i = 51; i >= 19; i -= 2)//下溢一层
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
			for (int i = 1; i < 19; i += 2)//清空
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
			}//再次插入
			fout << 4 << endl;
			for (int i = 1; i < size * 2 + 1; i += 2)
			{
				length = rand() % 19 + 1;
				for (int j = 0; j < length; ++j)
					value[j] = rand() % 26 + 97;
				value[length] = '\0';
				fout << "3 " << i << " " << value << endl;
				fout << 4 << endl;
			}//更新
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