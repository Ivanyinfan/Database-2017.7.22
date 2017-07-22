#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
using namespace std;

class Database
{
public:
	Database();
	Database(int scale);
	~Database();
private:
	int scale;
};

#endif // !DATABASE_H
