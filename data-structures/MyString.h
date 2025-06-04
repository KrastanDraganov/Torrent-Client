#pragma once

#include <iostream>

class MyString
{
public:
    MyString();
    MyString(const char *data);
    explicit MyString(size_t stringLength);

    MyString(const MyString &other);
    MyString(MyString &&other) noexcept;

    MyString &operator=(const MyString &other);
    MyString &operator=(MyString &&other) noexcept;
    ~MyString();

    size_t getCapacity() const;
    size_t getSize() const;

    const char *c_str() const;

    MyString &operator+=(const MyString &other);
    MyString &operator+=(char character);

    char &operator[](size_t index);
    const char &operator[](size_t index) const;

    friend std::ostream &operator<<(std::ostream &os, const MyString &obj);
    friend std::istream &operator>>(std::istream &is, MyString &ref);
    friend MyString operator+(const MyString &lhs, const MyString &rhs);

    MyString substr(size_t begin, size_t howMany) const;

private:
    void copyFrom(const MyString &other);
    void moveFrom(MyString &&other);

    void resize(unsigned newAllocatedDataSize);

    void free();

    char *data;
    size_t size;
    size_t allocatedDataSize;
};

bool operator==(const MyString &lhs, const MyString &rhs);
bool operator!=(const MyString &lhs, const MyString &rhs);
bool operator<(const MyString &lhs, const MyString &rhs);
bool operator<=(const MyString &lhs, const MyString &rhs);
bool operator>(const MyString &lhs, const MyString &rhs);
bool operator>=(const MyString &lhs, const MyString &rhs);