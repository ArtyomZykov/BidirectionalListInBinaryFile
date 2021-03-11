#pragma once
#include <iostream>
using namespace std;

class Integer {
protected:
	int size;
	int num;
public:
	
	Integer& operator = (const Integer&);


	void ShowBin_Integer(int);
	int AddBin_Integer(int);
	Integer();
	Integer(int);
	Integer(Integer* other);
	~Integer();
	friend class List;
};