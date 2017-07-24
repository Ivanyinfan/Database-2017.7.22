#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

fstream initializeFile(string filename);

class Database
{
public:
	Database();
	Database(int scale);
	int find(int key, string &value, int *indexAddress, int *pos,int *address, bool needValue);
	int dataFile_add(const string &value);
	void indexFile_add(const int key, const int dataAddress, const int indexAddress, const int pos, int size);
	void indexFile_addAndOverflow(const int key, const int dataAddress, const int indexAddress, const int pos, const int size);
	bool insert(const int key, const string &value);
	bool remove(const int key);
	bool update(const int key, const string &value);
	~Database();
private:
	int scale;
	fstream indexFile, dataFile;
};

#endif // !DATABASE_H
