#include<iostream>
#include "hstring.h"
using namespace std;
int main() {

	hstring test1("123456789");
	test1 + "abc";
	cout << "test1: "<< test1 << endl;

	hstring test2("123456789");
	test2 - "456";
	cout << "test2: " << test2 << endl;

	hstring test3("123456789");
	test3.mod("34", "abc");
	cout << "test3: " << test3 << endl;


	hstring test4 ("123456");
	cout << "test4: " << test4.find("34") << endl;

	hstring test5 = 666;
	cout << "test5: " << test5 << endl;
	return 0;

}