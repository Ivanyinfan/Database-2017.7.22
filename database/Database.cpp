#include "Database.h"

Database::Database()
{
	scale = 3;
	indexFile.open("index.txt", ios::app | ios::binary);
	dataFile.open("data.txt", ios::app | ios::binary);
	int firstEmpty;
	dataFile.seekg(0,ios::beg);
	dataFile.read(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
	if (firstEmpty == 0)
	{
		dataFile.seekp(0, ios::beg);
		dataFile << 4;
	}
}

int Database::find(int key, string &value, int *indexAddress, int *pos, int *dataAddress, bool needValue)
{
	int next;
	int begin, end, middle;
	int tmp, size;
	indexFile.seekg(0, ios::beg);
	indexFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	if (next == 0)
	{
		*indexAddress = 20;
		*pos = 0;
		return 0;
	}
	while (next > 0)
	{
		indexFile.seekg(next + 8);
		indexFile.read(reinterpret_cast<char *>(&size), sizeof(int));
		begin = 1;
		end = size;
		do
		{
			middle = (begin + end) / 2;
			indexFile.seekg(next + 12 + 8 * (middle - 1));
			indexFile.read(reinterpret_cast<char *>(&tmp), sizeof(int));
			if (tmp > key)
				end = middle;
			else
				begin = middle;
		} while ((end - begin) > 1);
		indexFile.seekg(next + 12 + 8 * (begin - 1) + 4);
		indexFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	}
	if (tmp == key)
	{
		*indexAddress = (int)indexFile.tellg() - 8 * middle - 12;
		*pos = middle;
		*dataAddress = -next;
		if (needValue)
		{
			dataFile.seekg(-next, ios::beg);
			dataFile >> value;
		}
		return 1;
	}
	if (key < tmp && begin == 1)
	{
		int first;
		indexFile.seekg(-8, ios::cur);
		indexFile.read(reinterpret_cast<char *>(&first), sizeof(int));
		if (key < first)
		{
			*indexAddress = (int)indexFile.tellg() + 4 - 8 * 1 - 12;
			*pos = 0;
			return 0;
		}
	}
	if (key > tmp && end == size)
	{
		int last;
		indexFile.read(reinterpret_cast<char *>(&last), sizeof(int));
		if (key > last)
		{
			*indexAddress = (int)indexFile.tellg() + 4 - 8 * size - 12;
			*pos = size;
			return 4;
		}
	}
	*indexAddress = (int)indexFile.tellg() - 8 * middle - 12;
	*pos = begin;
	return 2;
}

int Database::dataFile_add(const string &value)
{
	int dataAddress, next;
	dataFile.seekg(0, ios::beg);
	dataFile.read(reinterpret_cast<char *>(&dataAddress), sizeof(int));
	dataFile.seekg(dataAddress, ios::beg);
	dataFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	dataFile.seekp(dataAddress, ios::beg);
	dataFile.write(value.c_str(), value.size());
	dataFile.seekp(0, ios::beg);
	if (next == 0)
		next = dataAddress + 20;
	dataFile.write(reinterpret_cast<char *>(&next), sizeof(int));
	return dataAddress;
}

void Database::indexFile_add(const int key, const int dataAddress, const int indexAddress, const int pos, int size)
{
	int curKey, curPoint;
	for (int i = size - pos; i > 0; --i)
	{
		indexFile.seekg(indexAddress + 8 * (size - pos), ios::beg);
		indexFile.read(reinterpret_cast<char *>(&curKey), sizeof(int));
		indexFile.read(reinterpret_cast<char *>(&curPoint), sizeof(int));
		indexFile.seekp(indexFile.tellg());
		indexFile.write(reinterpret_cast<char *>(&curKey), sizeof(int));
		indexFile.write(reinterpret_cast<char *>(&curPoint), sizeof(int));
	}
	indexFile.seekp(indexAddress);
	indexFile.write((char *)(&key), sizeof(int));
	indexFile.write((char *)(&dataAddress), sizeof(int));
	size += 1;
	indexFile.seekp(indexAddress - 8 * pos - 4);
	indexFile.write(reinterpret_cast<char *>(&size), sizeof(int));
	if (pos == 0)
	{
		int parent;
		indexFile.seekg(indexAddress - 8 * pos - 12);
		indexFile.read(reinterpret_cast<char *>(&parent), sizeof(int));
		while (parent > 0)
		{
			indexFile.seekg(parent, ios::beg);
			indexFile.read(reinterpret_cast<char *>(&parent), sizeof(int));
			indexFile.seekp(parent + 12, ios::beg);
			indexFile.write((char *)(&key), sizeof(int));
		}
	}
}

void Database::indexFile_addAndOverflow(const int key, const int dataAddress, const int indexAddress, const int pos, const int size)
{
	if (size < scale)
		indexFile_add(key, dataAddress, indexAddress, pos, size);
	else
	{
		int middle = scale / 2 + 1;
		int size = scale - middle + 1;
		int *index, *data;
		int firstEmpty, nextEmpty;
		int parent, parentPositon;
		indexFile.seekg(4, ios::beg);
		indexFile.read(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
		index = new int[size];
		data = new int[size];
		indexFile.seekg(indexAddress - 8 * pos - 12);
		indexFile.read(reinterpret_cast<char *>
		if (pos < middle)
		{
			indexFile.seekg(indexAddress + 8 * (middle - pos - 1));
			for (int i = 0; i < size; ++i)
			{
				indexFile.read(reinterpret_cast<char *>(index[i]), sizeof(int));
				indexFile.read(reinterpret_cast<char *>(data[i]), sizeof(int));
			}
			indexFile_add(key, dataAddress, indexAddress, pos, middle - 1);	
		}
		else
		{
			indexFile.seekg(indexAddress + 8 * (middle - pos), ios::beg);
			for (int i = 0; i < size; ++i)
			{
				if (i == pos - middle)
				{
					index[i] = key;
					data[i] = dataAddress;
				}
				else
				{
					indexFile.read(reinterpret_cast<char *>(index[i]), sizeof(int));
					indexFile.read(reinterpret_cast<char *>(data[i]), sizeof(int));
				}
			}
		}
		indexFile.seekg(firstEmpty);
		indexFile.read(reinterpret_cast<char *>(&nextEmpty), sizeof(int));
		indexFile.seekp(firstEmpty + 8);
		indexFile.write(reinterpret_cast<char *>(&size), sizeof(int));
		for (int i = 0; i < size; ++i)
		{
			indexFile.write(reinterpret_cast<char *>(index[i]), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(data[i]), sizeof(int));
		}
		if (nextEmpty == 0)
			nextEmpty = firstEmpty + 12 + 8 * scale + 4;
		indexFile.seekp(4);
		indexFile.write(reinterpret_cast<char *>(&nextEmpty), sizeof(int));
		if (dataAddress > 0)
		{
			for (int i = 1; i <= size; ++i)
			{
				indexFile.seekp(data[i]);
				indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
				indexFile.write(reinterpret_cast<char *>(&i), sizeof(int));
			}
		}
		else
		{
			int nextLeaf;
			indexFile.seekg(indexAddress + 8 * (scale - pos));
			indexFile.read(reinterpret_cast<char *>(&nextLeaf), sizeof(int));
			indexFile.seekp(indexAddress + 8 * (scale - pos));
			indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
			indexFile.seekp(firstEmpty + 12 + 8 * scale);
			indexFile.write(reinterpret_cast<char *>(&nextLeaf), sizeof(int));
		}
		indexFile_addAndOverflow(index[0],data[0],)
	}
}

bool Database::insert(const int key, const string &value)
{
	string fvalue;
	int indexAddress, pos, dataAddress;
	int result = find(key, fvalue, &indexAddress, &pos, &dataAddress, false);
	if (result == 1)
		return false;
	int size;
	dataAddress = -dataFile_add(value);
	indexFile.seekg(indexAddress - 8 * pos - 4, ios::beg);
	indexFile.read(reinterpret_cast<char *>(&size), sizeof(int));
	if (size < scale - 1)
		indexFile_add(key, dataAddress, indexAddress, pos, size);
	else{}
}
