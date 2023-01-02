[#include "String.h"
#include <iostream>
using namespace std;


int String::getCharLength(const char* p)
{
	if (!p)
		return 0;
	int i = 0;
	while (p[i] != '\0')
	{
		i++;
	}
	return i;
}

String::String(const String& oldObject)
{
	size = oldObject.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = oldObject.data[i];
	}
}

String& String::operator = (const String& ref)
{
	if (this == &ref)
		return *this;
	this->~String();
	if (!ref.data)
		return *this;
	size = ref.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = ref.data[i];
	}
	return *this;
}

void String::strCopy(char* dest, const char* src)
{
	if (dest == nullptr)
		return;
	if (src == nullptr)
	{
		dest[0] = '\0';
		return;
	}
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

String::String()
{
	data = nullptr;
	size = 0;
}
String::String(const char c) :String()
{
	if (c == '\0')
		return;
	size = 2;
	data = new char[2]{ c,'\0' };
}
String::String(const char* s) : String()
{
	if (s == nullptr || *s == '\0')
		return;
	size = getCharLength(s) + 1;
	data = new char[size];
	strCopy(data, s);
}

String::String(String&& ref)
{
	this->~String();
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
}

String& String::operator = (String&& ref)
{
	this->~String();
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
	return *this;
}

String::~String()
{
	if (data)
		delete[] data;
	data = nullptr;
	size = 0;
}

bool String::isEmpty() const
{
	if (data == nullptr || data[0] == '\0')
		return true;
	return false;
}

int String::getSize() const
{
	return size;
}

char& String::operator [] (const int index)
{
	if (index >= 0 && index < size)
		return data[index];
	exit(0);
}

const char& String::operator [] (const int index) const
{
	if (index >= 0 && index < size)
		return data[index];
	exit(0);
}

bool String::operator !() const
{
	if (data == nullptr || data[0] == '\0')
		return true;
	return false;
}

int String::getLength() const
{
	if (data == nullptr || data[0] == '\0')
		return 0;
	int length = 0;
	while (data[length] != '\0')
	{
		length++;
	}
	return length;
}

void String::reSize(int ns)
{
	if (ns <= 0)
	{
		this->~String();
		return;
	}
	char* temp = new char[ns];
	int i = 0;
	while (i < ns && i < size)
	{
		temp[i] = data[i];
		i++;
	}
	this->~String();
	size = ns;
	data = temp;
}

bool String::isFound(const String src, int index) const
{
	for (int i = 0; i < src.getLength(); i++)
	{
		if (data[index] == src.data[i])
		{
			index++;
		}
		else
		{
			return false;
		}
	}
	return true;
}

int String::find(const String subStr, const int start) const
{
	int count = 0;
	int tempStart = start;
	int i = 0;
	while (start < getLength())
	{
		if (isFound(subStr, tempStart))
		{
			count++;
		}
		tempStart++;
	}
	return count;
}


void String::insert(int index, String subStr)
{
	int sizeOfSubStr = subStr.getLength();
	int i = 0;
	while (i < sizeOfSubStr)
	{
		if ((index + 1) == size)
		{
			reSize(size * 2);
		}
		data[index] = subStr.data[i];
		index++;
		i++;
	}
	data[index] = '\0';
}

void String::remove(const int index, const int count = 1)
{
	int tempIndex = index;
	int index2 = index + count;
	for (int i = 0; data[i] != '\0'; i++)
	{
		data[tempIndex] = data[index2];
		tempIndex++;
		index2++;
	}
}

int String::replace(const String old, const String newSubStr)
{
	int i = 0, count = 0;
	while (data[i] != '\0')
	{
		if (isFound(old, i))
		{
			insert(i, newSubStr);
			count++;
		}
		i++;
	}
	return count;
}

void String::trimLeft()
{
	int i = 0;
	while (data[i] == '\t' || data[i] == ' ')
	{
		i++;
	}
	remove(0, i);
}

void String::trimRight()
{
	int len = getLength();
	while (data[len - 1] == '\t' || data[len - 1] == ' ')
	{
		len--;
	}
	data[len] = '\0';
}

void String::trim()
{
	trimLeft();
	trimRight();
}

void String::makeUpper()
{
	for (int i = 0; i < size && data[i] != '\0'; i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z') //65-A and 98-a
		{
			data[i] = data[i] - 32;
		}
	}
}

void String::makeLower()
{
	for (int i = 0; i < size && data[i] != '\0'; i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z') //65-A and 98-a
		{
			data[i] = data[i] + 32;
		}
	}
}

void String::shrink()
{
	int newSize = getLength();
	char* temp = new char[newSize];
	for (int i = 0; i < newSize && data[i] != '\0'; i++)
	{
		temp[i] = data[i];
	}
	this->~String();
	size = newSize;
	data = temp;
}

int String::compare(const String s2) const
{
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] == s2.data[i])
		{
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

String String::left(const int count)
{
	char* substr = new char[count + 1];
	int i = 0;
	while (i < count)
	{
		substr[i] = data[i];
		i++;
	}
	substr[i] = '\0';
	String result(substr);
	return result;
}

String String::right(const int count)
{
	char* substr = new char[count + 1];
	int i = 0;
	int length = getLength();
	cout << length << endl;
	while (i < count)
	{
		substr[i] = data[length - count];
		i++;
		length++;
	}
	substr[i] = '\0';
	String result(substr);
	return result;
}

long long int String::convertToInteger() const
{
	long long int result = 0;
	int i = 0;
	while (i < getLength() && data[i] != '\0')
	{
		if (data[i] >= '0' && data[i] <= '9')
		{
			result = (result * 10) + data[i] - '0';
			i++;
		}
		else
		{
			break; //TBD
		}
	}
	return result;
}

float String::convertToFloat() const
{
	if (data == nullptr || data[0] == '\0')
		return 0;
	float result = 0.0;
	int i = 0;
	float divisor = 10;
	while (data[i] != '\0')
	{
		if (data[i] >= '0' && data[i] <= '9')
		{
			result = (result * 10) + data[i] - '0';
		}
		if (data[i] == '.')
		{
			i++;
			while (data[i] != '\0')
			{
				result = result + ((1.0 / divisor) * (data[i] - '0'));
				divisor = divisor * 10;
				i++;
			}
		}
		i++;
	}
	return result;
}


String String::operator + (const String& s2) const
{

	char* concatString = new char[(getLength() + s2.getLength() + 1) * 2];
	int i = 0;
	while (data[i] != '\0')
	{
		concatString[i] = data[i];
		i++;
	}
	for (int j = 0; s2.data[j] != '\0'; j++)
	{
		concatString[i] = s2.data[j];
		i++;
	}
	concatString[i] = '\0';
	String result(concatString);
	return result;
}

void String::operator += (const String& s2)
{
	int j = getLength();
	for (int i = 0; s2.data[i] != '\0'; i++)
	{
		if (j == size)
		{
			reSize(size * 2);
		}
		data[j] = s2.data[i];
		j++;
	}
	if (j == size)
	{
		reSize(size * 2);
	}
	data[j] = '\0';
}

int String::myGetIntegerDigits(int source)
{
	int length = 1;
	while (source / 10 != 0)
	{
		source = source / 10;
		length++;
	}
	return length;
}

char* String::myConvertToString(int source)
{
	int size = myGetIntegerDigits(source);
	char* num = new char[size + 1];
	int hundred = 1;
	for (int i = 0; i < (size - 1); i++)
	{
		hundred = hundred * 10;
	}
	for (int j = 0; j < size; j++)
	{
		num[j] = (source / hundred) + '0';
		source = source % hundred;
		hundred = hundred / 10;
	}
	num[size] = '\0';
	return num;
}

void String::setNumber(const long long int num)
{
	String s = myConvertToString(num);
	if (data)
	{
		this->reSize(24);
		int index = this->getLength();
		this->insert(index, s);
		return;
	}
	if (!data)
	{
		this->~String();
		this->reSize(4);
		this->insert(0, s);
		return;
	}
}

String& String::operator = (const long long int num)
{
	String s = myConvertToString(num);
	if (data)
	{
		this->reSize(24);
		int index = this->getLength();
		this->insert(index, s);
		return *this;
	}
	if (!data)
	{
		this->~String();
		this->reSize(4);
		this->insert(0, s);
		return *this;
	}
}

String& String::operator = (const double num)//123.321
{
	//this->~String();
	double temp = num;
	String s(myConvertToString(num));
	s.insert(myGetIntegerDigits(temp), '.');
	cout << s;
	cout << myGetIntegerDigits(temp);//3

	return *this;
}

String::operator long long int() const
{
	long long int result = 0;
	int i = 0;
	while (i < getLength() && data[i] != '\0')
	{
		if (data[i] >= '0' && data[i] <= '9')
		{
			result = (result * 10) + data[i] - '0';
			i++;
		}
		else
		{
			break; //TBD
		}
	}
	return result;
}

String::operator double() const
{
	if (data == nullptr || data[0] == '\0')
		return 0;
	float result = 0.0;
	int i = 0;
	float divisor = 10;
	while (data[i] != '\0')
	{
		if (data[i] >= '0' && data[i] <= '9')
		{
			result = (result * 10) + data[i] - '0';
		}
		if (data[i] == '.')
		{
			i++;
			while (data[i] != '\0')
			{
				result = result + ((1.0 / divisor) * (data[i] - '0'));
				divisor = divisor * 10;
				i++;
			}
		}
		i++;
	}
	return result;
}
String::operator bool() const
{
	//return !(!*this);
	return !operator!();
}

istream& operator >> (istream& temp, String& str)
{
	//str.input();
	if (str.data == nullptr || str.data[0] == '\0')
	{
		str.size = 1;
		str.data = new char[str.size];
	}
	char temp1;
	cin.get(temp1);
	int i = 0;
	while (temp1 != '\n')
	{
		str.data[i] = temp1;
		cin.get(temp1);
		if ((i + 1) == str.size)
		{
			str.reSize(str.size * 2);
		}
		i++;
	}
	str.data[i] = '\0';
	return temp;
}

ostream& operator << (ostream& temp, const String& str)
{
	if (str.data)
		cout << str.data;
	return temp;
}