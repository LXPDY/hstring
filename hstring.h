#pragma once
#include <iostream>
class hstring {
private:
	char* hstr = nullptr;
	unsigned short sizeMem = 0;
	unsigned short sizeStr = 0;
	unsigned short caculate_sizeStr(const char* newStr);
	void cpyStr(const char* newStr);
public:
	~hstring();
	hstring(const char* str);
	hstring(const int val);
	hstring& mod(const hstring& str, const hstring& des);
	int find(const hstring& str);
	hstring& operator=(const char* str);
	hstring& operator=(const int val);
	hstring& operator<<(const hstring& str);
	hstring& operator+(const hstring& str);
	hstring& operator+(const hstring&& str);
	hstring& operator-(const hstring& str);
	
	friend std::ostream& operator<<(std::ostream& _cout, hstring& _str);
};

