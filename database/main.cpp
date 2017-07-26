#include "Database.h"

int main()
{
	Database database;
	string value = "test1";
	database.insert(1, value);
	database.insert(2, "test2");
	database.insert(3, "test3");
	database.insert(5, "test5");
	database.insert(4, "test4");
	database.insert(6, "test6");
	database.insert(8, "test8");
	database.insert(7, "test7");
	database.insert(-1, "test9");
	for (int i = 1; i < 9; ++i)
	{
		if (database.select(i, value))
			cout << value << endl;
		else
		{
			cout << i << " error" << endl;
			break;
		}
	}
	if (database.select(-1, value))
		cout << value << endl;
	else
		cout << "-1" << " error" << endl;
	char c;
	cin >> c;
	return 0;
}

/*fstream f("C:/Users/lenovo/Desktop/index.txt", ios::binary | ios::in | ios::out);
int x;
f.seekg(0);
while (!f.eof())
{
x = 0;
f.read((char *)(&x), 1);
cout << x << endl;
}*/

/*
	fstream test("test.txt");
	string h = "test";
	char b[20];
	test.seekp(0);
	test.write(h.c_str(), h.size());
	test.seekg(0);
	test.getline(b, 20, '\0');
	cout << b << endl;
*/

/*
ifstream index("index.txt", ios::binary);
ifstream data("data.txt", ios::binary);
int test;
data.read(reinterpret_cast<char *>(&test), sizeof(int));
cout << test << endl;
index.close();
data.close();
*/