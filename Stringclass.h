#ifndef _MYSTRING_H
#define _MYSTRING_H
#include<iostream>
#include <fstream>
using namespace std;
class MyString
{
private:
    char *string;
    unsigned int size_of_string;
public:
    MyString();
    MyString(const MyString& str);
    MyString(const char* s);
    void resize (unsigned int n);
    unsigned int capacity() const noexcept;
    unsigned int size() const noexcept;
    unsigned int length() const noexcept;
    const char* data() const noexcept;
    bool empty() const noexcept;
    const char& front() const;
    const char& at (unsigned int pos) const;
    void clear() noexcept;
    MyString& operator= (const MyString& str);
    MyString& operator+= (const MyString& str);
    unsigned long find (const MyString& str, unsigned int pos) const noexcept;
    unsigned long find(const MyString& str) const noexcept;
    ~MyString();
};
    ostream& operator<< (ostream& os, const MyString& str);
    bool operator==(const MyString& str,const MyString& str2);
    MyString operator+ (const MyString& str,const MyString& str2);
#endif