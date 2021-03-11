#pragma once
#include <iostream>
#include "List.h"
#include "DataBase.h"
#include "Integer.h"
#include <iostream>
using namespace std;

int List::getCount() {
	int count, i;
	i = tellp();
	seekg(4, ios::beg);
	read((char*)(&count), sizeof(int));
	seekg(i, ios::beg);
	return count;
}

int List::getSum() {
	int count, i;
	i = tellp();
	seekg(12, ios::beg);
	read((char*)(&count), sizeof(int));
	seekg(i, ios::beg);
	return count;
}

void List::setSum(int count) {
	int i = tellp();
	seekg(12, ios::beg);
	write((char*)(&count), sizeof(int));
	seekg(i, ios::beg);
}

void List::setCount(int count) {
	int i = tellp();
	seekg(4, ios::beg);
	write((char*)(&count), sizeof(int));
	seekg(i, ios::beg);
}

void List::setStart(int start) {
	int i = tellp();
	seekg(0, ios::beg);
	write((char*)(&start), sizeof(int));
	seekg(i, ios::beg);
}

int List::getStart() {
	int start, i;
	i = tellp();
	seekg(0, ios::beg);
	read((char*)(&start), sizeof(int));
	seekg(i, ios::beg);
	return start;
}

void List::setLastStreamPos(int last) {
	int i = tellp();
	seekg(8, ios::beg);
	write((char*)(&last), sizeof(int));
	seekg(i, ios::beg);
}

int List::getLastStreamPos() {
	int last, i;
	i = tellp();
	seekg(8, ios::beg);
	read((char*)(&last), sizeof(int));
	seekg(i, ios::beg);
	return last;
}

void List::WriteInt(int i, int &pos) {
	seekg(pos, ios::beg);
	write((char*)(&i), sizeof(int));
	pos = tellp();
}

void List::WriteBool(bool i, int& pos) {
	seekg(pos, ios::beg);
	write((char*)(&i), sizeof(bool));
	pos = tellp();
}

void List::WriteCharP(char* i, int& pos) {	
	seekg(pos, ios::beg);
	write((char*)(&i), sizeof(i));	
	pos = tellp();
}

void List::WriteDouble(double i, int& pos) {
	seekg(pos, ios::beg);
	write((char*)(&i), sizeof(double));
	pos = tellp();
}

void List::WriteLongLong(long long i, int& pos) {
	seekg(pos, ios::beg);
	write((char*)(&i), sizeof(long long));
	pos = tellp();
}

bool List::ReadBool(int& pos) {
	bool iint;
	seekg(pos, ios::beg);
	read((char*)(&iint), sizeof(bool));
	pos = tellp();
	return iint;
}

int List::ReadInt(int& pos) {
	int iint;
	seekg(pos, ios::beg);
	read((char*)(&iint), sizeof(int));
	pos = tellp();
	return iint;
}

char* List::ReadCharP(int& pos) {
	char* cchar;
	seekg(pos, ios::beg);
	read((char*)(&cchar), sizeof(char*));
	pos = tellp();
	return cchar;
}

double List::ReadDouble(int& pos) {
	double ddouble;
	seekg(pos, ios::beg);
	read((char*)(&ddouble), sizeof(double));
	pos = tellp();
	return ddouble;
}

long long List::ReadLongLong(int& pos) {
	long long llong;
	seekg(pos, ios::beg);
	read((char*)(&llong), sizeof(long long));
	pos = tellp();
	return llong;
}

void List::ShowDataBase() {
	DataBase object;
	object.ShowBin_DataBase(getStart());
}

void List::ShowInteger() {
	Integer ineger;
	ineger.ShowBin_Integer(getStart());
}

void List::Delete(int num_elem) {	
	int next_ = getStart();
	int pos, size, for_prev, pos_next;
	if (num_elem == 1) {//удаление из начала
		pos = next_;
		pos -= 4;
		next_ = ReadInt(pos);
		setStart(next_);
		seekg(next_, ios::beg);
		pos = tellg();
		size = ReadInt(pos);
		pos += size;
		
		WriteInt(-111, pos);
	}
	else if (num_elem == getCount()) {//удаление из конца
		int _prev_;
		for (int i = 1; i < num_elem; i++) {
			seekg(next_, ios::beg);
			pos = tellg();
			pos -= 4;
			next_ = ReadInt(pos);
		}
		prev = pos;
		pos -= 4;
		WriteInt(-101, pos);
	}
	else if (num_elem > 0 && num_elem < getCount()) {
		for (int i = 1; i < num_elem; i++) {
			seekg(next_, ios::beg);
			pos = tellg();
			for_prev = tellg();
			pos -= 4;
			pos_next = pos;
			next_ = ReadInt(pos);
		}
		seekg(next_, ios::beg);
		pos = tellg();
		pos -= 4;
		next_ = ReadInt(pos);
		seekg(next_, ios::beg);
		pos = tellg();
	 	size = ReadInt(pos);
		pos += size;
		WriteInt(for_prev, pos);
		WriteInt(next_, pos_next);
	}
	setCount(getCount() - 1);
}

void List::Add(DataBase& other) {
	seekg(getLastStreamPos(), ios::beg);
	int l_next = -101;//значит последний элемент
	int f_prev = -111;//значит первый элемент
	if (getCount() == 0) {
		next = l_next;
		prev = f_prev;
		seekg(((int)tellg() - 4), ios::beg);
		write((char*)(&next), sizeof(int));
		prev = (int)tellg();			
		////////////////////////////////////////////object
		int pos = tellg();	
		pos = other.AddBin_DataBase(pos);
		seekg(pos, ios::beg);
		////////////////////////////////////////////object		
		WriteInt(f_prev, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
	else {
			seekg(getLastStreamPos(), ios::beg);
			next = (int)tellg();
			seekg((prev - 4), ios::beg);
			write((char*)(&next), sizeof(int));
			seekg(getLastStreamPos() - 4, ios::beg);
			write((char*)(&l_next), sizeof(int));
			int prev_ = prev;
			prev = (int)tellg();			
			////////////////////////////////////////////object
			int pos = tellg();
			pos = other.AddBin_DataBase(pos);
			seekg(pos, ios::beg);
			////////////////////////////////////////////object
			WriteInt(prev_, pos);
			setLastStreamPos(pos + 4);
			setCount(getCount() + 1);
	}
}

void List::Add(Integer& other) {
	seekg(getLastStreamPos(), ios::beg);
	int l_next = -101;//значит последний элемент
	int f_prev = -111;//значит первый элемент
	if (getCount() == 0) {
		next = l_next;
		prev = f_prev;
		seekg(((int)tellg() - 4), ios::beg);
		write((char*)(&next), sizeof(int));
		prev = (int)tellg();
		////////////////////////////////////////////object
		int pos = tellg();
		pos = other.AddBin_Integer(pos);
		seekg(pos, ios::beg);
		////////////////////////////////////////////object		
		WriteInt(f_prev, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
	else {
		seekg(getLastStreamPos(), ios::beg);
		next = (int)tellg();
		seekg((prev - 4), ios::beg);
		write((char*)(&next), sizeof(int));
		seekg(getLastStreamPos() - 4, ios::beg);
		write((char*)(&l_next), sizeof(int));
		int prev_ = prev;
		prev = (int)tellg();
		////////////////////////////////////////////object
		int pos = tellg();
		pos = other.AddBin_Integer(pos);
		seekg(pos, ios::beg);
		////////////////////////////////////////////object
		WriteInt(prev_, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
}

void List::Editor(DataBase& other, int position) {
	int next_ = getStart();
	int pos = getStart();
	if (position == 1) {
		seekg(pos, ios::beg);
		other.AddBin_DataBase(pos);
	}
	else {
		for (int i = 0; i < position; i++) {
			seekg(next_, ios::beg);
			pos = tellg();
			pos -= 4;
			next_ = ReadInt(pos);
		}
		other.AddBin_DataBase(pos);
	}
}

void List::Editor(Integer& other, int position) {
	int next_ = getStart();
	int pos = getStart();
	if (position == 1) {
		seekg(pos, ios::beg);
		other.AddBin_Integer(pos);
	}
	else {
		for (int i = 0; i < position; i++) {
			seekg(next_, ios::beg);
			pos = tellg();
			pos -= 4;
			next_ = ReadInt(pos);
		}
		other.AddBin_Integer(pos);
	}
}

void List::Insert(DataBase& other, int position) {
	int pos, next_, size, pos_next;
	int f_prev = -111;//значит первый элемент
	if (position == 1) {
		seekg(getStart(), ios::beg);
		pos = tellg();
		next_ = pos;
		size = ReadInt(pos);
		pos += size;//size + pos
		WriteInt(getLastStreamPos(), pos);
		seekg(getLastStreamPos() - 4, ios::beg);
		pos = tellg();
		WriteInt(next_, pos);
		setStart(pos);
		/////////////////
		pos = other.AddBin_DataBase(pos);
		seekg(pos, ios::beg);
		/////////////////
		WriteInt(f_prev, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
	else if (position < getCount()) {
		seekg(getStart() - 4, ios::beg);
		pos = tellg();
		pos_next = pos;
		next_ = ReadInt(pos);
		if (position != 2) {
			for (int i = 2; i < position; i++) {
				seekg(next_, ios::beg);
				pos = tellg();
				pos -= 4;
				pos_next = pos;
				next_ = ReadInt(pos);
			}
		}
		seekg(next_, ios::beg);
		pos = tellg();
		size = ReadInt(pos);
		pos += size;
		WriteInt(getLastStreamPos(), pos);
		seekg(getLastStreamPos() - 4, ios::beg);
		pos = tellg();
		WriteInt(next_, pos);
		WriteInt(pos, pos_next);
		//////////////////////////
		pos = other.AddBin_DataBase(pos);
		seekg(pos, ios::beg);
		//////////////////////////
		WriteInt(pos_next, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
}

void List::Insert(Integer& other, int position) {
	int pos, next_, size, pos_next;
	int f_prev = -111;//значит первый элемент
	if (position == 1) {
		seekg(getStart(), ios::beg);
		pos = tellg();
		next_ = pos;
		size = ReadInt(pos);
		pos += size;//size + pos
		WriteInt(getLastStreamPos(), pos);
		seekg(getLastStreamPos() - 4, ios::beg);
		pos = tellg();
		WriteInt(next_, pos);
		setStart(pos);
		/////////////////
		pos = other.AddBin_Integer(pos);
		seekg(pos, ios::beg);
		/////////////////
		WriteInt(f_prev, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
	else if (position < getCount()) {
		seekg(getStart() - 4, ios::beg);
		pos = tellg();
		pos_next = pos;
		next_ = ReadInt(pos);
		if (position != 2) {
			for (int i = 2; i < position; i++) {
				seekg(next_, ios::beg);
				pos = tellg();
				pos -= 4;
				pos_next = pos;
				next_ = ReadInt(pos);
			}
		}
		seekg(next_, ios::beg);
		pos = tellg();
		size = ReadInt(pos);
		pos += size;
		WriteInt(getLastStreamPos(), pos);
		seekg(getLastStreamPos() - 4, ios::beg);
		pos = tellg();
		WriteInt(next_, pos);
		WriteInt(pos, pos_next);
		//////////////////////////
		pos = other.AddBin_Integer(pos);
		seekg(pos, ios::beg);
		//////////////////////////
		WriteInt(pos_next, pos);
		setLastStreamPos(pos + 4);
		setCount(getCount() + 1);
	}
}

void List::SortDataBase() {
	int next_, next_1, prev_, pos;

	int size_1, size_2;
	int city_code_1, city_code_2, talk_time_1, talk_time_2;//код города /продолжительность в минутах
	long long phone_1, phone_2;//телефон абонента
	double rate_1, rate_2;//тариф
	char* city_1;//Город
	char* city_2;//Город
	int day_1, day_2, month_1, month_2, year_1, year_2;//дата
	int pay_day_1, pay_day_2, pay_month_1, pay_month_2, pay_year_1, pay_year_2;//дата оплаты
	int talk_min_1, talk_min_2, talk_hour_1, talk_hour_2;//время переговоров

	for (int i = 0; i < getCount(); i++) {
		int j;
		next_ = getStart();
		if (getCount() % 2 == 0) j = 0;
		else j = 2;
		for (; j < getCount(); j += 2) {
			seekg(next_ - 4, ios::beg);
			pos = tellg();
			next_1 = ReadInt(pos);
			/////////////////////
			size_1 = ReadInt(pos);
			ReadBool(pos);
			city_code_1 = ReadInt(pos);
			talk_time_1 = ReadInt(pos);
			phone_1 = ReadLongLong(pos);
			rate_1 = ReadDouble(pos);
			city_1 = _strdup(ReadCharP(pos));
			day_1 = ReadInt(pos);
			month_1 = ReadInt(pos);
			year_1 = ReadInt(pos);
			pay_day_1 = ReadInt(pos);
			pay_month_1 = ReadInt(pos);
			pay_year_1 = ReadInt(pos);
			talk_min_1 = ReadInt(pos);
			talk_hour_1 = ReadInt(pos);
			/////////////////////
			seekg(next_1 - 4, ios::beg);
			pos = tellg();
			next_ = ReadInt(pos);
			/////////////////////
			size_2 = ReadInt(pos);
			ReadBool(pos);
			city_code_2 = ReadInt(pos);
			talk_time_2 = ReadInt(pos);
			phone_2 = ReadLongLong(pos);
			rate_2 = ReadDouble(pos);
			city_2 = _strdup(ReadCharP(pos));
			day_2 = ReadInt(pos);
			month_2 = ReadInt(pos);
			year_2 = ReadInt(pos);
			pay_day_2 = ReadInt(pos);
			pay_month_2 = ReadInt(pos);
			pay_year_2 = ReadInt(pos);
			talk_min_2 = ReadInt(pos);
			talk_hour_2 = ReadInt(pos);
			/////////////////////
			prev_ = ReadInt(pos);

			if ((year_2 * (20 * 50) + month_2 * 20 + day_2) < (year_1 * (20 * 50) + month_1 * 20 + day_1)) {
				DataBase dataBase_1(city_code_1, talk_time_1, phone_1, rate_1, _strdup(city_1), day_1, month_1, year_1, pay_day_1, pay_month_1, pay_year_1, talk_min_1, talk_hour_1);
				DataBase dataBase_2(city_code_2, talk_time_2, phone_2, rate_2, _strdup(city_2), day_2, month_2, year_2, pay_day_2, pay_month_2, pay_year_2, talk_min_2, talk_hour_2);
				dataBase_1.AddBin_DataBase(next_1);
				dataBase_2.AddBin_DataBase(prev_);
			}
		}
		seekg(getStart() - 4, ios::beg);
		pos = tellg();
		next_ = ReadInt(pos);
		for (int j = 2; j < getCount(); j += 2) {
			seekg(next_ - 4, ios::beg);
			pos = tellg();
			next_1 = ReadInt(pos);
			/////////////////////
			size_1 = ReadInt(pos);
			ReadBool(pos);
			city_code_1 = ReadInt(pos);
			talk_time_1 = ReadInt(pos);
			phone_1 = ReadLongLong(pos);
			rate_1 = ReadDouble(pos);
			city_1 = _strdup(ReadCharP(pos));
			day_1 = ReadInt(pos);
			month_1 = ReadInt(pos);
			year_1 = ReadInt(pos);
			pay_day_1 = ReadInt(pos);
			pay_month_1 = ReadInt(pos);
			pay_year_1 = ReadInt(pos);
			talk_min_1 = ReadInt(pos);
			talk_hour_1 = ReadInt(pos);
			/////////////////////
			seekg(next_1 - 4, ios::beg);
			pos = tellg();
			next_ = ReadInt(pos);
			/////////////////////
			size_2 = ReadInt(pos);
			ReadBool(pos);
			city_code_2 = ReadInt(pos);
			talk_time_2 = ReadInt(pos);
			phone_2 = ReadLongLong(pos);
			rate_2 = ReadDouble(pos);
			city_2 = _strdup(ReadCharP(pos));
			day_2 = ReadInt(pos);
			month_2 = ReadInt(pos);
			year_2 = ReadInt(pos);
			pay_day_2 = ReadInt(pos);
			pay_month_2 = ReadInt(pos);
			pay_year_2 = ReadInt(pos);
			talk_min_2 = ReadInt(pos);
			talk_hour_2 = ReadInt(pos);
			/////////////////////
			prev_ = ReadInt(pos);

			if ((year_2 * (20 * 50) + month_2 * 20 + day_2) < (year_1 * (20 * 50) + month_1 * 20 + day_1)) {
				DataBase dataBase_1(city_code_1, talk_time_1, phone_1, rate_1, _strdup(city_1), day_1, month_1, year_1, pay_day_1, pay_month_1, pay_year_1, talk_min_1, talk_hour_1);
				DataBase dataBase_2(city_code_2, talk_time_2, phone_2, rate_2, _strdup(city_2), day_2, month_2, year_2, pay_day_2, pay_month_2, pay_year_2, talk_min_2, talk_hour_2);
				dataBase_1.AddBin_DataBase(next_1);
				dataBase_2.AddBin_DataBase(prev_);
			}
		}
	}
}

void List::SortInsert(DataBase& other) {
	int pos, next_ = getStart(), size, day, year, month, num = 1;
	do {
		seekg(next_, ios::beg);
		pos = tellg();
		pos -= 4;
		next_ = ReadInt(pos);
		size = ReadInt(pos);
		size -= 32;
		pos += size;
		day = ReadInt(pos);
		month = ReadInt(pos);
		year = ReadInt(pos);
		int i = (year * (20 * 50) + month * 20 + day);
		int j = (other.year * (20 * 50) + other.month * 20 + other.day);
		if ((year * (20 * 50) + month * 20 + day) >= (other.year * (20 * 50) + other.month * 20 + other.day)) next_ = -101;
		num++;
	} while (next_ != -101);
	Insert(other, --num);
}

void List::Compression() {
	fstream fileBuff;
	fileBuff.open("Buff.bin", ios::binary | ios::out);
	try {
		if (!fileBuff.is_open()) { throw 1;	}
	}
	catch (...) {
		cerr << "Ошибка открытия файла" << endl;
		exit(1);
	}
	fileBuff.close();
	fileBuff.open("Buff.bin", fstream::in | fstream::out | fstream::binary);
	try {
		if (!fileBuff.is_open()) { throw 1;	}
	}
	catch (...) {
		cerr << "Ошибка открытия файла" << endl;
		exit(1);
	}
	
	fileBuff.seekg(0, ios::beg);
	fileBuff.write((char*)(&start), sizeof(int));

	fileBuff.seekg(12, ios::beg);
	int count = getCount();
	fileBuff.write((char*)(&count), sizeof(int));
	
	int pos, posB, prev_pos, prev_;
	int iii;
	bool bbb;
	long long lll;
	double ddd;
	char* ccc;
	int i = 1;
	int l_next = -111;//значит первый элемент
	int f_prev = -101;//значит последний элемент
	int next_ = getStart();
	fileBuff.seekg(start - 4, ios::beg);
	while (true) {
		seekg(next_ - 4, ios::beg);
		pos = tellg();
		next_ = ReadInt(pos);
		
		if (i == 1) {
			fileBuff.write((char*)(&f_prev), sizeof(int));
			prev_pos = fileBuff.tellg();
			prev = prev_pos;
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			bbb = ReadBool(pos); fileBuff.write((char*)(&bbb), sizeof(bool));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos);	fileBuff.write((char*)(&iii), sizeof(int));
			lll = ReadLongLong(pos); fileBuff.write((char*)(&lll), sizeof(long long));
			ddd = ReadDouble(pos); fileBuff.write((char*)(&ddd), sizeof(double));
			ccc = _strdup(ReadCharP(pos)); fileBuff.write((char*)(&ccc), sizeof(char*));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			fileBuff.write((char*)(&l_next), sizeof(int));
		}
		else {
			fileBuff.write((char*)(&f_prev), sizeof(int));
			prev_ = fileBuff.tellg();
			prev = prev_;
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			bbb = ReadBool(pos); fileBuff.write((char*)(&bbb), sizeof(bool));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos);	fileBuff.write((char*)(&iii), sizeof(int));
			lll = ReadLongLong(pos); fileBuff.write((char*)(&lll), sizeof(long long));
			ddd = ReadDouble(pos); fileBuff.write((char*)(&ddd), sizeof(double));
			ccc = _strdup(ReadCharP(pos)); fileBuff.write((char*)(&ccc), sizeof(char*));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			iii = ReadInt(pos); fileBuff.write((char*)(&iii), sizeof(int));
			fileBuff.write((char*)(&prev_pos), sizeof(int));

			posB = fileBuff.tellg();
			fileBuff.seekg(prev_pos - 4, ios::beg);
			fileBuff.write((char*)(&prev_), sizeof(int));
			fileBuff.seekg(posB, ios::beg);

			prev_pos = prev_;
		}
		if (next_ == -101) break;	
		i++;
	}

	iii = fileBuff.tellg();
	iii += 4;
	fileBuff.seekg(8, ios::beg);
	fileBuff.write((char*)(&iii), sizeof(int));	
	
	fileBuff.seekg(4, ios::beg);
	fileBuff.write((char*)(&i), sizeof(int));
	
	fileBuff.close();
	close();
	
	remove("bList.bin");
	if (rename("Buff.bin", "bList.bin") != 0) {
		cout << "Rename Error";
		exit(1);
	}
		
	try {
		open("bList.bin", fstream::in | fstream::out | fstream::binary);
		seekg(0, ios::beg);
	}
	catch (...) {
		cerr << "Ошибка открытия файла" << endl;
		exit(1);
	}
	
}


List::List() {
	try {
		open("bList.bin", fstream::in | fstream::out | fstream::binary);
		seekg(0, ios::beg);
	}
	catch (...) {
		cerr << "Ошибка открытия файла" << endl;
		exit(1);
	}
	//open("bList.bin", fstream::in | fstream::out | fstream::binary);
	//setCount(0);
	//setSum(0);
	//setStart(22);
	//setLastStreamPos(22);
	//seekg(0, ios::beg);
}

List::~List() {
	close();
}
