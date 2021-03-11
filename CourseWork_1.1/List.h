#pragma once
#include <iostream>
#include <fstream>
#include "DataBase.h"
#include "Integer.h"
using namespace std;

class List : public fstream {
public:
	int prev, next;
	int start = 22;
public:
	int getCount();
	int getSum();
	void setSum(int);
	void setCount(int);
	int getStart();
	void setStart(int);
	int getLastStreamPos();
	void setLastStreamPos(int);
	void WriteInt(int, int&);
	void WriteCharP(char*, int&);
	void WriteDouble(double, int&);
	void WriteLongLong(long long, int&);
	void WriteBool(bool, int&);

	bool ReadBool(int&);
	int ReadInt(int&);
	char* ReadCharP(int&);
	double ReadDouble(int&);
	long long ReadLongLong(int&);


	void Compression();
	void Delete(int);
	void ShowDataBase();
	void ShowInteger();
	void Add(DataBase&);//Вставка в конец
	void SortInsert(DataBase&);
	void Add(Integer&);//Вставка в конец
	void Editor(DataBase&, int position);//Изменение записи по номеру
	void Editor(Integer&, int position);//Изменение записи по номеру
	void Insert(DataBase&, int position);//Вставка со смещением (номер position - перед какой записью будет вставлен новый элемент)
	void Insert(Integer&, int position);//Добавление в конец через функцию Add
	void SortDataBase();
	List();
	~List();
};