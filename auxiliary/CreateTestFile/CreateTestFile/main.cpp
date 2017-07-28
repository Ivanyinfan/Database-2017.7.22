#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

int main()
{
	ofstream fout("D:/Microsoft Visual Studio/2017/Community/Projects/database/database/SimpelTestFile.txt");
	srand(time(NULL));
	int size = pow(5, 3);
	int length;
	char value[20];
	for (int i = 1; i < size * 2 + 1; i += 2)
	{
		length = rand() % 19 + 1;
		for (int i = 0; i < length; ++i)
			value[i] = rand() % 26 + 97;
		value[length] = '\0';
		fout << "1 " << i << " " << value << endl;
	}
	fout.close();
	return 0;
}