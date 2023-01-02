#ifndef STRING_H
#define STRING_H
#include <iostream>
using namespace std;

class String
{
	friend istream& operator >> (istream&, String&);
	friend ostream& operator << (ostream&, const String&);

	char* data;	//data member 
	int size;	//data member
	int getCharLength(const char* p);	 //Member function
	bool isFound(const String src, int index) const;//Member Function
	char* myConvertToString(int source);//OLD FUNCTIONS
	int myGetIntegerDigits(int source);//OLD FUNCTIONS
public:
	void strCopy(char* dest, const char* src);
	String();
	String(const char c);
	String(const char* s);
	String(const String&); //Copy Constructor
	String& operator = (const String& ref);	//Copy Assignment
	String(String&&);//Move ctor
	String& operator = (String&&);//Move Assignment
	~String();

	//Other Functions
	int getSize() const;
	bool isEmpty() const;
	char& operator [] (const int index); //char& at(const int index); 
	const char& operator [] (const int index) const; //New Function
	bool operator !() const;
	int getLength() const;
	void reSize(int ns);
	int find(const String subStr, const int start = 0) const;
	void insert(int index, String subStr);
	void remove(const int index, const int count);
	int replace(const String old, const String newSubStr);
	void trimLeft();
	void trimRight();
	void trim();
	void makeUpper();
	void makeLower();
	void shrink();
	int compare(const String s2) const;

	//New Functions! 
	String left(const int count);
	String right(const int count);
	long long int convertToInteger() const;
	float convertToFloat() const;
	String operator + (const String& s2) const; //	String concatenate(const String& s2) const;
	void operator += (const String& s2); //	void concatEqual(const String& s2);

	void setNumber(const long long int num);
	String& operator = (const long long int num); //New Functionality
	String& operator = (const double num);

	explicit operator long long int() const;
	explicit operator double() const;
	explicit operator bool() const;
};


#endif


