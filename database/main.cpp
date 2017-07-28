#include <map>
#include "Database.h"

int main()
{
	ifstream fin("SimpleTestFile.txt");
	Database database;
	map<int, string> answer;
	int op, key;
	string value;
	int flag = true;
	map<int, string>::iterator it;
	while (fin >> op)
	{
		switch (op)
		{
			case 0:
				fin >> key;
				if (database.select(key, value))
				{
					if (answer.find(key) == answer.end())
					{
						cout << "error" << endl;
						cout << "Open log.txt to get more details.Test stop." << endl;
						flag = false;
					}
					else
					{
						if (value != answer[key])
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
					}
				}
				else
				{
					if (answer.find(key) != answer.end())
					{
						cout << "error" << endl;
						cout << "Open log.txt to get more details.Test stop." << endl;
						flag = false;
					}
				}
				break;
			case 1:
				fin >> key >> value;
				database.insert(key, value);
				answer[key] = value;
				break;
			case 2:
				fin >> key;
				database.remove(key);
				answer.erase(key);
				break;
			case 3:
				fin >> key >> value;
				database.update(key, value);
				answer[key] = value;
				break;
			case 4:
				for (it = answer.begin(); it != answer.end(); ++it)
				{
					if (!database.select(it->first, value))
					{
						cout << "error" << endl;
						cout << "Open log.txt to get more details.Test stop." << endl;
						flag = false;
						break;
					}
					else if (value != it->second)
					{
						cout << "error" << endl;
						cout << "Open log.txt to get more details.Test stop." << endl;
						flag = false;
						break;
					}
				}
				if (flag)
					cout << "pass" << endl;
				break;
			default:
				break;
		}
		if (!flag)
			break;
	}
	if (flag)
	{
		cout << "No problem found.Test manully." << endl;
		while (true)
		{
			cout << "0.SELECT" << endl;
			cout << "1.INSERT" << endl;
			cout << "2.REMOVE" << endl;
			cout << "3.UPDATE" << endl;
			cout << "4.TEST ALL" << endl;
			cout << "5.quit" << endl;
			cout << "Please input a number:";
			cin >> op;
			if (op == 5)
				break;
			switch (op)
			{
				case 0:
					cin >> key;
					if (database.select(key, value))
					{
						if (answer.find(key) == answer.end() || answer[key] != value)
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
							cout << "key:" << key << " value:" << value << endl;
					}
					else
					{
						if (answer.find(key) != answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
							cout << "key:" << key << " NOT FOUND" << endl;
					}
					break;
				case 1:
					cin >> key >> value;
					if (database.insert(key, value))
					{
						if (answer.find(key) != answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
						{
							cout << "INSERT key:" << key << " value:" << value << endl;
							answer[key] = value;
						}
					}
					else
					{
						if (answer.find(key) == answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
							cout << "INSERT key:" << key << " ALREADY EXISTS" << endl;
					}
					break;
				case 2:
					cin >> key;
					if (database.remove(key))
					{
						if (answer.find(key) == answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
						{
							cout << "REMOVE key:" << key << endl;
							answer.erase(key);
						}
					}
					else
					{
						if (answer.find(key) != answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
							cout << "REMMOVE key:" << key << " NOT FOUND" << endl;
					}
					break;
				case 3:
					cin >> key >> value;
					if (database.update(key, value))
					{
						if (answer.find(key) == answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
						{
							cout << "UPDATE key:" << key << " value:" << value << endl;
							answer.erase(key);
						}
					}
					else
					{
						if (answer.find(key) != answer.end())
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
						}
						else
							cout << "UPDATE key:" << key << " NOT FOUND" << endl;
					}
					break;
				case 4:
					for (it = answer.begin(); it != answer.end(); ++it)
					{
						if (!database.select(it->first, value))
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
							break;
						}
						else if (value != it->second)
						{
							cout << "error" << endl;
							cout << "Open log.txt to get more details.Test stop." << endl;
							flag = false;
							break;
						}
						else
							cout << "pass" << endl;
					}
					break;
				default:
					break;
			}
			if (!flag)
				break;
		}
	}
	cout << "Bye" << endl;
	return 0;
}