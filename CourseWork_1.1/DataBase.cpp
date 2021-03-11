#include <sstream>
#include <iostream>
#include <fstream>
#include "DataBase.h"
#include "list.h"
#include <Windows.h>
using namespace std;


template<int text_color = 7> ostream& color(ostream& text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color); //(WORD)((bg << 4) | txt)
	return text;
}

enum COLOR {
	BLACK = 0,
	GREY = 8,
	BLUE = 9,
	GREEN = 10,
	TURQUOISE = 11,
	RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15,
	STANDART = 7
};


DataBase& DataBase::operator =(const DataBase& other) {
	this->flag = other.flag;
	this->size = other.size;	
	this->city_code = other.city_code;
	this->talk_time = other.talk_time;
	this->phone = other.phone;
	this->rate = other.rate;
	this->city = _strdup(other.city);
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
	this->pay_day = other.pay_day;
	this->pay_month = other.pay_month;
	this->pay_year = other.pay_year;
	this->talk_min = other.talk_min;
	this->talk_hour = other.talk_hour;
	return *this;
}

void DataBase::ShowBin_DataBase(int pos) {
	int next_, size_citi_;
	bool flag;
	List list77;
	list77.setSum(0);
	int count = 1;
	cout << color<RED> << "=================================================================================================================================================================================================================\n" << color;
	while (true) {
		double rate;
		int sum, time;
		pos -= 4;
		next_ = list77.ReadInt(pos);
		//cout << color<WHITE>  << "NEXT: " << next_ << " " << color;
		cout << color<BLUE> << "SIZE: " << list77.ReadInt(pos) << color << "\t";
		/////////////
		flag = list77.ReadBool(pos);
		if (flag) {
			cout << color<RED> << count << ")  ";
			cout << "city_code: " << list77.ReadInt(pos) << "\t";
			cout << "talk_time: " << list77.ReadInt(pos) << "\t";
			cout << "phone: " << list77.ReadLongLong(pos) << "\t";
			cout << "rate: " << list77.ReadDouble(pos) << "\t";
			cout << "city: " << list77.ReadCharP(pos) << "\t";
			cout << "date: " << list77.ReadInt(pos);
			cout << "/" << list77.ReadInt(pos);
			cout << "/" << list77.ReadInt(pos) << "\t\t\t\t";
			list77.ReadInt(pos);
			list77.ReadInt(pos);
			list77.ReadInt(pos);
			cout << "talk_time: " << list77.ReadInt(pos);
			cout << ":" << list77.ReadInt(pos) << color << "\t\t";
		}
		else {
			cout << count << ")  ";
			cout << "city_code: " << list77.ReadInt(pos) << "\t";
			time = list77.ReadInt(pos);
			cout << "talk_time: " << time << "\t";
			cout << "phone: " << list77.ReadLongLong(pos) << "\t";
			rate = list77.ReadDouble(pos);
			cout << "rate: " << rate << "\t";
			cout << "city: " << list77.ReadCharP(pos) << "\t";
			cout << "date: " << list77.ReadInt(pos);
			cout << "/" << list77.ReadInt(pos);
			cout << "/" << list77.ReadInt(pos) << "\t";
			cout << "pay_date: " << list77.ReadInt(pos);
			cout << "/" << list77.ReadInt(pos);
			cout << "/" << list77.ReadInt(pos) << "\t";
			cout << "talk_time: " << list77.ReadInt(pos);
			cout << ":" << list77.ReadInt(pos) << "\t\t";
			sum = time * rate;
			list77.setSum(list77.getSum() + sum);
		}
		/////////////
		list77.ReadInt(pos);
		cout << "\n";
		//cout << color<WHITE> << "PREV: " << list77.ReadInt(pos) << color << "\n";
		if (next_ == -101) break;
		list77.seekg(next_, ios::beg);
		pos = list77.tellg();
		count++;
	}
	cout << color<GREEN> << "SUM: " << list77.getSum() << " руб." << color << "\n";
	cout << color<RED> << "=================================================================================================================================================================================================================\n" << color;
}

int DataBase::AddBin_DataBase(int pos) {
	int p = pos;
	List list;
	list.WriteInt(this->size, p);
	list.WriteBool(this->flag, p);
	list.WriteInt(this->city_code, p);
	list.WriteInt(this->talk_time, p);
	list.WriteLongLong(this->phone, p);
	list.WriteDouble(this->rate, p);
	list.WriteCharP(_strdup(this->city), p);
	list.WriteInt(this->day, p);
	list.WriteInt(this->month, p);
	list.WriteInt(this->year, p);
	list.WriteInt(this->pay_day, p);
	list.WriteInt(this->pay_month, p);
	list.WriteInt(this->pay_year, p);
	list.WriteInt(this->talk_hour, p);
	list.WriteInt(this->talk_min, p);
	return p;
}

DataBase::DataBase() {
	flag = 1;
	size = sizeof(int) * 10 + sizeof(long long) + sizeof(double) + sizeof(city);
	city_code = 0;
	talk_time = 0;
	phone = 0;
	rate = 0;
	city = _strdup("No Data");
	//size_city = sizeof(city);
	day = 0;
	month = 0;
	year = 0;
	pay_day = 0;
	pay_month = 0;
	pay_year = 0;
	talk_min = 0;
	talk_hour = 0;
}

DataBase::DataBase(int city_code, int talk_time, long long phone, double rate, char* city, int day, int month, int year, int pay_day, int pay_month, int pay_year, int talk_min, int talk_hour) {
	this->size = sizeof(int) * 10 + sizeof(long long) + sizeof(double) + sizeof(city) + sizeof(bool);
	this->city_code = city_code;	
	this->talk_time = talk_time;
	this->phone = phone;
	this->rate = rate;
	this->city = _strdup(city);
	//this->size_city = sizeof(city);
	this->day = day;
	this->month = month;
	this->year = year;
	if (pay_day == 0 && pay_month == 0 && pay_year == 0) flag = 1; //non pay
	else flag = 0;
	this->pay_day = pay_day;
	this->pay_month = pay_month;
	this->pay_year = pay_year;
	this->talk_min = talk_min;
	this->talk_hour = talk_hour;
}

DataBase::DataBase(DataBase *other) {
	this->flag = flag;
	this->size = size;
	this->city_code = city_code;
	this->talk_time = talk_time;
	this->phone = phone;
	this->rate = rate;
	this->city = _strdup(city);
	this->day = day;
	this->month = month;
	this->year = year;
	this->pay_day = pay_day;
	this->pay_month = pay_month;
	this->pay_year = pay_year;
	this->talk_min = talk_min;
	this->talk_hour = talk_hour;
}

DataBase::~DataBase() {
	delete[] city;
}