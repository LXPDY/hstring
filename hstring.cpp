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

//���ַ������ݿ���������
void hstring::cpyStr(const char* newStr) {
	unsigned short newLen = caculate_sizeStr(newStr);

	if (newLen > sizeMem) {
		//����ǰ��������СС�����ַ������ȣ������·���
		if (hstr != nullptr) {
			delete[] hstr;
		}
		hstr = new char[newLen];
		sizeMem = newLen;
	}
	memcpy(hstr, newStr, newLen);
	sizeStr = newLen;
}


//�ַ������͹��캯��
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
	char temp[0x20]{};//���ڴ��ת����int
	char x[0x20]{}; //���ڴ�ż�����ĵ����ַ���
	short i = 0,j=0;//λ������
	//������
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


//����������������������ַ���β��������ַ���
hstring& hstring::operator<<(const hstring& str) {
	unsigned short newLen = sizeStr + str.sizeStr - 1;
	//ͬ���죬���ɿռ俽����ɾ��
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
	//��Ҫ��ȥ���ַ������ȴ���ԭ�ַ��������޷����,������ֱ�ӷ���
	if (str.sizeStr > sizeStr) {
		return *this;
	}
	//Ѱ���Ӵ�,ɾ����һ��������ƥ����
	char* memp = hstr;
	unsigned short end = sizeStr - str.sizeStr+1;//������β
	unsigned short cmpSize = str.sizeStr - 1;
	for (unsigned short i = 0;i <= end;i++ , memp++) {
		//�ҵ�ƥ����,ʹ��memcmpֱ�ӱ�������
		if (memcmp(memp, str.hstr, cmpSize) == 0) {
			unsigned short sizeEnd = sizeStr - i - cmpSize;//β���ַ����ĳ���
			memcpy(memp, memp + cmpSize, sizeEnd);
			sizeStr = sizeStr - cmpSize;
			return *this;
		}
	}
	//δ��������ֱ�ӷ���
	return *this;
}

//�滻Ŀ���ַ���
hstring& hstring::mod(const hstring& str, const hstring& des) {
	//��Ҫ���滻���ַ������ȴ���ԭ�ַ��������޷��滻,������ֱ�ӷ���
	if (str.sizeStr > sizeStr) {
		return *this;
	}
	//Ѱ���Ӵ�,�޸ĵ�һ��������ƥ����
	char* memp = hstr;
	unsigned short end = sizeStr - str.sizeStr + 1;//������β
	unsigned short cmpSize = str.sizeStr - 1;
	for (unsigned short i = 0;i <= end;i++, memp++) {
		//�ҵ�ƥ����,ʹ��memcmpֱ�ӱ�������
		if (memcmp(memp, str.hstr, cmpSize) == 0) {
			//��������������������
			unsigned short newLen = sizeStr + des.sizeStr - str.sizeStr;
			unsigned short sizeDes = des.sizeStr - 1;
			char* newMemp = nullptr;
			if (str.sizeMem < newLen) {
				char* oldMem = hstr;
				hstr = new char[newLen];
				newMemp = hstr + i;
				memcpy(hstr, oldMem, i);
				unsigned short sizeEnd = sizeStr - i - cmpSize;//β���ַ����ĳ���
				//��β�����������ڴ�ռ���
				memcpy(newMemp + sizeDes, memp + cmpSize, sizeEnd);
				delete[] oldMem;
				sizeMem = newLen;
			}
			else {
				newMemp = memp;
				unsigned short sizeEnd = sizeStr - i - cmpSize;
				memcpy(newMemp + sizeDes, memp + cmpSize, sizeEnd);
			}
			//���滻���ֿ���
			memcpy(newMemp, des.hstr, sizeDes);
			sizeStr = sizeStr - cmpSize + sizeDes;
			return *this;
		}
	}
	//δ��������ֱ�ӷ���
	return *this;
}

//��Ѱ�Ӵ����س�ʼ�±꣬���������򷵻�-1
int hstring::find(const hstring& str) {
	//��Ҫ���滻���ַ������ȴ���ԭ�ַ��������޷��滻,������ֱ�ӷ���
	if (str.sizeStr > sizeStr) {
		return -1;
	}
	//Ѱ���Ӵ�,�޸ĵ�һ��������ƥ����
	char* memp = hstr;
	unsigned short end = sizeStr - str.sizeStr + 1;//������β
	unsigned short cmpSize = str.sizeStr - 1;
	for (unsigned short i = 0;i <= end;i++, memp++) {
		//�ҵ�ƥ����,ʹ��memcmpֱ�ӱ�������
		if (memcmp(memp, str.hstr, cmpSize) == 0) {
			return i;
		}
	}
	//δ��������ֱ�ӷ���
	return -1;
}

//������������������ڱ�׼�ַ������
std::ostream& operator<<(std::ostream& _cout, hstring& _str) {
	_cout << _str.hstr;
	return _cout;
}