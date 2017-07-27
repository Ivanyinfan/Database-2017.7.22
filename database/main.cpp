#include "Database.h"

int main()
{
	Cache cache;
	int key = 0;
	string value;
	cache.insert(1, "test1", &key, &value);
	if (key != 0 || value != "")cout << "error" << endl;
	cache.insert(2, "test2", &key, &value);
	cache.insert(3, "test3", &key, &value);
	cache.insert(5, "test5", &key, &value);
	cache.insert(4, "test4", &key, &value);
	cache.insert(6, "test6", &key, &value);
	cache.insert(8, "test8", &key, &value);
	cache.insert(7, "test7", &key, &value);
	cache.insert(9, "test9", &key, &value);
	string value3 = "te";
	cache.update(1, value3);
	cache.insert(16385, "test", &key, &value);
	cout << key << value << endl;
	for (int i = 1; i <= 9; ++i)
	{
		if (!cache.select(i, value))
			cout << "error" << i << endl;
		else
			cout << value << endl;
	}
	cache.select(16385, value);
	cout << value << endl;
	value = "hehe";
	cache.update(9, value);
	vector<int> key2; vector<string> value2;
	cache.save(&key2, &value2);
	for (int i = 0; i < key2.size(); ++i)
	{
		cout << key2[i] << value2[i] << endl;
	}
	if (!cache.insert(2, value3, &key, &value))
		cout << "error" << endl;
	/*Database database;
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
	database.remove(8);
	for (int i = 1; i < 8; ++i)
	{
		if (database.select(i, value))
			cout << value << endl;
		else
		{
			cout << i << " error" << endl;
			break;
		}
	}
	database.remove(4);
	for (int i = 1; i < 8; ++i)
	{
		if (i == 4)
			continue;
		if (database.select(i, value))
			cout << value << endl;
		else
		{
			cout << i << " error" << endl;
			break;
		}
	}
	database.insert(8, "test8");
	database.remove(5);
	for (int i = 1; i <= 8; ++i)
	{
		if (i == 4 || i == 5)
			continue;
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
		cout << "-1" << " error" << endl;*/
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