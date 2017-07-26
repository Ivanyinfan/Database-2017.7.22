#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Database
{
public:
	Database();
	void dataFile_find(const int dataAddress, string &value);
	int dataFile_add(const string &value);
	void dataFile_delete(const int dataAddress);
	void dataFile_replace(const int dataAddress, string &value);
	int indexFile_find(int key, int *indexAddress, int *pos, int *dataAddress);
	void indexFile_add(const int key, const int dataAddress, const int indexAddress, int pos, int size);
	void indexFile_addAndOverflow(const int key, const int dataAddress, const int indexAddress, const int pos, const int size);
	bool select(const int key, string &value);
	bool insert(const int key, const string &value);
	bool remove(const int key);
	bool update(const int key, const string &value);
	~Database();
private:
	int scale;
	fstream indexFile, dataFile;
	const int ZERO = 0;
	const char END = '\0';
};

#endif // !DATABASE_H
