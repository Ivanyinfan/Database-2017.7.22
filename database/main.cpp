#include <map>
#include "Database.h"

int main()
{
	Database database;
	map<int, string> answer;
	ifstream fin("SimpleTestFile.txt");
	if (!fin)cout << "error" << endl;
	int op, key;
	string value;
	while (fin >> op)
	{
		switch (op)
		{
			case 1:
				fin >> key >> value;
				database.insert(key, value);
				answer[key] = value;
				break;
			default:
				break;
		}
	}
	map<int, string>::iterator it;
	for (it = answer.begin(); it != answer.end(); ++it)
	{
		if (!database.select(it->first, value))
		{
			cout << "error1" << endl;
			break;
		}
		else if (value != it->second)
		{
			cout << "error2" << endl;
			break;
		}
		else
			cout << "pass" << endl;
	}
	while (true)
	{
		cout << "Please:";
		cin >> op;
		if (op == 5)
			break;
		switch (op)
		{
			case 0:
				cin >> key;
				if (database.select(key, value))
					cout << "key:" << key << " value:" << value << endl;
				else
					cout << "key:" << key << " NOT FOUND" << endl;
				break;
			case 1:
				cin >> key >> value;
				if (database.insert(key, value))
				{
					cout << "INSERT key:" << key << " value:" << value << endl;
					answer[key] = value;
				}
				else
					cout << "INSERT key:" << key << " ALREADY EXISTS" << endl;
				break;
			case 2:
				cin >> key;
				if (database.remove(key))
				{
					cout << "REMOVE key:" << key << endl;
					answer.erase(key);
				}
				else
					cout << "REMOVE key:" << key << " NOT FOUND" << endl;
				break;
			case 3:
				break;
			case 4:
				for (it = answer.begin(); it != answer.end(); ++it)
				{
					if (!database.select(it->first, value))
					{
						cout << "error1" << endl;
						break;
					}
					else if (value != it->second)
					{
						cout << "error2" << endl;
						break;
					}
					else
						cout << "pass" << endl;
				}
				break;
			default:
				break;
		}
	}
	char c;
	cin >> c;
	return 0;
}
/*Cache cache;
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