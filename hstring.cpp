#include"hstring.h"
unsigned short hstring::caculate_sizeStr(const char *newStr) {
	unsigned short newSize = 0;
	for (;newStr[newSize++];);
	return newSize;
}

hstring::~hstring() {
	if (hstr != nullptr) {
		delete[] hstr;
	}
}

//将字符串内容拷贝到类中
void hstring::cpyStr(const char* newStr) {
	unsigned short newLen = caculate_sizeStr(newStr);

	if (newLen > sizeMem) {
		//若当前缓冲区大小小于新字符串长度，则重新分配
		if (hstr != nullptr) {
			delete[] hstr;
		}
		hstr = new char[newLen];
		sizeMem = newLen;
	}
	memcpy(hstr, newStr, newLen);
	sizeStr = newLen;
}


//字符串类型构造函数
hstring::hstring(const char *newStr) {
	cpyStr(newStr);
}

hstring::hstring(const int val) {
	*this = val;
}

hstring& hstring::operator=(const char* str) {
	cpyStr(str);
	return *this;
}
hstring& hstring::operator=(const int val) {
	int v = val;
	char temp[0x20]{};//用于存放转换的int
	char x[0x20]{}; //用于存放计算出的倒序字符串
	short i = 0,j=0;//位数计数
	//处理负数
	if (v < 0) {
		temp[0] = '-';
		v = -v;
		j++;
	}
	do {
		x[i] = v % 10 + 48;
		v = v / 10;
		i++;
	} while (v != 0);

	for (i = i-1; i >= 0;j++,i--) {
		temp[j] = x[i];
	}
	temp[j+1] = '\0';
	cpyStr(temp);
	return *this;
}


//重载左移运算符，用于在字符串尾部添加新字符串
hstring& hstring::operator<<(const hstring& str) {
	unsigned short newLen = sizeStr + str.sizeStr - 1;
	//同构造，将旧空间拷贝后删除
	if (newLen > sizeMem) {
		char* oldmem = hstr;
		hstr = new char[newLen];
		memcpy(hstr, oldmem, sizeStr);
		if (oldmem != nullptr) {
			delete[] oldmem;
		}
		sizeMem = newLen;
	}
	memcpy(hstr + sizeStr - 1, str.hstr, str.sizeStr);
	sizeStr = newLen;
	return *this;
}

hstring& hstring::operator+(const hstring& str) {
	return *this << str;
}
hstring& hstring::operator+(const hstring&& str)
{
	return *this << str;
}

hstring& hstring::operator-(const hstring& str) {
	//若要减去的字符串长度大于原字符串，则无法相减,不操作直接返回
	if (str.sizeStr > sizeStr) {
		return *this;
	}
	//寻找子串,删除第一个遇到的匹配项
	char* memp = hstr;
	unsigned short end = sizeStr - str.sizeStr+1;//搜索结尾
	unsigned short cmpSize = str.sizeStr - 1;
	for (unsigned short i = 0;i <= end;i++ , memp++) {
		//找到匹配项,使用memcmp直接暴力搜索
		if (memcmp(memp, str.hstr, cmpSize) == 0) {
			unsigned short sizeEnd = sizeStr - i - cmpSize;//尾部字符串的长度
			memcpy(memp, memp + cmpSize, sizeEnd);
			sizeStr = sizeStr - cmpSize;
			return *this;
		}
	}
	//未搜索到则直接返回
	return *this;
}

//替换目标字符串
hstring& hstring::mod(const hstring& str, const hstring& des) {
	//若要被替换的字符串长度大于原字符串，则无法替换,不操作直接返回
	if (str.sizeStr > sizeStr) {
		return *this;
	}
	//寻找子串,修改第一个遇到的匹配项
	char* memp = hstr;
	unsigned short end = sizeStr - str.sizeStr + 1;//搜索结尾
	unsigned short cmpSize = str.sizeStr - 1;
	for (unsigned short i = 0;i <= end;i++, memp++) {
		//找到匹配项,使用memcmp直接暴力搜索
		if (memcmp(memp, str.hstr, cmpSize) == 0) {
			//若缓冲区不够大，则扩区
			unsigned short newLen = sizeStr + des.sizeStr - str.sizeStr;
			unsigned short sizeDes = des.sizeStr - 1;
			char* newMemp = nullptr;
			if (str.sizeMem < newLen) {
				char* oldMem = hstr;
				hstr = new char[newLen];
				newMemp = hstr + i;
				memcpy(hstr, oldMem, i);
				unsigned short sizeEnd = sizeStr - i - cmpSize;//尾部字符串的长度
				//将尾部拷贝到新内存空间中
				memcpy(newMemp + sizeDes, memp + cmpSize, sizeEnd);
				delete[] oldMem;
				sizeMem = newLen;
			}
			else {
				newMemp = memp;
				unsigned short sizeEnd = sizeStr - i - cmpSize;
				memcpy(newMemp + sizeDes, memp + cmpSize, sizeEnd);
			}
			//将替换部分拷贝
			memcpy(newMemp, des.hstr, sizeDes);
			sizeStr = sizeStr - cmpSize + sizeDes;
			return *this;
		}
	}
	//未搜索到则直接返回
	return *this;
}

//搜寻子串返回初始下标，搜索不到则返回-1
int hstring::find(const hstring& str) {
	//若要被替换的字符串长度大于原字符串，则无法替换,不操作直接返回
	if (str.sizeStr > sizeStr) {
		return -1;
	}
	//寻找子串,修改第一个遇到的匹配项
	char* memp = hstr;
	unsigned short end = sizeStr - str.sizeStr + 1;//搜索结尾
	unsigned short cmpSize = str.sizeStr - 1;
	for (unsigned short i = 0;i <= end;i++, memp++) {
		//找到匹配项,使用memcmp直接暴力搜索
		if (memcmp(memp, str.hstr, cmpSize) == 0) {
			return i;
		}
	}
	//未搜索到则直接返回
	return -1;
}

//重载左移运算符，用于标准字符流输出
std::ostream& operator<<(std::ostream& _cout, hstring& _str) {
	_cout << _str.hstr;
	return _cout;
}