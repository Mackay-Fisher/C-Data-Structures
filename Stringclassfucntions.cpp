#include<iostream>
#include <fstream>
#include "Stringclass.h"
using namespace std;
MyString::MyString(): string(nullptr),size_of_string(0)
{
	size_of_string=0;
	string = new char[1];
	string[0]='\0';
}

MyString::MyString(const MyString& str): string(nullptr),size_of_string(0){
	int i=0;
	size_of_string=0;
	while (str.string[i]!='\0')
	{
		size_of_string++;
		i++;
	}
	string = new char[size_of_string+1];
	for ( unsigned int i = 0; i < size_of_string; i++)
	{
		string[i]=str.string[i];
	}
}

MyString::MyString(const char* s): string(nullptr),size_of_string(0){
	int i=0;
	size_of_string=0;
	while (s[i]!='\0')
	{
		size_of_string++;
		i++;
	}
	string = new char[size_of_string+1];
	for (unsigned int j = 0; j < size_of_string; j++)
	{
		string[j]=s[j];
	}
}

void MyString::resize (unsigned int n){
string = new char[size_of_string+n+1];
	for (unsigned int j = size_of_string; j < size_of_string+n; j++)
	{
		string[j]= string[j]+' ';
	}
}

unsigned int MyString::capacity() const noexcept{
return size_of_string;
}

unsigned int MyString::size() const noexcept{	
return size_of_string;
}

unsigned int MyString::length() const noexcept{
return size_of_string;
}

const char* MyString::data() const noexcept{
return string;
}

bool MyString::empty() const noexcept{
	if (string[0]=='\0')
	{
		return 1;
	}
	return 0;
}

const char& MyString::front() const{
return string[0];
}

const char& MyString::at(unsigned int pos) const{
if (pos>=size_of_string)
{
	throw invalid_argument("Out of range");
}
else{
return string[pos];
}
}

void MyString::clear() noexcept{
char *temp = new char[1];
temp[0]='\0';
delete []string;
size_of_string=0;
string=temp;
}

MyString& MyString::operator= (const MyString& str){
	if (this == &str){
		return *this;
	}else{
	char *temp = new char[str.size()+1];
	for (unsigned int i = 0; i < str.size(); i++)
	{
		temp[i]=str.string[i];
	}
	temp[str.size()]='\0';
	delete [] string;
	string = temp;
	size_of_string=str.size();
	}
	return *this;
}

MyString& MyString::operator+=(const MyString& str){
	unsigned int temp_size=size_of_string+str.size();
	char *temp = new char[temp_size+1];
	for (unsigned int i = 0; i < size_of_string; i++)
	{
		temp[i]=string[i];
	}
	for (unsigned int i = 0; i < str.size(); i++)
	{
		temp[i+size_of_string]=str.at(i);
	}
	delete []string;
	temp[temp_size]='\0';
	string=temp;
	size_of_string=temp_size;
	return *this;
}

unsigned long MyString::find (const MyString& str, unsigned int pos) const noexcept{
unsigned int i, j;
if(size_of_string<str.size()){
	return -1;
}
for(i=pos; i<size_of_string; i++)
{
	if(string[i]==str.string[0])
	{
		for(j=1; j<str.size(); j++){
			if (string[i+j]!=str.string[j])
			{
				break;
			}
			if(j==str.size()-1){
				return i;
			}
		}
	}
}
return -1;
}

unsigned long MyString::find(const MyString& str) const noexcept{
unsigned int i, j;
if(size_of_string<str.size()){
	return -1;
}
for(i=0; i<size_of_string; i++)
{
	if(string[i]==str.string[0])
	{
		if (str.size()==1)
		{
			return i;
		}
		for(j=1; j<str.size(); j++){
			if (string[i+j]!=str.string[j])
			{
				break;
			}
			if(j==str.size()-1){
				return i;
			}
		}
	}
}
return -1;
}

MyString::~MyString()
{
delete []string;
size_of_string=0;
string=nullptr;
}

ostream& operator<< (ostream& os, const MyString& str){
    os<<str.data();
    return os;
}
bool operator==(const MyString& str,const MyString& str2){
	if(str.size()!=str2.size()){
		return false;
	}
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str.at(i)!=str2.at(i))
		{
			return false;
		}
	}
	return true;
}

MyString operator+ (const MyString& str,const MyString& str2){
	unsigned int temp_size=str2.size()+str.size();
	char *temp = new char[temp_size+1];
	for (unsigned int i = 0; i < str.size(); i++)
	{
		temp[i]=str.at(i);
	}
	for (unsigned int i = 0; i < str2.size(); i++)
	{
		temp[i+str.size()]=str2.at(i);
	}
	temp[temp_size]='\0';
	MyString add_string(temp);
	return add_string;
}

MyString operator+ (const MyString& str,const MyString& str2);