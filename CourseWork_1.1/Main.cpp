#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include "Integer.h"
#include "DataBase.h"
#include "List.h"
using namespace std;

int main() {
	
	setlocale(LC_ALL, "Russian");	
	srand(time(NULL));
	List list_1;
	//Если пользователь хочет работать с пустой базой
	int start = 22;
	list_1.setStart(start);
	list_1.setSum(0);
	list_1.setCount(0);
	list_1.setLastStreamPos(start);
	////////////////////////////////////////////////
		
	int time;
	bool point = 1;	
	cout << "Введя 1, вы увидите меню\n";
	while (point) {
		cout << "Введите команду: ";
		cin >> time;
		switch (time) {
		case 1: {
			cout << "1) Меню\n";
			cout << "2) Просмотр файла\n";
			cout << "3) Добавление элемента (и в нужную позицию)\n";
			cout << "4) Удаление записи\n";
			cout << "5) Вставка с сохранением порядка\n";
			cout << "6) Рандомное добавление объектвов\n";
			cout << "7) Сортировка\n";
			cout << "8) Сжатие\n";
			cout << "9) Очистить консоль\n";		

			break;
		}
		case 2: {
			if (list_1.getCount() != 0) list_1.ShowDataBase();
			break;
		}
		case 3: {
			int city_code, talk_time;//код города /продолжительность в минутах
			long long phone;//телефон абонента
			double rate;//тариф
			char city[30] = "";//Город
			int day, month, year;//дата
			int pay_day, pay_month, pay_year;//дата оплаты
			int talk_min, talk_hour;//время переговоров
			int num;
			cout << "На какую позицию хотите поместить запись? ";
			cin >> num;
			if (num > list_1.getCount()) {
				cout << "  city_code: "; cin >> city_code; cout << "  ";
				cout << "talk_time: "; cin >> talk_time; cout << "  ";
				cout << "phone: "; cin >> phone; cout << "  ";
				cout << "rate: "; cin >> rate; cout << "  ";
				cout << "city: "; cin >> city; cout << "  ";
				cout << "day: "; cin >> day; cout << "  ";
				cout << "month: "; cin >> month; cout << "  ";
				cout << "year: "; cin >> year; cout << "  ";
				cout << "pay_day: "; cin >> pay_day; cout << "  ";
				cout << "pay_month: "; cin >> pay_month; cout << "  ";
				cout << "pay_year: "; cin >> pay_year; cout << "  ";
				cout << "talk_min: "; cin >> talk_min; cout << "  ";
				cout << "talk_hour: "; cin >> talk_hour; cout << "\n";

				DataBase dataBase(city_code, talk_time, phone, rate, strdup(city), day, month, year, pay_day, pay_month, pay_year, talk_min, talk_hour);
				list_1.Add(dataBase);
			} 
			else {
				cout << "  city_code: "; cin >> city_code; cout << "  ";
				cout << "talk_time: "; cin >> talk_time; cout << "  ";
				cout << "phone: "; cin >> phone; cout << "  ";
				cout << "rate: "; cin >> rate; cout << "  ";
				cout << "city: "; cin >> city; cout << "  ";
				cout << "day: "; cin >> day; cout << "  ";
				cout << "month: "; cin >> month; cout << "  ";
				cout << "year: "; cin >> year; cout << "  ";
				cout << "pay_day: "; cin >> pay_day; cout << "  ";
				cout << "pay_month: "; cin >> pay_month; cout << "  ";
				cout << "pay_year: "; cin >> pay_year; cout << "  ";
				cout << "talk_min: "; cin >> talk_min; cout << "  ";
				cout << "talk_hour: "; cin >> talk_hour; cout << "\n";

				DataBase dataBase(city_code, talk_time, phone, rate, strdup(city), day, month, year, pay_day, pay_month, pay_year, talk_min, talk_hour);
				list_1.Insert(dataBase, num);
			}
			break;
		}
		case 4: {
			int num;
			cout << "Какую запись хотите удалить? ";
			cin >> num;
			if (!list_1.getCount() < 2) {
				list_1.Delete(num);
			}
			break;
		}
		case 5: {
			int city_code, talk_time;//код города /продолжительность в минутах
			long long phone;//телефон абонента
			double rate;//тариф
			char city[30] = "";//Город
			int day, month, year;//дата
			int pay_day, pay_month, pay_year;//дата оплаты
			int talk_min, talk_hour;//время переговоров
			cout << "  city_code: "; cin >> city_code; cout << "  ";
			cout << "talk_time: "; cin >> talk_time; cout << "  ";
			cout << "phone: "; cin >> phone; cout << "  ";
			cout << "rate: "; cin >> rate; cout << "  ";
			cout << "city: "; cin >> city; cout << "  ";
			cout << "day: "; cin >> day; cout << "  ";
			cout << "month: "; cin >> month; cout << "  ";
			cout << "year: "; cin >> year; cout << "  ";
			cout << "pay_day: "; cin >> pay_day; cout << "  ";
			cout << "pay_month: "; cin >> pay_month; cout << "  ";
			cout << "pay_year: "; cin >> pay_year; cout << "  ";
			cout << "talk_min: "; cin >> talk_min; cout << "  ";
			cout << "talk_hour: "; cin >> talk_hour; cout << "\n";
			DataBase dataBase(city_code, talk_time, phone, rate, strdup(city), day, month, year, pay_day, pay_month, pay_year, talk_min, talk_hour);
			list_1.SortInsert(dataBase);
			break;
		}
		case 6: {
			int num;
			int city_code, talk_time;//код города /продолжительность в минутах
			long long phone;//телефон абонента
			double rate;//тариф
			char city[30] = "";//Город
			int day, month, year;//дата
			int pay_day, pay_month, pay_year;//дата оплаты
			int talk_min, talk_hour;//время переговоров

			cout << "Сколько оъектов хотите добавить? ";
			cin >> num;
			for (int i = 0; i < num; i++) {
				city_code = rand() % 100000 + 1;
				talk_time = rand() % 100 + 1;
				phone = rand() % 100000000000 + 1;
				rate = (double)(rand()) / RAND_MAX * 6;
				day = rand() % 30 + 1;
				month = rand() % 11 + 1;
				while (true) {
					year = rand() % 2020;
					if (year > 2000) break;
				}
				if (i % 5 == 0) {
					pay_day = 0;
					pay_month = 0;
					pay_year = 0;
				} else {
				pay_day = rand() % 30 + 1;
				pay_month = rand() % 11 + 1;
				while (true) {
					pay_year = rand() % 2020;
					if (pay_year > 2000) break;
				}
				}
				talk_min = rand() % 58;
				talk_hour = rand() % 23;
				DataBase dataBase(city_code, talk_time, phone, rate, _strdup("HHHH"), day, month, year, pay_day, pay_month, pay_year, talk_min, talk_hour);
				list_1.Add(dataBase);
			}
			break;
		}
		case 7: {
			list_1.SortDataBase();
			break;
		}
		case 8: {
			list_1.Compression();
			break;
		}
		case 9: {
			system("cls");
			break;
		}
		default: point = 0;
		}
	}

	

	return 0;
}