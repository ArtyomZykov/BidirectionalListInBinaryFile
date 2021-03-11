#pragma once
#include <iostream>
using namespace std;

class DataBase {
private:
	bool flag;
	int size;
	int city_code, talk_time;//код города /продолжительность в минутах
	long long phone;//телефон абонента
	double rate;//тариф
	char* city;//√ород
	int day, month, year;//дата
	int pay_day, pay_month, pay_year;//дата оплаты
	int talk_min, talk_hour;//врем€ переговоров
public:
	int getCity_code();
	int getTalk_time();
	long long getPhone();
	double getRate();
	char* getCity();
	int getDay();
	int getMonth();
	int getYear();
	int getPay_day();
	int getPay_month();
	int getPay_year();
	int getTalk_min();
	int getTalk_hour();

	void setCity_code(int);
	void setTalk_time(int);
	void setPhone(long long);
	void setRate(double);
	void setCity(char*);
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	void setPay_day(int);
	void setPay_month(int);
	void setPay_year(int);
	void setTalk_min(int);
	void setTalk_hour(int);
	DataBase& operator = (const DataBase&);

	
	void ShowBin_DataBase(int);
	int AddBin_DataBase(int);
	DataBase();
	DataBase(int, int, long long, double, char*, int, int, int, int, int, int, int, int);
	DataBase(DataBase* other);
	~DataBase();
	friend class List;
};