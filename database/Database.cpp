#include "Database.h"

Database::Database()
{
	scale = 5;
	indexFile.open("index.txt", ios::in | ios::out | ios::binary | ios::trunc);
	dataFile.open("data.txt", ios::in | ios::out | ios::binary | ios::trunc);
	/*if (!indexFile)
	{*/
		indexFile.close();
		dataFile.close();
		ofstream index("index.txt", ios::binary);
		ofstream data("data.txt", ios::binary);
		int firstEmpty = 8 + 12 + 8 * scale + 4;
		index.write((char *)(&ZERO), sizeof(int));
		index.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
		for (int i = 0; i < 5; ++i)
			index.write((char *)(&ZERO), sizeof(int));
		firstEmpty = 4;
		data.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
		cout << "index and data file initialize complete." << endl;
		index.close();
		data.close();
		indexFile.open("index.txt", ios::in | ios::out | ios::binary);
		dataFile.open("data.txt", ios::in | ios::out | ios::binary);
		if (!dataFile)cout << "error" << endl;
	//}
}

void Database::dataFile_find(const int dataAddress, string &value)
{
	char tmp[20];
	dataFile.clear();
	dataFile.seekg(dataAddress, ios::beg);
	dataFile.read((char *)tmp, 20);
	value = tmp;
	cout << "dataFile_find dataAddress:" << dataAddress << " value:" << value << " tmp:" << tmp << endl;
}

int Database::dataFile_add(const string &value)
{
	int dataAddress, next = 0;
	dataFile.seekg(0, ios::beg);
	dataFile.read(reinterpret_cast<char *>(&dataAddress), sizeof(int));
	dataFile.seekg(dataAddress, ios::beg);
	dataFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	dataFile.clear();
	dataFile.seekp(dataAddress, ios::beg);
	dataFile.write(value.c_str(), value.size() + 1);
	dataFile.seekg(dataAddress, ios::beg);
	if (next == 0)
		next = dataAddress + 20;
	dataFile.seekp(0, ios::beg);
	dataFile.write(reinterpret_cast<char *>(&next), sizeof(int));
	cout << "dataFile_add value:" << value << " dataAddress:" << dataAddress << " next:" << next << endl;
	return dataAddress;
}

void Database::dataFile_delete(const int dataAddress)
{
	int next;
	dataFile.seekg(0);
	dataFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	dataFile.seekp(0);
	dataFile.write((char *)(&dataAddress), sizeof(int));
	dataFile.seekp(dataAddress);
	dataFile.write(reinterpret_cast<char *>(&next), sizeof(int));
}

void Database::dataFile_replace(const int dataAddress, string &value)
{
	dataFile.seekp(dataAddress);
	dataFile.write(value.c_str(), value.size());
}

int Database::indexFile_find(int key, int *indexAddress, int *pos, int *dataAddress)
{
	int next = 0;
	int begin, end, middle, last;
	int tmp, size;
	indexFile.clear();
	indexFile.seekg(0, ios::beg);
	indexFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	if (next == 0)
	{
		*indexAddress = 8;
		*pos = 0;
		return 0;
	}
	while (next > 0)
	{
		indexFile.clear();
		indexFile.seekg(next + 8);
		indexFile.read(reinterpret_cast<char *>(&size), sizeof(int));
		begin = 1;
		end = size;
		do
		{
			middle = (begin + end) / 2;
			indexFile.seekg(next + 12 + 8 * (middle - 1));
			indexFile.read(reinterpret_cast<char *>(&tmp), sizeof(int));
			cout << "[indexFile_find] middle:" << middle << " tmp:" << tmp << endl;
			if (tmp == key)
				begin = end = middle;
			else if (tmp > key)
				end = middle;
			else
				begin = middle;
		} while ((end - begin) > 1);
		cout << "[indexFile_find] key:" << key << " address:" << next << " begin:" << begin << " end:" << end << " middle:" << middle << " tmp:" << tmp << " size:" << size << endl;
		if (end == size)
		{
			indexFile.seekg(next + 12 + 8 * (size - 1));
			indexFile.read(reinterpret_cast<char *>(&last), sizeof(int));
			if (key >= last)
				begin = size;
		}
		indexFile.seekg(next + 12 + 8 * (begin - 1) + 4);
		indexFile.read(reinterpret_cast<char *>(&next), sizeof(int));
	}
	if (tmp == key)
	{
		*indexAddress = (int)indexFile.tellg() - 8 * middle - 12;
		*pos = middle;
		*dataAddress = -next;
		return 1;
	}
	if (key < tmp && begin == 1)
	{
		int first;
		indexFile.seekg(-8, ios::cur);
		indexFile.read(reinterpret_cast<char *>(&first), sizeof(int));
		if (key == first)
		{
			indexFile.read(reinterpret_cast<char *>(dataAddress), sizeof(int));
			*indexAddress = (int)indexFile.tellg() - 8 * begin - 12;
			*pos = begin;
			*dataAddress = -*dataAddress;
			return 1;
		}
		if (key < first)
		{
			*indexAddress = (int)indexFile.tellg() + 4 - 8 * 1 - 12;
			*pos = 0;
			return 0;
		}
	}
	if (begin == size)
	{
		*indexAddress = (int)indexFile.tellg() - 8 * size - 12;
		*pos = size;
		if (last == key)
		{
			*dataAddress = -next;
			return 1;
		}
		return 4;
	}
	/*if (key > tmp && end == size)
	{
		if (size == 1)
		{
			*indexAddress = (int)indexFile.tellg() - 8 * size - 12;
			*pos = size;
			return 4;
		}
		indexFile.read(reinterpret_cast<char *>(&last), sizeof(int));
		cout << "indexFile_find last:" << last << endl;
		if (key == last)
		{
			indexFile.read(reinterpret_cast<char *>(dataAddress), sizeof(int));
			*indexAddress = (int)indexFile.tellg() - 8 * size - 12;
			*pos = size;
			*dataAddress = -*dataAddress;
			return 1;
		}
		if (key > last)
		{
			*indexAddress = (int)indexFile.tellg() + 4 - 8 * size - 12;
			*pos = size;
			return 4;
		}
	}*/
	*indexAddress = (int)indexFile.tellg() - 8 * middle - 12;
	*pos = begin;
	return 2;
}

void Database::indexFile_add(const int key, const int dataAddress, const int indexAddress, int pos, int size)
{
	cout << "indexFile_add key:" << key << " dataAddress:" << dataAddress << " indexAddress:" << indexAddress << " pos:" << pos << " size:" << size << endl;
	int curKey, curPoint;
	for (int i = size; i > pos; --i)
	{
		indexFile.seekg(indexAddress + 12 + 8 * (i - 1), ios::beg);
		indexFile.read(reinterpret_cast<char *>(&curKey), sizeof(int));
		indexFile.read(reinterpret_cast<char *>(&curPoint), sizeof(int));
		indexFile.seekp(indexFile.tellg(), ios::beg);
		indexFile.write(reinterpret_cast<char *>(&curKey), sizeof(int));
		indexFile.write(reinterpret_cast<char *>(&curPoint), sizeof(int));
	}
	indexFile.seekp(indexAddress + 12 + 8 * pos);
	indexFile.write((char *)(&key), sizeof(int));
	indexFile.write((char *)(&dataAddress), sizeof(int));
	size += 1;
	indexFile.seekp(indexAddress + 8);
	indexFile.write(reinterpret_cast<char *>(&size), sizeof(int));
	if (pos == 0)
	{
		int parent = 0;
		indexFile.seekg(indexAddress);
		indexFile.read(reinterpret_cast<char *>(&parent), sizeof(int));
		if (parent == 0)
		{
			indexFile.seekp(0);
			indexFile.write((char *)(&indexAddress), sizeof(int));
		}
		else
		{
			while (parent > 0)
			{
				indexFile.seekg(parent, ios::beg);
				indexFile.read(reinterpret_cast<char *>(&parent), sizeof(int));
				indexFile.seekp(parent + 12, ios::beg);
				indexFile.write((char *)(&key), sizeof(int));
			}
		}
	}
	if (dataAddress > 0)
	{
		pos += 1;
		indexFile.seekp(dataAddress);
		indexFile.write((char *)(&indexAddress), sizeof(int));
		indexFile.write((char *)(&pos), sizeof(int));
	}
}

void Database::indexFile_addAndOverflow(const int key, const int dataAddress, const int indexAddress, const int pos, const int size)
{
	cout << "indexFile_addAndOverflow key:" << key << " dataAddress:" << dataAddress << " indexAddress:" << indexAddress << " pos:" << pos << " size:" << size << endl;
	if (size < scale)
		indexFile_add(key, dataAddress, indexAddress, pos, size);
	else
	{
		int middle = scale / 2 + 1;
		int rightSize = scale - middle + 1, leftSize;
		int *index, *data;
		int firstEmpty, nextEmpty = 0;
		int parent = 0, parentPositon = 0, parentSize = 0;
		index = new int[rightSize];
		data = new int[rightSize];
		if (pos < middle)
		{
			indexFile.seekg(indexAddress + 12 + 8 * (middle - 1));
			for (int i = 0; i < rightSize; ++i)
			{
				indexFile.read(reinterpret_cast<char *>(index[i]), sizeof(int));
				indexFile.read(reinterpret_cast<char *>(data[i]), sizeof(int));
			}
			leftSize = scale - rightSize;
			indexFile.seekp(indexAddress + 8);
			indexFile.write(reinterpret_cast<char *>(&leftSize), sizeof(int));
			indexFile_add(key, dataAddress, indexAddress, pos, leftSize);	
		}
		else
		{
			indexFile.seekg(indexAddress + 12 + 8 * middle, ios::beg);
			for (int i = 0; i < rightSize; ++i)
			{
				if (i == pos - middle)
				{
					index[i] = key;
					data[i] = dataAddress;
				}
				else
				{
					indexFile.read(reinterpret_cast<char *>(&index[i]), sizeof(int));
					indexFile.read(reinterpret_cast<char *>(&data[i]), sizeof(int));
				}
			}
			leftSize = scale + 1 - rightSize;
			indexFile.seekp(indexAddress + 8);
			indexFile.write(reinterpret_cast<char *>(&leftSize), sizeof(int));
		}
		for (int i = 0; i < rightSize; ++i)
		{
			cout << "[indexFile_addAndOverflow] index[" << i << "]:" << index[i] << endl;
			cout << "[indexFile_addAndOverflow] data[" << i << "]:" << data[i] << endl;
		}
		indexFile.clear();
		indexFile.seekg(4, ios::beg);
		indexFile.read(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
		indexFile.seekg(firstEmpty);
		indexFile.read(reinterpret_cast<char *>(&nextEmpty), sizeof(int));
		if (nextEmpty == 0)
			nextEmpty = firstEmpty + 12 + 8 * scale + 4;
		indexFile.clear();
		indexFile.seekp(firstEmpty + 8);
		indexFile.write(reinterpret_cast<char *>(&rightSize), sizeof(int));
		for (int i = 0; i < rightSize; ++i)
		{
			indexFile.write(reinterpret_cast<char *>(&index[i]), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&data[i]), sizeof(int));
		}
		indexFile.seekp(4);
		indexFile.write(reinterpret_cast<char *>(&nextEmpty), sizeof(int));
		cout << "indexFile_addAndOverflow new node firstEmpty:" << firstEmpty << " nextEmpty:" << nextEmpty << endl;
		if (dataAddress > 0)
		{
			for (int i = 1; i <= rightSize; ++i)
			{
				indexFile.seekp(data[i]);
				indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
				indexFile.write(reinterpret_cast<char *>(&i), sizeof(int));
			}
		}
		else
		{
			int nextLeaf = 0;
			indexFile.seekg(indexAddress + 12 + 8 * scale);
			indexFile.read(reinterpret_cast<char *>(&nextLeaf), sizeof(int));
			indexFile.seekp(indexAddress + 12 + 8 * scale);
			indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
			indexFile.seekp(firstEmpty + 12 + 8 * scale);
			indexFile.write(reinterpret_cast<char *>(&nextLeaf), sizeof(int));
			cout << "[indexFile_addAndOverflow] currentLeaf:" << firstEmpty << " nextLeaf:" << nextLeaf << endl;
		}
		indexFile.seekg(indexAddress);
		indexFile.read(reinterpret_cast<char *>(&parent), sizeof(int));
		if (parent == 0)
		{
			int left;
			int leftChild = indexAddress;
			int right = index[0];
			int rightChild = firstEmpty;
			int rootSize = 2;
			nextEmpty = 0;
			indexFile.clear();
			indexFile.seekg(indexAddress + 12);
			indexFile.read(reinterpret_cast<char *>(&left), sizeof(int));
			indexFile.seekg(4);
			indexFile.read(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
			indexFile.seekg(firstEmpty);
			indexFile.read(reinterpret_cast<char *>(&nextEmpty), sizeof(int));
			if (nextEmpty == 0)
				nextEmpty = firstEmpty + 12 + 8 * scale + 4;
			indexFile.clear();
			indexFile.seekp(firstEmpty);
			indexFile.write(reinterpret_cast<char *>(&parent), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&parentPositon), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&rootSize), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&left), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&leftChild), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&right), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&rightChild), sizeof(int));
			indexFile.clear();
			indexFile.seekp(0);
			indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&nextEmpty), sizeof(int));
			parentPositon = 1;
			indexFile.seekp(leftChild);
			indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&parentPositon), sizeof(int));
			parentPositon = 2;
			indexFile.seekp(rightChild);
			indexFile.write(reinterpret_cast<char *>(&firstEmpty), sizeof(int));
			indexFile.write(reinterpret_cast<char *>(&parentPositon), sizeof(int));
			cout << "[indexFile_addAndOverflow] newRoot:" << firstEmpty << " left:" << left << " leftChild:" << leftChild << " right:" << right << " rightChild:" << rightChild << " nextEmpty:" << nextEmpty << endl;
		}
		else
		{
			indexFile.read(reinterpret_cast<char *>(&parentPositon), sizeof(int));
			indexFile.seekg(parent + 8);
			indexFile.read(reinterpret_cast<char *>(&parentSize), sizeof(int));
			indexFile_addAndOverflow(index[0], firstEmpty, parent, parentPositon, parentSize);
		}
		delete[] index;
		delete[] data;
	}
}


bool Database::select(const int key, string &value)
{
	cout << endl << "SELECT key:" << key << endl;
	int indexAddress, pos, dataAddress;
	int result = indexFile_find(key, &indexAddress, &pos, &dataAddress);
	cout << "select find result:" << result << endl;
	if (result != 1)
		return false;
	dataFile_find(dataAddress, value);
	cout << "SELECT key:" << key << " indexAddress:" << indexAddress << " pos:" << pos << " dataAddress:" << dataAddress << " value:" << value << endl;
	return true;
}

bool Database::insert(const int key, const string &value)
{
	cout << endl << "INSERT key:" << key << " value:" << value << endl;
	string fvalue;
	int indexAddress, pos, dataAddress;
	int result = indexFile_find(key, &indexAddress, &pos, &dataAddress);
	cout << "insert find result:" << result << endl;
	if (result == 1)
		return false;
	int size;
	dataAddress = -dataFile_add(value);
	indexFile.seekg(indexAddress + 8, ios::beg);
	indexFile.read(reinterpret_cast<char *>(&size), sizeof(int));
	cout << "insert key:" << key << " dataAddress:" << dataAddress << " indexAddress:" << indexAddress << " pos:" << pos << " size:" << size << endl;
	indexFile_addAndOverflow(key, dataAddress, indexAddress, pos, size);
	return true;
}

Database::~Database()
{
	indexFile.close();
	dataFile.close();
}