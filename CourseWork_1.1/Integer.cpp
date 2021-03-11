#include <sstream>
#include <iostream>
#include <fstream>
#include "Integer.h"
#include "list.h"
#include <Windows.h>

using namespace std;

template<int text_color = 7>
ostream& color(ostream& text)
{
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

Integer& Integer::operator =(const Integer& other) {
	this->num = other.num;
	this->size = other.size;	
	return *this;
}

void Integer::ShowBin_Integer(int pos) {
	int next_, size_citi_;
	List list77;
	int count = 1;
	while (true) {
		pos -= sizeof(int);
		next_ = list77.ReadInt(pos);
		cout << color<WHITE> << "NEXT: " << next_ << " " << color;
		cout << color<BLUE> << "SIZE: " << list77.ReadInt(pos) << color << "\t";
		/////////////
		cout << count << ")  ";		
		cout << "num: " << list77.ReadInt(pos) << "\t\t";
		/////////////
		cout << color<WHITE> << "PREV: " << list77.ReadInt(pos) << color << "\n";
		if (next_ == -101) break;
		list77.seekg(next_, ios::beg);
		pos = list77.tellg();
		count++;
	}
}

int Integer::AddBin_Integer(int pos) {
	int p = pos;
	List list;
	list.WriteInt(this->size, p);
	list.WriteInt(this->num, p);	
	return p;
}

Integer::Integer() {
	size = sizeof(int);
	num = 0;
}


Integer::Integer(int num) {
	this->size = sizeof(int);
	this->num = num;
}

Integer::Integer(Integer* other) {
	this->num = num;
	this->size = size;
}

Integer::~Integer() {
	
}